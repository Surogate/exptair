/* 
 * File:   main.cpp
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:14 PM
 */

#include <iostream>
#include "Ai.h"
#include "AParser.hpp"

// bon il reste a faire le chainage arriere,
//a gérée le fait d'avoir une expression type A*B=C*D (actuellement il te vomit si tu met plus d'une lettre en sortie)

int main(int ac, char** av) {
    Ai topClass;
    std::string path;
    if (ac >= 2) {
        path = av[ac - 1];
    } else {
        std::cout << "base file path ?" << std::endl;
        std::cin >> path;
    }
    if (topClass.loadPath(path)) {
        topClass.forward();
        topClass.backward();
    }
    return 0;
}

