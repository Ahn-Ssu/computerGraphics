#version 330 core  // 3.3 core profile 부터 실행이 가능하다.
layout (location = 0) in vec3 aPos; // location 0은 VAO attr 0번을 의마한다.
// aPos에 데이터가 하나씩 쉐이더에 넘어오게 됨.
	void main() {
    gl_Position = vec4(aPos, 1.0);
}