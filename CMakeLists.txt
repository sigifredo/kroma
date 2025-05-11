cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(SLang VERSION 0.0.1 LANGUAGES CXX)

include(config/build.cmake)
include_directories(include ${PROJECT_BINARY_DIR}/include/)

set(SRC
    src/Token.cpp
)

# Agrega el ejecutable desde el archivo fuente
add_executable(slang src/main.cpp ${SRC})
