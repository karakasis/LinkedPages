#include "Array.h"
#include "ezRateProgressBar.hpp"

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//IO Functions

void Array::insertLink(int page, int link){
    cout<<"running: insertLink("<<page<<","<<link<<");"<<endl;
    if(pairs.size()<=page){
        cout<<"page "<<page<<" was created"<<endl;
        makePair(page,link);
        cout<<"added link "<<link<<" in page "<<page<<endl;
    }else{
        if(!pairs.at(page).empty()){
            int posLink = binarySearch(pairs[page],1,pairs[page].size()-1,link);
            if(posLink!=-1){
                cout<<"link "<<link<<" in page "<<page<<" already exists"<<endl;

            }else{
                pairs[page].push_back(link);
                //quickSort(pairs[page],1,pairs[page].size() - 1);
                bubbleSort(pairs[page],pairs[page].size());
                cout<<"added link "<<link<<" in page "<<page<<endl;
            }
        }else{
            cout<<"page "<<page<<" was created"<<endl;
            makePair(page,link);
            cout<<"added link "<<link<<" in page "<<page<<endl;
        }
    }
}

void Array::deleteLink(int page, int link){
    cout<<"running: deleteLink("<<page<<","<<link<<");"<<endl;
    if(pairs.size() <= page){
        cout<<"page "<<page<<" not found"<<endl;
    }else{
       if(!pairs.at(page).empty()){
            int posLink = binarySearch(pairs[page],1,pairs[page].size()-1,link);
            if(posLink!=-1){
                pairs[page].erase(pairs[page].begin() + posLink + 1);
                cout<<"deleted "<<link<<" from page "<<page<<endl;
                //quickSort(pairs[page],1,pairs[page].size() - 1);
                bubbleSort(pairs[page],pairs[page].size());
            }else{
                cout<<"link "<<link<<" in page "<<page<<" not found"<<endl;
            }
        }else{
            cout<<"page "<<page<<" not found"<<endl;
        }
    }
}

void Array::findNeighbors(int page){
    cout<<"running: findNeighbors("<<page<<");"<<endl;
    if(pairs.at(page).size()!=0){
        cout<<"[ ";
        for(int n : findNeighbors(pairs.at(page))){
            cout<<n<<" ";
        }
        cout<<"]"<<endl;
    }
    else
        cout<<"page "<<page<<" not found"<<endl;

    cout<<endl;
}

std::vector<int> Array::findNeighbors(std::vector<int> neighbors){

    neighbors.erase(neighbors.begin());
    return neighbors;
}

void Array::findNumConnectedComponents(){
    cout<<"running: findNumConnectedComponents();"<<endl;

    //trigger cloning
    cout<<"Cloning ..."<<endl;
    Array cloned(*this);
    duplicateLinks(cloned);
    cout<<"Finished cloning "<<endl;

    //edw prepei na ginete kathe fora arxikopoiisi tou color me to plithos twn pages
    //giati mporei na exei proigithei insert i delete    cout<<
    //cout<<cloned.pairs.size()<<endl;
    //cout<<pairs.size()<<endl;
    color = new int[cloned.pairs.size()];

    for(int i =0;i<cloned.pairs.size();i++){
        color[i]=1; //oloi oi komvoi white(arxikopoiisi)
    }
    int cc=DFS(cloned);
    delete [] color;
    cout<<"Connected Components: "<<cc<<endl;
    cout<<endl;
}

//components

void Array::makePair(int page, int link){

    if(pairs.size() <= page){ // then pairs doesnt include page
        allocationStep = page - pairs.size() + 1;
        reAllocVector();
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
}

void Array::sortLinks(){
    cout<<"Sorting..."<<endl;
    for(int i=0;i<pairs.size();i=i+1){
        //std::vector<int> trimNode = findNeighbors(pairs[page]);
        //quickSort(findNeighbors(pairs[i]),0,pairs[i].size()-1);
        bubbleSort(pairs[i],pairs[i].size());
    }
}

void Array::reAllocVector(){
    const int x =pairs.size();
    for(int i = x; i< x+allocationStep; i++){
        pairs.insert(pairs.begin() +i,std::vector<int>(0));
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
                swap(arr[j], arr[j+1]);
              //swapCells(&arr[j], &arr[j+1]);
}

void Array::quickSort(vector<int> &arr, int left, int right) {

  int i = left, j = right;
  int tmp;
  int pivot = arr[(left + right) / 2];

  /* partition */
  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i <= j) {
      swapCells(&arr[j], &arr[j+1]);
      i++;
      j--;
    }
  };

  /* recursion */
  if (left < j)
    quickSort(arr, left, j);
  if (i < right)
    quickSort(arr, i, right);
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
int Array::DFS(Array& cloned){
    int counter=0;
    for(int j=0;j<cloned.pairs.size();j++){
        if(color[j]==1 && cloned.pairs[j].size()!=0){
            DFSvisit(j, cloned);
            counter=counter+1;
        }
    }
    return counter;
}

//Vriskei sindedemenous komvous tou u(emmesa kai amesa) kai tous markarei.
void Array::DFSvisit(int u, Array& cloned){
    color[u]=2;
    //cout<<"here "<<endl;
    vector<int> neighbors = cloned.findNeighbors(cloned.pairs[u]); //paizei na einai kenos kai na exei thema
    //cout<<"here "<<endl;
    for(int k =0;k<neighbors.size();k++){
        if(color[neighbors[k]]==1){
            DFSvisit(neighbors[k],cloned);
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
