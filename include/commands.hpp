#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "tokens.hpp"
#include <functional>
#include <unordered_map>

namespace comm
{
   bool cd(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool curdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool echo(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool throw_f(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool clear(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool clerr(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool quit(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool version(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool info(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool help(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool touch(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool mkdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool cat(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool cp(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool mv(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool rename(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool ls(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool rm(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool rmdir(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool wr(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool wren(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool history(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);
   bool clearhist(Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd);

   static inline std::unordered_map<std::string, std::function<bool(
      Catcher& catcher, std::vector<Token>& tokens, size_t& i, fs::path& cwd
   )>> commands
   {
      {"cd"s, cd}, {"curdir"s, curdir}, {"echo"s, echo}, {"throw"s, throw_f},
      {"clear"s, clear}, {"clerr"s, clerr}, {"quit"s, quit}, {"version"s, version},
      {"info"s, info}, {"help"s, help}, {"touch"s, touch}, {"mkdir"s, mkdir},
      {"cat"s, cat}, {"cp"s, cp}, {"mv"s, mv}, {"rename"s, rename}, {"ls"s, ls},
      {"rm"s, rm}, {"rmdir"s, rmdir}, {"wr"s, wr}, {"wren"s, wren},
      {"history"s, history}, {"clearhist"s, clearhist}
   };
} // namespace commands

#endif // COMMANDS_HPP
