cmake_minimum_required(VERSION 3.14)

project(ADS_LIB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ADS_LIB SHARED
  ADS_LIB_global.h
  ads_lib.cpp
  ads_lib.h
)

target_compile_definitions(ADS_LIB PRIVATE ADS_LIB_LIBRARY)
