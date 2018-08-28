# Setting options
isEmpty(PREFIX) {
	PREFIX = /usr/local
}
message("Setting install prefix to $$PREFIX")
isEmpty(LIBDIR) {
	contains(QT_ARCH, x86_64){
		LIBDIR = "$$PREFIX/lib64"
	} else {
		LIBDIR = "$$PREFIX/lib"
	}
}
message("Installing libraries to $$LIBDIR")
isEmpty(INCLUDEDIR) {
	INCLUDEDIR = "$$PREFIX/include/qtreetabs"
}
message("Installing headers to $$INCLUDEDIR")

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
