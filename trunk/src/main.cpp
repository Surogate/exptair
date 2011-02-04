/* 
 * File:   main.cpp
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:14 PM
 */

#include <iostream>
#include "Ai.h"
#include "AParser.hpp"

int main(int ac, char** av) {
    Ai topClass;
    std::string path;

    if (ac >= 2) {
        for (int i = 1; i < ac; i++) {
            path = av[i];
            if (topClass.loadPath(path)) {
                std::cout << "load " << path << " ok !!§§" << std::endl;
            }
        }
        topClass.forward();
    }

    topClass.backward();
    return 0;
}

