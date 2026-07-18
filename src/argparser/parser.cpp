#include <argparser/parser.hpp>

#include <vector>
#include <map>
#include <string>
#include <utility>


namespace ArgParser {
    using namespace std;
    
    Parser::Parser() : error(ErrorType::NO_ERROR, "") {
    }

    // operations with member "validArguments"
    bool Parser::add_validArgument(
            string argName, string argDefinition, bool required) {

        if(this->validArguments.contains(argName)) {
            return false;
        }
        ValidArgumentType argument;
        argument.argDefinition = argDefinition;
        argument.required = required;
        this->validArguments[argName] = argument;
        return true;
    }

    bool Parser::rem_validArgument(string argName) {
        if(!this->validArguments.contains(argName)) {
            return false;
        }
        this->validArguments.erase(argName);
        return true;
    }

    const map<string, ValidArgumentType>& Parser::get_validArguments() const {
        return this->validArguments;
    }

    // operations with member "arguments"
    void Parser::add_argument(const string& arg) {
       this->arguments.push_back(arg);
       return;
    }

    int Parser::search_argument(string arg) const {
        int i = 0;
        for(const auto x: this->arguments) {
            if(x == arg) {
               if(x == arg) {
                   return i;
               } 
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
    const vector<pair<string, string>>& Parser::get_parsedArguments() const {
        return this->parsedArguments;
    }

    // getter for member "error"
    const pair<ErrorType, string>& Parser::get_error() const {
        return this->error;
    }

    // parse method
    int Parser::parse() {
        //TODO implementation of "parse" method
    }

}
