#ifndef ARGPARSER_PARSER_HPP
#define ARGPARSER_PARSER_HPP

#include <vector>
#include <string>

namespace ArgParser {

    enum class ErrorType {
        NO_ERROR,
        INVALID_ARGUMENT, 
        MISSING_OPTION,
        MISSING_REQUIRED_ARGUMENT
        
    };

    struct Error {
        ErrorType type = ErrorType::NO_ERROR;
        std::string argument = "";
    };

    struct ValidArgument {
        std::vector<std::string> flags;
        std::string name;
        bool isBoolFlag;
        bool required;
    };

    struct ParsedArgument {
        std::string name;
        std::string value;
    };

    class Parser {
        private:
            //std::map<std::string, ValidArgumentType> validArguments;
            std::vector<ValidArgument> validArguments;
            std::vector<std::string> arguments;
            Error error;

            std::vector<ParsedArgument> parsedArguments;
        public:
            Parser();

            bool add_validArgument(std::string argName, 
                    std::vector<std::string> argFlags, 
                    bool isBoolFlag = false, bool required = false);
            int search_validArgument(std::string argName) const;
            bool rem_validArgument(size_t idx);
            const std::vector<ValidArgument>& get_validArguments() const;
            
            void add_argument(const std::string& arg);
            int search_argument(std::string arg) const;
            bool rem_argument(size_t idx);
            const std::vector<std::string>& get_arguments() const;

            const std::vector<ParsedArgument>& get_parsedArguments() const;

            const Error& get_error() const;

            bool parse();

    };

}

#endif
