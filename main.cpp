#include <iostream>
#include <fstream>

#include "Controller.h"
#include "InputParser.h"

using namespace std;
int main(int argc, char* argv[])
{
    /*
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " requires 1 argument (1,2 or 3)" <<endl;
        return 1;
    }else{
        cout << "Running: " << argv[0] << " with argument -"<<argv[1]<<endl;
        Controller(atoi(argv[1]));
    }
    */


    Controller(1);
    return 0;
}
