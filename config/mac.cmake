

if(APPLE)
    message(STATUS "Configuración para macOS")

    # Establecer compiladores predeterminados (si no se definieron antes)
    if(NOT DEFINED CMAKE_C_COMPILER)
        set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "" FORCE)
    endif()

    if(NOT DEFINED CMAKE_CXX_COMPILER)
        set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "" FORCE)
    endif()
endif()
