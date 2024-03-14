cmake_minimum_required(VERSION 3.5)

project(assignment-list VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(USE_QT5 "Use Qt5, instead of Qt6" no)
option(USE_QT6 "Use Qt6, instead of Qt5" no)

set(qt_components "Core" "Gui" "Sql" "UiTools" "Widgets")
set(qt_names "Qt6" "Qt5")
if(USE_QT5)
	set(qt_names "Qt5")
	# Requires Qt version >= 5.4
elseif(USE_QT6)
	set(qt_names "Qt6")
endif()

find_package(QT NAMES ${qt_names} REQUIRED COMPONENTS ${qt_components})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${qt_components})

message("Using Qt${QT_VERSION_MAJOR}")

set(qt_libraries "")
foreach(X ${qt_components})
	list(APPEND qt_libraries "Qt${QT_VERSION_MAJOR}::${X}")
endforeach()

set(project_sources
	"src/addEntryForm.cpp"
	"src/addEntryForm.h"
	"src/addGroupForm.cpp"
	"src/addGroupForm.h"
	"src/backend/db_sqlite.cpp"
	"src/backend/db_sqlite.h"
	"src/assignmentList.cpp"
	"src/assignmentList.h"
	"src/assignmentList.ui"
	"src/editGroupForm.cpp"
	"src/editGroupForm.h"
	"src/editEntryForm.cpp"
	"src/editEntryForm.h"
	"src/entry.cpp"
	"src/entry.h"
	"src/entryLayout.cpp"
	"src/entryLayout.h"
	"src/entryForm.ui"
	"src/group.cpp"
	"src/group.h"
	"src/groupLayout.cpp"
	"src/groupLayout.h"
	"src/groupForm.ui"
	"src/lib.cpp"
	"src/lib.h"
	"src/main.cpp"
	"src/preferencesDialog.cpp"
	"src/preferencesDialog.h"
	"src/preferencesDialog.ui"
	"src/rule.cpp"
	"src/rule.h"
	"src/ruleLayout.cpp"
	"src/ruleLayout.h"
	"src/rulesDialog.cpp"
	"src/rulesDialog.h"
	"src/rulesDialog.ui"
)

add_executable(assignment-list
	${project_sources}
)

target_link_libraries(assignment-list ${qt_libraries})
