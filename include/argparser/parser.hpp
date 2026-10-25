#ifndef ARGPARSER_PARSER_HPP
#define ARGPARSER_PARSER_HPP

#include <vector>
#include <string>

namespace ArgParser {

    enum class ErrorType {
        NO_ERROR,
        INVALID_ARGUMENT, 
        NO_ARGUMENTS,
        MISSING_OPTION,
        MISSING_REQUIRED_ARGUMENT
        
    };

    struct Error {
        ErrorType type = ErrorType::NO_ERROR;
        std::string argument = "";
    };

    struct ValidArgument {
        std::string shortFlag = "";
        std::string longFlag = "";
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

            void set_error(ErrorType type, const std::string &arg);

        public:
            // deletion of the copy constructor
            Parser(Parser &copy) = delete;
            Parser& operator=(const Parser &copy) = delete;

            Parser();

            bool add_validArgument(std::string argName, 
                    std::string shortFlag, std::string longFlag = "", 
                    bool isBoolFlag = false, bool required = false);
            int searchByName_validArgument(const std::string &argName) const;
            int searchByShortFlag_validArgument(const std::string &flag) const;
            int searchByLongFlag_validArgument(const std::string &flag) const;
            bool rem_validArgument(size_t idx);
            const std::vector<ValidArgument>& get_validArguments() const;
            
            void add_argument(const std::string &arg);
            int search_argument(const std::string &arg) const;
            bool rem_argument(size_t idx);
            const std::vector<std::string>& get_arguments() const;

            const std::vector<ParsedArgument>& get_parsedArguments() const;
            int search_parsedArgument(const std::string &argName) const;

            const Error& get_error() const;

            bool parse();

    };

}

#endif
