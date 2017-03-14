#ifndef MAINTABS_H
#define MAINTABS_H

#include <QWidget>
#include <QList>
#include <QMap>

// Advanced declarations
class OpenTab;
class QWebEngineView;
class QStackedWidget;
class QWebEngineProfile;
class QWebChannel;

class QTreeTabs : public QWidget
{
    Q_OBJECT
public:
    explicit QTreeTabs(QWidget *parent = 0);
    ~QTreeTabs();

    OpenTab* addItem(QWidget* widget, bool childOfActive = false, bool displayNow = true);

    OpenTab* tabFromUuid(const QString& uuid) const;
//    void closeCurrentTab(bool suppressSignals = false);
//    OpenTab* closeTab(OpenTab* tab, bool suppressSignals = false);

    OpenTab* currentTab() const;
    void setCurrentTab(OpenTab* tab);
    QList<OpenTab*>* openTabs() const;
    OpenTab* findTabByWidget(QWidget* widget) const;
signals:
    void tabCreated(const QString& uuid);
    void tabRequested();
    // Signifies that the text from an underlying tab has changed. Should only be called
    // by the JavaScript code that's part of this widget. This signal is a hack around a
    // limitation of the QWebChannel code. If that code is ever updated, then this signal
    // will probably go away
    void textChanged(const QString& uuid, const QString& text);
    void iconUrlChanged(const QString& uuid, const QString& url);
    void tabChanged(OpenTab* oldTab,  OpenTab* newTab);
//    void closedTab(int topLevelTabsRemaining);

public slots:
    void onTabRequested();
    void onTextChanged(const QString& text);
    void onIconUrlChanged(const QString& url);
    void setCurrentTab(const QString& uuid);

private:
    QWebEngineView* m_tabs;
    QStackedWidget* m_widgets;
    QWebEngineProfile* m_profile;
    OpenTab* m_currentTab;
    QMap<QString, OpenTab*>* m_map;
    QWebChannel* m_channel;
};

#endif // MAINTABS_H
