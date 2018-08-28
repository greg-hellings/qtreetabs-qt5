include(../qtreetabs.pri)

# Build an appropriately named lib, both dynamic and static
TEMPLATE = lib
TARGET = qtreetabs
POST_TARGETDEPS = staticlib

# Define the sources
SOURCES = opentab.cpp \
          qtreetabs.cpp \
          js/localscript.cpp
FORMS = qtreetabs.ui
RESOURCES = web/web.qrc \
            js/resources.qrc

# Define the headers that are used to build
PUBLIC_HEADERS = qtreetabs.h \
                 opentab.h
PRIVATE_HEADERS = js/localscript.h
HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

# Define the installation behaviors
target.path = $$LIBDIR
headers.path = $$INCLUDEDIR
headers.files = $$PUBLIC_HEADERS
INSTALLS += target headers
