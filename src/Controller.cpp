#include "Controller.h"
#include "InputParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

Controller::~Controller()
{
    //dtor
}

/// Enum for String values we want to switch on
enum class Commands
{
    ReadData,
    InsertLink,
    DeleteLink,
    FindNeighbors,
    FindNumConnectedComponents
};

/// Map from strings to enum values
map<string, Commands> s_mapStringToCommands =
{
    { "READ_DATA", Commands::ReadData },
    { "INSERT_LINK", Commands::InsertLink },
    { "DELETE_LINK", Commands::DeleteLink },
    { "FIND_NEIGHBORS", Commands::FindNeighbors },
    { "FIND_NUM_CONNECTED_COMPONENTS", Commands::FindNumConnectedComponents },
};

/// Map from enum values to strings
map<Commands, string> s_mapCommandsToString
{
    {Commands::ReadData, "READ_DATA"},
    {Commands::InsertLink, "INSERT_LINK"},
    {Commands::DeleteLink, "DELETE_LINK"},
    {Commands::FindNeighbors, "FIND_NEIGHBORS"},
    {Commands::FindNumConnectedComponents, "FIND_NUM_CONNECTED_COMPONENTS"},
};

void Controller::readCommands(){
    fstream infile;
    infile.open("commands.txt",std::fstream::in);

    string cmd;
    string b; string c;
    stringstream ss;

    if(infile.is_open()){
        while(getline(infile,cmd)){\
            ss.str(cmd);
            executeCommand(ss);
            ss.str("");
            ss.clear();
        }
    }
}

void Controller::executeCommand(stringstream& ss){
    /*
    InputParser parser;
    arr = parser.readToArray();
    avl = parser.readToAVL();

    arr.findNumConnectedComponents();
    arr.deleteLink(0,5);
    avl.print_connected_cmd();
    avl.get(0).remove(5);
    arr.findNumConnectedComponents();
    avl.print_connected_cmd();
    //cout<<"Cloning AVL.."<<endl;
    //AVL<AVL<int>> clone(avl);
*/

    vector<int> ints;  //container to store ints
    vector<string> strings;  //container to store strings
    split(ss.str().c_str(),ints,strings);

    Commands cmd = s_mapStringToCommands[strings.at(0)];

    if(argSwitch == 1)
            switch(cmd){
                case Commands::ReadData :
                {
                    InputParser parser;
                    arr = parser.readToArray();
                   break;
                }
                case Commands::InsertLink :
                {
                    arr.insertLink(ints.at(0),ints.at(1));
                    arr.findNeighbors(ints.at(0));
                   break;
                }
                case Commands::DeleteLink :
                {
                    arr.deleteLink(ints.at(0),ints.at(1));
                    arr.findNeighbors(ints.at(0));
                   break;
                }
                case Commands::FindNeighbors :
                {
                    arr.findNeighbors(ints.at(0));
                   break;
                }
                case Commands::FindNumConnectedComponents :
                {
                    arr.findNumConnectedComponents();
                   break;
                }
                default:
                    cout<<"Invalid user input.";
                }
    else if(argSwitch == 2)
            switch(cmd){
                case Commands::ReadData :
                {
                    InputParser parser;
                    avl = parser.readToAVL();
                   break;
                }
                case Commands::InsertLink :
                {
                    avl.createLink(ints.at(0),ints.at(1));
                   break;
                }
                case Commands::DeleteLink :
                {
                    avl.deleteLink(ints.at(0),ints.at(1));
                   break;
                }
                case Commands::FindNeighbors :
                {
                    //avl.findNeighbors(ints.at(1));
                    cout<<"under development"<<endl;
                   break;
                }
                case Commands::FindNumConnectedComponents :
                {
                    ofstream out("test.txt", ofstream::out);
                    //avl.print_all_tree(out);
                    avl.connected(avl,cout);
                   break;
                }
                default:
                    cout<<"Invalid user input.";

                }
    else if(argSwitch == 3)
        cout<<"hashtable--"<<endl;
    else
        cout<<"Invalid user input.";

}

vector<string> Controller::split(const char* str, vector<int> &ints, vector<string> &strings)
{

    vector<string> result;
    char space = ' ';
    char tab = '\t';
    int i =0;

        const char *begin = str;

        while( (*str != space && *str!= tab ) && *str){//look for string command
           str++;
        }
        strings.push_back(string(begin, str));
        //cout<<"["<<strings[0]<<"]";

        str++;
        const char *begin2 = str;
        while( (*str != space && *str!= tab ) && *str){//look for int
           str++;
        }
        ints.push_back(atoi(string(begin2,str).c_str()));
        //cout<<" ["<<ints[0]<<"]";

        str++;
        const char *begin3 = str;
        while( (*str != space && *str!= tab ) && *str){//look for int
           str++;
        }
        ints.push_back(atoi(string(begin3,str).c_str()));
        //cout<<" ["<<ints[1]<<"]";

        /*
        istringstream is( test );
        int n;
        while( is >> n ) {
             // do something with n
             ints.push_back(n);
        }
*/



    return result;

}
