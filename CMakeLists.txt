cmake_minimum_required(VERSION 3.21)

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
set(NSIS_PRODUCT_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}.0")

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
	set(NSIS_PRODUCT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.0.0")
endif()

set(qt_components "Core" "Gui" "Sql" "UiTools" "Widgets" "Quick")
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

# QtWidgets sources
set(project_sources_frontend
	"src/frontend/qtwidgets/addEntryForm.cpp"
	"src/frontend/qtwidgets/addGroupForm.cpp"
	"src/frontend/qtwidgets/assignmentList.cpp"
	"src/frontend/qtwidgets/editGroupForm.cpp"
	"src/frontend/qtwidgets/editEntryForm.cpp"
	"src/frontend/qtwidgets/entry.cpp"
	"src/frontend/qtwidgets/entryLayout.cpp"
	"src/frontend/qtwidgets/group.cpp"
	"src/frontend/qtwidgets/groupLayout.cpp"
	"src/frontend/qtwidgets/lib.cpp"
	"src/frontend/qtwidgets/main.cpp"
	"src/frontend/qtwidgets/preferencesDialog.cpp"
	"src/frontend/qtwidgets/rule.cpp"
	"src/frontend/qtwidgets/ruleLayout.cpp"
	"src/frontend/qtwidgets/rulesDialog.cpp"
)

set(project_sources_backend
	"src/backend/db_sqlite.cpp"
)

set(project_sources
	${project_sources_frontend}
	${project_sources_backend}
)

set(project_headers_frontend
	"src/frontend/qtwidgets/addEntryForm.h"
	"src/frontend/qtwidgets/addGroupForm.h"
	"src/frontend/qtwidgets/assignmentList.h"
	"src/frontend/qtwidgets/editGroupForm.h"
	"src/frontend/qtwidgets/editEntryForm.h"
	"src/frontend/qtwidgets/entry.h"
	"src/frontend/qtwidgets/entryLayout.h"
	"src/frontend/qtwidgets/group.h"
	"src/frontend/qtwidgets/groupLayout.h"
	"src/frontend/qtwidgets/lib.h"
	"src/frontend/qtwidgets/preferencesDialog.h"
	"src/frontend/qtwidgets/rule.h"
	"src/frontend/qtwidgets/ruleLayout.h"
	"src/frontend/qtwidgets/rulesDialog.h"
)

set(project_headers_backend
	"src/backend/db_sqlite.h"
)

set(project_headers
	${project_headers_frontend}
	${project_headers_backend}
)

set(project_uis
	"src/frontend/qtwidgets/assignmentList.ui"
	"src/frontend/qtwidgets/entryForm.ui"
	"src/frontend/qtwidgets/groupForm.ui"
	"src/frontend/qtwidgets/preferencesDialog.ui"
	"src/frontend/qtwidgets/rulesDialog.ui"
)

set(project_misc
	"resources.qrc"
	"src/icon/assignment-list.rc"
)

set(project_sources_full
	${project_sources}
	${project_headers}
	${project_uis}
	${project_misc}
)

# Sources unique to qtquick
set(qtquick_sources
	"src/frontend/qtquick/main.cpp"
	"src/frontend/qtquick/qml.qrc"
)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)
if(CMAKE_SYSTEM MATCHES "Windows*")
	configure_file(nsis/installer.nsi.in ${CMAKE_CURRENT_BINARY_DIR}/installer.nsi @ONLY)
endif()

#add_executable(assignment-list
#	${project_sources_full}
#)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(assignment-list
        MANUAL_FINALIZATION
		${project_sources_full}
    )
	qt_add_executable(assignment-list-mobile
		MANUAL_FINALIZATION
		${qtquick_sources}
	)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt_quick_hello APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(assignment-list SHARED
			${project_sources_full}
        )
		add_library(assignment-list-mobile SHARED
			${qtquick_sources}
		)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(assignment-list
			${project_sources_full}
        )
		add_executable(assignment-list-mobile
			${qtquick_sources}
		)
    endif()
endif()

# Avoid opening console on windows
set_target_properties(assignment-list PROPERTIES WIN32_EXECUTABLE ON)
set_target_properties(assignment-list-mobile PROPERTIES WIN32_EXECUTABLE ON)

target_link_libraries(assignment-list PUBLIC ${qt_libraries})
target_link_libraries(assignment-list-mobile PUBLIC ${qt_libraries})

# Installation
include(GNUInstallDirs)
install(TARGETS assignment-list
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install desktop entry and icon
if(CMAKE_SYSTEM MATCHES "Linux.*")
	configure_file(data/assignment-list.desktop.in ${CMAKE_CURRENT_SOURCE_DIR}/data/assignment-list.desktop @ONLY)
	install(FILES data/assignment-list.desktop DESTINATION share/applications)
	install(FILES data/assignment-list.svg DESTINATION share/pixmaps)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(assignment-list)
	qt_finalize_executable(assignment-list-mobile)
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

# Get Windows dependencies/dlls for nsis
# Based on https://stackoverflow.com/q/69139412
if(CMAKE_SYSTEM MATCHES "Windows*")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_TITLE})
	include(InstallRequiredSystemLibraries)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
	add_custom_command(TARGET assignment-list POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy/
		COMMAND ${WINDEPLOYQT_EXECUTABLE}
			--dir ${CMAKE_BINARY_DIR}/qtDeploy 
			--compiler-runtime $<TARGET_FILE:assignment-list>
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
