//Parses all the links from the input.txt to the program.

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <fstream>
#include <iostream>

#include "ezRateProgressBar.hpp"
#include "Array.h"
#include "AVL.h"


class InputParser
{
    public:
        int c,d;
        InputParser();
        virtual ~InputParser();
        Array readToArray();
        void readToAVL();

    protected:

    private:
        int a,b;
        ez::ezRateProgressBar<int> p;
        std::fstream startLoader();

};

#endif // INPUTPARSER_H
