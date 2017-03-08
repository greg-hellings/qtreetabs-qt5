#ifndef LOCALSCRIPT_H
#define LOCALSCRIPT_H

#include <QWebEngineScript>

class QString;

class LocalScript : public QWebEngineScript
{
public:
    LocalScript(const QString& name);
};

#endif // LOCALSCRIPT_H
