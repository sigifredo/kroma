include(ExternalProject)

set(RL_DIR ${CMAKE_SOURCE_DIR}/third_party/readline)

ExternalProject_Add(rl
    PREFIX ${CMAKE_BINARY_DIR}/_deps/readline
    GIT_REPOSITORY https://git.savannah.gnu.org/git/readline.git
    GIT_TAG master
    CONFIGURE_COMMAND ./configure
    BUILD_COMMAND make
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE 1
)

ExternalProject_Get_Property(rl source_dir)

add_library(librl STATIC IMPORTED GLOBAL)

set_target_properties(librl PROPERTIES
    IMPORTED_LOCATION ${source_dir}/lib/libreadline.a
    INTERFACE_INCLUDE_DIRECTORIES ${source_dir}
)

# Asegurar que se construya readline antes de usar la librería
add_dependencies(librl rl)
