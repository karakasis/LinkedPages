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
    //std::vector<std::vector<int>> pairs(300, std::vector<int>(10));

    pairs.reserve(300);
    //pairs(300);
}

Array::~Array()
{
    //dtor
}

std::vector<int> Array::getLinkedPages(std::vector<int> linkedPages){

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
    cout<<pairs.size()<<" is size"<<endl;
    if(pairs.size() <= page){ // then pairs doesnt include page
        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        pairs.push_back(aPair);
    }else{
        if(pairs.at(page).empty()){
            std::vector<int> aPair;
            aPair.push_back(page);
            aPair.push_back(link);
            pairs.insert(pairs.begin() + page,aPair);
        }else{
            //TODO check if we need to have only 1 copy of an ID and not multiple, will raise complexity by n
            pairs.at(page).push_back(link);
        }
    }
    /*
    int pos = binarySearch(pairs,0,pairs.size()-1,page);
    if(pos == -1){

        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        pairs.push_back(aPair);
        bubbleSort2d(pairs,pairs.size());

    }
    else{
         pairs[pos].push_back(link);
    }
    */
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
    myfile.open ("output.txt");

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

int Array::binarySearch(vector<vector<int>> arr, int l, int r, int x){
     if (r >= l)
   {
        int mid = l + (r - l)/2;

        // If the element is present at the middle
        // itself
        if (arr[mid][0] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid][0] > x)
            return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
   }

   // We reach here when element is not
   // present in array
   return -1;
}

void Array::swap1d(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
void Array::swap2d(vector *xp, vector *yp)
{
    vector temp = *xp;
    *xp = *yp;
    *yp = temp;
}
*/

// A function to implement bubble sort
//Sorts linked pages IDs
void Array::bubbleSort1d(vector<int> &arr, int n)
{
   int i, j;
   for (i = 1; i < n-1; i++)

       // Last i elements are already in place
       for (j = 1; j < n-i; j++)
           if (arr[j] > arr[j+1])
              swap1d(&arr[j], &arr[j+1]);
}

void Array::sortLinks(){
    for(int i=0;i<pairs.size();i=i+1){
        bubbleSort1d(pairs[i],pairs[i].size());
    }
}


//Sorts pages
void Array::bubbleSort2d(vector<vector<int>> &arr, int n){
    int i, j;
    for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j][0] > arr[j+1][0]){
            arr[j].swap(arr[j+1]);
           }

              //swap2d(&arr[j], &arr[j+1]);
}

void Array::deleteLink(int page, int link){
    int posPage = binarySearch(pairs,0,pairs.size()-1,page);
    if(posPage!=-1){
        std::vector<int> trimNode = getLinkedPages(pairs[posPage]);
        int posLink = binarySearch1D(trimNode,0,trimNode.size()-1,link);
        if(posLink!=-1){
            pairs[posPage].erase(pairs[posPage].begin() + posLink + 1);
            cout<<"deleted "<<link<<" from page "<<page<<endl;
            bubbleSort1d(pairs[posPage],pairs[posPage].size());
        }else{
            cout<<"link "<<link<<" in page "<<page<<" not found"<<endl;
        }
    }else{
        cout<<"page "<<page<<" not found"<<endl;
    }

}

void Array::insertLink(int page, int link){
    int posPage = binarySearch(pairs,0,pairs.size()-1,page);
    if(posPage!=-1){
        std::vector<int> trimNode = getLinkedPages(pairs[posPage]);
        int posLink = binarySearch1D(trimNode,0,trimNode.size()-1,link);
        if(posLink!=-1){
            cout<<"link "<<link<<" in page "<<page<<" already exists"<<endl;

        }else{
            pairs[posPage].push_back(link);
            bubbleSort1d(pairs[posPage],pairs[posPage].size());
            cout<<"added link "<<link<<" in page "<<page<<endl;
        }
    }else{
        cout<<"page "<<page<<" was created"<<endl;
        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        pairs.push_back(aPair);
        cout<<"added link "<<link<<" in page "<<page<<endl;
    }
}

int Array::binarySearch1D(vector<int> arr, int l, int r, int x){
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
            return binarySearch1D(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch1D(arr, mid+1, r, x);
   }

   // We reach here when element is not
   // present in array
   return -1;
}
