#include "catcher.hpp"
#include "commands.hpp"
#include "tokens.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main()
{
   printf("\033[38;2;0;0;255mBasic Shell.\033[0m\n");
   fs::path cwd = fs::current_path();
   Catcher catcher;

   while (true)
   {
      printf("%s > ", cwd.c_str());
      std::string input;
      std::getline(std::cin, input);

      std::fstream history (".history.txt"s, std::ios::app);
      history << input << '\n';

      Lexer lexer (catcher, input, cwd);
      auto& tokens = lexer.tokenize();

      if (catcher.display())
         continue;

      size_t i = 0;
      bool success = true;

      while (i < tokens.size())
      {
         if (tokens.at(i).type != Token::command)
         {
            catcher.error("Expected a command name, type 'help' for list of all commands."s);
            break;
         }

         success = comm::commands.at(tokens.at(i).lexeme)(catcher, tokens, i, cwd);
         bool cond = false;

         if (i >= tokens.size())
            break;

         if (tokens.at(i).type == Token::logical_and)
            cond = true;
         else if (tokens.at(i).type == Token::logical_or)
            cond = false;
         else if (tokens.at(i).type == Token::semicolon)
            cond = success = true;
         else
         {
            catcher.error("Expected either nothing or an operator at the end of a command."s);
            break;
         }

         if (cond == success) ++i; else break;
      }
      catcher.display();
      history.close();
   }
}
