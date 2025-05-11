cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(SLang CXX)

# Estándar de C++ requerido
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SRC
    src/Token.cpp
)

# Agrega el ejecutable desde el archivo fuente
add_executable(slang src/main.cpp ${SRC})
