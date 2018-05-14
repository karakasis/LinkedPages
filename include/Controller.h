#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Array.h"
#include <sstream>
#include <map>

class Controller
{
    public:
        Controller(int arg);
        virtual ~Controller();

    protected:

    private:
        void readCommands();
        void executeCommand(std::stringstream& cmd);
        int argSwitch;
        //enum class Commands;
        //std::map<std::string, Commands> s_mapStringToCommands;
        Array arr;
};

#endif // CONTROLLER_H
