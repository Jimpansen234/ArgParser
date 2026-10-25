#ifndef CRAWLGEN_CONFIG_HPP
#define CRAWLGEN_CONFIG_HPP

#include <vector>
#include <string>

namespace CrawlGen {

    enum class Compilertype {
        GCC,
        CLANG,
        MSVC
    };

    class Config {
        private:
            std::vector<std::string> librarys;

            bool islib = false;
            bool useasm = false;
            bool haslibs = false;
            bool isMinGW = false;
            bool isMinGW_w64= false;

            std::string sourcePath = "./src";
            std::string objectsPath = "./obj";
            std::string outputPath = "./out";
            std::string includePath = "./include";
            std::string libpath = "./lib";
            std::string asmPath = "./asm";
            std::string shell = "/bin/sh";

            Compilertype compiler = Compilertype::GCC;
            
        public:
            Config();
            
            std::vector<std::string> get_librarys();
            bool isLibrary();
            bool usesAsm();
            bool hasLibrarys();
            std::string get_sourcePath();
            std::string get_objectsPath();
            std::string get_outputPath();
            std::string get_includePath();
            std::string get_asmPath();
            Compilertype get_compiler();

    };

}

#endif
