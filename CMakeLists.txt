# Установка минимальной требуемой версии CMake.
cmake_minimum_required(VERSION 3.27.9 FATAL_ERROR)

# Название проекта.
project(Project-EngineGame)



# Указание исходных файлов.
set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/EBO.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/EBO.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/VAO.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/VAO.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/VBO.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/buffer/VBO.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/shader/ShaderProgram.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphic/shader/ShaderProgram.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/system/console/Console.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/console/Console.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/manager/Directory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/manager/Directory.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/manager/ResourceManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/manager/ResourceManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/window/Window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/window/Window.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# Поиск всех ресурсов в директории 'res'.
file(GLOB_RECURSE RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/*
)

# Группировка исходных файлов в структурированные каталоги для IDE.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCES})

# Группировка ресурсов в структурированные каталоги для IDE.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/res" PREFIX "Resource" FILES ${RESOURCES})

# Список всех файлов проекта.
set(FILE
    ${SOURCES}
    ${RESOURCES}
)

# Создание исполняемого файла проекта.
add_executable(${PROJECT_NAME} ${FILE})

# Указание стандарта C++17 для компиляции.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Установка проекта как основного для Visual Studio.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})



# Установка директории вывода исполняемых файлов.
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# Копирование ресурсов после сборки.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

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