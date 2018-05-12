#include "Array.h"

#include <vector>
#include <iostream>


Array::Array()
{
    //ctor
}

Array::~Array()
{
    //dtor
}

void Array::insertLink(int page1){
    std::vector<int>::iterator it;
    it = links.begin();
    links.insert(it,2,page1);
}

void Array::show(){
    int i;
    std::cout<<links.size()<<std::endl;
    for(i=0;i<links.size();i=i+1){
        std::cout<<links[i]<<std::endl;
    }
}
