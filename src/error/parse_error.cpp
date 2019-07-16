#include "include/error/parse_error.h"

namespace ns {
const char* ParseError::what() const noexcept {
    return errorMsg.c_str();
}
}
