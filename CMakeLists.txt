# Установка минимальной требуемой версии CMake.
cmake_minimum_required(VERSION 3.27.9 FATAL_ERROR)

# Название проекта.
project(Project-EngineGame)

# Указание исходных файлов.
set(SOURCES    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Группировка исходных файлов в структурированные каталоги для IDE.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCES})

# Поиск всех ресурсов в директории 'res'.
file(GLOB_RECURSE RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/*
)

# Группировка ресурсов в структурированные каталоги для IDE.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/res" PREFIX "Resource" FILES ${RESOURCES})

# Список всех файлов проекта.
set(FILE
    ${SOURCES}
    ${RESOURCES}
)

# Создание исполняемого файла проекта.
add_executable(${PROJECT_NAME} ${FILE})

# Установка параметров GLFW.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Добавление поддиректории с библиотекой GLFW и связывание её с проектом.
add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Добавление поддиректории с библиотекой GLAD и связывание её с проектом.
add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)