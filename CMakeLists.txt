# Options
macro(_SET_FANCY _var _value _comment)
    if (NOT DEFINED ${_var})
        set(${_var} ${_value})
    else()
        set(${_var} "${${_var}}" CACHE STRING "${_comment}")
    endif()
endmacro(_SET_FANCY)
_set_fancy(CMAKE_INSTALL_DIR "/usr/local" "Default base directory to install")
_set_fancy(BIN_INSTALL_DIR "${CMAKE_INSTALL_DIR}/bin" "Directory to install architecture-dependent files")
_set_fancy(LIB_INSTALL_DIR "${CMAKE_INSTALL_DIR}/lib" "Directory to install object code libraries.")
_set_fancy(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_DIR}/include/qtreetabs-qt5" "Directory to install C/C++ header files.")

# Declare our project name
project(qtreetabs)
# Set minimum version - since I don't have younger versions to test
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) # moc files get put into the current directory, so include that

# Source directory for files
set(CXX_SRC
    src/qtreetabs.cpp
    src/opentab.cpp
    src/js/localscript.cpp)
set(QRC_SRC
    src/js/resources.qrc
    web/web.qrc)
set(HEADERS
    src/qtreetabs.h
    src/opentab.h
    src/localscript.h)
set(DIST_HEADERS
    src/qtreetabs.h
    src/opentab.h)
set(UI
    src/qtreetabs.ui)

# Versioning information
set(qtreetabs_version_major "0")
set(qtreetabs_version_minor "1")
set(qtreetabs_version_patch "0")
set(qtreetabs_version "${qtreetabs_version_major}.${qtreetabs_version_minor}.${qtreetabs_version_patch}")

# Find necessary libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)

# Configure build parameters
include_directories("${Qt5Widgets_INCLUDE_DIRS}")
include_directories("${Qt5WebEngineWidgets_INCLUDE_DIRS}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/")
add_definitions(${Qt5Core_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5WebEngineWidgets_EXECUTABLE_COMPILE_FLAGS} -fPIC")

# Prebuild
#qt5_wrap_cpp(MOCS ${HEADERS})
qt5_wrap_UI(UI_SRC ${UI})

# Add library
add_library(qtreetabs SHARED ${CXX_SRC} ${QRC_SRC} ${UI_SRC})
target_link_libraries(qtreetabs Qt5::WebEngineWidgets Qt5::Widgets)
# Installs
install(TARGETS qtreetabs
    RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
)
install(FILES ${DIST_HEADERS}
    DESTINATION "${INCLUDE_INSTALL_DIR}"
)

# Create subdirectory configs
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/examples")
