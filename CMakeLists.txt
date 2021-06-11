cmake_minimum_required(VERSION 3.10)

project(myMarcher)

find_package(OpenGL REQUIRED)

add_library(
    lib
    STATIC
    src/include/app.h
    src/include/app.cpp
    src/include/renderer.h
    src/include/renderer.cpp
    src/include/camera.h
    src/include/camera.cpp
    src/include/window.h
    src/include/window.cpp
    src/include/shader.h
    src/include/shader.cpp   
)
include_directories(src/include)
link_directories(src/include)

# glfw setup
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(src/libs/glfw)
include_directories(src/libs/glfw/include)

# glad setup
include_directories(src/libs/GLAD/include)
link_directories(src/libs/GLAD/include)
add_library(glad STATIC src/libs/GLAD/src/glad.c)

#glm setup
add_subdirectory(src/libs/glm)
include_directories(src/libs/glm)

#stb image
add_library(stb STATIC src/libs/stb_image/stb_image.h src/libs/stb_image/stb_image.cpp)
include_directories(src/libs/stb_image)
link_directories(src/libs/stb_image)

#imgui
add_library(
    imgui STATIC
    src/libs/imgui/imgui.h
    src/libs/imgui/imgui.cpp
    src/libs/imgui/imgui_draw.cpp
    src/libs/imgui/imgui_tables.cpp
    src/libs/imgui/imgui_widgets.cpp
    src/libs/imgui/backends/imgui_impl_glfw.cpp
    src/libs/imgui/backends/imgui_impl_opengl3.cpp
    src/libs/imgui/backends/imgui_impl_glfw.h
    src/libs/imgui/backends/imgui_impl_opengl3.h
)
include_directories(src/libs/imgui)
link_directories(src/libs/imgui)

add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC src/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad OpenGL::GL glfw glm stb imgui lib)