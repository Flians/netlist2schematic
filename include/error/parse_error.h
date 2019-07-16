#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>
#include <string>

namespace ns {

class ParseError : public std::exception
{
   std::string errorMsg;
public:
    explicit ParseError(){}

    explicit ParseError(const std::string& errorMsg){
        this->errorMsg = errorMsg;
    }

    virtual ~ParseError() noexcept{}

    virtual const char* what() const noexcept;
};

}

#endif // PARSE_ERROR_H
