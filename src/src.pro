include(../qtreetabs.pri)

TEMPLATE = lib
TARGET = qtreetabs
PUBLIC_HEADERS = qtreetabs.h \
                 opentab.h
PRIVATE_HEADERS = js/localscript.h
HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS
SOURCES = opentab.cpp \
          qtreetabs.cpp \
          js/localscript.cpp
RESOURCES = web/web.qrc \
            js/resources.qrc
FORMS = qtreetabs.ui

target.path = $$LIBDIR
headers.path = $$INCLUDEDIR
headers.files = $$PUBLIC_HEADERS
INSTALLS += target headers
