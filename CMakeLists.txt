cmake_minimum_required(VERSION 3.0)
project(sfml-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ресурсы
set(RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/Raleway.ttf
)

set(GENERATED_HEADERS "")

foreach(RESOURCE ${RESOURCES})
    get_filename_component(BASENAME ${RESOURCE} NAME_WE)
    set(HEADER "${CMAKE_CURRENT_BINARY_DIR}/${BASENAME}.h")

    add_custom_command(
        OUTPUT ${HEADER}
        COMMAND xxd -i ${RESOURCE} > ${HEADER}
        DEPENDS ${RESOURCE}
        COMMENT "Embedding resource ${BASENAME}"
        VERBATIM
    )

    list(APPEND GENERATED_HEADERS ${HEADER})
endforeach()

add_custom_target(embed_resources ALL DEPENDS ${GENERATED_HEADERS})

# SFML
set(SFML_DIR "C:/libs/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 REQUIRED COMPONENTS graphics window system audio)

# исходники — исключаем служебные
file(GLOB_RECURSE ALL_SRC_FILES "src/*.cpp")

# фильтрация лишних файлов
set(SRC_FILES "")
foreach(FILE ${ALL_SRC_FILES})
    if(NOT FILE MATCHES ".*/CMakeFiles/.*")
        list(APPEND SRC_FILES ${FILE})
    endif()
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(sfml-engine ${SRC_FILES} ${GENERATED_HEADERS})

add_dependencies(sfml-engine embed_resources)

target_link_libraries(sfml-engine
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


if(WIN32)
    add_custom_command(TARGET sfml-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/libs/SFML-2.6.2/bin" $<TARGET_FILE_DIR:sfml-engine>
    )
endif()
