/**
 * Copyright (c) 2026 Jerome Alexander Korf (Github: Jimpansen234)
 *
 * This project is licensed under the GNU LGPL v3.0
 * with the SPDX-identifier: LGPL-3.0-or-later WITH LGPL-3.0-linking-exception
 *
 * Full exception terms ale provided in the LICENSE file at the root
 */

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

            void set_error(ErrorType type, std::string_view arg);

        public:
            // deletion of the copy constructor
            Parser(const Parser &copy) = delete;
            Parser& operator=(const Parser &copy) = delete;

            Parser();

            bool add_validArgument(std::string argName, 
                    std::string shortFlag, std::string longFlag = "", 
                    bool isBoolFlag = false, bool required = false);
            int searchByName_validArgument(std::string_view argName) const;
            int searchByShortFlag_validArgument(std::string_view flag) const;
            int searchByLongFlag_validArgument(std::string_view flag) const;
            bool rem_validArgument(size_t idx);
            const std::vector<ValidArgument>& get_validArguments() const;
            
            void add_argument(const std::string &arg);
            int search_argument(std::string_view arg) const;
            bool rem_argument(size_t idx);
            const std::vector<std::string>& get_arguments() const;

            const std::vector<ParsedArgument>& get_parsedArguments() const;
            int search_parsedArgument(std::string_view argName) const;

            const Error& get_error() const;

            bool parse();

    };

}

#endif
