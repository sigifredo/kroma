cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(kroma VERSION 0.0.1 LANGUAGES CXX)

include(config/build.cmake)
include_directories(include ${PROJECT_BINARY_DIR}/include/)

set(SRC
    src/ArgumentParser.cpp
    src/BinaryExpr.cpp
    src/DummyListener.cpp
    src/Expr.cpp
    src/GroupingExpr.cpp
    src/LiteralExpr.cpp
    src/REPL.cpp
    src/Scanner.cpp
    src/Token.cpp
    src/TokenType.cpp
    src/UnaryExpr.cpp
    src/Value.cpp
)

# Agrega el ejecutable desde el archivo fuente
add_executable(kroma src/main.cpp ${SRC})

target_link_libraries(kroma PRIVATE readline)
