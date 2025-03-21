cmake_minimum_required(VERSION 3.0)
project(sfml-engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/Raleway.ttf
)

# создадим h-файлы рядом с бинарником
set(GENERATED_HEADERS "")

foreach(RESOURCE ${RESOURCES})
get_filename_component(BASENAME ${RESOURCE} NAME_WE) # без расширения
set(HEADER "${CMAKE_CURRENT_BINARY_DIR}/${BASENAME}.h")

add_custom_command(
    OUTPUT ${HEADER}
    COMMAND xxd -i -n ${BASENAME} ${RESOURCE} > ${HEADER}
    DEPENDS ${RESOURCE}
    COMMENT "Embedding resource ${FILENAME}"
    VERBATIM
)


    list(APPEND GENERATED_HEADERS ${HEADER})
endforeach()

# создадим "виртуальную цель", чтобы автоматически включалась
add_custom_target(embed_resources ALL DEPENDS ${GENERATED_HEADERS})



find_package(SFML 2.6 COMPONENTS graphics REQUIRED) # дополните нужными вам модулями

file(GLOB_RECURSE SRC_FILES src/*.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(sfml-engine ${SRC_FILES} ${GENERATED_HEADERS} )

add_dependencies(sfml-engine embed_resources)

target_link_libraries(sfml-engine sfml-graphics)  # дополните нужными вам модулями

if(WIN32)
    add_custom_command(TARGET sfml-engine POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SFML_DIR}/bin $<TARGET_FILE_DIR:sfml-engine>)
endif()