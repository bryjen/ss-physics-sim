cmake_minimum_required(VERSION 3.10)
project(ss_phys_sim C)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")


# CREATING EXECUTABLE
set(HEADER_FILES
    include/ssps/common/arena.h

    include/ssps/physics/vec3.h
    include/ssps/physics/simulation.h
    include/ssps/rendering/raylib_renderer.h
)

set(SOURCE_FILES
    src/main.c
    
    src/physics/simulation.c
    src/rendering/raylib_renderer.c
)

add_executable(ss_phys_sim ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(ss_phys_sim PRIVATE ${CMAKE_SOURCE_DIR}/include)


# FIND/LINK "OpenGL"
# conditional
if(DEFINED ENV{INCLUDE_OPENGL})
    message(STATUS "INCLUDE_OPENGL is set to $ENV{INCLUDE_OPENGL}")
    message(STATUS "Including OpenGL")
    message(AUTHOR_WARNING "Can cause collisions with Raylib")

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    target_include_directories(ss_phys_sim PRIVATE ${GLUT_INCLUDE_DIRS})
    target_link_libraries(ss_phys_sim PRIVATE ${OPENGL_gl_LIBRARY} ${GLUT_glut_LIBRARY})
endif()


# FIND/LINK "Raylib"
find_package(raylib CONFIG REQUIRED)
target_link_libraries(ss_phys_sim PRIVATE raylib)


if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "ARM64")
    add_definitions(-D_M_ARM64)
endif()