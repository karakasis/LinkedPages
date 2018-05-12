//Parses all the links from the input.txt to the program.

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <fstream>
#include <iostream>




class InputParser
{
    public:
        int c,d;
        InputParser();
        virtual ~InputParser();
        void read();

    protected:

    private:
        int a,b;
        //ifstream f;

};

#endif // INPUTPARSER_H
