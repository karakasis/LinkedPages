#include <iostream>
#include "InputParser.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " ARGUMENT" <<endl;
        return 1;
    }

    switch(atoi(argv[1])){
        case 1 :
            {
            //kataskevi antikeimenou array
            cout<<"array"<<endl;
            InputParser parser;
            parser.read();
            break;
            }
        case 2:
            {
            //AVL
            cout<<"AVL"<<endl;
            break;
            }
        case 3:
            {
            //hashtable
            cout<<"hashtable"<<endl;
            break;
            }
        default:
            cout<<"Invalid user input.";

    }

    //cout<<argc<<" "<<argv[0]<<" "<<argv[1]<<endl;
    return 0;
}
