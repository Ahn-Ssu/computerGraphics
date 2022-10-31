#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr> &shaders){
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders)) // 초기화
        return nullptr;
    return std::move(program);
}
// shader랑 모양이 똑같음

// glCreateProgram()으로 새로운 OpenGL program object 생성
// glAttachShader()로 program에 shader를 붙이기
// glLinkProgram()으로 program 링크
// glGetProgramiv()로 프로그램 링크 상태 확인
// 링크에 실패했다면 glGetProgramInfoLog()로 에러 로그 가져오기
bool Program::Link(const std::vector<ShaderPtr> &shaders){
    m_program = glCreateProgram();

    for (auto &shader : shaders) // iteractor를 활용한 advanced for statements
        glAttachShader(m_program, shader->Get());
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success){
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: {}", infoLog);
        return false;
    }
    return true;
}

// glDeleteProgram()으로 OpenGL program object 제거
Program::~Program() {
  if (m_program) {
    glDeleteProgram(m_program);
  }
}

void Program::Use() const {
    glUseProgram(m_program);
}


// glCreateProgram(): OpenGL program object 생성
// glAttachShader(): program에 shader를 붙이기
// glLinkProgram(): program 링크
// glGetProgramiv(): program에 대한 정수형 정보를 얻어옴
// glGetProgramInfoLog(): program에 대한 로그를 얻어옴. 링크 에러 얻어내는 용도로 사용
// glDeleteProgram(): program object 제거