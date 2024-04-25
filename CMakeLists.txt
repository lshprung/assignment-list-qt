cmake_minimum_required(VERSION 3.12)

# Get the date for last git commit (or today if it can't)
if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/.git")
	find_package(Git)
	if(GIT_FOUND)
		execute_process(COMMAND ${GIT_EXECUTABLE} show --no-patch --format=%cd --date=format:'%Y%m%d'
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE patchdate
			OUTPUT_STRIP_TRAILING_WHITESPACE
			ERROR_QUIET)
		string(REGEX REPLACE "'" "" patchdate "${patchdate}")
	endif()
endif()
if(NOT DEFINED patchdate)
	string(TIMESTAMP patchdate "%Y%m%d" UTC)
endif()

project(assignment-list VERSION 0.0.${patchdate} HOMEPAGE_URL "https://github.com/lshprung/assignment-list-qt" LANGUAGES CXX)

set(ORGANIZATION_NAME "assignment-list-qt")
set(PROJECT_TITLE "Assignment List")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Options
option(USE_QT5 "Use Qt5, instead of Qt6" no)
option(USE_QT6 "Use Qt6, instead of Qt5" no)
option(IS_RELEASE "Set if this is a release candidate" no)

if(IS_RELEASE)
	unset(CMAKE_PROJECT_VERSION_PATCH)
	message("Marked as release: excluding patch in version number")
endif()

set(qt_components "Core" "Gui" "Sql" "UiTools" "Widgets")
set(qt_names "Qt6" "Qt5")
if(USE_QT5)
	set(qt_names "Qt5")
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
include(GNUInstallDirs)
install(TARGETS assignment-list)

# install desktop entry and icon
if(CMAKE_SYSTEM MATCHES "Linux.*")
	configure_file(data/assignment-list.desktop.in ${CMAKE_CURRENT_SOURCE_DIR}/data/assignment-list.desktop @ONLY)
	install(FILES data/assignment-list.desktop DESTINATION share/applications)
	install(FILES data/assignment-list.svg DESTINATION share/pixmaps)
endif()

# CPack configuration
set(CPACK_PACKAGE_DESCRIPTION "A QT application for managing grouped tasks")
if(IS_RELEASE)
	set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR})
else()
	set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}+${CMAKE_PROJECT_VERSION_PATCH})
endif()
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_PACKAGE_CONTACT "Louie Shprung <lshprung@tutanota.com>")
set(CPACK_SOURCE_IGNORE_FILES "/\.git.*;/\.cache;/build;/compile_commands\.json$;/config\.h$;/data/assignment-list\.desktop$")

# CPack NSIS configuration
set(CPACK_NSIS_DEFINES "RequestExecutionLevel user")
# Based on https://stackoverflow.com/q/69139412
if(CMAKE_SYSTEM MATCHES "Windows*")
	include(InstallRequiredSystemLibraries)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
	add_custom_command(TARGET assignment-list POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy/
		COMMAND ${WINDEPLOYQT_EXECUTABLE}
			--dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:assignment-list>
		)
	install(
		DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		FILES_MATCHING_PATTERN "*.*"
		)
endif()

# CPack Deb configuration
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
if(QT_VERSION_MAJOR VERSION_EQUAL 5)
	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.7), libqt5core5a (>= 5.4), libqt5gui5 (>= 5.4), libqt5sql5 (>= 5.4), libqt5sql5-sqlite (>= 5.4), libqt5svg5 (>= 5.4), libqt5widgets5 (>= 5.4)")
elseif(QT_VERSION_MAJOR VERSION_EQUAL 6)
	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.34), libqt6core6, libqt6gui6, libqt6sql6, libqt6sql6-sqlite, libqt6svg6, libqt6uitools6, libqt6widgets6")
endif()
set(CPACK_DEBIAN_PACKAGE_SECTION utils)

# CPack RPM configuration
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
if(QT_VERSION_MAJOR VERSION_EQUAL 5)
	set(CPACK_RPM_PACKAGE_REQUIRES "qt5-qtsvg >= 5.4")
elseif(QT_VERSION_MAJOR VERSION_EQUAL 6)
	set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtsvg")
endif()
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION /usr/share/applications /usr/share/pixmaps)

include(CPack)
