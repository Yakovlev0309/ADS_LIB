cmake_minimum_required(VERSION 3.14)

project(ADS_LIB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ADS_LIB SHARED
  ADS_LIB_global.h
  ads_lib.h
  ads_lib.cpp

  algorithms/searchings.hpp
  algorithms/sortings.hpp

  data_structures/linked_list.hpp
  data_structures/stack.hpp
  data_structures/queue.hpp
  data_structures/binary_tree.hpp
  data_structures/data_structure.hpp
)

target_compile_definitions(ADS_LIB PRIVATE ADS_LIB_LIBRARY)
