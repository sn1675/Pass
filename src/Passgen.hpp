#pragma once
#include <string>

class PassGen {
    public:
        struct Options {
            int len;
            bool maj;
            bool num;
            bool spe;
        };

    static std::string genratePassword(const Options& opts);

};
