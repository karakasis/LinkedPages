#include "Array.h"
#include "ezRateProgressBar.hpp"

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
Array::Array()
{
    reAllocVector();
    reAllocConnectedVector();
}

Array::~Array()
{

}

//IO Functions

void Array::insertLink(int page, int link){
    if(pairs.size()<=page){
        cout<<"page "<<page<<" was created"<<endl;
        makePair(page,link);
        cout<<"added link "<<link<<" in page "<<page<<endl;
    }else{
        if(!pairs.at(page).empty()){
            std::vector<int> trimNode = findNeighbors(pairs[page]);
            int posLink = binarySearch(trimNode,1,trimNode.size()-1,link);
            if(posLink!=-1){
                cout<<"link "<<link<<" in page "<<page<<" already exists"<<endl;

            }else{
                pairs[page].push_back(link);
                bubbleSort(pairs[page],pairs[page].size());
                cout<<"added link "<<link<<" in page "<<page<<endl;
            }
        }else{
            cout<<"page "<<page<<" was created"<<endl;
            makePair(page,link);
            cout<<"added link "<<link<<" in page "<<page<<endl;
        }
    }
    insertConnectedLink(link,page);
}

void Array::deleteLink(int page, int link){
    if(pairs.size() <= page){
        cout<<"page "<<page<<" not found"<<endl;
    }else{
       if(!pairs.at(page).empty()){
            std::vector<int> trimNode = findNeighbors(pairs[page]);
            int posLink = binarySearch(trimNode,1,trimNode.size()-1,link);
            if(posLink!=-1){
                pairs[page].erase(pairs[page].begin() + posLink + 1);
                cout<<"deleted "<<link<<" from page "<<page<<endl;
                bubbleSort(pairs[page],pairs[page].size());
            }else{
                cout<<"link "<<link<<" in page "<<page<<" not found"<<endl;
            }
        }else{
            cout<<"page "<<page<<" not found"<<endl;
        }
    }
    deleteConnectedLink(link,page);

}

std::vector<int> Array::findNeighbors(std::vector<int> neighbors){

    neighbors.erase(neighbors.begin());
    return neighbors;
}

int Array::findNumConnectedComponents(){
    //edw prepei na ginete kathe fora arxikopoiisi tou color me to plithos twn pages
    //giati mporei na exei proigithei insert i delete
    color = new int[connectedPairs.size()];
    for(int i =0;i<connectedPairs.size();i=i+1){
        color[i]=1; //oloi oi komvoi white(arxikopoiisi)
    }
    int cc=DFS();
    return cc;
}

//components

void Array::makePair(int page, int link){

    if(pairs.size() <= page){ // then pairs doesnt include page
        do{
            reAllocVector();
        }while(pairs.size() <= page);
        //and since we came here vector cell will be empty so no need to check more
        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        pairs[page] = aPair;
    }else{
        if(pairs.at(page).size()==0){
            std::vector<int> aPair;
            aPair.push_back(page);
            aPair.push_back(link);
            pairs[page] = aPair;
        }else{
            //TODO check if we need to have only 1 copy of an ID and not multiple, will raise complexity by n
            pairs.at(page).push_back(link);
        }
    }
    makeConnectedPairStart(page,link);
}

void Array::makeConnectedPairStart(int page, int link){ // see arguments are reversed when called

    if(connectedPairs.size() <= page){ // then pairs doesnt include page
        do{
            reAllocConnectedVector();
        }while(connectedPairs.size() <= page);
        //and since we came here vector cell will be empty so no need to check more
        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        connectedPairs[page] = aPair;
    }else{
        if(connectedPairs.at(page).size()==0){
            std::vector<int> aPair;
            aPair.push_back(page);
            aPair.push_back(link);
            connectedPairs[page] = aPair;
        }else{
            //TODO check if we need to have only 1 copy of an ID and not multiple, will raise complexity by n
            //where n are the links of page
            int n = binarySearch(connectedPairs.at(page),1,connectedPairs.at(page).size()-1,link);
            if(n == -1){
                connectedPairs.at(page).push_back(link);
            }
        }
    }
    makeConnectedPairEnd(link,page);
}

void Array::makeConnectedPairEnd(int page, int link){ // see arguments are reversed when called

    if(connectedPairs.size() <= page){ // then pairs doesnt include page
        do{
            reAllocConnectedVector();
        }while(connectedPairs.size() <= page);
        //and since we came here vector cell will be empty so no need to check more
        std::vector<int> aPair;
        aPair.push_back(page);
        aPair.push_back(link);
        connectedPairs[page] = aPair;
    }else{
        if(connectedPairs.at(page).size()==0){
            std::vector<int> aPair;
            aPair.push_back(page);
            aPair.push_back(link);
            connectedPairs[page] = aPair;
        }else{
            //TODO check if we need to have only 1 copy of an ID and not multiple, will raise complexity by n
            //where n are the links of page
            int n = binarySearch(connectedPairs.at(page),1,connectedPairs.at(page).size()-1,link);
            if(n == -1){
                connectedPairs.at(page).push_back(link);
            }
        }
    }

}

void Array::deleteConnectedLink(int page, int link){
    if(connectedPairs.size() <= page){
        cout<<"page "<<page<<" not found"<<endl;
    }else{
       if(!connectedPairs.at(page).empty()){
            std::vector<int> trimNode = findNeighbors(connectedPairs[page]);
            int posLink = binarySearch(trimNode,1,trimNode.size()-1,link);
            if(posLink!=-1){
                connectedPairs[page].erase(connectedPairs[page].begin() + posLink + 1);
                cout<<"deleted "<<link<<" from page "<<page<<endl;
                bubbleSort(connectedPairs[page],connectedPairs[page].size());
            }else{
                cout<<"link "<<link<<" in page "<<page<<" not found"<<endl;
            }
        }else{
            cout<<"page "<<page<<" not found"<<endl;
        }
    }
}

void Array::insertConnectedLink(int page, int link){
    if(connectedPairs.size()<=page){
        cout<<"page "<<page<<" was created"<<endl;
        makeConnectedPairStart(page,link);
        cout<<"added link "<<link<<" in page "<<page<<endl;
    }else{
        if(!connectedPairs.at(page).empty()){
            std::vector<int> trimNode = findNeighbors(connectedPairs[page]);
            int posLink = binarySearch(trimNode,1,trimNode.size()-1,link);
            if(posLink!=-1){
                cout<<"link "<<link<<" in page "<<page<<" already exists"<<endl;

            }else{
                connectedPairs[page].push_back(link);
                bubbleSort(connectedPairs[page],connectedPairs[page].size());
                cout<<"added link "<<link<<" in page "<<page<<endl;
            }
        }else{
            cout<<"page "<<page<<" was created"<<endl;
            makeConnectedPairStart(page,link);
            cout<<"added link "<<link<<" in page "<<page<<endl;
        }
    }
}

void Array::sortLinks(){
    for(int i=0;i<pairs.size();i=i+1){
        bubbleSort(pairs[i],pairs[i].size());
    }
    sortConnectedLinks();
}

void Array::sortConnectedLinks(){
    for(int i=0;i<connectedPairs.size();i=i+1){
        bubbleSort(connectedPairs[i],connectedPairs[i].size());
    }
}

void Array::reAllocVector(){
    const int x =pairs.size();
    for(int i = x; i< x+300; i++){
        pairs.insert(pairs.begin() +i,std::vector<int>(0));
    }
}

void Array::reAllocConnectedVector(){
    const int x = connectedPairs.size();
    for(int i = x; i< x+300; i++){
        connectedPairs.insert(connectedPairs.begin() +i,std::vector<int>(0));
    }
}

//utilities

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

// A function to implement bubble sort
//Sorts linked pages IDs
void Array::bubbleSort(vector<int> &arr, int n)
{
   int i, j;
   for (i = 1; i < n-1; i++)

       // Last i elements are already in place
       for (j = 1; j < n-i; j++)
           if (arr[j] > arr[j+1])
              swapCells(&arr[j], &arr[j+1]);
}

void Array::swapCells(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//colors: 1->White, 2->Gray, 3->Black
//kathe fora pou ekteleitai vriskei mia sinektiki sinistwsa kai tin markarei
//counter me arithmo ektelesis tis= arithmos S.S.
int Array::DFS(){
    int counter=0;
    color = new int[connectedPairs.size()];
    for(int i =0;i<connectedPairs.size();i=i+1){
        color[i]=1; //oloi oi komvoi white(arxikopoiisi)
    }
    for(int j=0;j<connectedPairs.size();j=j+1){
        if(color[j]==1){
            DFSvisit(j);
            counter=counter+1;
        }
    }
    return counter;
}

//Vriskei sindedemenous komvous tou u(emmesa kai amesa) kai tous markarei.
void Array::DFSvisit(int u){
    color[u]=2;
    vector<int> neighbors = findNeighbors(connectedPairs[u]); //paizei na einai kenos kai na exei thema
    for(int k =0;k<neighbors.size();k=k+1){
        if(color[k]==1){
            DFSvisit(k);
        }

    }
    color[u]=3;
}

void Array::show(std::vector<std::vector<int>> vec){
    int i;
    cout<<endl;
    for(std::vector<int> &node : vec){
        if(!node.empty()){
            std::cout<<"["<<node[0]<<"] -> [";
            for(int i=1;i<node.size();i=i+1){
                std::cout<<" "<<node[i];
            }
            std::cout<<" ]"<<std::endl;
        }
    }
    cout<<endl;
}

void Array::printer(){
    ofstream myfile;
    std::string line;
    ostringstream s;
    myfile.open ("output.txt");

    for(std::vector<int> &node : pairs){
        if(!node.empty()){
            s.str("");
            s.clear();

            s << node[0] << "," << node.size()-1 ;
            for(int i=1;i<node.size();i=i+1){
                s << "," << node[i] ;
            }
            s << "\n" ;
            std::string line(s.str());
            myfile << line;

        }

    }

    myfile.close();
}
