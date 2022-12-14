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
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  // top left
    };
    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // buffer object를 생성하기전에 array object를 먼저 만들 것
    // VAO binding -> VBO binding -> vertex attribute setting; VBO description to VAO
    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(
                                GL_ARRAY_BUFFER,
                                GL_STATIC_DRAW,
                                vertices,
                                sizeof(float) * 12);

    
    
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); 
    // 점의 위치를 어떻게 생겼는지 묘사를 하는 것
    //     n: 정점의 n번째 attribute
    // size: 해당 attribute는 몇개의 값으로 구성되어 있는가?
    // type: 해당 attribute의 데이터 타입
    // normalized: 0~1사이의 값인가
    // stride: 두 정점간의 간격 (byte 단위)
    // offset: 첫 정점의 헤당 attribute까지의 간격 (byte 단위)

    m_indexBuffer = Buffer::CreateWithData(
                                GL_ELEMENT_ARRAY_BUFFER,
                                GL_STATIC_DRAW,
                                indices,
                                sizeof(uint32_t) * 6);



    

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


    return true;
}

// openGL은 [-1, 1] 가로세로의 정규화된 위치를 사용함 

// Render()가 glClear()를 호출하도록 구현
void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // for text code
    m_program->Use();
    // glDrawArrays(GL_POINTS, 0, 1);
    // glDrawArrays(GL_TRIANGLES, 0, 6); // 이제 삼각형을 그리라는 것 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



// glDrawArray(primitive, offset, count)
    // 현재 설정된 program, VBO, VAO로 그림을 그린다 --> 현재 binding 되어 있는 VBO,VAO로.
    // primitive: 그리고자 하는 primitive 타입
    // offset: 그리고자 하는 첫 정점의 index
    // count: 그리려는 정점의 총 개수

// glDrawArrays()를 이용하여 그림을 그리려면 정점이 6개가 필요
// 정점의 낭비가 있음


// Element Buffer Object (EBO)
// 정점의 인덱스를 저장할 수 있는 버퍼
// 인덱스 버퍼라고도 부름
// 정점 정보와 별개로 정점의 인덱스로만 구성된 삼각형 정보를 전달 가능
// indexed drawing

// glDrawElements(primitive, count, type, pointer/offset)
    // 현재 바인딩된 VAO, VBO, EBO를 바탕으로 그리기
    // primitive: 그려낼 기본 primitive 타입
    // count: 그리고자 하는 EBO 내 index의 개수
    // type: index의 데이터형
    // pointer/offset: 그리고자 하는 EBO의 첫 데이터로부터의 오프셋