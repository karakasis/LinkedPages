#include "InputParser.h"
#include "Array.h"

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

        Array ar;
        ifstream infile("input.txt");
        if(infile.is_open()){
            cout<<"File opened successfully"<<endl;
            while(infile >> c >> d){
                //cout<<c<<" "<<d<<endl;
                ar.insertLink(c);
                ar.insertLink(d);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        ar.show();



}
