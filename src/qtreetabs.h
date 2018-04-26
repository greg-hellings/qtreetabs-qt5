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
    void textChanged(const QString& uuid, const QString& text);
    void iconUrlChanged(const QString& uuid, const QString& url);
    void tabChanged(OpenTab* oldTab,  OpenTab* newTab);
    void closedTab(const QString& uuid, int topLevelTabsRemaining);

public slots:
	// Specifically to hear from the JavaScript
    void jsRequestTab();
    void jsRequestClose(const QString& uuid);
	// Specifically to send from the tab to the JavaScript
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
