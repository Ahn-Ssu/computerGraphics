#include "context.h"

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

// Shader혹은 Program 생성 실패시 false를 리턴하여 메모리 할당을 자동 해제
// 한번만 실행해도 되는 glClearColor()를 이쪽으로 이동시킴
bool Context::Init()
{
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader}); // auto 대신 지역변수에 저장
    if (!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f); // 랜더링 코드, 컬러 프레임버퍼 화면을 클리어할 색상을 지정함

    // for text code
    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}

// Render()가 glClear()를 호출하도록 구현
void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // for text code
    glUseProgram(m_program->Get());
    glDrawArrays(GL_POINTS, 0, 1);
}
