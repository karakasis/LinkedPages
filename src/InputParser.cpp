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

void InputParser::startLoader(std::fstream& infile){
    int _length;
    infile.open("input.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_shuffled.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_test.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_small.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_v_small.txt",std::fstream::in|std::fstream::ate);
    infile.seekg(0,ios_base::end);
    _length = infile.tellg();
    _length = sizeof(char) * _length * 0.001;
    //cout<<_length<<endl;
    infile.seekg(0, ios_base::beg);
    p.n = _length;
    p.units = "KB";
    p.start();
}


Array InputParser::readToArray(){

        Array arr; //< 1 stands for dynamic allocation step
        int _last;

        std::fstream infile;
        startLoader(infile);


        if(infile.is_open()){
            while(infile >> c >> d){
                arr.createLink(c,d);

                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        arr.sortLinks();
        return arr;
}

AVL<AVL<int>> InputParser::readToAVL(){

        AVL<AVL<int>> avl;
        int _last;

        std::fstream infile;
        startLoader(infile);


        if(infile.is_open()){
            while(infile >> c >> d){

                avl.createLink(c,d);

                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }

        return avl;
}

HashTable InputParser::readToHashTable(){

        HashTable hashTable;
        int _last;

        std::fstream infile;
        startLoader(infile);


        if(infile.is_open()){
            while(infile >> c >> d){
                hashTable.createLink(c,d);

                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        return hashTable;
}
