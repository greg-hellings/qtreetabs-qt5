#include "qtreetabs.h"

#include "opentab.h"
#include "js/localscript.h"

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineScriptCollection>
#include <QWebChannel>
#include <QStackedWidget>
#include <QSplitter>
#include <QMap>
#include <QLayout>
#include <QUrl>
#include <iostream>

QTreeTabs::QTreeTabs(QWidget *parent) :
    QWidget(parent),
    m_profile(new QWebEngineProfile("tabs", this)),
    m_currentTab(NULL),
    m_map(new QMap<QString, OpenTab*>())
{
    // Setup the basic layout
    QSplitter* splitter = new QSplitter(Qt::Orientation::Horizontal, this);
    this->m_tabs = new QWebEngineView(splitter);
    this->m_tabs->setMinimumWidth(80);
    this->m_widgets = new QStackedWidget(splitter);
    this->m_widgets->setMinimumWidth(300);

    // Create and configure the QWebChannel for communication between the
    // JavaScript in the tabs view and ourselves
    this->m_channel = new QWebChannel(this);
    this->m_channel->registerObject("god", this);

    // Create the WebEngine instance that will do the Lord's work
    QWebEnginePage* page = new QWebEnginePage(this->m_profile, this->m_tabs);
    this->m_tabs->setPage(page);
    Q_INIT_RESOURCE(web);
    this->m_tabs->setUrl(QUrl("qrc:///tabs.html"));
    page->setWebChannel(this->m_channel);

    qRegisterMetaType<OpenTab*>();
}

QTreeTabs::~QTreeTabs()
{
    // Nothing here?
}

OpenTab* QTreeTabs::addItem(QWidget *widget, bool childOfActive, bool displayNow)
{
    // Create new tab
    OpenTab* tab = new OpenTab(widget);

    // Currently, this doesn't work - items registered after the first client connects are
    // not able to be registered into the namespace. When that feature is lifted, this next
    // line will become relevant once again
//    this->m_channel->registerObject(tab->uuid(), tab);
    tab->connect(tab, &OpenTab::onTextChanged, this, static_cast<void (QTreeTabs::*)(OpenTab*, const QString&)> (&QTreeTabs::onTextChanged));
    tab->connect(tab, &OpenTab::onIconUrlChanged, this, static_cast<void (QTreeTabs::*)(OpenTab*, const QString&)> (&QTreeTabs::onIconUrlChanged));

    this->m_map->insert(tab->uuid(), tab);
    this->m_widgets->addWidget(widget);
    // Notify listeners of new tab creation
    emit onTabCreated(tab->uuid());
    if (displayNow) {
        this->m_widgets->setCurrentWidget(widget);
        OpenTab* previous = this->m_currentTab;
        this->m_currentTab = tab;
        emit onTabChanged(previous, tab);

    }

    return tab;
}

OpenTab* QTreeTabs::tabFromUuid(const QString &uuid)
{
    return this->m_map->value(uuid, NULL);
}

void QTreeTabs::tabRequested()
{
    emit onTabRequested();
}

void QTreeTabs::setCurrentTab(const QString &uuid)
{
    this->setCurrentTab(this->tabFromUuid(uuid));
}

void QTreeTabs::setCurrentTab(OpenTab *tab)
{
    if (tab != NULL) {
        if (this->m_widgets->indexOf(tab->widget()) != -1) {
            this->m_widgets->setCurrentWidget(tab->widget());
            OpenTab* previous = this->m_currentTab;
            this->m_currentTab = tab;
            emit onTabChanged(previous, tab);
        }
    }
}

OpenTab* QTreeTabs::currentTab() const {
    return this->m_currentTab;
}

void QTreeTabs::onTextChanged(OpenTab *tab, const QString &text)
{
    emit onTextChanged(tab->uuid(), text);
}

void QTreeTabs::onIconUrlChanged(OpenTab *tab, const QString &url)
{
    emit onIconUrlChanged(tab->uuid(), url);
}
