#include "InputParser.h"
#include "Array.h"
#include "AVL.hpp"
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

void InputParser::startLoader(std::fstream& infile){
    int _length;

    //std::fstream infile;
    //infile.open("input.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_shuffled.txt",std::fstream::in|std::fstream::ate);
    //infile.open("input_test.txt",std::fstream::in|std::fstream::ate);
    infile.open("input_small.txt",std::fstream::in|std::fstream::ate);
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

        Array arr(1); //< 1 stands for dynamic allocation step
        int _last;

        std::fstream infile;
        startLoader(infile);


        if(infile.is_open()){
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
        std::cout<<endl;
        //arr.show(arr.pairs);
        //arr.show(arr.connectedPairs);
        //std::cout<<arr.pairs.size()<<" "<<arr.connectedPairs.size()<<endl;
    /*
        arr.findNumConnectedComponents();

        arr.deleteLink(0,3);
        arr.deleteLink(0,0);
        arr.deleteLink(7,3);

        arr.findNumConnectedComponents();

        arr.deleteLink(1,12);
        arr.deleteLink(0,1);

        arr.findNumConnectedComponents();

        arr.insertLink(0,3);
        arr.insertLink(12,0);
        arr.insertLink(0,0);

        arr.findNumConnectedComponents();

        //arr.show(arr.pairs);
        //arr.show(arr.connectedPairs);
        //  ~TEST~
*/
        arr.printer();
        return arr;
}
AVL<AVL<int>> InputParser::readToAVL(){

        AVL<AVL<int>> avl;
        int _last;

        std::fstream infile;
        startLoader(infile);


        if(infile.is_open()){
            while(infile >> c >> d){

                avl.add(c).add(d);
                avl.add(d).add(c);

                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        cout<<endl;
        cout<<endl;
        cout<<endl;
        std::ofstream out("test.txt", std::ofstream::out);
        //avl.print_all_tree(out);
        //avl.print_connected_cmd(avl);

        out.close();

        return avl;
}
