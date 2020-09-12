
#ifndef INCLUDE_MYEXCEPTION_HPP_
#define INCLUDE_MYEXCEPTION_HPP_
// данный файл нужен для обработки исключительных ситуаций
#include "json.hpp"
#include <exception>

class Except : public exception
{
public:

    const char*what() const noexcept
    {
        return "Error: Wrong input information!!!\n";
    }
};


#endif 
