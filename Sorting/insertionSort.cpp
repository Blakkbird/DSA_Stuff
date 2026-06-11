#include <iostream>
using namespace std;
void inserSort(int array[], int l)
{
    for(int i=1;i<l;i++)
    {
        int key=array[i];
        int j=i-1;

        while(key>array[j] && j>=0)
        {
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=key;
    }
}
void printer(int array[], int l)
{
    for(int i=0;i<l;i++)
    {cout<<array[i]<<" ";}
}
int main()
{
    int array[]={2,1,44,23,16,3,0,8};
    int len=sizeof(array)/sizeof(int);

    inserSort(array,len);
    printer(array,len);
    return 0;
}
/*

*/