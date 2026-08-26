#include "catcher.hpp"

void Catcher::insert(const std::string& error)
{
   this->errors.push_back(error);
}

void Catcher::error(const std::string& error)
{
   this->insert(error);
   this->display();
}

void Catcher::clear()
{
   this->errors.clear();
}

bool Catcher::empty() const
{
   return this->errors.empty();
}

bool Catcher::display()
{
   auto count = this->errors.size();

   if (count == 0)
      return false;

   printf("\n\033[38;2;255;0;0m%zu error%c occurred:\033[38;2;255;125;125m\n", count, (count == 1 ? char{} : 's'));
   for (const auto& error : this->errors)
      printf("%s\n", error.c_str());

   printf("\033[0m\n");
   this->errors.clear();
   return true;
}
