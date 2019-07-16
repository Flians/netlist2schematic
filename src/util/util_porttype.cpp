#include <algorithm>
#include "include/graph/port.h"

namespace ns {
/**
* Returns the next side in clockwise order.
*
* @return the next side in clockwise order
*/
PortType toPortType(const std::string &type) {
    std::string low;
    transform(type.begin(),type.end(),low.begin(),::tolower);
    if(low == "input")
    {
        return PortType::INPUT;
    } else if (low == "output") {
        return PortType::OUTPUT;
    } else if (low == "inout") {
        return PortType::INOUT;
    } else {
        return PortType::UNDEFINED;
    }
}

}
