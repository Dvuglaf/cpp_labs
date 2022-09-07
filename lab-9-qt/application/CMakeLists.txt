cmake_minimum_required(VERSION 3.10)

project(Application)

find_package(Qt5 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME}
        Main.cpp
        Utils.h 
        Snake.h
        Snake.cpp
        Fruit.cpp
        Fruit.h 
        GameOver.cpp
        GameOver.h
        window.cpp
        window.h
        SettingWindow.h
        SettingWindow.cpp
        Settings.h
        Settings.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

# При каждой сборке:
# 1. Удаляем старую папку с ресурсами.
# 2. Копируем папку с ресурсами из директории с исходным кодом в директорию с исполняемым файлом.
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        "${CMAKE_CURRENT_BINARY_DIR}/resources")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "${CMAKE_CURRENT_BINARY_DIR}/resources")

if (WIN32)
    # Чтобы убрать консоль
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)

    # Копирование DLL-файлов библиотеки Qt в выходную директорию
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:${PROJECT_NAME}>
    )
endif (WIN32)
