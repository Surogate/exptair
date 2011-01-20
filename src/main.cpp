/* 
 * File:   main.cpp
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:14 PM
 */

#include <iostream>
#include "Ai.h"

int main(int ac, char** av) {
    Ai topClass;

    if (ac == 1) {
        topClass.loadPath(av[1]);
    }
    else {
        std::string path;
        std::cout << "base file path ?" << std::endl;
        std::cin >> path;
        topClass.loadPath(path);
    }
    topClass.forward();
    topClass.backward();
    return 0;
}

