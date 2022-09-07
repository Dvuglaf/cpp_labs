cmake_minimum_required(VERSION 3.10)

project(WebServer)

find_package(Qt5 COMPONENTS Core Network)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} Main.cpp "WebServer.cpp")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)

if (WIN32)
    # Копирование DLL-файлов библиотеки Qt в выходную директорию
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:${PROJECT_NAME}>
    )
endif (WIN32)
