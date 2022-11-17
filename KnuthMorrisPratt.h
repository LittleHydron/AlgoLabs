#ifndef ALGOLABS_KNUTHMORRISPRATT_H
#define ALGOLABS_KNUTHMORRISPRATT_H
#include<iostream>
namespace KMP{
    class KnuthMorrisPratt;
};
class KMP::KnuthMorrisPratt {
public:
    static int numberOfReps(std::string& data, std::string& pattern);
};
#include "KnuthMorrisPratt.cpp"
#endif //ALGOLABS_KNUTHMORRISPRATT_H
