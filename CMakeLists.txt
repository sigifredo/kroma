cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(kroma VERSION 0.0.1 LANGUAGES CXX)

include(config/build.cmake)
include(config/tests.cmake)
include_directories(include ${PROJECT_BINARY_DIR}/include/)

set(SRC
    src/ArgumentParser.cpp
    src/ATSPrinter.cpp
    src/DummyListener.cpp
    src/Environment.cpp
    src/IO.cpp
    src/Parser.cpp
    src/REPL.cpp
    src/Scanner.cpp
    src/TokenType.cpp
    src/Value.cpp
)

# Agrega el ejecutable desde el archivo fuente
add_library(kroma_core ${SRC})
add_executable(kroma src/main.cpp)

target_link_libraries(kroma_core PRIVATE readline)
target_link_libraries(kroma PRIVATE readline kroma_core)
