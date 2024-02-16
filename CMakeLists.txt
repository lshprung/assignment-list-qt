cmake_minimum_required(VERSION 3.1.0)

project(assignment-list VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui UiTools Widgets REQUIRED)

add_executable(assignment-list
	"${CMAKE_CURRENT_SOURCE_DIR}/src/add_entry_form.ui"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/add_group_form.ui"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/assignmentList.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/assignmentList.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.ui"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/preferences_dialog.ui"
)

target_link_libraries(assignment-list Qt5::Core Qt5::Gui Qt5::UiTools Qt5::Widgets)
