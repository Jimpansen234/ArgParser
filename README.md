# ArgParser

## 1. What is this?
This is my project "ArgParser".
Purpose of the ArgParser is, using the raw arguments, that were passed in the commandline
and transform them into a predictable output, to make validation of arguments easier.

Also: this is my first project I release to the general public. I hope it helps someone.

## 2. Why?
I am too lazy to rewrite a parsing mechanism every time in the main, so I made this.

## 3. Where is the documentation?
Well: This project told me 'why' you should write a documentation and what happens if you don't,
so there is no documentation.

## 4. How to use:
As of now, you have to compile this by yourself with a buildsystem of your choice.
The ArgParser namespace has a class "Parser".
You instantiate an object of this class with the default constructor `ArgParser::Parser::Parser()`.
Then you feed your so called "validArguments" into the parser using the `ArgParser::Parser::add_validArgument(std::string argName, std::string shortFlag, std::stringlongFlag = "", bool isBoolFlag = false, bool required = false)` method.
To parse the inline arguments, the parser also needs the arguments itself.
you can add them using the `ArgParser::Parser::add_argument(const std::string &arg)` method.
After that you need to call the `ArgParser::Parser::parse()` method. This will return you either true for success or false for failure.
When it returns false, you should check the `ArgParser::parser::get_error()` method, 
it will return you the error. `ArgParser::Error::type` is the "ErrorType" itself. 
Please look it up in the headerfile for now, until I come up with a basic manual.
`ArgParser::Error::argument` tells you the Argument, where the error occured so you can print it to the end user or something. As of now: `ArgParser::Parser::error.argument` remains empty if the ErrorType is `ArgParser::ErrorType::MISSING_REQUIRED_ARGUMENT`.
If the return value of the parsing is true, then you may look into the `ArgParser::Parser::get_parsedArguments()` method. This will return you a `std::vector` with all the parsed arguments. 
The vector consists of the type `ArgParser::ParsedArgument`. Every parsed argument
consists of the 2 values `std::string name` and `std::string value`.
The name will be what you have defined as `argName` and the value the coresponding value that was passed in the commandline.

## 5. About my coding
Please don't hate me, because I used `using namespace std;` in my parser.cpp.
It doesn't affect your code in any way, as I didn't write that line in my parser.hpp.

## 6. Licensing
I am Licensing this project to the general public under the terms of the GNU LGPL v3.0 with a static linking exception.
SPDX identifier: LGPL-3.0-linking-exception
Details about the exceptions are found in the LICENSE document.
For short: I don't care if you link it staticly or dynamicly but all remaining terms apply.

