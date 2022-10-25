# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)  # PROJECT_BINARY_DIR: pre defined, 빌드 폴더를 말하는 거임
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
# CMake 제공 함수 ExternalProject_Add
ExternalProject_Add(
    dep_spdlog # 해당 프로젝트를 컴파일 할 때의 대표 이름: 이 이름으로 빌드가 됨 
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git" # 외부 라이브러리 (git)의 repo URL
    GIT_TAG "v1.x" # 버전 설정 -> repo 홈피에서 가져오면 됨 Branches/Tags의 label을 사용하면 됨
    GIT_SHALLOW 1  # flag, Git_shallow 활성화. repo commit의 모든 log를 다운 받지 않고 최신버전 것만 다운 받음
    UPDATE_COMMAND "" TEST_COMMAND "" PATCH_COMMAND "" # git repo clone 과정 중에 해당 step을 실행하지 않기 위해서. (git pull, .. 등 하지 않게끔)
    # update -> 최신화  sync를 모니터하고 계속 맞추어줌 / patch -> 수정 때에 사용하는 건데 안할거라서 대충.
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}  # cmake cfg 할 때 사용할 인자를 어떻게 사용할진 -D: definition
    # CMAKE가 빌드를 다 했을 때 저장할 곳을 미리 설정하는 것. 
    )
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) # $<$ cmake에서 generator 문법, cfg가 아닌 빌드단계에서 실행되게 함
# config가 디버그면 d를 붙이고 아니면 안 붙인다 
# ${DEP_LIBS} 는 사전 선언이 안되어있으면, 그냥 비어있는 상태에서 추가를 함 

# glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.3"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF   # 예제와, 테스트파일과, 문서 등을 우리가 필요가 없어서 컷
        -DGLFW_BUILD_TESTS=OFF      # 키워드 등은 repo의 CmakeLists.txt 에서 확인을 하면 됨 
        -DGLFW_BUILD_DOCS=OFF
    )
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)


# glad -> loader-genrator
# opengl lib는 bander가 제공을 함, 그래픽드라이버를 개발하는 글카회사들이 드라이버와 함께  opengl lib를 제공함
# 각각의 h/w 마다 loading function이 따로 존재함
# 그래서 우리는 code 안에서 사용하기 위해서 loading function을 또 loading 하는 lib가 필요함
# 기본적인 함수는 glfw에서는 제공하지만, 3.3 이상에서는 loader function을 사용하는 것이 좋음.
# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        # -DGLAD_INSTALL=ON # 이거 오류날 수 있는데, 파이썬 설치하면 됨 그래도 안되면 주석처리
    TEST_COMMAND ""
    )
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)