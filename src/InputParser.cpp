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

std::fstream InputParser::startLoader(){
    int _length;

    std::fstream infile;
    infile.open("input.txt",std::fstream::in|std::fstream::ate);

    infile.seekg(0,ios_base::end);
    _length = infile.tellg();
    _length = sizeof(char) * _length * 0.001;
    infile.seekg(0, ios_base::beg);

    ez::ezRateProgressBar<int> p(_length);
    p.units = "KB";
    p.start();

    return infile;
}


Array InputParser::readToArray(){

        Array arr;
        int _last;

        std::fstream infile = startLoader();

        if(infile.is_open()){
            //cout<<"File opened successfully"<<endl;

            while(infile >> c >> d){
                //arr.insertPage(c);
                //arr.insertLink(d);
                arr.makePair(c,d);
                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        arr.sortLinks();
        //  ~TEST~

        arr.deleteLink(0,3);
        arr.deleteLink(0,0);
        arr.deleteLink(7,3);
        arr.deleteLink(1,12);
        arr.deleteLink(0,1);
        arr.insertLink(0,3);
        arr.insertLink(12,0);
        arr.insertLink(0,0);

        arr.show();
        //  ~TEST~
        arr.printer();
        //links.show();

        return arr;
}
