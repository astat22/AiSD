//Jacek Mucha
//Lista 5 na PZI
//drzewo BST
//algorytmy: InOrder, Search, Minimum, Maximum, Successor, Predecessor, Insert, Delete, BSTSort
//11 maja 2013

#include <iostream>
//#include <fstream>
#include <math.h>
//#include <conio.h>

using namespace std;

//typedef struct BST* Tree;//Adres wezla

//Wezel
struct Tree
{
       Tree* pater;
       int key;
       Tree* left;
       Tree* right;
};

//zmienna globalna
int ptr2;

//deklaracje
Tree* TabToTree(Tree* T, int A[], int N);
void WriteTab(int A[], int N);

//przepisywanie tablicy
void Rewrite( int A[],  int B[],  int N)
{
    for( int i=0;i<N;i++)
    {
        B[i]=A[i];
    }
}//Rewrite

//wypisz elementy drzewa w porzadku rosnacym
void InOrder(Tree* x, int N)
{
     if(x!=NULL /*&& N>=0*/)
     {
         InOrder(x->left, N-1);
         int K=x->key;
         cout<<K<<" ";
         InOrder(x->right, N-1);
     }
};

//przepisz do tablicy w porzadku rosnacym
void ToTabInOrder(Tree* x, int ptr, int B[], int N)
{
     if(x!=NULL /*&& N>=0*/)
     {

         ToTabInOrder(x->left, ptr, B, N);
         int K=x->key;
         B[N-ptr2]=K;
         ptr2--;
         //cout<<N-ptr2<<" ";
         ToTabInOrder(x->right, ptr, B, N);
     }
}

//BSTSort
void Sort(int B[], int N)
{
     int ptr=N;
     Tree* T=NULL;
     T=TabToTree(T,B,N);
     ToTabInOrder(T,N,B,N);
     cout<<endl;
     WriteTab(B,N);
}

//wyszukaj adres elementu o zadanym kluczu
Tree* Search(Tree* x, int k)
{
    if(x==NULL || x->key==k)
        return x;
    else
    {
        if(k<x->key)
            x=Search(x->left,k);
        else
            x=Search(x->right,k);
        return x;
    }
        
};

//wyszukaj adres minimum
Tree* Min(Tree* T)
{
    if(T!=NULL)
        while(T->left!=NULL)
            T=T->left;
    return T;
};

//wyszukaj adres maksimum
Tree* Max(Tree* x)
{
    if(x!=NULL)
        while(x->right!=NULL)
            x=x->right;
    return x;    
}

//wyszukaj adres korzenia elementu x
Tree* Root(Tree* x)
{
    //cout<<",";
    if(x==NULL)
        return x;
    else {
    while(x->pater!=NULL)
        x=x->pater;
    //cout<<",";
    return x; }
}

//wyszukaj adres nastepnika
Tree* Successor(Tree* x)
{
    if(x!=Max(Root(x)))
    {
    Tree* ret;
    if(x->right!=NULL)
    {
        ret=Min(x->right);
        return ret;
    }
    Tree* y=x->pater;
    while(y!=NULL && x->pater!=NULL && x==(x->pater)->right)
    {
        y=y->pater;
        x=x->pater;
    }
    return y;
    }
    else return x;
}

//wyszukaj adres poprzednika
Tree* Predecessor(Tree* x)
{
    if(x!=Min(Root(x)))
    {
    if(x->left!=NULL)
        return Max(x->left);
    Tree* y=x->pater;
    while(y!=NULL && x==y->left)//x==(x->pater)->left)
    {
        x=y;
        y=y->pater;
        //x=x->pater;
    }
    return y;
    }
    else return x;
}

//wstaw nowy element do drzewa
Tree* Insert(Tree* T, int kz)
{
    Tree* z = new Tree;
    z->pater=NULL;
    z->left=NULL;
    z->right=NULL;
    z->key=kz;
    Tree *x=Root(T);
    Tree* y;
    if(x==NULL)
        return z;
    else
    {
        while(x!=NULL)
        {
            y=x;
            if(z->key<x->key)
                x=x->left;
            else 
                x=x->right;
        }
        z->pater=y;
        if(z->key<y->key)
            y->left=z;
        else
            y->right=z;
        return T;
    }
}

//podepnij poddrzewo v do ojca u
Tree* Transplant(Tree* T,Tree* u, Tree* v)
{
    if(u->pater==NULL)//u nkorzeniem => korzeniem v
        return v;
    else       //u ma ojca
        if(u==(u->pater)->left) //u jest lewym synem
            (u->pater)->left=v; //lewym synem ojca u niech bedzie v
        else
            (u->pater)->right=v; //u jest prawym synem. prawym synem niech bedzie teraz v
    if(v!=NULL)
        v->pater=u->pater; //jesli v nie jest pusty, niechze jego ojcem bedzie ojciec u
    return T;
}

Tree* CormenDelete(Tree* T, Tree* z)
{
    if(z->left==NULL)// nie ma mniejszych od siebie
        T=Transplant(T,z,z->right);//po prostu prawego syna podepnij do ojca z
    else //z ma lewego syna
        if(z->right==NULL)//z nie ma prawego, ale ma lewego
            Transplant(T,z,z->left);//po prostu podepnij lewego syna do ojca z
        else//ma obu synow
        {
            Tree* y=Min(z->right); //ustaw y jako minimum prawego syna
            if(y->pater!=z)//moze sie zdarzyc, ze y to nie jest syn z
            {
                T=Transplant(T,y,y->right);//podmieniamy
                y->right=z->right;//pocmien synow prawych
                (y->right)->pater=y;//zmien ojca prawego syna
            }
            T=Transplant(T,z,y);//podmieniamy y z z
            y->left=z->left;//podmieniamy lewego syna
            (y->left)->pater=y;   //ustawiamy lewemu synowi nowego ojca
        }
        return T;//zwracamy korzen
}

//usun element. nie dziala, nic nie robi. przeanalizowac, gdzie blad.
Tree* Delete(Tree* T, Tree* z)
{
    Tree* y;
    Tree* t;
    if(z->left==NULL || z->right==NULL)
        y=z;
    else
        y=Successor(z);
    if(y->left!=NULL)
        t=y->left;
    else
        t=y->right;
    if(t!=NULL)
        t->pater=y->pater;
    if(y==(y->pater)->left)
        y=(y->pater)->left;
    else
        y=(y->pater)->right;
    if(z!=y)
        z->key=y->key;
    return T;  
}

void RandArray(int Array[], int A_length, int exponent)
{
    srand (time(NULL));
    for(int j=0;j<A_length;j++)
    {
        Array[j]=0;
        for(int j2=0;j2<exponent;j2++)//losowanie liczby z rozk³adu jednostajnego za pomoc¹ systemu dwójkowego
        {
            Array[j]=Array[j]+(rand()%2)*(int)pow(2,j2);
        }//for losowanie liczby dla komorki w tablicy
    }//for cala tablica
}//RandArray

//wypisz tablice
void WriteTab(int A[], int N)
{
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}

//przepisz tablice do drzewa
Tree* TabToTree(Tree* T, int A[], int N)
{
     for(int i=0;i<N;i++)
         T=Insert(T,A[i]);
    // cout<<"koniec";
     return T;
}

//wypisz klucz wezla x
void WriteF(Tree* x)
{
     if(x!=NULL)
         cout<<x->key;
     else
         cout<<"brak";
}

int main()
{
    srand (time(NULL));
    Tree* T=NULL;
    int N=15;
    int exp=10;
    int A[N], B[N];
    RandArray(A,N,exp);
    Rewrite(A,B,N);
    WriteTab(A,N);
    T=TabToTree(T,A,N);
    cout<<endl;
    InOrder(T,N);
    cout<<endl<<"min= ";
    WriteF(Min(T));
    cout<<" max= ";
    WriteF(Max(T));
    cout<<endl<<endl<<"Ktory element usunac? ";
    int K;
    cin>>K;
    Tree* z;
    z=Search(T,K);

    if(Predecessor(z)!=z)
    {
        cout<<endl<<"Poprzednik: ";
        WriteF(Predecessor(z));
    }
    if(Successor(z)!=z)
    {
        cout<<endl<<"Nastepnik: ";
        WriteF(Successor(z));
    }
    cout<<endl<<endl;
    T=Delete(T,z);
    T=CormenDelete(T,z);
    ptr2=N;
    InOrder(T,N);
    cout<<endl<<endl<<"Sortuj";
    Sort(B,N);   
    system("Pause");
    return 0;
}
