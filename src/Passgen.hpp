
#ifndef PASSGEN_HPP
#define PASSGEN_HPP

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

#endif // GEN_H
