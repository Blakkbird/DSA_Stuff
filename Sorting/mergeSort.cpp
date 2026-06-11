#include <iostream>
#include <vector>

using namespace std;

void merge(vector <int>& arr, int l, int m, int r){

    int n1=m+1-l, n2=r-m;

    vector <int> left(n1);
    vector <int> right(n2);

    for(int i=0;i<n1;i++)
        left[i]=arr[l+i];
    for(int i=0;i<n2;i++)
        right[i]=arr[m+1+i];

    int i,j,k;
    i=j=0;
    k=l;

    while(i < n1 && j < n2){
        if(left[i] < right[j]){
            arr[k]=left[i];
            i++;
        }else{
            arr[k]=right[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k]=left[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k]=right[j];
        j++;
        k++;
    }
    
}

void ms(vector <int>& arr, int l, int r){
    if(l < r){
        int m=(l+r)/2; // mid in odd, left mid in even

        ms(arr, l, m);
        ms(arr, m+1, r); // keep dividing until we hit base case

        merge(arr, l, m, r);
    }
}

int main(){
    vector <int> arr={5,7,2,3,0,1,9,11};
    int len=arr.size();

    ms(arr, 0, len-1);
    
    for(int x : arr)
        cout << x << '\t';
    return 0;
}