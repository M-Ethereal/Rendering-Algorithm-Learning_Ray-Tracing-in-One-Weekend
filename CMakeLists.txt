cmake_minimum_required(VERSION 3.0.0)
project(RTOW_learning VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ppm_image ppm_image.cpp)
add_executable(sending_rays_into_the_scene sending_rays_into_the_scene.cpp)
add_executable(antialiasing antialiasing.cpp)
add_executable(Diffuse_Materials Diffuse_Materials.cpp)
add_executable(metal metal.cpp)
add_executable(glass glass.cpp)
add_executable(positionable_camera positionable_camera.cpp)
add_executable(final_render final_render.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
