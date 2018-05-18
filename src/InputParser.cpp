#include "InputParser.h"
#include "Array.h"
#include "AVL.h"
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
    infile.open("input_test.txt",std::fstream::in|std::fstream::ate);

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

        Array arr(1); //< 1 stands for dynamic allocation step
        int _last;

        //std::fstream infile = startLoader();


        int _length;

    std::fstream infile;
    infile.open("input_test.txt",std::fstream::in|std::fstream::ate);

    infile.seekg(0,ios_base::end);
    _length = infile.tellg();
    _length = sizeof(char) * _length * 0.001;
    //cout<<_length<<endl;
    infile.seekg(0, ios_base::beg);
    ez::ezRateProgressBar<int> p(_length);
    p.units = "KB";
    p.start();


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
        arr.sortConnectedLinks();
        //  ~TEST~
        std::cout<<endl;
        arr.show(arr.pairs);
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

void InputParser::readToAVL(){

        AVL<AVL<int>> avl;
        AVL<int> *inner_avl;
        //AVL small;
        int _last;

        //std::fstream infile = startLoader();


        int _length;

    std::fstream infile;
    infile.open("input_test.txt",std::fstream::in|std::fstream::ate);

    infile.seekg(0,ios_base::end);
    _length = infile.tellg();
    _length = sizeof(char) * _length * 0.001;
    infile.seekg(0, ios_base::beg);

    ez::ezRateProgressBar<int> p(_length);
    p.units = "KB";
    p.start();

        if(infile.is_open()){
            //cout<<"File opened successfully"<<endl;

            while(infile >> c >> d){
                //arr.insertPage(c);
                //arr.insertLink(d);
                //avl.get(c);
                if(c == 3)
                    true;
                inner_avl = avl.insert_link(c)->self;
                inner_avl->insert_link(d);

                //arr.makePair(c,d);
                _last = infile.tellg();
                _last = sizeof(char) * _last * 0.001;
                p.update(_last);
            }

        }
        else{
            cout<<"File could not open properly"<<endl;
        }
        std::ofstream out("test.txt", std::ofstream::out);
        //avl.get(10)->self->delete_link(2);
        //avl.delete_link(10);
        //avl.printTree(out);
        for(int i=0; i<10; i++){
            inner_avl = avl.get(i)->self;
            if(inner_avl!=NULL){
                out<<i<<" : ";
                inner_avl -> printTree(out);
            }
        }
        //inner_avl = avl.get(3)->self;
        //avl.printTree(out);
        //inner_avl ->printTree(out);
        out.close();
        //std::cout<<out.rdbuf();



        /*
        arr.sortLinks();
        arr.sortConnectedLinks();
        //  ~TEST~
        std::cout<<endl;
        arr.show(arr.pairs);
        arr.show(arr.connectedPairs);


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

        arr.show(arr.pairs);
        arr.show(arr.connectedPairs);
        //  ~TEST~

        arr.printer();
        */
}
