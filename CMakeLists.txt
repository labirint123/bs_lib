cmake_minimum_required(VERSION 3.0)
project(sfml-engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED) # дополните нужными вам модулями

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(sfml-engine ${SRC_FILES})

target_link_libraries(sfml-engine sfml-graphics)  # дополните нужными вам модулями

if(WIN32)
    add_custom_command(TARGET sfml-engine POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SFML_DIR}/bin $<TARGET_FILE_DIR:sfml-engine>)
endif()