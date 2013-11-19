#include <string> 

std::size_t found = str.find(str2);
if (found!=std::string::npos)
    std::cout << "first found at: " << found << '\n';

str.replace(str.find(str2),str2.length(),"new word");
