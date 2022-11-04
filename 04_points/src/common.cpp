#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream fin(filename); // C++ style 파일 생성자
    if (!fin.is_open()) {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {}; // 아무것도 없는 값이 리턴이 됨
    }
    std::stringstream text;
    text << fin.rdbuf(); // 스트림에 전부 때려박고
    return text.str(); // 스트링 타입으로 리턴, ooptional type에 감싸져서 리턴이 됨 
}