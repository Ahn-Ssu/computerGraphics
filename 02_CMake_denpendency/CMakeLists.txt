cmake_minimum_required(VERSION 3.13)
# 해당 Cmake project manage를 위한 최소한의 cmake version 제약 
set(PROJECT_NAME cmake_project_example) # set -> 변수 선언 
set(CMAKE_CXX_STANDARD 17)              # 변수 사용 ${var1}

set(WINDOW_NAME "Hello, OpenGL!") # main.cpp 내부에서 사용하려고 함
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME}) 
add_executable(${PROJECT_NAME} src/main.cpp)



# 참고사항
# CMakeLists.txt 설정 변경 후 저장하면 configure 알아서 동작이 됨 
include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # 추가를 해줘야 소스코드를 사용할 수 있음 
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR}) # 바이너리 코드들 링크해서 실행파일에 포함 시킴 
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) #

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    ) # define macro 처럼 동작할 수 있게 함

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})
# 컴파일 순서를 지정해줌 DEP_LIST를 먼저 함 -> 만약에 적지 않으면 CPU를 병렬로 사용해서 동시에 돌아감, 컴파일 에러가 남