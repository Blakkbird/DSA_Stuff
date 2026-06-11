#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void heapify(vector<int>& arr, int len, int ind){ // simple 2 changes for min heap/descending!
    int l=2*ind+1;
    int r=2*ind+2;
    int nxt=ind; // index of largest elem
    if(l < len && arr[l] > arr[nxt]){
        nxt=l;
    }
    if(r < len && arr[r] > arr[nxt]){
        nxt=r;
    }
    if(nxt != ind){
        swap(arr[nxt], arr[ind]);
        heapify(arr, len, nxt); // recurse to sort this branch
    }
}
void heapSort(vector <int>& arr){
    int len=arr.size();
    
    for(int i=len-1;i>0;i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0); // now len is i
    }
}
int main(){
    vector <int> arr={4,2,6,3,1,8,5};
    int len=arr.size();

    for(int i=len/2-1;i>=0;i--){ // create max heap
        heapify(arr, len, i);
    }
    for(int x : arr){ // print
        cout << x << '\t';
    }
    cout << "" << endl;
    heapSort(arr);

    for(int x : arr){ // print
        cout << x << '\t';
    }
    return 0;
}