#include "Locality.h"
#include <cstring>

Locality::Locality(const char* city, size_t count) {
    if (count > MAX_COUNT) {
        throw std::invalid_argument("Invalid number of citizens!");
    }
    _city = new char[strlen(city) + 1];
    strcpy(_city, city);
    _count = count;
}

std::ostream& operator<<(std::ostream& out, const Locality* vertex) {
    std::cout << "(" << vertex->getCity() << ", " << vertex->getCount() << ")";
    return (out);
}

std::ostream& operator<<(std::ostream& out, const Locality& vertex) {
    std::cout << "(" << vertex.getCity() << ", " << vertex.getCount() << ")";
    return (out);
}

Locality::~Locality() {
    std::cout<<"\ndl\n";
    delete[] _city;
}