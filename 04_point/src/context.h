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
};

#endif // __CONTEXT_H__
// glfwTerminate() 함수 실행 전에 
// 우리가 만든 shader, program 등의 메모리를 한꺼번에 정리하기 위해서 관리하는 디자인 