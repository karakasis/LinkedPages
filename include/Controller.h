#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Array.h"
#include "AVL.hpp"
#include "HashTable.h"

#include <sstream>
#include <map>

class Controller
{
    public:
        Controller(int arg){
            argSwitch = arg;
            readCommands();
        };

        virtual ~Controller();

    protected:

    private:
        void readCommands();
        void executeCommand(std::stringstream& ss);
        int argSwitch;
        //enum class Commands;
        //std::map<std::string, Commands> s_mapStringToCommands;
        Array arr;
        AVL<AVL<int>> avl;
        HashTable hashTable;
        //AVL<AVL<int>> clone;
        std::vector<std::string> split(const char* str, std::vector<int> &ints, std::vector<std::string> &strings);
};

#endif // CONTROLLER_H
