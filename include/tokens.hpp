#ifndef TOKENS_HPP
#define TOKENS_HPP

#include "catcher.hpp"
#include <filesystem>

using namespace std::string_literals;
namespace fs = std::filesystem;

struct Token
{
   enum Type : int8_t
   {
      file, string, command, logical_and, logical_or, semicolon
   };

   Type type;
   std::string lexeme;
};

class Lexer
{
public:
   Lexer(Catcher& catcher, std::string& source, fs::path& cwd);
   ~Lexer() = default;

   std::vector<Token>& tokenize();

private:
   Catcher& catcher;
   std::string& source;
   fs::path& cwd;
   std::vector<Token> tokens;   
};

#endif // TOKENS_HPP
