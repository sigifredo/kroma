cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(kroma VERSION 0.0.1 LANGUAGES CXX)

include(config/build.cmake)
include_directories(include ${PROJECT_BINARY_DIR}/include/)

set(SRC
    src/ArgumentParser.cpp
    src/ATSPrinter.cpp
    src/DummyListener.cpp
    src/Parser.cpp
    src/REPL.cpp
    src/Scanner.cpp
    src/Token.cpp
    src/TokenType.cpp
    src/Value.cpp
)
    
set(SRC_EXPRESSIONS
    src/expressions/BinaryExpr.cpp
    src/expressions/CallExpr.cpp
    src/expressions/Expr.cpp
    src/expressions/GroupingExpr.cpp
    src/expressions/LiteralExpr.cpp
    src/expressions/UnaryExpr.cpp
)

# Agrega el ejecutable desde el archivo fuente
add_executable(kroma src/main.cpp ${SRC} ${SRC_EXPRESSIONS})

target_link_libraries(kroma PRIVATE readline)
