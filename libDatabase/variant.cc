#include "variant.h"
#include <iostream>
#include <string>

const std::string Variant::toString() const
{
    std::string result = "";
    switch (type) {
        case CHAR:  result += data.c; break;
        case SHORT: result = std::to_string(data.sh); break;
        case INT:   result = std::to_string(data.i); break;
        case LONG:  result = std::to_string(data.l); break;
        case FLOAT: result = std::to_string(data.f); break;
        case DOUBLE:result = std::to_string(data.d); break;
        case TIME:
            {
                char buffer[128] = {0};
                size_t len = strftime(buffer, sizeof(buffer), "%F %T", &data.t);
                result = std::string(buffer);
            }
            break;
        case STRING:
        default:    result = s; break;
    }
    return result;
}

