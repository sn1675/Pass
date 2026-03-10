#include "Crypto.hpp"
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>
#include <fstream>
//#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

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

/*std::vector<unsigned char> Crypto::aes256Encrypt(const std::string& mdp, const std::vector<unsigned char>& key){

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("EVP_CIPHER_CTX_new failed");

    std::vector<unsigned char>  iv(16);
    if (!RAND_bytes(iv.data(), iv.size()))
        throw std::runtime_error("IV generation failed");

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data()))
        throw std::runtime_error("EncryptInit failed");

    std::vector<unsigned char> ciphertext(mdp.size() + 16);

    int len = 0, ciphertext_len = 0;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(mdp.data()), mdp.size());
    ciphertext_len += len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);

    // prepend IV
    std::vector<unsigned char> output;
    output.insert(output.end(), iv.begin(), iv.end());
    output.insert(output.end(), ciphertext.begin(), ciphertext.end());

    return output;
}

std::string Crypto::aes256Decrypt(const std::vector<unsigned char>& encrypted, const std::vector<unsigned char>& key) {
    if (encrypted.size() < 16)
        throw std::runtime_error("Invalid encrypted data");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("EVP_CIPHER_CTX_new failed");

    const unsigned char* iv = encrypted.data();
    const unsigned char* ciphertext = encrypted.data() + 16;
    int ciphertext_len = encrypted.size() - 16;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv))
        throw std::runtime_error("DecryptInit failed");

    std::vector<unsigned char> plaintext(ciphertext_len + 16);
    int len = 0;
    int plaintext_len = 0;

    EVP_DecryptUpdate(
        ctx,
        plaintext.data(),
                      &len,
                      ciphertext,
                      ciphertext_len
    );
    plaintext_len += len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
        throw std::runtime_error("Wrong password or corrupted data");

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return std::string(
        reinterpret_cast<char*>(plaintext.data()),
                       plaintext_len
    );
}

std::vector<unsigned char> Crypto::deriveKey(const std::string& password, const std::vector<unsigned char>& salt, int iterations) {
    std::vector<unsigned char> key(32);

    if (!PKCS5_PBKDF2_HMAC(password.c_str(),
                           password.size(),
                           salt.data(),
                           salt.size(),
                           iterations,
                           EVP_sha256(),
                           key.size(),
                           key.data()
    )) {
        throw std::runtime_error("PBKDF2 failed");
    }

    return key;
}*/


