#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int partition(vector<int>& arr, int l, int h){ // try diff. pivot strategies
    int i=l-1;
    int pivot=arr[h];
    for(int j=l;j<h;j++){
        if(arr[j] < pivot){ // simple change for ascending or descending
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[h]); // sort pivot
    return i+1;
}
void quickSort(vector <int>& arr, int l, int h){
    if(l < h){
        int sortedIdx=partition(arr, l, h);

        quickSort(arr, l, sortedIdx-1);
        quickSort(arr, sortedIdx+1, h);
    }
}
int main(){
    vector <int> arr={4,2,6,3,1,8,5};
    int len=arr.size();

   quickSort(arr, 0, len-1);

    for(int x : arr){ // print
        cout << x << '\t';
    }

    return 0;
}