#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string &filename, GLenum shaderType)
{
    auto shader = std::unique_ptr<Shader>(new Shader());
    // Shader class 내부의 함수이기 때문에 ner Shader()가 가능함.
    // 생성된 사용된 shader는 UPtr이다.
    if (!shader->LoadFile(filename, shaderType))
        // UPtr이기 때문에 해당 scope에서만 사용이 가능함
        // nullptr return인 경우 delete가 자동으로 수행이 됨
        return nullptr;
    // 정상적으로 생성된 경우 UPtr의 소유권을 이전해야하기 때문에 move로 호출
    return std::move(shader);
}

// 파일 로딩 실패시 false를 리턴
// 성공시 로딩된 텍스트 포인터 및 길이를 가져옴
bool Shader::LoadFile(const std::string &filename, GLenum shaderType)
{
    // common.h에 선언했던 함수 optional return.
    auto result = LoadTextFile(filename);
    // optional type이 실제 값이 있는지 확인을 하는 것 
    if (!result.has_value()) 
        return false;

    
    // std::string code = result.value();       얘는 메모리 카피가 일어남
    // std::string& code = result.value();      얘는 reference type으로 메모리를 유지한채로 사용됨
    //  등의 방법으로 받을 순 있으나, 용도가 다 다름
    auto &code = result.value(); // auto는 &를 붙일지 안 붙일지 결정을 하지 않음 
    const char *codePtr = code.c_str(); // c_str(): char* 리턴, string의 첫번째 문자 주소값 포인터를 반환함 
    int32_t codeLength = (int32_t)code.length(); // 비트수로 명시적으로 사용이 가능하니까 이게 더 도움이 될 것(권장)

    // create and compile shader
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar *const *)&codePtr, &codeLength);
    glCompileShader(m_shader);

    // check compile error
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // shader의 정보를 얻어옴, success 포인터에다가 결과를 써줌
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}

// 소멸자 ~Shader 구현
// m_shader는 처음에 0으로 초기화
// m_shader에 0이 아닌 다른 값이 들어가 있다면 glDeleteShader()를 호출하여 shader object 제거
Shader::~Shader() {
  if (m_shader) {
    glDeleteShader(m_shader);
  }
}