#include "InputParser.h"
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
    //f.open("intput.txt",ios::in);
        //if(f.is_open()){
        ifstream infile("input.txt");
        if(infile.is_open()){
            std::cout<<"File opened successfully"<<std::endl;
            while(infile >> a >> b){
                cout<<a<<" "<<b<<endl;
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
}
