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

    linkedPages.erase(linkedPages.begin());
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

void Array::makePair(int page, int link){
    int contains;
    /*
    for ( std::vector<int>  &node : pairs )
    {

       if(node[0] == page){
            //std::vector<int> linkedPages = getLinkedPages(node);
            node.push_back(link);
            contains = true;
            break;
       }
    }
    */
    contains = binarySearch(pairs,0,pairs.size()-1,page);
    if(contains == -1){

        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        pairs.push_back(aPair);
    }
    else{
         pairs[contains].push_back(link);
    }
}

void Array::show(){
    int i;

    for(std::vector<int> &node : pairs){
        std::cout<<"["<<node[0]<<"] -> [";
        for(int i=1;i<node.size();i=i+1){
            std::cout<<" "<<node[i];
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

    for(std::vector<int> &node : pairs){
        s.str("");
        s.clear();

        s << node[0] << "," << node.size()-1 ;
        for(int i=1;i<node.size();i=i+1){
            s << "," << node[i] ;
        }
        s << "\n" ;
        std::string line(s.str());
        myfile << line;

        //_last++;
        //p.update(_last);
    }

    myfile.close();
}

int Array::binarySearch(vector<int> arr, int l, int r, int x){
     if (r >= l)
   {
        int mid = l + (r - l)/2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
   }

   // We reach here when element is not
   // present in array
   return -1;
}
