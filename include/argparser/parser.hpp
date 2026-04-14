#ifndef ARGPARSER_PARSER_HPP
#define ARGPARSER_PARSER_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>

namespace ArgParser {

    enum class ErrorType {
        NO_ERROR,
        INVALID_ARGUMENT, 
        MISSING_OPTION,
        MISSING_REQUIRED_ARGUMENT
        
    };

    struct ValidArgumentType {
        std::string argDefinition;
        bool required;
    };

    class Parser {
        private:
            std::map<std::string, ValidArgumentType> validArguments;
            std::vector<std::string> arguments;
            std::pair<ErrorType, std::string> error;

            std::vector<std::pair<std::string, std::string>> parsedArguments;
        public:
            Parser();

            int add_validArgument(std::string argName, std::string argDefinition, bool required = false);
            bool rem_validArgument(std::string argName);
            const std::map<std::string, ValidArgumentType>& get_validArguments() const;
            
            bool add_argument(std::string arg);
            int search_argument(std::string arg) const;
            bool rem_argument(size_t idx);
            const std::vector<std::string>& get_arguments() const;

            const std::vector<std::pair<std::string, std::string>>& get_parsedArguments() const;

            const std::pair<ErrorType, std::string>& get_error() const;

    };

}

#endif
