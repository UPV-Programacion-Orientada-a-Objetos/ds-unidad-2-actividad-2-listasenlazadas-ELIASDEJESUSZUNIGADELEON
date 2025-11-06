cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(DecodificadorPRT7 VERSION 1.0 LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de inclusión
include_directories(${PROJECT_SOURCE_DIR}/include)

# Archivos fuente (se irán agregando conforme avancemos)
set(SOURCES
    src/main.cpp
    # Aquí se agregarán más archivos .cpp
)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Configuración para Windows (comunicación serial)
if(WIN32)
    # No necesitamos librerías externas, usaremos Win32 API
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS_BUILD)
endif()

# Opciones de compilación
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Mensaje de información
message(STATUS "Configurando proyecto: ${PROJECT_NAME}")
message(STATUS "Directorio de fuentes: ${PROJECT_SOURCE_DIR}")
