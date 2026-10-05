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

        if(this->searchByName_validArgument(argName) != -1) {
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

    int Parser::searchByName_validArgument(const string &argName) const {
        int i = 0;
        for(const auto &x: this->validArguments) {
            if(x.name == argName) {
                return i;
            }
            i++;
        }
        return -1;
    }

    int Parser::searchByFlag_validArgument(const string &flag) const {
        int i = 0;
        for(const auto &x: this->validArguments) {
            for(const auto &y: x.flags) {
                if(y == flag) {
                    return i;
                }
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

    int Parser::search_argument(const string &arg) const {
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

    int Parser::search_parsedArgument(const string &argName) const {
        int i = 0;
        for(const auto &x: this->parsedArguments) {
            if(x.name == argName) {
                return i;
            }
        }
        return -1;
    }

    // getter for member "error"
    const Error& Parser::get_error() const {
        return this->error;
    }

    // parse method
    bool Parser::parse() {
        for(int i = 0; i < this->arguments.size(); i++) {
            int validArgIndex = this->searchByFlag_validArgument(this->arguments[i]);
            if(validArgIndex == -1) {
                Error &err = this->error;
                err.type = ErrorType::INVALID_ARGUMENT;
                err.argument = this->arguments[i];
                return false;
            }
            const ValidArgument &validArg = this->validArguments[validArgIndex];
            ParsedArgument parsedArg;
            parsedArg.name = validArg.name;
            if(validArg.isBoolFlag) {
                parsedArg.value = true;
            } else {
                if(this->arguments.size() <= i+1) {
                    Error &err = this->error;
                    err.type= ErrorType::MISSING_OPTION;
                    err.argument = this->arguments[i];
                    return false;
                }
                parsedArg.value = this->arguments[i+1];
                i++;
            }
            this->parsedArguments.push_back(parsedArg);
        }
        
        vector<string> requiredArguments;
        for(const auto &x: this->validArguments) {
            // making a list of all required arguments
            if(x.required) {
                requiredArguments.push_back(x.name);
            }

        }

        for(const auto &x: requiredArguments) {
            if(search_parsedArgument(x) == -1) {
                Error &err = this->error;
                err.argument = x;
                err.type = ErrorType::MISSING_REQUIRED_ARGUMENT;
                return false;
            }
        }

        if(this->arguments.empty()) {
            Error &err = this->error;
            err.argument = "";
            err.type = ErrorType::NO_ARGUMENTS;
            return false;
        }
        return true;
    }

}
