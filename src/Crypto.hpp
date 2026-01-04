#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>
#include <unordered_map>

class Crypto {
    public:
        static std::string generateSalt();

        static std::string hashPassword(const std::string& password, const std::string& salt);

        static bool verifyMasterPassword(const std::string& inputPwd, const std::string& envHash, const std::string& salt);

        static std::unordered_map<std::string, std::string> Envload(const std::string& path);

        static std::string get(const std::string& path, const std::string& key);
};

#endif
