CONFIG += qt
QT += widgets webenginewidgets

INCLUDEPATH += $$PWD/src $$PWD/src/js $$PWD/src/web
DEPENDPATH += $$PWD/src

win32 {
	CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/
	CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/
}

unix {
	LIBS += -L$$OUT_PWD/../src/
}
