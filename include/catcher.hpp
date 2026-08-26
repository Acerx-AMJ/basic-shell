#ifndef CATCHER_HPP
#define CATCHER_HPP

#include <string>
#include <vector>

class Catcher
{
public:
   Catcher() = default;
   ~Catcher() = default;

   // Insert a new error in the vector
   void insert(const std::string& error);

   // Insert a new error and instantly display it
   void error(const std::string& error);

   // Clear all errors without displaying them
   void clear();

   // Check if there are no errors
   bool empty() const;

   // Display all accumulated errors and return a boolean based on if any
   // errors were shown
   bool display();

private:
   std::vector<std::string> errors;
};

#endif // CATCHER_HPP
