
option(BUILD_TESTS "Build tests for Kroma" OFF)

if(BUILD_TESTS)
    message(STATUS "Configuring tests...")

    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/Catch2)

    enable_testing()

    include_directories(${CMAKE_SOURCE_DIR}/tests/include)

    add_executable(kroma_tests
        ${CMAKE_SOURCE_DIR}/tests/src/stmt/expressionstmt.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/stmt/returnstmt.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/stmt/varstmt.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/argumentparser.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/environment.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/fstring.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/rangeexpr.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/token.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/tokentype.cpp
        ${CMAKE_SOURCE_DIR}/tests/src/value.cpp
    )

    target_link_libraries(kroma_tests PRIVATE
        kroma_core
        Catch2::Catch2WithMain
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(kroma_tests)
endif()