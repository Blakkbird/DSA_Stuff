#include <iostream>
using namespace std;
void bubSort(int array[], int l)
{
    
    for(int i=0;i<l-1;i++)
    {
        bool swapped=false;
        for(int j=0;j<l-i-1;j++)
        {
            if(array[j]>array[j+1])
            {
                int t=array[j];
                array[j]=array[j+1];
                array[j+1]=t;
                swapped=true;
            }
        }
            if(swapped==false){break;}
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

    bubSort(array,len);
    printer(array,len);
    return 0;
}