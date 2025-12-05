cmake_minimum_required(VERSION 3.16)

project(BSVault VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}/ui/pages
    ${CMAKE_SOURCE_DIR}/ui/dialogs
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Network)

set(PROJECT_SOURCES
        src/main.cpp
	#main window
        src/mainwindow.cpp
	#Vault
	src/Vault.cpp
	src/VaultEntry.cpp
	#pages
	src/pages/VaultListPage.cpp
	src/pages/LockedPage.cpp
	#dialogs
	src/dialogs/LoginDialog.cpp
	src/dialogs/AddEntryDialog.cpp
	src/dialogs/EditEntryDialog.cpp
	src/dialogs/ConfirmDeleteDialog.cpp
	src/dialogs/NewLoginDialog.cpp
	#models
	src/models/VaultListModel.cpp
	#delegates
	src/delegates/ShowButtonDelegate.cpp
)

set(HEADERS
	#main window
	include/mainwindow.h
	# Vault
	include/Vault.h
	include/VaultEntry.h
	#pages
	include/pages/VaultListPage.h
	include/pages/LockedPage.h
	#dialogs
	include/dialogs/LoginDialog.h
	include/dialogs/AddEntryDialog.h
	include/dialogs/EditEntryDialog.h
	include/dialogs/ConfirmDeleteDialog.h
	include/dialogs/NewLoginDialog.h
	#models
	include/models/VaultListModel.h
	#delegates
	include/delegates/ShowButtonDelegate.h
)

set(UI_FILES
        #main window
	ui/mainwindow.ui
	#pages
	ui/pages/ExportPage.ui
	ui/pages/VaultListPage.ui
	ui/pages/LockedPage.ui
	#dialogs
	ui/dialogs/LoginDialog.ui
	ui/dialogs/AddEntryDialog.ui
	ui/dialogs/EditEntryDialog.ui
	ui/dialogs/ConfirmDeleteDialog.ui
	ui/dialogs/NewLoginDialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BSVault
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
	${HEADERS}
	${UI_FILES}
	ui/BSlogo.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BSVault APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BSVault SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BSVault
	    MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
	    ${HEADERS}
	    ${UI_FILES}
        )
    endif()
endif()

target_link_libraries(BSVault PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Network
	)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BSVault)
endif()
set_target_properties(BSVault PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BSVault
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(BSVault PRIVATE
	include
	include/pages
	include/dialogs
	include/models
	include/delegates
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BSVault)
endif()

#Integrate Libsodium
# Include third-party headers
target_include_directories(BSVault PRIVATE "${CMAKE_SOURCE_DIR}/third_party/libsodium/include")

# Link the static library
target_link_libraries(BSVault PRIVATE "${CMAKE_SOURCE_DIR}/third_party/libsodium/lib/libsodium.a")


