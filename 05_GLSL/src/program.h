#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program {
public:
    static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders); // reference type이 인자임 (복사가 되지 않음)

    ~Program();
    uint32_t Get() const { return m_program; }  
    void Use() const;  
private:
    Program() {}
    bool Link(const std::vector<ShaderPtr>& shaders);
    uint32_t m_program { 0 };
};

#endif // __PROGRAM_H__

// shader class 형태랑 매우 비슷하게 생겼음 
// 이렇게 설계된 이유 (vertex shader랑 아주 똑같음)
    // vertex, fragment shader 외에 여러 개의 Shader를 링크할 수도 있게 함
    // Shader 인스턴스 인자는 필요하지만 소유할 필요는 없음
    // Shader 인스턴스는 다른 Program 인스턴스를 만드는 데 재사용할 수도 있음 -> 그래서 받는게 ptr임 
        // 내부에 reference counter가 있어서 모두가 사용하지 않을 때 (out of scope) 메모리를 해제함 
    // 따라서 shared pointer를 사용: ShaderPtr

