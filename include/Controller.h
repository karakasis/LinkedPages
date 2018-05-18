#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Array.h"
#include "AVL.h"
#include <sstream>
#include <map>

template <class T>
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
        void executeCommand(const char *cmd);
        int argSwitch;
        //enum class Commands;
        //std::map<std::string, Commands> s_mapStringToCommands;
        Array arr;
        AVL<AVL<node<T>>> avl;
        std::vector<std::string> split(const char *str, std::vector<int> &ints, std::vector<std::string> &strings);
};

#endif // CONTROLLER_H
