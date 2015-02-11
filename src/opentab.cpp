#include "opentab.h"

#include <QTreeWidgetItem>
#include <QTimer>

OpenTab::OpenTab(QTreeWidget* parent, const QString& text, QWidget* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWidget(view),
    up(parent->invisibleRootItem())
{
}

OpenTab::OpenTab(QTreeWidgetItem* parent, const QString& text, QWidget* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWidget(view),
    up(parent)
{
}

OpenTab* OpenTab::closestSibling(QTreeWidgetItem* parent)
{
    OpenTab* target = 0;
    if (parent->childCount() > 1) {
        int myIndex = parent->indexOfChild(this);
        // If this is not the oldest child, then choose the next oldest (above) child
        if (myIndex > 0) {
            target = dynamic_cast<OpenTab*>(parent->child(myIndex - 1));
        } else {
            // Otherwise, choose the second oldest child
            target = dynamic_cast<OpenTab*>(parent->child(1));
        }
    }

    return target;
}

OpenTab* OpenTab::removeSelf()
{
    OpenTab* closestRelative = 0;
    // If this tab has children, the eldest child is the closest relative
    if (this->childCount() > 0) {
        closestRelative = dynamic_cast<OpenTab*>(this->takeChild(0));
        // And promote that child to this one's status
        closestRelative->addChildren(this->takeChildren());
        closestRelative->setExpanded(true);
        // And promote this to the parent
        this->up->insertChild(this->up->indexOfChild(this), closestRelative);
        closestRelative->up = this->up;
    } else {
        closestRelative = closestSibling(this->up);
    }
    // Remove this one from its parent
    this->up->removeChild(this);

    return closestRelative;
}

QWidget* OpenTab::widget() const
{
    return this->myWidget;
}

void OpenTab::addChildren(const QList<QTreeWidgetItem *> &children)
{
    QTreeWidgetItem::addChildren(children);
    for (QList<QTreeWidgetItem*>::const_iterator it = children.begin(); it != children.end(); ++it) {
        (dynamic_cast<OpenTab*>(*it))->up = this;
    }
}
