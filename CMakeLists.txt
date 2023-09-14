cmake_minimum_required(VERSION 3.26)

# CMake useful variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpy VERSION 1.1.2)

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Mac needed variables (adapt according to your needs)
set(CMAKE_MACOSX_RPATH ON)
#set(CMAKE_SKIP_BUILD_RPATH FALSE)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
#set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# add include
add_subdirectory(include)

# add source files
add_subdirectory(src)

option(CPY_TEST "Build tests" ON)
if(CPY_TEST)
    enable_testing()
    add_subdirectory(test)

add_subdirectory(res)

# docs
option(CPY_BUILD_DOCS "Build documentation" OFF)
if(CPY_BUILD_DOCS)
    # find doxygen and generate documentation
    find_package(Doxygen)
    # check doxygen was found
    if (DOXYGEN_FOUND)
        # use the readme as main page
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
        set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs/doxygen")
        # use doxygen_add_docs to generate documentation
        doxygen_add_docs(
            cpy_docs
            ${CMAKE_SOURCE_DIR}
            COMMENT "Generate docs pages"
        )
        add_custom_target(docs
            DEPENDS cpy_docs
        )
    else()
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
endif()
