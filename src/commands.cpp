#include "commands.hpp"
#include "version.hpp"
#include <fstream>

bool comm::cd(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_directory(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a directory after the 'cd' command."s);
      i += 2;
      return false;
   }
   cwd /= tokens.at(i + 1).lexeme;
   cwd = fs::canonical(cwd);

   i += 2;
   return true;
}

bool comm::curdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   printf("\n%s\n", cwd.c_str());
   ++i;
   return true;
}

bool comm::echo(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{  
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::string)
   {
      catcher.insert("Expected a string after the 'echo' command."s);
      i += 2;
      return false;
   }
   printf("%s\n", tokens.at(i + 1).lexeme.c_str());
   i += 2;
   return true;
}

bool comm::throw_f(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::string)
   {
      catcher.insert("Expected a string after the 'throw' command."s);
      i += 2;
      return false;
   }
   catcher.insert(tokens.at(i + 1).lexeme);
   i += 2;
   return false;
}

bool comm::clear(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   ++i;
   return !system("clear");
}

bool comm::clerr(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   ++i;
   catcher.clear();
   return true;
}

bool comm::quit(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   printf("\n\033[38;2;0;0;255mQuitting...\033[0m\n");
   ++i;
   exit(0);
}

bool comm::version(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   printf("\n\033[38;2;0;0;255mVersion: %s\n", version::string);
   printf("Version Date: %s\033[0m\n", version::date);
   ++i;
   return true;
}

bool comm::info(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   printf("\n\033[38;2;0;0;255mBasic Shell created by Daniel Vishnevsky.\n");
   printf("Version: %s\n", version::string);
   printf("Type 'help' for commands.\033[0m\n");
   ++i;
   return true;
}

bool comm::help(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   printf("\n\033[38;2;0;0;255mREPL commands:\n");
   printf("'quit'              - quit the program.\n");
   printf("'version'           - show the version.\n");
   printf("'info'              - show info about the program.\n");
   printf("'help'              - show command info.\n");

   printf("\nCommands:\n");
   printf("cd DIRECTORY        - change directory relatively to the passed in directory.\n");
   printf("curdir              - echo the current working directory.\n");
   printf("echo \"STRING\"       - echo to the terminal.\n");
   printf("throw \"STRING\"      - throw an error.\n");
   printf("clear               - clear the terminal.\n");
   printf("clerr               - clear errors.\n");
   printf("touch FILE          - create a new file.\n");
   printf("mkdir DIRECTORY     - create a new directory.\n");
   printf("cat FILE            - show file's contents.\n");
   printf("cp FILE DESTINATION - copy a file to the given destination.\n");
   printf("mv FILE DESTINATION - move a file to the given destination.\n");
   printf("rename NEW OLD      - rename a file.\n");
   printf("ls                  - list all files in the current directory.\n");
   printf("ls DIRECTORY        - list all files in the given directory.\n");
   printf("rm FILE             - remove a file.\n");
   printf("rmdir DIRECTORY     - remove a directory.\n");
   printf("wr FILE \"STRING\"    - write to the whole file.\n");
   printf("wren FILE \"STRING\"  - write to the end of the file.\n");
   printf("history             - show command history.\n");
   printf("clearhist           - clear command history.\n");

   printf("\nOperators:\n");
   printf("'&&'                - run the next command if the previous command was successful.\n");
   printf("'||'                - run the next command if the previous command was not successful.\n");
   printf("';'                 - run the next command no matter if the previous command was successful or not.\033[0m\n");
   ++i;
   return true;
}

bool comm::touch(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file)
   {
      catcher.insert("Expected a file after the 'touch' command."s);
      i += 2;
      return false;
   }

   if (!fs::exists(cwd / tokens.at(i + 1).lexeme))
   {
      std::ofstream file (cwd / tokens.at(i + 1).lexeme);
      file.close();
   }
   i += 2;
   return true;
}

bool comm::mkdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file)
   {
      catcher.insert("Expected a directory after the 'mkdir' command."s);
      i += 2;
      return false;
   }

   try
   {
      fs::create_directory(cwd / tokens.at(i + 1).lexeme);
   }
   catch (...)
   {
      catcher.insert("Could not create directory '"s + (cwd / tokens.at(i + 1).lexeme).string() + "'."s);
      i += 2;
      return false;
   }
   i += 2;
   return true;
}

bool comm::cat(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_regular_file(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid file after the 'cat' command."s);
      i += 2;
      return false;
   }

   std::fstream file (cwd / tokens.at(i + 1).lexeme);

   if (!file.is_open())
   {
      catcher.insert("File '"s + (cwd / tokens.at(i + 1).lexeme).string() + "' does not exist."s);
      i += 2;
      return false;
   }

   std::string line;
   while (std::getline(file, line))
      printf("%s\n", line.c_str());

   i += 2;
   return true;
}

bool comm::cp(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 2 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::exists(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected the first 'cp' command argument to be a valid file/directory.\n"s);
      i += 3;
      return false;
   }

   if (tokens.at(i + 2).type != Token::file)
   {
      catcher.insert("Expected the second 'cp' command argument to be a file.\n"s);
      i += 3;
      return false;
   }

   try
   {
      fs::copy(cwd / tokens.at(i + 1).lexeme, cwd / tokens.at(i + 2).lexeme);
   }
   catch (...)
   {
      catcher.insert("Could not copy file '"s + (cwd / tokens.at(i + 1).lexeme).string() + "'."s);
      i += 3;
      return false;
   }
   i += 3;
   return true;
}

bool comm::mv(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 2 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::exists(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected the first 'mv' command argument to be a valid file/directory.\n"s);
      i += 3;
      return false;
   }

   if (tokens.at(i + 2).type != Token::file || !fs::is_directory(cwd / tokens.at(i + 2).lexeme))
   {
      catcher.insert("Expected the second 'mv' command argument to be a valid directory.\n"s);
      i += 3;
      return false;
   }

   try
   {
      fs::copy(cwd / tokens.at(i + 1).lexeme, cwd / tokens.at(i + 2).lexeme);
      fs::remove(cwd / tokens.at(i + 1).lexeme);
   }
   catch (...)
   {
      catcher.insert("Could not move file '"s + (cwd / tokens.at(i + 1).lexeme).string() + "'."s);
      i += 3;
      return false;
   }
   i += 3;
   return true;
}

bool comm::rename(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 2 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::exists(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected the first 'rename' command argument to be a valid file/directory.\n"s);
      i += 3;
      return false;
   }

   if (tokens.at(i + 2).type != Token::file)
   {
      catcher.insert("Expected the second 'rename' command argument to be a file/directory.\n"s);
      i += 3;
      return false;
   }

   try
   {
      fs::rename(cwd / tokens.at(i + 1).lexeme, cwd / tokens.at(i + 2).lexeme);
   }
   catch (...)
   {
      catcher.insert("Could not rename file '"s + (cwd / tokens.at(i + 1).lexeme).string() + "'."s);
      i += 3;
      return false;
   }
   i += 3;
   return true;
}

bool comm::ls(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file)
   {
      for (const auto& file : fs::directory_iterator(cwd))
         printf("\033[38;2;0;0;255m%s\033[0m\n", file.path().filename().c_str());
      ++i;
      return true;
   }

   if (!fs::is_directory(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid directory after the 'ls' command."s);
      i += 2;
      return false;
   }

   for (const auto& file : fs::directory_iterator(cwd / tokens.at(i + 1).lexeme))
      printf("\033[38;2;0;0;255m%s\033[0m\n", file.path().filename().c_str());
   i += 2;
   return true;
}

bool comm::rm(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_regular_file(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid file after the 'rm' command."s);
      i += 2;
      return false;
   }
   fs::remove(cwd / tokens.at(i + 1).lexeme);
   i += 2;
   return true;
}

bool comm::rmdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 1 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_directory(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid directory after the 'rmdir' command."s);
      i += 2;
      return false;
   }
   fs::remove_all(cwd / tokens.at(i + 1).lexeme);
   i += 2;
   return true;
}

bool comm::wr(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 2 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_regular_file(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid file as the first argument after the 'wr' command."s);
      i += 3;
      return false;
   }

   if (tokens.at(i + 2).type != Token::string)
   {
      catcher.insert("Expected a string as a second argument after the 'wr' command."s);
      i += 3;
      return false;
   }

   std::ofstream file (cwd / tokens.at(i + 1).lexeme);
   file << tokens.at(i + 2).lexeme;
   file.close();

   i += 3;
   return true;
}

bool comm::wren(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (i + 2 >= tokens.size() || tokens.at(i + 1).type != Token::file || !fs::is_regular_file(cwd / tokens.at(i + 1).lexeme))
   {
      catcher.insert("Expected a valid file as the first argument after the 'wr' command."s);
      i += 3;
      return false;
   }

   if (tokens.at(i + 2).type != Token::string)
   {
      catcher.insert("Expected a string as a second argument after the 'wr' command."s);
      i += 3;
      return false;
   }

   std::ofstream file (cwd / tokens.at(i + 1).lexeme, std::ios::app);
   file << tokens.at(i + 2).lexeme;
   file.close();

   i += 3;
   return true;
}

bool comm::history(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (!fs::exists(".history.txt"s))
   {
      ++i;
      return true;
   }
   std::fstream history (".history.txt"s);
   std::string line;
   size_t index = 0;

   while (std::getline(history, line))
      printf("%3zu \033[38;2;0;0;255m%s\033[0m\n", ++index, line.c_str());
   history.close();

   ++i;
   return true;
}

bool comm::clearhist(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd)
{
   if (!fs::exists(".history.txt"s))
   {
      ++i;
      return true;
   }
   std::ofstream history (".history.txt"s);
   history.close();

   ++i;
   return true;
}
