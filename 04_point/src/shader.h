#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader
{
public:
    static ShaderUPtr CreateFromFile(const std::string &filename, GLenum shaderType);

    ~Shader();
    uint32_t Get() const { return m_shader; }

private: // private constructor, 초기화도 private, opengl shader id를 저장할 곳도 private
    Shader() {}
    bool LoadFile(const std::string &filename, GLenum shaderType);
    uint32_t m_shader{0};
};

#endif // __SHADER_H__

// 생성자가 private인 이유:
// CreateFromFile() static 함수 외에 다른 방식 Shader 인스턴스의 생성을 막기 위해서
// 또한 리턴타입이 UPtr임, unique_pointer  방식 외에는 결제하지 못하게 함
// Get()은 있는데 Set()는 없는 이유:
// Shader 오브젝트의 생성 관리는 Shader 내부에서만 관리
// OpenGL에서만 관리하라고 이렇게 구성을 하는 것
// LoadFile()이 bool을 리턴하는 이유:
// 생성에 실패할 경우 false를 리턴하기 위해서.