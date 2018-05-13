#include "InputParser.h"
#include "Array.h"
#include "ezRateProgressBar.hpp"

#include <fstream>
#include <iostream>


using namespace std;

InputParser::InputParser()
{
    //ctor
}

InputParser::~InputParser()
{
    //dtor
}

void InputParser::read(){

        Array arr;
        int _length, _last;
        //arr = new Array();
        //Array links;
        std::fstream infile;

        infile.open("input.txt",std::fstream::in|std::fstream::ate);
        infile.seekg(0,ios_base::end);
        _length = infile.tellg();
        infile.seekg(0, ios_base::beg);

        ez::ezRateProgressBar<int> p(_length);
        p.units = "MB";
        p.start();

        if(infile.is_open()){
            //cout<<"File opened successfully"<<endl;

            while(infile >> c >> d){
                //arr.insertPage(c);
                //arr.insertLink(d);
                arr.makePair(c,d);
                _last = infile.tellg();
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        //arr.show();
        arr.printer();
        //links.show();



}
