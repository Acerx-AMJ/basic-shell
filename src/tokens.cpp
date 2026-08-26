#include "tokens.hpp"
#include "commands.hpp"

Lexer::Lexer(Catcher& catcher, std::string& source, fs::path& cwd)
   : catcher(catcher), source(source), cwd(cwd) {}

std::vector<Token>& Lexer::tokenize()
{
   const auto size = this->source.size();

   for (size_t i = 0; i < size; ++i)
   {
      char ch = this->source.at(i);

      if (isspace(ch))
         continue;
      else if (ch == '&' && i + 1 < size && this->source.at(i + 1) == '&')
      {
         Token logical_and {Token::logical_and, "&&"};
         this->tokens.push_back(logical_and);
         ++i;
      }
      else if (ch == '|' && i + 1 < size && this->source.at(i + 1) == '|')
      {
         Token logical_or {Token::logical_or, "||"};
         this->tokens.push_back(logical_or);
         ++i;
      }
      else if (ch == ';')
      {
         Token semicolon {Token::semicolon, ";"};
         this->tokens.push_back(semicolon);
      }
      else if (isalnum(ch) || ch == '_' || ch == '/' || ch == '"' || ch == '.')
      {
         std::string string;
         bool is_string = false;

         if (ch == '"')
         {
            is_string = true;
            ++i;
         }

         for (; i < size; ++i)
         {
            ch = this->source.at(i);

            if ((!is_string && !isalnum(ch) && ch != '_' && ch != '/' && ch != '.') || (is_string && ch == '"'))
            {
               --i;
               break;
            }
            if (ch == '\\')
            {
               if (i + 1 >= size)
                  break;

               ++i;
               ch = this->source.at(i);

               if (ch == 'n')
                  string += '\n';
               continue;
            }

            string += ch;
         }

         if (is_string && ch != '"')
         {
            this->catcher.insert("Unterminated string: '"s + string + "'."s);
            return tokens;
         }
         if (is_string)
            ++i;

         Token token {.lexeme = string};

         if (is_string)
            token.type = Token::string;
         else if (comm::commands.find(string) != comm::commands.end())
            token.type = Token::command;
         else
            token.type = Token::file;

         this->tokens.push_back(token);
      }
      else
      {
         this->catcher.insert("Unexpected character: '"s + std::string(1, ch) + "'."s);
         return tokens;
      }
   }
   return tokens;
}
