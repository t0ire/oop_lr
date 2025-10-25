#include "figure.h"

namespace figures {

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.printVertices(os);  
    return os;  
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.readFromStream(is); 
    return is; 
}

}