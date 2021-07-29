//Lista 0 Zadanie 3
//Zmodyfikowane sortowanie przez wstawianie
//Nowy element porownuj wpierw ze srodkowym elementem posortowanej tablicy, 
//potem ze srodkowym wlasciwej polowy itd
//Jacek Mucha
// II 2013
#include <iostream>
#include <fstream>

using namespace std;

//Zmienne globalne
//Liczba porównañ
    long long int ptr1;
//Liczba przypisañ
    long long int ptr2;

int powMoja (int base, int exponent)
{
    int wyniczek=1;
    for(int i3=exponent;i3>0;i3--)
            wyniczek=wyniczek*base;
    return wyniczek;
}

void InsertSortMed(long long int A[], long int N )
{
     long long int x;//=A[0];
     long int s,p,l, i4;
//sortowanie zaczynamy od pierwszego elementu
     for(i4=1;i4<N; i4++)
     {
         x=A[i4];
         p=i4;
         l=0;
         //int i5=0;
         s=(p+l)/2;
         ptr2=ptr2+4;
         while(l<p)//szukamy pozycji, na ktorej chcemy umiescic x
         {
             ptr1=ptr1+2;
             if(x>A[s])// >= pozwoli nam zaoszczêdziæ na operacjach
             {
                 l=s+1;
             }
             else
             {
                 p=s;
             }
             s=(p+l)/2;
             //cout<<l<<" "<<s<<" "<<p<<endl;
         }// while l<p. dostalismy wspolrzedna s.
//              cout<<endl;
//robimy miejsce. przesuwamy elementy.
         for(long int i5=i4;i5>l;i5--)
         {
             A[i5]=A[i5-1];
             ptr2++;
         }
         A[l]=x;//tu umieszczamy x
  //       for(int i6=0;i6<N;i6++)
  //                cout<<A[i6]<<" ";
         ptr2++;
     }//for i4
}//koniec InsertSortMed

int main()
{    
    srand (time(NULL));
//Plik do danych
    fstream PTesty;
    PTesty.open("wynikiTC.txt",ios::out);
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
    long long int x;
//Œrednio porownan
    long long int ptr1S;
//Srednio przypisan
    long long int ptr2S;
    int Testy=50;
//Liczba testów
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
//Wype³nianie tablicy losowymi liczbami
           for(long int j2=0;j2<N;j2++)
           {
               A[j2]=0;
               for(int j3=0;j3<10;j3++)
               {
                   A[j2]=A[j2]+(rand()%2)*powMoja(2,j3);
               }    
               //cout<<A[j2]<<" ";
           }//for losowanie
           //cout<<endl;
//InsertSortMed
           InsertSortMed(A,N);
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
        }//while Testy>0
        Testy=50;
        ptr1S=S1/Testy;
        ptr2S=S2/Testy;
        cout<<"Dla N="<<N<<" Srednio porownan: "<<ptr1S<<endl<<"Srednio przypisan: "<<ptr2S<<endl;
        cout<<"Maksymalnie porownan: "<<MXpor<<" Minimalnie porownan: "<<MNpor<<endl;
        cout<<"Maksymalnie przypisan: "<<MXprz<<" Minimalnie przypisan: "<<MNprz<<endl<<endl;
        PTesty<<endl<<endl;
        PTesty<<"Dla N="<<N<<" Srednio porownan: "<<ptr1S<<endl<<"Srednio przypisan: "<<ptr2S<<endl;
        PTesty<<"Maksymalnie porownan: "<<MXpor<<" Minimalnie porownan: "<<MNpor<<endl;
        PTesty<<"Maksymalnie przypisan: "<<MXprz<<" Minimalnie przypisan: "<<MNprz<<endl<<endl<<endl;
    }//for z roznymi rozmiarami tablic
    PTesty.close();
    system("Pause");
    return 0;
}
