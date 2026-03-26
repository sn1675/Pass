#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Crypto {
    public:
        static std::string generateSalt();

        static std::string hashPassword(const std::string& password, const std::string& salt);

        static bool verifyMasterPassword(const std::string& inputPwd, const std::string& envHash, const std::string& salt);

        static std::unordered_map<std::string, std::string> Envload(const std::string& path);

        static std::string get(const std::string& path, const std::string& key);

        static std::vector<unsigned char> aes256Encrypt(const std::string& mdp, const std::vector<unsigned char>& key);

        static std::string aes256Decrypt(const std::vector<unsigned char>& encrypted, const std::vector<unsigned char>& key);

        static std::vector<unsigned char> deriveKey(const std::string& password, const std::vector<unsigned char>& salt, int iterations = 100000);

        static std::vector<unsigned char> hexToBytes(const std::string& hex);
};
