
option(BUILD_TESTS "Build tests for Kroma" OFF)

if(BUILD_TESTS)
    message(STATUS "Configuring tests...")

    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/Catch2)

    enable_testing()

    add_executable(kroma_tests
        ${CMAKE_SOURCE_DIR}/tests/test_environment.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_value.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_token.cpp
    )

    target_link_libraries(kroma_tests PRIVATE
        kroma_core
        Catch2::Catch2WithMain
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(kroma_tests)
endif()