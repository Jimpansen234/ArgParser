#ifndef CRAWLGEN_CONFIG_HPP
#define CRAWLGEN_CONFIG_HPP

#include <vector>
#include <string>

#include <crawlgen/configtypes.hpp>

namespace CrawlGen {

    class Config {
        private:
            std::vector<std::string> argv;
            std::vector<std::string> librarys;

            bool islib = false;
            bool useasm = false;
            bool haslibs = false;

            std::string sourcePath = "./src";
            std::string objectsPath = "./obj";
            std::string outputPath = "./out";
            std::string includePath = "./include";
            std::string asmPath = "./asm";

            Compilertype compiler = Compilertype::GCC;
            
        public:
            Config(std::vector<std::string> &argv);
            
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
