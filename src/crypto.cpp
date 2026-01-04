#include "Crypto.hpp"
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>
#include <fstream>

std::string Crypto::generateSalt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::ostringstream oss;
    for (int i = 0; i < 16; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return oss.str();
}

std::string Crypto::hashPassword(const std::string& password, const std::string& salt) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password + salt));
}

bool Crypto::verifyMasterPassword(const std::string& inputPwd, const std::string& envHash, const std::string& salt){
    return Crypto::hashPassword(inputPwd, salt) == envHash;
}

std::unordered_map<std::string, std::string> Crypto::Envload(const std::string& path){
    std::unordered_map<std::string, std::string> env;
    std::ifstream file(path);

    if (!file) return env;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        env[key] = value;
    }
    return env;
}

std::string Crypto::get(const std::string& path, const std::string& key){
    auto env = Envload(path);
    return env.count(key) ? env[key] : "";
}
