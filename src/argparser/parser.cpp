/**
 * Copyright (c) 2026 Jerome Alexander Korf (Github: Jimpansen234)
 *
 * This project is licensed under the GNU LGPL v3.0
 * with the SPDX-identifier: LGPL-3.0-or-later WITH LGPL-3.0-linking-exception
 *
 * Full exception terms ale provided in the LICENSE file at the root
 */

#include <argparser/parser.hpp>

#include <vector>
#include <string>
#include <string_view>

namespace ArgParser {
    using namespace std;

    void Parser::set_error(ErrorType type, const string &arg) {
        Error &err = this->error;
        err.type = type;
        err.argument = arg;
    }
    
    Parser::Parser() {
    }

    // operations with member "validArguments"
    bool Parser::add_validArgument(
            string argName, string shortFlag, string longFlag, 
            bool isBoolFlag, bool required) {
        if(shortFlag.empty() && longFlag.empty()) {
            return false;
        }

        if(this->searchByName_validArgument(argName) != -1) {
            return false;
        }
        
        ValidArgument argument;
        argument.isBoolFlag = isBoolFlag;
        argument.shortFlag = shortFlag;
        argument.longFlag = longFlag;
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

    int Parser::searchByShortFlag_validArgument(const string &flag) const {
        int i = 0;
        for(const auto &x: this->validArguments) {
            if(x.shortFlag == flag) {
                return i;
            }
            i++;
        }
        return -1;
    }

    int Parser::searchByLongFlag_validArgument(const string &flag) const {
        int i = 0;
        for(const auto &x: this->validArguments) {
            if(x.longFlag == flag) {
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
            i++;
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
            string_view argument = this->arguments[i];
            string value = "";
            string name = "";
            if(argument.size() <= 1) {
                set_error(ErrorType::INVALID_ARGUMENT, static_cast<string>(argument));
                return false;

            }
            if(argument[0] != '-') {
                set_error(ErrorType::INVALID_ARGUMENT, static_cast<string>(argument));
                return false;
            }

            if(argument[0] == '-' && argument[1] != '-') {
                argument.remove_prefix(1); 
                
                int validArgIndex;
                int j;
                ValidArgument validArg;
                bool boolflag;
                 
                for(j = 0;j < argument.size();j++) {
                    const char &c = argument[j];
                    validArgIndex = searchByShortFlag_validArgument(string(1,c));
                    if(validArgIndex == -1) {
                        set_error(ErrorType::INVALID_ARGUMENT,"-" + string(1,c));
                        return false;
                    }
                    
                    validArg = this->validArguments[validArgIndex];
                    boolflag = validArg.isBoolFlag;
                    name = validArg.name;
                    if(boolflag) {
                        value = "true";
                        ParsedArgument parsedArg;
                        parsedArg.value = value;
                        parsedArg.name = name;
                        this->parsedArguments.push_back(parsedArg);

                    } else {
                        break;
                    }

                }

                if(!boolflag) {
                    if(j < argument.size()-1) {
                        value = argument.substr(j+1);
                    } else if(i < this->arguments.size()-1) {
                        value = this->arguments[i+1];
                        i++;
                    } else {
                        set_error(ErrorType::MISSING_OPTION, "-" + string(1,argument[j]));
                        return false;
                    }
                
                    ParsedArgument parsedArg;
                    parsedArg.value = value;
                    parsedArg.name = name;
                    this->parsedArguments.push_back(parsedArg);
                }

            } else if(argument[0] == '-' && argument[1] == '-') {
                if(argument.size() == 2) {
                    set_error(ErrorType::INVALID_ARGUMENT, static_cast<string>(argument));
                    return false;
                }
                argument.remove_prefix(2);
                bool boolflag = true;
                if(argument.starts_with("no-")) {
                    boolflag = false;
                    argument.remove_prefix(3);
                }

                
                int equalAt = argument.find("=");
                bool hasEqual = false;
                if(equalAt != -1) {
                    value = argument.substr(equalAt+1);

                    argument = argument.substr(0, equalAt);
                    hasEqual = true;
                }

                int validArgIndex = this->searchByLongFlag_validArgument(static_cast<string>(argument));
                if(validArgIndex == -1) {
                    set_error(ErrorType::INVALID_ARGUMENT, static_cast<string>(argument));
                    return false;
                }

                const ValidArgument &validArg = this->get_validArguments()[validArgIndex];
                if(!(validArg.isBoolFlag || boolflag)) {
                    set_error(ErrorType::INVALID_ARGUMENT, "--no-" + static_cast<string>(argument));
                    return false;
                }

                if(validArg.isBoolFlag && hasEqual && value == "1") {
                    value = "true";
                } else if(validArg.isBoolFlag && hasEqual && value == "0") {
                    value = "false";
                }

                if(validArg.isBoolFlag && hasEqual && !(value == "true" || value == "false")) {
                    set_error(ErrorType::INVALID_ARGUMENT, "--" + static_cast<string>(argument));
                    return false;

                }

                
                if(validArg.isBoolFlag && !hasEqual) {
                    if(boolflag) value = "true"; else value = "false";
                    
                } else if(!validArg.isBoolFlag && !hasEqual && i + 1 == this->arguments.size()) {
                    set_error(ErrorType::MISSING_OPTION, "--" + static_cast<string>(argument));
                    return false;
                } else if(!validArg.isBoolFlag && !hasEqual) {
                    // thats too much nesting
                    value = this->arguments[i+1];
                    i++;
                }
                name = validArg.name;
                ParsedArgument parsedArg;
                parsedArg.value = value;
                parsedArg.name = name;
                this->parsedArguments.push_back(parsedArg);
                
            }
                
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
                set_error(ErrorType::MISSING_REQUIRED_ARGUMENT, x);
                return false;
            }
        }

        if(this->arguments.empty()) {
            set_error(ErrorType::NO_ARGUMENTS, "");
            return false;
        }
        return true;
    }

}
