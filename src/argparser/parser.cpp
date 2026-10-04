#include <argparser/parser.hpp>

#include <vector>
#include <string>

namespace ArgParser {
    using namespace std;
    
    Parser::Parser() {
    }

    // operations with member "validArguments"
    bool Parser::add_validArgument(
            string argName, vector<string> argFlags, 
            bool isBoolFlag, bool required) {

        if(this->search_validArgument(argName) != -1) {
            return false;
        }
        ValidArgument argument;
        argument.isBoolFlag = isBoolFlag;
        argument.flags = argFlags;
        argument.name = argName;
        argument.required = required;
        this->validArguments.push_back(argument);
        return true;
    }

    int Parser::search_validArgument(string argName) const {
        int i = 0;
        for(const auto &x: this->validArguments) {
            if(x.name == argName) {
                return i;
            }
            i++;
        }
        return -1;
    }

    bool Parser::rem_validArgument(size_t idx) {
        validArguments.erase(validArguments.begin() + idx); 
        return true;
    }

    const vector<ValidArgument>& Parser::get_validArguments() const {
        return this->validArguments;
    }

    // operations with member "arguments"
    void Parser::add_argument(const string& arg) {
       this->arguments.push_back(arg);
       return;
    }

    int Parser::search_argument(string arg) const {
        int i = 0;
        for(const auto &x: this->arguments) {
            if(x == arg) {
                return i;
            }
            i++;
        }
        return -1;
    }

    bool Parser::rem_argument(size_t idx) {
        if(idx >= this->arguments.size()) {
            return false;
        }
        this->arguments.erase(this->arguments.begin() + idx);
        return true;
    }

    const vector<string>& Parser::get_arguments() const {
        return this->arguments;
    }

    // getter for member "parsedArguments"
    const vector<ParsedArgument>& Parser::get_parsedArguments() const {
        return this->parsedArguments;
    }

    // getter for member "error"
    const Error& Parser::get_error() const {
        return this->error;
    }

    // parse method
    bool Parser::parse() {
        //TODO implementation of "parse" method
        
    }

}
