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

#add_executable(assignment-list
#	${project_sources}
#	${project_headers}
#	${project_uis}
#	${project_misc}
#)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(assignment-list
        MANUAL_FINALIZATION
        ${project_sources}
		${project_headers}
		${project_uis}
		${project_misc}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt_quick_hello APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(assignment-list SHARED
			${project_sources}
			${project_headers}
			${project_uis}
			${project_misc}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(assignment-list
			${project_sources}
			${project_headers}
			${project_uis}
			${project_misc}
        )
    endif()
endif()

# Avoid opening console on windows
set_target_properties(assignment-list PROPERTIES WIN32_EXECUTABLE ON)

target_link_libraries(assignment-list PUBLIC ${qt_libraries})

# Installation
include(GNUInstallDirs)
# Do not install normally if on Windows (we will install to / rather than /bin of install location)
if(NOT CMAKE_SYSTEM MATCHES "Windows*")
	install(TARGETS assignment-list
		BUNDLE DESTINATION .
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
endif()

# install desktop entry and icon
if(CMAKE_SYSTEM MATCHES "Linux.*")
	configure_file(data/assignment-list.desktop.in ${CMAKE_CURRENT_SOURCE_DIR}/data/assignment-list.desktop @ONLY)
	install(FILES data/assignment-list.desktop DESTINATION share/applications)
	install(FILES data/assignment-list.svg DESTINATION share/pixmaps)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(assignment-list)
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

## CPack NSIS configuration
## Allow regular users to run installer
#set(CPACK_NSIS_DEFINES "RequestExecutionLevel user")
## Set installer icons
#set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/data/assignment-list.ico")
#set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/data/assignment-list.ico")
## Install a StartMenu Shortcut
#set(CPACK_NSIS_CREATE_ICONS_EXTRA
#	"CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_TITLE}.lnk' '$INSTDIR\\\\assignment-list.exe'"
#)
#set(CPACK_NSIS_DELETE_ICONS_EXTRA
#	"Delete '$SMPROGRAMS\\\\$START_MENU\\\\${PROJECT_TITLE}.lnk'"
#)
## Set FinishPage
#set(CPACK_NSIS_EXECUTABLES_DIRECTORY "/")
#set(CPACK_NSIS_MUI_FINISHPAGE_RUN "assignment-list.exe")
## Based on https://stackoverflow.com/q/69139412
#if(CMAKE_SYSTEM MATCHES "Windows*")
#	set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_TITLE})
#	include(InstallRequiredSystemLibraries)
#	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
#	add_custom_command(TARGET assignment-list POST_BUILD
#		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy/
#		COMMAND ${WINDEPLOYQT_EXECUTABLE}
#			--dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:assignment-list>
#		)
## Install dlls
#	install(CODE "set(CMAKE_MINGW_SYSTEM_LIBRARY_PATH \"${CMAKE_FIND_ROOT_PATH}/bin/\")")
#	install(
#		DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
#		DESTINATION /
#		FILES_MATCHING PATTERN "*.*"
#		)
## FIXME this only works on MSYS2 with NO flexibility!
#	find_file(SQLITE_DLL "libsqlite3-0.dll" PATHS ${CMAKE_SYSTEM_LIBRARY_PATH} ${CMAKE_MINGW_SYSTEM_LIBRARY_PATH} NO_DEFAULT_PATH)
#	target_link_libraries(assignment-list PRIVATE ${SQLITE_DLL})
#	install(FILES ${SQLITE_DLL} DESTINATION /)
## Based on https://discourse.cmake.org/t/runtime-dependencies-cannot-find-dll/3782
## and https://discourse.cmake.org/t/get-runtime-dependencies-does-not-seem-to-work-with-mingw/2239
#	install(TARGETS assignment-list
#		RUNTIME_DEPENDENCIES
#			PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
#			POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
#			DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH} ${CMAKE_MINGW_SYSTEM_LIBRARY_PATH}
#		DESTINATION /
#	)
#	#install(CODE [[
#	#	file(GET_RUNTIME_DEPENDENCIES 
#	#		LIBRARIES "$<TARGET_FILE:assignment-list>"
#	#		RESOLVED_DEPENDENCIES_VAR _r_deps
#	#		UNRESOLVED_DEPENDENCIES_VAR _u_deps
#	#		DIRECTORIES ${DEPENDENCY_PATHS}
#	#		PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
#	#		POST_EXCLUDE_REGEXES" ".*system32/.*\\.dll"
#	#	)
#	#	foreach(_file ${_r_deps})
#	#		file(INSTALL
#	#			DESTINATION "${CMAKE_INSTALL_BINDIR}"
#	#			TYPE SHARED_LIBRARY
#	#			FILES "${_file}"
#	#		)
#	#	endforeach()
#	#	list(LENGTH _u_deps _u_length)
#	#	if("${_u_length}" GREATER 0)
#	#		message(WARNING "Unresolved dependencies detected!")
#	#	endif()
#	#]])
#endif()

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
