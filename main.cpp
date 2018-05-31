#include <iostream>
#include <fstream>

#include "Controller.h"

using namespace std;
int main(int argc, char* argv[])
{
    std::ofstream out("output.txt", std::ofstream::out);
    out<<"";
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " requires 1 argument (1,2 or 3)" <<endl;
        cerr << "Running default argument instead : "<<3<<endl;
        Controller(3);
    }else{
        cout << "Running: " << argv[0] << " with argument -"<<argv[1]<<endl;
        Controller(atoi(argv[1]));
    }

    cout<<"Results saved in output.txt"<<endl;
    return 0;
}
