#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

int main(int argc, const char** argv){
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr; // str에 로그를 받아온 뒤에 출력
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description); // fmt에서 사용하는 형식
        return -1;
    }

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, // 빨간 밑줄은 CMake에서 잘 됨
    // auto -> 형식에 맞추어서 알아서 지원해줌 C++ 11 부터 지원해줌 
      nullptr, nullptr); // 모니터 종류, 다른 윈도우랑 context 공유할 것인가! 
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // 윈도우와 interaction을 수집하는 함수 
        // 없으면 실행이 너무 빨리 되어서 멈추지 않음 
    }

    glfwTerminate();
    return 0;
}