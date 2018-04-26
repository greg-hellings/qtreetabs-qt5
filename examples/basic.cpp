#include "qtreetabs.h"
#include "opentab.h"

#include <QApplication>
#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>

#include <iostream>

QTreeTabs* tabs;

class Test : public QObject {
public slots:
    void whenTabRequested() {
        QLineEdit* line = new QLineEdit();
        OpenTab* tab = tabs->addItem(line, true, true);
        tab->connect(line, &QLineEdit::textChanged, tab, &OpenTab::setText);
        tab->connect(line, &QLineEdit::textChanged, tab, &OpenTab::setIconUrl);
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QMainWindow window;
    tabs = new QTreeTabs(&window);
    window.setMinimumHeight(400);
    window.setMinimumWidth(600);
    window.setCentralWidget(tabs);
    window.show();
    window.activateWindow();

    Test* test = new Test();
    test->connect(tabs, &QTreeTabs::tabRequested, test, &Test::whenTabRequested);

    return app.exec();
}
