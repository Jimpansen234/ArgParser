#ifndef CGCONFIG_HPP
#define CGCONFIG_HPP

#include <vector>
#include <string>
#include "cgconfigtypes.hpp"

namespace cg {

    class Config {
        private:
            std::vector<std::string> argv;
            bool islibrary;
            bool useasm;
            bool uselibrarys;
            std::string sourcepath = "./src";
            std::string objectspath = "./obj";
            std::string outputpath = "./out";
            std::string includepath = "./include";
            std::string asmpath = "./asm";
            Compilertype compiler = Compilertype::GCC;
            
        public:
            Config(int argc, std::vector<std:string> argv);

    }

}

#endif
