cmake_minimum_required(VERSION 3.26)
project(OpenGL4_HelloWindow)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/GLDevLibs/include")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    link_directories("C:/GLDevLibs/lib/Debug")
else()
    link_directories("C:/GLDevLibs/lib/Release")
endif ()

add_executable(OpenGL4_HelloWindow main.cpp Tools/Model3D.cpp Tools/Mesh.cpp Tools/Shader.cpp Tools/stb_image.cpp Tools/tiny_obj_loader.cpp Camera/Camera.cpp
        water.h)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    target_link_libraries(OpenGL4_HelloWindow glfw3.lib libglew32d.lib opengl32.lib)
else()
    target_link_libraries(OpenGL4_HelloWindow glfw3.lib libglew32.lib opengl32.lib)
endif ()