
cmake_minimum_required(VERSION 3.14)

project(ZTcURL)

include(FetchContent)

FetchContent_Declare(
  ziti-sdk-c
  GIT_REPOSITORY https://github.com/openziti/ziti-sdk-c.git
  GIT_TAG ${LATEST_ZITI_RELEASE} main
)

FetchContent_MakeAvailable(ziti-sdk-c)

add_executable(ZTcURL ZTcURL.c)

find_package(CURL REQUIRED)

target_link_libraries(ZTcURL PRIVATE ziti CURL::libcurl)
