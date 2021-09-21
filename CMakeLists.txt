cmake_minimum_required(VERSION 3.14.5)
project (aspartamev0 LANGUAGES CXX)

file(GLOB_RECURSE hdrs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/aspartamev0/*.cc)
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PUBLIC ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

include(FetchContent)
FetchContent_Declare(cppcfwv0 GIT_TAG v0.0.1 GIT_REPOSITORY https://github.com/hojin-koh/cppcfw.git)
FetchContent_MakeAvailable(cppcfwv0)
target_link_libraries(${PROJECT_NAME} PUBLIC cppcfwv0)
