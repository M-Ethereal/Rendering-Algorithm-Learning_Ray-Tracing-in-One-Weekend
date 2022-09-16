cmake_minimum_required(VERSION 3.0.0)
project(RTOW_learning VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ppm_image ppm_image.cpp)
add_executable(sending_rays_into_the_scene sending_rays_into_the_scene.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
