
#include "Passgen.hpp"

#include <stdexcept>
#include <time.h>

std::string PassGen::genratePassword(const Options &opts){

    std::string let = "abcdefghijklmnopqrstuvwxyz";
    std::string majLet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numb = "0123456789";
    std::string spec = "!@#$%^&*()-_=+[]{};:,.<>?/";

    std::string mdp;

    if (opts.maj) let += majLet;
    if (opts.num) let += numb;
    if (opts.spe) let += spec;

    if(opts.len <= 0){
        throw std::invalid_argument("Le mdp doit etre > 0");
    }

    srand(time(NULL));

    mdp.reserve(opts.len);
    for(int i=0; i<opts.len; ++i){
        mdp += let[rand() % let.size()];
    }

    return mdp;
}

