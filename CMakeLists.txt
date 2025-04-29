cmake_minimum_required(VERSION 3.16)

project(online_minesweeper_final VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apponline_minesweeper_final
    main.cpp
)

qt_add_qml_module(apponline_minesweeper_final
    URI online_minesweeper_final
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES websocketserver.h websocketserver.cpp
        QML_FILES Cell.qml
        QML_FILES CellLogic.js
        QML_FILES BoardLogic.js
        QML_FILES Board.qml
        SOURCES gameBuilder.h
        SOURCES gameBuilder.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apponline_minesweeper_final PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apponline_minesweeper_final
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apponline_minesweeper_final
    PRIVATE Qt6::Quick
    PRIVATE Qt6::WebSockets
)

include(GNUInstallDirs)
install(TARGETS apponline_minesweeper_final
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
