#include <iostream>
#include <iostream>
using namespace std;
void selSort(int array[], int l)
{
    for(int i=0;i<l-1;i++)
    {
        int min=i;
        for(int j=i+1;j<l;j++)
        {
            if(array[j]<array[min])
            min=j;
        }
        int t=array[min];
        array[min]=array[i];
        array[i]=t;
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

    selSort(array,len);
    printer(array,len);
    return 0;
}