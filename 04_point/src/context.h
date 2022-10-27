#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"

CLASS_PTR(Context)
class Context {
public:
    static ContextUPtr Create();
    void Render();    
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;
    // VBO를 담아둘 uint32_t형 멤버 변수를 Context 클래스에 선언
    uint32_t m_vertexBuffer;
    // Context 클래스에 VAO를 담아둘 변수 선언
    uint32_t m_vertexArrayObject;
};

#endif // __CONTEXT_H__
// glfwTerminate() 함수 실행 전에 
// 우리가 만든 shader, program 등의 메모리를 한꺼번에 정리하기 위해서 관리하는 디자인 



// Vertex buffer object (VBO)
// 정점 데이터를 담은 버퍼 오브젝트
// 정점에 대한 다양한 데이터를 GPU가 접근 가능한 메모리에 저장해둔다
// position, normal, tangent, color, texture coordinate...


// Vertex Array Object (VAO)
// 정점 데이터의 구조를 알려주는 오브젝트
// 각 정점은 몇 byte로 구성되었는가?
// 두 정점은 몇 byte만큼 떨어져 있는가?
// 정점의 0번째 데이터는 어떤 사이즈의 데이터가 몇개 있는 형태인가?