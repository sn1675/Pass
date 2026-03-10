
#ifndef APP_HPP
#define APP_HPP

#include <string>

class App {
    public:

    static void login();

    static void menu(const std::string& sessionPath, const std::string& sessionHash, const std::string& sessionSalt);
};

#endif // APP_H
