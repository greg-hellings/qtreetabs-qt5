#include "qtreetabs.h"
#include "ui_qtreetabs.h"

#include "opentab.h"

#include <QItemSelectionModel>
#include <QSizePolicy>

QTreeTabs::QTreeTabs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideTabs()),
    openTab(NULL)
{
    this->ui->setupUi(this);

    this->connect(this->ui->tabs, SIGNAL(itemSelectionChanged()), SLOT(tabChanged()));

    this->ui->tabs->setFocusPolicy(Qt::NoFocus);
    this->ui->tabs->setSelectionMode(QAbstractItemView::SingleSelection);
}

QTreeTabs::~QTreeTabs()
{
    delete ui;
}

OpenTab* QTreeTabs::getNewOpenTab(QWidget* content, QTreeWidgetItem *parent)
{
    return new OpenTab(parent, QString(""), content);
}

OpenTab* QTreeTabs::getNewOpenTab(QWidget *content, QTreeWidget *parent)
{
    return new OpenTab(parent, QString(""), content);
}

OpenTab* QTreeTabs::newTab(QWidget *widget, bool childOfActive, bool displayNow)
{
    OpenTab* tab = 0;
    if (childOfActive) {
        tab = this->getNewOpenTab(widget, this->currentTab());
        this->currentTab()->setExpanded(true);
    } else
        tab = this->getNewOpenTab(widget, this->ui->tabs);
    this->configureNewTab(tab);
    if (displayNow || this->openTab == NULL)
        this->setCurrentTab(tab);

    return tab;
}

OpenTab* QTreeTabs::newTab(QWidget *widget, QWidget *parent, bool displayNow)
{
    OpenTab* tab = this->getNewOpenTab(widget, this->findTabByWidget(parent));
    this->configureNewTab(tab);
    if (displayNow || this->openTab == NULL)
        this->setCurrentTab(tab);

    return tab;
}

void QTreeTabs::closeCurrentTab(bool suppressSignals)
{
    OpenTab* oldTab = this->openTab;
    OpenTab* newCurrent = this->closeTab(this->openTab, suppressSignals);
    // And of course we must be sure to always have some sort of tab
    if (newCurrent != NULL) {
        this->openTab = dynamic_cast<OpenTab*>(newCurrent);
        this->ui->tabs->clearSelection();
        this->openTab->setSelected(true);
        this->openTab->setExpanded(true);
    }
    if (!suppressSignals) {
        emit tabChanged(oldTab, newCurrent);
    }
}

OpenTab* QTreeTabs::closeTab(OpenTab* tab, bool suppressSignals)
{
    // Remove the widget from the stack
    this->ui->widgets->removeWidget(tab->widget());
    // Promote first child to parent if one exists
    QTreeWidgetItem* newCurrent = tab->removeSelf();
    if (!suppressSignals) {
        emit closedTab(this->ui->tabs->invisibleRootItem()->childCount());
    }
    return dynamic_cast<OpenTab*>(newCurrent);
}

void QTreeTabs::configureNewTab(OpenTab* newTab)
{
    this->ui->widgets->addWidget(newTab->widget());
}

OpenTab* QTreeTabs::currentTab() const
{
    return this->openTab;
}

void QTreeTabs::setCurrentTab(OpenTab* newTab)
{
    OpenTab* oldTab = this->openTab;
    this->openTab = newTab;
    if (!newTab->isSelected())
        newTab->setSelected(true);
    if (oldTab != NULL && oldTab != newTab)
        oldTab->setSelected(false);
    this->ui->widgets->setCurrentWidget(newTab->widget());
    emit tabChanged(oldTab, newTab);
}

void QTreeTabs::setCurrentWidget(QWidget *newCurrentWidget)
{
    OpenTab* newTab = this->findTabByWidget(newCurrentWidget);
    if (newTab != NULL) {
        this->setCurrentTab(newTab);
    }
}

void QTreeTabs::tabChanged()
{
    QList<QTreeWidgetItem*> tabs = this->ui->tabs->selectedItems();
    // I don't yet know how to grok multiple tab selection and we'll deal with a default
    // selection at a later time, if deselection is possible
    if (tabs.count() == 1) {
        OpenTab* tab = dynamic_cast<OpenTab*>(tabs.at(0));
        this->setCurrentTab(tab);
        tab->widget()->setFocus();
    }
}

OpenTab* QTreeTabs::findTabByWidget(QWidget *view)
{
    QTreeWidgetItem* item = this->ui->tabs->invisibleRootItem();
    return this->findTabByWidgetRecursion(item, view);
}

OpenTab* QTreeTabs::findTabByWidgetRecursion(QTreeWidgetItem* item, QWidget* view)
{
    bool found = false;
    for (int i = 0; i < item->childCount() && !found; ++i) {
        OpenTab* tab = dynamic_cast<OpenTab*>(item->child(i));
        if (tab->widget() == view) {
            return tab;
        }
        tab = this->findTabByWidgetRecursion(tab, view);
        if (tab != NULL) {
            return tab;
        }
    }

    return NULL;
}

QList<OpenTab*>* QTreeTabs::openTabs()
{
    QList<OpenTab*>* openTabs = new QList<OpenTab*>();
    QTreeWidgetItem* root = this->ui->tabs->invisibleRootItem();
    for (int i = 0; i < root->childCount(); ++i) {
        openTabs->append(dynamic_cast<OpenTab*>(root->child(i)));
    }
    return openTabs;
}
