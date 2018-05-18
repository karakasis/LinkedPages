#include <iostream>
#include <fstream>

#include "Controller.h"
#include "InputParser.h"

using namespace std;
int main(int argc, char* argv[])
{
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " ARGUMENT" <<endl;
        return 1;
    }

    Controller(atoi(argv[1]));
    return 0;
}
