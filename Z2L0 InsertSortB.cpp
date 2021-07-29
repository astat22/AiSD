//Lista 0 Zadanie 2
//Zmodyfikowane sortowanie przez wstawianie
//Wstawiaj jednocze�nie 2 elementy
//Jacek Mucha
//25 II 2013

#include <iostream>
#include <fstream>

using namespace std;

int powMoja (int base, int exponent )
{
    int wyniczek=1;
    for(int i3=exponent;i3>0;i3--)
            wyniczek=wyniczek*base;
    return wyniczek;
}

int main()
{    
    srand (time(NULL));
//Liczba por�wna�
    long long int ptr1;
//Liczba przypisa�
    long long int ptr2;
//Max/min przypisan
    long long int MXprz=0;
    long long int MNprz=0;
//Max/min porownan
    long long int MXpor=0;
     long long int MNpor=0;
//Sumy kontrolne
    long long int S1, S2;
//Rozmiar tablicy
    long int N;
    long int j;
    long long int x,y;
//�rednio porownan
    long long int ptr1S;
//Srednio przypisan
    long long int ptr2S;
    int Testy=50;
//Plik do danych
    fstream PTesty;
    PTesty.open("wynikiTb.txt",ios::out);
//Liczba test�w
    for(N=100;N<10000;N=N*2)
    {       
        S1=0;
        S2=0;
        MXpor=0;
        MNpor=100000000;
        MXprz=0;
        MNprz=100000000;
        long long int A[N];
        while(Testy>0)
        {
           ptr1=0;
           ptr2=0;
//Wype�nianie tablicy losowymi liczbami
           for(long int j2=0;j2<N;j2++)
           {
               A[j2]=0;
               for(int j3=0;j3<10;j3++)
               {
                   A[j2]=A[j2]+(rand()%2)*powMoja(2,j3);
               }    
           }
//InsertSortB
           for(long int i=0; i<N;i=i+2)
           {
              if(A[i]>A[i+1])
              {
                  x=A[i];
                  y=A[i+1];
              }
              else
              {
                  x=A[i+1];
                  y=A[i];
              }
              ptr1++;
              ptr2=ptr2+3;
              j=i-1;
              while(j>-1&&A[j]>x)
              {
                 A[j+2]=A[j];
                 j=j-1;
                 ptr2=ptr2+2;
                 ptr1++;
              }
              A[j+2]=x;
              A[j+1]=y;
              while(j>-1&&A[j]>y)
              {
                  A[j+1]=A[j];
                  j--;
                  ptr1++;
                  ptr2=ptr2+2;
              }
              ptr2++;
              ptr2++;
           }
           PTesty<<ptr1<<" "<<ptr2<<endl;
           if(ptr1>MXpor)
               MXpor=ptr1;
           if(ptr1<MNpor)
               MNpor=ptr1;
           if(ptr2>MXprz)
               MXprz=ptr2;
           if(ptr2<MNprz)
               MNprz=ptr2;
           Testy--;
           S1=S1+ptr1;
           S2=S2+ptr2;
        }
        Testy=50; //odnawianie liczby testow do petli
        ptr1S=S1/Testy;
        ptr2S=S2/Testy;
        cout<<"Dla N="<<N<<" Srednio porownan: "<<ptr1S<<endl<<"Srednio przypisan: "<<ptr2S<<endl;
        cout<<"Maksymalnie porownan: "<<MXpor<<" Minimalnie porownan: "<<MNpor<<endl;
        cout<<"Maksymalnie przypisan: "<<MXprz<<" Minimalnie przypisan: "<<MNprz<<endl<<endl;
        PTesty<<endl<<endl;
        PTesty<<"Dla N="<<N<<" Srednio porownan: "<<ptr1S<<endl<<"Srednio przypisan: "<<ptr2S<<endl;
        PTesty<<"Maksymalnie porownan: "<<MXpor<<" Minimalnie porownan: "<<MNpor<<endl;
        PTesty<<"Maksymalnie przypisan: "<<MXprz<<" Minimalnie przypisan: "<<MNprz<<endl<<endl<<endl;
    }
    PTesty.close();
    system("Pause");
    return 0;
}
