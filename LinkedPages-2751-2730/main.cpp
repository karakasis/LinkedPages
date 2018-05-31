#include <iostream>
#include <fstream>

#include "Controller.h"

using namespace std;
int main(int argc, char* argv[])
{
    std::ofstream out("output.txt", std::ofstream::out);
    out<<"";
    int arg;
    if(argc != 2){
        arg = 1;
        cerr << argv[0] << " requires 1 argument (1,2 or 3)" <<endl;
        cerr << "Running default argument instead : "<<arg;

    }else{
        cout << "Running: " << argv[0] << " with argument -"<<argv[1];
        arg = atoi(argv[1]);
    }
    if(arg == 1){
        cout << " -> Arrays"<< endl;
        out << " -> Arrays <-"<< endl;
    }else if(arg == 2){
        cout << " -> AVL"<< endl;
        out << " -> AVL <-"<< endl;

    }else if(arg == 3){
        cout << " -> Hash Table"<< endl;
        out << " -> Hash Table <-"<< endl;

    }else{
        cout << " -> Arrays (Default)"<< endl;
        out << " -> Arrays <-"<< endl;
    }
    Controller controller(arg);


    cout<<"Results saved in output.txt"<<endl;
    return 0;
}
