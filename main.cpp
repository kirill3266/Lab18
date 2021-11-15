#include <iostream>

#include <string>
#include <iostream>
#include "LFU.h"

int main() {
    LFUCache<std::string> first;
    first.Insert("Adam");
    first.Insert("Artur");
//first.Touch("Adam");
//first.Touch("Artur");
std::cout << first.ReplCandidate();
    return 0;
}