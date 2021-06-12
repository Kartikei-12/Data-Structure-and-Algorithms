// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Utility Code Source

#include "Utility_/Utility_.hpp"

namespace self
{

exception::exception(std::string msg/* = ""*/) {
    message = "Exception: " + msg;
}
const char* exception::what() const throw() {
    return message.c_str();
}

}
