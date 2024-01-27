cmake_minimum_required(VERSION 3.27)
project(kompute)

set(CMAKE_CXX_STANDARD 26)

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(kompute src/main.cpp src/pch.hpp src/vkh.hpp src/file_utils.hpp src/glm_utils.hpp src/meshlets.hpp)
target_link_libraries(kompute PUBLIC SDL2::SDL2)
target_link_libraries(kompute PUBLIC Vulkan::Vulkan)

function(target_compile_shaders TARGET_NAME)
    foreach(SHADER ${ARGN})
        # Compile shader to SPIR-V
        add_custom_command(
            OUTPUT ${SHADER}.spv
            COMMAND glslc ${SHADER} -o ${SHADER}.spv
            DEPENDS ${SHADER}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

        # Add SPIR-V to target
        target_sources(${TARGET_NAME} PRIVATE ${SHADER}.spv)

        # Add SPIR-V to CMake's dependency graph
        set_source_files_properties(${SHADER}.spv PROPERTIES GENERATED TRUE)
    endforeach()
endfunction()

target_compile_shaders(kompute "${CMAKE_CURRENT_SOURCE_DIR}/shaders/ps.comp")