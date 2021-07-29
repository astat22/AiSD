//Sortowanie przez scalanie
//wariant dzielenia tablicy na trzy cz�ci
//Zadanie 2 lista 1 z Przegl�du Zagadnie� Informatycznych
//Jacek Mucha
//8 III 2013
//oznaczenia zgodne z oznaczeniami na li?cie zada�
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
//iteratory licz�ce porownania i przypisania-zmienne globalne
//long int ptrComp, ptrAssign;
//scalanie
void Merge(long int A[], long int k, long int m, long int l)
{
    long int i, j, x, B[l];
    i=k;
    j=m+1;
    x=0;
    //ptrAssign=ptrAssign+3;
    while(i<=m||j<=l)
    {
        if(i>m)
        {
            B[x]=A[j];
            j++;
            //ptrComp=ptrComp+3;
        }//if i>m
        else
        {
            if(j>l)
            {
                B[x]=A[i];
                i++;
                //ptrComp=ptrComp+4;
            }//if j>l,i<=m
            else
            {
                if(A[i]<A[j])
                {
                    B[x]=A[i];
                    i++;
                }//if j<=l,i<=m,A[i]<A[j]
                else
                {
                    B[x]=A[j];
                    j++;
                }//j<=l,i<=m,A[i]>=A[j]
                //ptrComp=ptrComp+5;
            }//else j<=l,i<=m
        }//else i<=m
        //cout<<B[x]<<"  ";
        x++;
        //ptrAssign++;
    }//while
    //cout<<endl;
    for(i=k;i<l+1;i++)
    {
        A[i]=B[i-k];
        //ptrAssign++;
       //ptrComp++;
        //cout<<l<<" "<<k;
    }
    //ptrAssign++;
    //cout<<ptrAssign<<endl;
}//Merge
//sortowanie przez scalanie
void MergeSort(long int A[], long int k, long int l)
{
    long int m1, m2;
    if(k<l)
    {
        m1=k+(l-k)/3;
        m2=m1+(l-k)/3;
        //ptrAssign++;
        //ptrComp++;
        //cout<<l<<" "<<m1<<" "<<m2<<" "<<k<<endl;
        if(m1<m2)
        {
            MergeSort(A,k,m1);
        //cout<<"jestem";
        //system("Pause");
            MergeSort(A,m1+1,m2);
            MergeSort(A,m2+1,l);
            Merge(A,k,m1,m2);
            Merge(A,k,m2,l);
        }
        else
        {
            MergeSort(A,k,m1);
            MergeSort(A,m1+1,l);
            Merge(A,k,m1,l);
        }
        //cout<<ptrAssign<<"  ";
    }
}//MergeSort
//funkcja base^exponent dla int�w
int MyPow (int base, int exponent)
{
    int pow=1;
    for(int i3=exponent;i3>0;i3--)
            pow=pow*base;
    return pow;
}//MyPow
//wype�nianie tablicy losowymi liczbami
void RandTab(long int A[], long int N)
{
    srand (time(NULL));
    for(long int j=0;j<N;j++)
        {
            A[j]=0;
                for(int j2=0;j2<20;j2++)//losowanie liczby z rozk�adu jednostajnego za pomoc� systemu dw�jkowego
                {
                   A[j]=A[j]+(rand()%2)*MyPow(2,j2);
                }
                //cout<<A[j]<<"  ";
        }//for losowanie
        //cout<<endl;
        
}//RandTab
int main()
{
    srand (time(NULL));
//Plik do danych
    fstream PTests;
    PTests.open("wynikiAMerge_b.txt",ios::out);
//pomiar czasu
    //time_t t0,tk;
    clock_t Tk,T0,dt;
    //float dt;
//Rozmiar tablicy
    long long int N;
    for(N=10000;N<200000;N=N+2000)
    {
        long int A[N];
        RandTab(A,N);
        //for(long int i=0;i<N;i++) cout<<A[i]<<"  ";
        cout<<endl<<endl;
        //ptrComp=0;
        //ptrAssign=0;
        //time( & t0 );
        T0=clock();
        MergeSort(A,0,N-1);
        //time( & tk );
        //Tk=clock();
        dt=clock()-T0;
        cout<<"Rozmiar tablicy: "<<N<<" "<<"takty procesora: "<<(float)dt<<endl;//ptrComp<<"  "<<ptrAssign<<endl;
        PTests<<N<<"\t"<<(float)dt<<endl;//ptrComp<<"  "<<ptrAssign<<endl;
        //for(long int i=0;i<N;i++) cout<<A[i]<<"  ";
    }
    PTests.close();
    system("Pause");
    return 0;    
}
