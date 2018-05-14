#include <iostream>
#include <fstream>

#include "Controller.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " ARGUMENT" <<endl;
        return 1;
    }

    Controller(atoi(argv[1]));

    //cout<<argc<<" "<<argv[0]<<" "<<argv[1]<<endl;
    return 0;
}
