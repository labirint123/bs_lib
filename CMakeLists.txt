cmake_minimum_required(VERSION 3.10)
project(sfml-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# bin2c builder
add_executable(bin2c tools/bin2c/bin2c.c)

set(RESOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/res/Raleway.ttf"
)

get_filename_component(BASENAME ${RESOURCE} NAME_WE)
set(HEADER "${CMAKE_CURRENT_BINARY_DIR}/${BASENAME}.h")
 
add_custom_command(
    OUTPUT ${HEADER}
    COMMAND bin2c ${RESOURCE} ${HEADER} ${BASENAME}
    DEPENDS ${RESOURCE} bin2c
    COMMENT "Embedding ${RESOURCE} as ${BASENAME}"
)

add_custom_target(embed_resources ALL DEPENDS ${HEADER})
include_directories(${CMAKE_CURRENT_BINARY_DIR})



file(GLOB_RECURSE ALL_SRC_FILES "src/*.cpp")

set(SRC_FILES "")
foreach(FILE ${ALL_SRC_FILES})
    if(NOT FILE MATCHES ".*/CMakeFiles/.*") 
        list(APPEND SRC_FILES ${FILE})
    endif()
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools/json)

add_executable(sfml-engine ${SRC_FILES} ${GENERATED_SOURCES} tools/json/json.hpp)
add_dependencies(sfml-engine embed_resources)

# SFML
set(SFML_DIR "C:/libs/SFML-2.6.2/lib/cmake/SFML") 
set(SFML_BIN_DIR "C:/libs/SFML-2.6.2/bin") 
find_package(SFML 2.6.2 REQUIRED COMPONENTS graphics window system audio)

target_link_libraries(sfml-engine
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

if(WIN32)
    add_custom_command(TARGET sfml-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_BIN_DIR} $<TARGET_FILE_DIR:sfml-engine> # CHANGE PATH
    )
endif()

if(WIN32)
    add_compile_definitions(PLATFORM_WINDOWS)
    message("PLATFORM_WINDOWS!")
elseif(APPLE)
    add_compile_definitions(PLATFORM_MAC)
    message("PLATFORM_MAC!")
elseif(UNIX)
    add_compile_definitions(PLATFORM_LINUX)
    message("PLATFORM_LINUX!")
    else()
    message(FATAL_ERROR "Unsupported platform!")
endif()
