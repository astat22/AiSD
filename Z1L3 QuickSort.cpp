//Quicksort
//Zadanie 1 lista 3 z Przegl¹du Zagadnieñ Informatycznych
//Jacek Mucha
//2 IV 2013
//oznaczenia zgodne z oznaczeniami na wyk³adzie

#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std;

void RandArray(long int Array[], long int A_length, int exponent)
{
    srand (time(NULL));
    for(long int j=0;j<A_length;j++)
    {
        Array[j]=0;
        for(int j2=0;j2<exponent;j2++)//losowanie liczby z rozk³adu jednostajnego za pomoc¹ systemu dwójkowego
        {
            Array[j]=Array[j]+(rand()%2)*(int)pow(2,j2);
        }//for losowanie liczby dla komorki w tablicy
    }//for cala tablica
}//RandArray

long int Partition(long int A[], long int k, long int l)
{
    long int i=k-1,j=l+1,x=A[k],pom;
    //cout<<A[k];
    while(1)
    {
        i++;
        while(A[i]<x)
        {
            ++i;
        }//while A[i]>=x
        j--;
        while(A[j]>x)
        {
            --j;
        }//while A[j]<=x
        if(i<j )
        {
            pom=A[i];
            A[i]=A[j];
            A[j]=pom;
            //for(long int i=0;i<10;i++) cout<<A[i]<<"  "; cout<<endl; // !!!!!!!!!!tu wypisanie tablicy po ka¿dej podmianie!!!!!!!!
            //cout<<"."; 
            //if(x!=A[j] && x!=A[i] &&(j==k || i==k)) { i++; j--;}
            //j--;
        }//if i<j
        else
            return j;
        //time--;
    }//while(true)
    return j;
}//Partition

void QuickSort(long int A[],long int k,long int l)
{
    long int m;
    if(k<l)
    {
        m=Partition(A,k,l);
        //cout<<k<<" "<<m<<" "<<l<<endl;
        QuickSort(A,k,m);
        QuickSort(A,m+1,l);
    }
    //cout<<m;
    //system("Pause");
}//QuickSort

int main()
{
    srand (time(NULL));
//Plik do danych
    fstream PTests;
    PTests.open("wynikiAQuick.txt",ios::out);
//pomiar czasu
    clock_t Tk,T0,dt;
//Rozmiar tablicy
    long int N;
    for(N=17;N<202;N=N+2000)
    {
        long int A[N];//={22,1,1,0,9,9,45,46,10,0,4};;
        RandArray(A,N,4); 
        //A[3]=A[7];
        for(long int i=0;i<N;i++) cout<<A[i]<<"  ";
        cout<<endl<<endl;
        T0=clock();
        QuickSort(A,0,N-1);
        dt=clock()-T0;
        //cout<<N<<" "<<(float)dt<<endl;//ptrComp<<"  "<<ptrAssign<<endl;
        //PTests<<N<<" "<<(float)dt<<endl;//ptrComp<<"  "<<ptrAssign<<endl;
        cout<<endl<<endl;
        for(long int i=0;i<N;i++) cout<<A[i]<<"  ";
    }
    PTests.close();
    system("Pause");
    return 0; 
}
