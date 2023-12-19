cmake_minimum_required(VERSION 3.5)
project(marketProduce VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_executable(marketProduce main.cpp src/CustomerClass.cpp src/ProduceClass.cpp src/MenuClass.cpp src/ManagerClass.cpp)
set_target_properties(marketProduce PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(marketProduce PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
