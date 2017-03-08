#include "localscript.h"

#include <QString>
#include <QFile>
#include <QFileInfo>

LocalScript::LocalScript(const QString& name)
{
    // Make sure the files are all loaded
    Q_INIT_RESOURCE(resources);
    QFileInfo info(name);
    QFile tabs_js(name);
    tabs_js.open(QIODevice::ReadOnly);
    setName(info.fileName());
    setSourceCode(tabs_js.readAll());
    tabs_js.close();
}
