#ifndef OPENTAB_H
#define OPENTAB_H

#include <QObject>
#include <QUuid>

class OpenTab : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY onTextChanged)
    Q_PROPERTY(QString iconUrl READ iconUrl WRITE setIconUrl NOTIFY onIconUrlChanged)
    Q_PROPERTY(QWidget* widget READ widget)
    Q_PROPERTY(QString uuid READ uuid)
public:
    OpenTab(QWidget* view, const QString& uuid = QUuid::createUuid().toString());
    OpenTab(const OpenTab&);
    OpenTab();

    QWidget* widget() const { return this->m_widget; }
    QString text() const { return this->m_text; }
    QString iconUrl() const { return this->m_iconUrl; }
    QString uuid() const { return this->m_uuid; }

signals:
    void onTextChanged(OpenTab* tab, const QString& text);
    void onIconUrlChanged(OpenTab* tab, const QString& url);

public slots:

    void setText(const QString& text) {
        this->m_text = text;
        emit onTextChanged(this, text);
    }
    void setIconUrl(const QString& url) {
        this->m_iconUrl = url;
        emit onIconUrlChanged(this, url);
    }

private:
    QWidget* m_widget;
    QString m_uuid;
    QString m_text;
    QString m_iconUrl;
};

Q_DECLARE_METATYPE(OpenTab);

#endif // OPENTAB_H
