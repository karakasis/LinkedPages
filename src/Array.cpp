#include "Array.h"
#include "ezRateProgressBar.hpp"

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
Array::Array()
{
    //ctor
}

Array::~Array()
{
    //dtor
}

std::vector<int> getLinkedPages(std::vector<int> linkedPages){
    linkedPages.erase(0);
    return linkedPages;
}

void Array::insertPage(int page){
    pages.push_back(page);
}

void Array::insertLink(int link){
    links.push_back(link);
}

/*
std::vector<int> Array::initVector(int link){
    std::vector< int > linksVector;
    linksVector.push_back(link);
    return linksVector;
}
*/

void Array::makePair(int linkPage, int link){
    bool contains = false;
    for ( std::vector<int>  &node : pairs )
    {

       if(node[0] == linkPage){
            //std::vector<int> linkedPages = getLinkedPages(node);
            node.push_back(link);
            contains = true;
            break;
       }
    }
    if(contains == false){

        std::vector<int> aPair;
        aPair.push_back(linkPage);
        aPair.push_back(link);
        pairs.push_back(aPair);
    }
}

void Array::show(){
    int i;

    for(std::pair<int,std::vector<int>> &node : pairs){
        std::cout<<"["<<node.first<<"] -> [";
        for(int &link : node.second){
            std::cout<<" "<<link;
        }
        std::cout<<" ]"<<std::endl;
    }
}

void Array::printer(){
    ofstream myfile;
    std::string line;
    ostringstream s;
    myfile.open ("arrays_printer.txt");

    //int _last,_length;
    //_last = 0;
    //_length = pairs.size();
    //ez::ezRateProgressBar<int> p(_length);
        //p.units = "MB";
        //p.start();

    for(std::pair<int,std::vector<int>> &node : pairs){
        s.str("");
        s.clear();

        s << node.first << "," << node.second.size() ;
        for(int &link : node.second){
            s << "," << link ;
        }
        s << "\n" ;
        std::string line(s.str());
        myfile << line;

        //_last++;
        //p.update(_last);
    }

    myfile.close();
}
