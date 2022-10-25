#version 330 core  // 3.3 core profile 부터 실행이 가능하다.
layout (location = 0) in vec3 aPos;

void main() { // shader 도 main 함수가 필요함 
  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}