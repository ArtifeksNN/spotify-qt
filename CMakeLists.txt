cmake_minimum_required(VERSION 3.5)

project(spotify-qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional D-Bus support
if (NOT DEFINED USE_DBUS)
	set(USE_DBUS 1)
endif ()

# Find Qt
find_package(Qt5 COMPONENTS Core Widgets Network Gui Svg REQUIRED)
if (USE_DBUS)
	find_package(Qt5 OPTIONAL_COMPONENTS DBus QUIET)
endif ()

# Glob source files
file(GLOB MAIN_SRC "src/*.[hc]pp")
file(GLOB SUB_SRC "src/*/*.[hc]pp")

if (USE_QT_QUICK)
	set(QML_RES qml/res.qrc)
endif ()

# Add all source files to main executable
if (ANDROID)
	add_library(spotify-qt SHARED ${MAIN_SRC} ${SUB_SRC} ${QML_RES} res.qrc)
else ()
	add_executable(spotify-qt ${MAIN_SRC} ${SUB_SRC} ${QML_RES} ${LIB_SRC} res.qrc)
endif ()

# Get version from Git
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE GIT_COMMIT
			OUTPUT_STRIP_TRAILING_WHITESPACE)
	target_compile_definitions(spotify-qt PRIVATE GIT_COMMIT="${GIT_COMMIT}")
endif ()

# Set install targets for 'make install'
install(TARGETS spotify-qt RUNTIME DESTINATION bin)
if (UNIX)
	# Install icons and desktop shortcut on unix-like
	install(FILES res/logo/spotify-qt.svg DESTINATION share/icons/hicolor/scalable/apps)
	install(FILES res/app/spotify-qt.desktop DESTINATION share/applications)
endif ()

# Don't show console window under windows
if (WIN32)
	target_link_options(spotify-qt PRIVATE -mwindows)
endif ()

# Link Qt
target_link_libraries(spotify-qt PRIVATE
		Qt5::Core
		Qt5::Widgets
		Qt5::Network
		Qt5::Gui
		Qt5::Svg)

# Check if we should include Qt Quick
if (USE_QT_QUICK)
	add_subdirectory(qml)
	target_compile_definitions(spotify-qt PRIVATE USE_QT_QUICK)
	target_link_libraries(spotify-qt PRIVATE spotify-qt-quick)
endif ()

# D-Bus support is optional
if (Qt5DBus_FOUND)
	target_compile_definitions(spotify-qt PRIVATE USE_DBUS)
	target_link_libraries(spotify-qt PRIVATE Qt5::DBus)
endif ()