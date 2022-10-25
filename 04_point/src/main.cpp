#include "common.h"
#include "shader.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h> // path가 왜 이렇게 지정되는지 잘 모르겠으면 build로 컴파일 해놓고 보면 됨
// 그리고 glad를 먼저 추가 한 뒤이 glfw를 추가 해야한다. (안그러면 err)
#include <GLFW/glfw3.h>

// GLFW로 생성된 윈도우에 특정 이벤트가 발생했을 떄 실행되는 콜백함수 지정
// 윈도우의 크기가 변경되었을 때
// 윈도우에 마우스 입력이 들어왔을 때
// 윈도우에 키보드 입력이 들어왔을 때
// 기타 등등...
// glfwXXXXCallback() 의 함수 프로토타입을 가지고 있음

// 윈도우의 프레임버퍼 크기가 변경되었을 때 호출하기 위한 콜백 정의
// Viewport(): opengl이 그림을 그릴 영역 지정
void OnFramebufferSizeChange(GLFWwindow *window, int width, int height)
{
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height); // (x, y, w , h)
}

// 키보드 입력 콜백 정의
// Escape 키 누르면 프로그램 종료
void OnKeyEvent(GLFWwindow *window,
                int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, modifiers: {}{}{}",
                key, scancode,
                action == GLFW_PRESS ? "Pressed" : action == GLFW_RELEASE ? "Released"
                                               : action == GLFW_REPEAT    ? "Repeat"
                                                                          : "Unknown",
                mods & GLFW_MOD_CONTROL ? "C" : "-",
                mods & GLFW_MOD_SHIFT ? "S" : "-",
                mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char **argv)
{
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit())
    {
        const char *description = nullptr; // str에 로그를 받아온 뒤에 출력
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description); // fmt에서 사용하는 형식
        return -1;
    }

    // ... glfwInit() 호출 후
    // GLFW 원도우 생성 전, 희망하는 OpenGL 버전을 추가
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ... glfwCreateWindow() 호출 전

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, // 빨간 밑줄은 CMake에서 잘 됨
                                                                             // auto -> 형식에 맞추어서 알아서 지원해줌 C++ 11 부터 지원해줌
                                   nullptr, nullptr);                        // 모니터 종류, 다른 윈도우랑 context 공유할 것인가!
    if (!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    // glfwCreateWindow() 함수 호출에 window가 만들어지고, 그 window에서 사용될 context가 만들어짐
    // openGL functions 은 어떤 window에 대해 그림을 그려라 - 하는 window setting이 따로 없음 -> 그저 지금 (focus)생성되어 있는 context에서만 실행됨
    // context를 사용하겠다고 명시적으로 선언해주기 위해서, window가 만들어진 직후에 실행을 함
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    // OpenGL context를 생성한 이후에 실행.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    // 로딩 이후에는 OpenGL function을 사용할 수 있게 됨
    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", glVersion);

    auto vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    auto fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    SPDLOG_INFO("vertex shader id: {}", vertexShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragmentShader->Get());

    // callback을 glfw쪽에서 호출을 할 수 있도록 설정
    // 당연히, gl function이 loading 된 후에.
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우 생성 직후에는 프레임버퍼 변경 이벤트가 발생하지 않으므로, 첫 호출을 수동으로 만들어 놓음
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // 윈도우와 interaction을 수집하는 함수
        // 없으면 실행이 너무 빨리 되어서 멈추지 않음

        glClearColor(0.1f, 0.2f, 0.3f, 0.0f); // 랜더링 코드, 컬러 프레임버퍼 화면을 클리어할 색상을 지정함
        glClear(GL_COLOR_BUFFER_BIT);         // 실제로 프레임버퍼를 클리어하는 친구, (위에서 설정한 색으로 버퍼를 초기화 해버림) 사이즈 바꿔도 이제 frame 짤리지 않음

        // 화면에 그림을 그리는 과정
        // 프레임버퍼 2개를 준비 (front/back)
        // back buffer에 그림 그리기 ; front에 그림을 그리면, 그림을 그리는 과정이 보여서 더러움
        // front와 back을 교환함 (double buffering)
        // 그림이 그려지는 과정이 노출되지 않도록 해줌
        // 요즘 대부분은 double buffer 이상으로 수행함
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// opengl remarks

// 1) function의 2가지 종류
// i. state-setting function
// state가 opengl context에 저장이 된다.
// 예 glViewport(), glClearColor()
// ii. state-using function
// openGl context에 저장된 state를 이용함
// glClear()