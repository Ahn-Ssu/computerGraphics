#ifndef __COMMON_H__ 
#define __COMMON_H__ // 이 이름 중복되면 안됨

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>; 

// CLASS_PTR(Shader) // 매크로 함수
// class Shader // 클래스 이름 선언
// using Shader ## UPtr = std::unique_ptr<Shader>; \ // using을 사용해서 alias를 사용함
// using Shader ## Ptr = std::shared_ptr<Shader>; \
// using Shader ## WPtr = std::weak_ptr<Shader>;// define으로 macro function을 설정할 때에 \를 이용해서 이어짐을 나타내야함.
// Shader ## UPtr -> ShaderUPter 

std::optional<std::string> LoadTextFile(const std::string& filename);
// optional <>
// C++ 17부터 사용 가능한 표준 라이브러리
// 어떤 값이 있거나 없는 경우를 포인터 없이 표현 가능
    // 처리 예제
    // text file을 읽는 상황
    // file을 찾아서 읽거나 못 읽는 경우 만약 빈 string을 리턴? / 못 연건지 파일이 비어있는지??
    // 그래서 이걸 pointer로 리턴을 하게끔 함 -> string pointer / 포인터, 주소값, 동적할당이 되어있음.. free를 무조건 해줘야함
    // 그래서 동적할당 형태를 안전하게 하기 위함
// 값이 들어 있는 경우에는 꺼낼 수 있고, 없는 경우에는 못 꺼냄 





#endif // __COMMON_H__

// #include "common.h" 를 main.cpp에서 수행할 때,
// ifndef -> if not define, then define the below codes
// -> if define, then #endif 
// 소스코드에서 만약에 include를 3번 했을 때, 해당 필터를 걸지 않으면 링크가 3번 붙어버림
// 그러면 함수도 여러번 선언이 되어서, 함수 충돌로 인해 컴파일 에러가 남. 
// ifnder, defin, endif를 같이 사용할 수 있도록 하세요 



