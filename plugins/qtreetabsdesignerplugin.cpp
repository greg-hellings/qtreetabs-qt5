#include "qtreetabsdesignerplugin.h"
#include "qtreetabs.h"

QTreeTabsDesignerPlugin::QTreeTabsDesignerPlugin(QObject* parent)
    : QObject(parent)
{
}

void QTreeTabsDesignerPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if(this->initialized)
	return;
    this->initialized = true;
}

bool QTreeTabsDesignerPlugin::isInitialized() const
{
    return this->initialized;
}

QWidget* QTreeTabsDesignerPlugin::createWidget(QWidget *parent)
{
    QTreeTabs* tabs = new QTreeTabs(parent);
    // Maybe do some stuff, here?
    return tabs;
}

QString QTreeTabsDesignerPlugin::name() const
{
	return QStringLiteral("QTreeTabs");
}

QString QTreeTabsDesignerPlugin::group() const
{
    return QStringLiteral("Containers");
}

QIcon QTreeTabsDesignerPlugin::icon() const
{
    return QIcon();
}

QString QTreeTabsDesignerPlugin::toolTip() const
{
    return QStringLiteral("Horizontal tabs with optional tree-like sturcture");
}

QString QTreeTabsDesignerPlugin::whatsThis() const
{
    return QStringLiteral("A tabbed widget to contain multiple other widgets. Tabs are aligned vertically "
                          "down the size of the space, instead of across the top. Tabs can optionally be "
                          "given a tree structure in their display.");
}

bool QTreeTabsDesignerPlugin::isContainer() const
{
    return true;
}

QString QTreeTabsDesignerPlugin::includeFile() const
{
    return QStringLiteral("qtreetabs.h");
}

QString QTreeTabsDesignerPlugin::domXml() const
{
    return  "<ui language=\"c++\">\n"
            "  <widget class=\"QTreeTabs\" name=\"treeTabs\">\n"
            "    <property name=\"geometry\">\n"
            "      <rect>\n"
            "        <x>0</x>\n"
            "        <y>0</y>\n"
            "      </rect>\n"
            "    </property>\n"
            "  </widget>\n"
            "</ui>";
}
