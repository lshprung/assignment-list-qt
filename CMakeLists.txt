cmake_minimum_required(VERSION 3.5)

project(assignment-list VERSION 0.0.1 LANGUAGES CXX)

set(ORGANIZATION_NAME "assignment-list-qt")
set(PROJECT_TITLE "Assignment List")

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
	"src/addGroupForm.cpp"
	"src/backend/db_sqlite.cpp"
	"src/assignmentList.cpp"
	"src/editGroupForm.cpp"
	"src/editEntryForm.cpp"
	"src/entry.cpp"
	"src/entryLayout.cpp"
	"src/group.cpp"
	"src/groupLayout.cpp"
	"src/lib.cpp"
	"src/main.cpp"
	"src/preferencesDialog.cpp"
	"src/rule.cpp"
	"src/ruleLayout.cpp"
	"src/rulesDialog.cpp"
)

set(project_headers
	"src/addEntryForm.h"
	"src/addGroupForm.h"
	"src/backend/db_sqlite.h"
	"src/assignmentList.h"
	"src/editGroupForm.h"
	"src/editEntryForm.h"
	"src/entry.h"
	"src/entryLayout.h"
	"src/group.h"
	"src/groupLayout.h"
	"src/lib.h"
	"src/preferencesDialog.h"
	"src/rule.h"
	"src/ruleLayout.h"
	"src/rulesDialog.h"
)

set(project_uis
	"src/assignmentList.ui"
	"src/entryForm.ui"
	"src/groupForm.ui"
	"src/preferencesDialog.ui"
	"src/rulesDialog.ui"
)

set(project_misc
	"resources.qrc"
	"src/icon/assignment-list.rc"
)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

add_executable(assignment-list
	${project_sources}
	${project_headers}
	${project_uis}
	${project_misc}
)

# Avoid opening console on windows
set_target_properties(assignment-list PROPERTIES WIN32_EXECUTABLE ON)

target_link_libraries(assignment-list ${qt_libraries})

# Installation
install(TARGETS assignment-list)

# install desktop entry and icon
if(CMAKE_SYSTEM MATCHES "Linux.*")
	configure_file(data/assignment-list.desktop.in ${CMAKE_CURRENT_SOURCE_DIR}/data/assignment-list.desktop @ONLY)
	install(FILES data/assignment-list.desktop DESTINATION share/applications)
	install(FILES data/assignment-list.svg DESTINATION share/pixmaps)
endif()

include(CPack)
