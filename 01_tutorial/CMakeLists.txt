cmake_minimum_required(VERSION 3.13)
# 해당 Cmake project manage를 위한 최소한의 cmake version 제약 
set(PROJECT_NAME camke_project_example) # set -> 변수 선언 
set(CMAKE_CXX_STANDARD 17)              # 변수 사용 ${var1}

project(${PROJECT_NAME}) 
add_executable(${PROJECT_NAME} src/main.cpp)