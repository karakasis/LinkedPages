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

/// <summary>
/// Enum for String values we want to switch on
/// </summary>
enum class Commands
{
    ReadData,
    WriteIndex,
    InsertLink,
    DeleteLink,
    FindNeighbors,
    FindNumConnectedComponents
};

/// <summary>
/// Map from strings to enum values
/// </summary>
map<string, Commands> s_mapStringToCommands =
{
    { "READ_DATA", Commands::ReadData },
    { "WRITE_INDEX", Commands::WriteIndex },
    { "INSERT_LINK", Commands::InsertLink },
    { "DELETE_LINK", Commands::DeleteLink },
    { "FIND_NEIGHBORS", Commands::FindNeighbors },
    { "FIND_NUM_CONNECTED_COMPONENTS", Commands::FindNumConnectedComponents },
};

/// <summary>
/// Map from enum values to strings
/// </summary>
map<Commands, string> s_mapCommandsToString
{
    {Commands::ReadData, "READ_DATA"},
    {Commands::WriteIndex, "WRITE_INDEX"},
    {Commands::InsertLink, "INSERT_LINK"},
    {Commands::DeleteLink, "DELETE_LINK"},
    {Commands::FindNeighbors, "FIND_NEIGHBORS"},
    {Commands::FindNumConnectedComponents, "FIND_NUM_CONNECTED_COMPONENTS"},
};

void Controller::readCommands(){
    ifstream infile("commands.txt");
    string cmd;
    stringstream ss;
    //infile.open("commands.txt",fstream::in);
    /*
    if(infile.is_open()){
        while(getline(infile, cmd)){
                cout<<cmd;
            //stringstream ss(cmd);
            //stringstream ss;
            //ss << cmd;
            //ss.str("");
            //ss.clear();
            //ss << cmd << endl;
            //vector<int> ints;  //container to store ints
    //vector<string> strings;  //container to store strings
            //split(cmd.c_str(),ints,strings);
            executeCommand(cmd.c_str());
        }
    }
    */
    executeCommand(cmd.c_str());
}

void Controller::executeCommand(const char *cmd_ss){
    InputParser parser;
    //arr = parser.readToArray();
    avl = parser.readToAVL();
    /*
    vector<int> ints;  //container to store ints
    vector<string> strings;  //container to store strings
    istringstream ss( cmd_ss );
    cout<<cmd_ss;
    std::istringstream buf(cmd_ss);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> tokens(beg, end); // done!

    for(auto& s: tokens)
        std::cout << '"' << s << '"' << '\n';
        //comment above while
    while(true) {
      int intValue;
      char* stringValue;
      if(ss.eof())
        break;

      if(ss >> intValue) {
        ints.push_back(intValue);
      } else if (ss >> stringValue) {
        strings.push_back(stringValue);
      } else {
        cout << "Error: unknown value read in, not recognized as int or string" << endl;
        exit(-1);
      }
    }


    Commands cmd = s_mapStringToCommands[strings.at(0)];

    switch(argSwitch){
        case 1 :
            {

                switch(cmd){
                    case Commands::ReadData :
                    {
                        InputParser parser;
                        arr = parser.readToArray();
                       break;
                    }
                    case Commands::WriteIndex :
                    {
                        arr.printer();
                        exit(1);
                       break;
                    }
                    case Commands::InsertLink :
                    {
                        arr.insertLink(ints.at(0),ints.at(1));
                       break;
                    }
                    case Commands::DeleteLink :
                    {
                        arr.deleteLink(ints.at(0),ints.at(1));
                       break;
                    }
                    case Commands::FindNeighbors :
                    {
                        cout<<"under_development"<<endl;
                       break;
                    }
                    case Commands::FindNumConnectedComponents :
                    {
                        cout<<"under_development"<<endl;
                       break;
                    }
                    default:
                        cout<<"Invalid user input.";
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
    }
    */
}

vector<string> Controller::split(const char *str, vector<int> &ints, vector<string> &strings)
{

    vector<string> result;
    char space = ' ';
    char tab = '\t';
    int i =0;
    /*
        const char *begin = str;

        while( (*str != space || *str!= tab ) && *str){//look for string command
           cout<<"["<< *str<<"]";
           str++;
           i++;
        }
        strings.push_back(string(begin, str));
        string test = &str.substr(i);
        cout<<"["<<test<<"]";
        istringstream is( test );
        int n;
        while( is >> n ) {
             // do something with n
             ints.push_back(n);
        }


*/

    return result;

}
