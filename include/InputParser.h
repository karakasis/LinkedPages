//Parses all the links from the input.txt to the program.

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <fstream>
#include <iostream>

#include "ezRateProgressBar.hpp"
#include "Array.h"
#include "AVL.hpp"


class InputParser
{
    public:
        int c,d;
        InputParser();
        virtual ~InputParser();


        Array readToArray();
        AVL<AVL<int>> readToAVL();

    protected:

    private:
        ez::ezRateProgressBar<int> p;
        int a,b;
        void startLoader(std::fstream& infile);

};

#endif // INPUTPARSER_H