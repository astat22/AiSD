//Jacek Mucha
//Lista 6 na PZI
//drzewo RBT
//1 czerwca 2013

#include <iostream>
#include <fstream>
#include <math.h>
#include <conio.h>

#define red true
#define black false

using namespace std;
int MaxLevelRBT;
int MaxLevelBST;

//typedef struct BST* Tree;//Adres wezla

//Wezel
struct Tree
{
       Tree* pater;
       int key;
       Tree* left;
       Tree* right;
       bool color; //0 czarny 1 czerwony
       int level; //pietro drzewa
};

Tree* FixupRBT(Tree* T, Tree* z,Tree* wartownik);
Tree* InsertRBT(Tree* T, int kz,Tree* wartownik);


void InOrder(Tree* x, int N, Tree* wartownik)
{
     if(x!=wartownik && x!=NULL/*&& N>=0*/)
     {
         InOrder(x->left, N-1, wartownik);
         int K=x->key;
         cout<<K<<" ";
         InOrder(x->right, N-1,wartownik);
     }
};

Tree* Search(Tree* x, int k, Tree* wartownik)
{
    if(x==wartownik || x->key==k || x==NULL)
        return x;
    else
    {
        if(k<x->key)
            x=Search(x->left,k,wartownik);
        else
            x=Search(x->right,k,wartownik);
        return x;
    }
        
};

Tree* Min(Tree* T, Tree* wartownik)
{
    if(T!=wartownik && T!=NULL)
        while(T->left!=wartownik && T->left!=NULL)
            T=T->left;
    return T;
};

Tree* Max(Tree* x, Tree* wartownik)
{
    if(x!=wartownik && x!=NULL)
        while(x->right!=wartownik  && x->right!=NULL)
            x=x->right;
    return x;    
}

Tree* Root(Tree* x, Tree* wartownik)
{
    //cout<<",";
    if(x==wartownik || x==NULL)
        return x;
    else {
    while(x->pater!=wartownik && x->pater!=NULL)
        x=x->pater;
    //cout<<",";
    return x; }
}

Tree* Successor(Tree* x, Tree* wartownik)
{
    if(x!=Max(Root(x,wartownik),wartownik))
    {
    Tree* ret;
    if(x->right!=wartownik)
    {
        ret=Min(x->right,wartownik);
        return ret;
    }
    Tree* y=x->pater;
    while(y!=wartownik && x->pater!=wartownik && x==(x->pater)->right)
    {
        y=y->pater;
        x=x->pater;
    }
    return y;
    }
    else return x;
}

Tree* Predecessor(Tree* x, Tree* wartownik)
{
    if(x!=Min(Root(x,wartownik),wartownik))
    {
    if(x->left!=wartownik)
        return Max(x->left,wartownik);
    Tree* y=x->pater;
    while(y!=wartownik && x==y->left)//x==(x->pater)->left)
    {
        x=y;
        y=y->pater;
        //x=x->pater;
    }
    return y;
    }
    else return x;
}

Tree* Insert(Tree* T, int kz)
{
    Tree* z = new Tree;
    z->pater=NULL;
    z->left=NULL;
    z->right=NULL;
    z->key=kz;
    Tree *x=Root(T,NULL);

    Tree* y;

    if(x==NULL)
    {
        z->color=false;
        return z;
    }
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

Tree* Transplant(Tree* T,Tree* u, Tree* v)
{
    if(u->pater==NULL)
        return v;
    else
        if(u==(u->pater)->left)
            (u->pater)->left=v;
        else
            (u->pater)->right=v;
        if(v!=NULL)
            v->pater=u->pater;
    return T;
}

Tree* CormenDelete(Tree* T, Tree* z)
{
    if(z->left==NULL)
        T=Transplant(T,z,z->right);
    else 
        if(z->right==NULL)
            Transplant(T,z,z->left);
        else
        {
            Tree* y=Min(z->right,NULL);
            if(y->pater!=z)
            {
                T=Transplant(T,y,y->right);
                y->right=z->right;
                (y->right)->pater=y;
            }
            T=Transplant(T,z,y);
            y->left=z->left;
            (y->left)->pater=y;   
        }
        return T;
}

Tree* Delete(Tree* T, Tree* z)
{
    Tree* y;
    Tree* t;
    if(z->left==NULL || z->right==NULL)
        y=z;
    else
        y=Successor(z,NULL);
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

void WriteTab(int A[], int N)
{
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}

Tree* TabToTree(Tree* T, int A[], int N,Tree* wartownik)
{
     for(int i=0;i<N;i++)
         T=InsertRBT(T,A[i],wartownik);
    // cout<<"koniec";
     return T;
}

Tree* TabToTreeBST(Tree* T, int A[], int N)
{
     for(int i=0;i<N;i++)
         T=Insert(T,A[i]);
    // cout<<"koniec";
     return T;
}

void WriteF(Tree* x, Tree* wartownik)
{
     if(x!=wartownik)
         cout<<x->key;
     else
         cout<<"brak";
}

Tree* RightRotate(Tree* T, Tree* x, Tree* wartownik)
{
    if(x->left==wartownik)
    {
        cout<<"Blad 006: brak lewego syna x przy prawej rotacji";
        return T;
    }
    Tree* y=x->left;
    x->left=y->right;
    if(y->right!=wartownik)
        (y->right)->pater=x;
    y->pater=x->pater;
    Tree* ret=T;;
    if(x->pater==wartownik)
        ret=y;
    else
        if(x==(x->pater)->left)
            (x->pater)->left=y;
        else
            (x->pater)->right=y;
    x->pater=y;
    y->right=x;
    return ret;            
}

Tree* LeftRotate(Tree* T, Tree* x, Tree* wartownik)
{
    if(x->right==wartownik)
    {
        cout<<"Blad 006: brak prawego syna x przy lewej rotacji";
        return T;
    }
    Tree* y=x->right;
    x->right=y->left;
    if(y->left!=wartownik)
        (y->left)->pater=x;
    y->pater=x->pater;
    Tree* ret=T;
    if(x->pater==wartownik)
        ret=y;
    else
        if(x==(x->pater)->left)
            (x->pater)->left=y;
        else
            (x->pater)->right=y;
    y->left=x;
    x->pater=y;
    return ret;
}

Tree* InsertRBT(Tree* T, int kz, Tree* wartownik)
{
    Tree* y=wartownik;
    Tree* x=Root(T,wartownik);
    Tree* z = new Tree;
    z->pater=wartownik;
    z->left=wartownik;
    z->right=wartownik;
    z->key=kz;
    if(x==NULL || x==wartownik)
    {
        z->color=false;
        return z;
    }
    while(x!=wartownik)
    {
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }          
    z->pater=y;
    if(y==wartownik)
    {
        z->color=false;
        return z;
    }
    else
        if(z->key<y->key)
            y->left=z;
        else
            y->right=z;
    z->color=true;
    T=FixupRBT(T,z,wartownik);
    return T;
}

Tree* FixupRBT(Tree* T, Tree* z, Tree* wartownik)
{
    Tree* y;
    while((z->pater)->color)
    {
        if(z->pater==((z->pater)->pater)->left)
        {
            y=((z->pater)->pater)->right;
            if(y->color)
            {
                (z->pater)->color=black;
                y->color=false;
                ((z->pater)->pater)->color=true;
                z=(z->pater)->pater;
            }// if y red
            else
            {
                if(z==(z->pater)->right)
                {
                    z=z->pater;
                    T=LeftRotate(T,z,wartownik);
                }// z prawym synem swego ojca
                (z->pater)->color=false;
                ((z->pater)->pater)->color=true;
                T=RightRotate(T,z->pater->pater,wartownik);
            }// if y black
        }
        else
        {
            y=((z->pater)->pater)->left;
            if(y->color)
            {
                (z->pater)->color=false;
                y->color=false;
                ((z->pater)->pater)->color=true;
                z=(z->pater)->pater;
            }
            else
            {
                if(z==(z->pater)->left)
                {
                    z=z->pater;
                    T=RightRotate(T,z,wartownik);
                }
                (z->pater)->color=false;
                ((z->pater)->pater)->color=true;
                T=LeftRotate(T,(z->pater)->pater,wartownik);
            }
        }
    }
    y=Root(T,wartownik);
    y->color=false;
    return T;
}

Tree* TransplantRBT(Tree* T, Tree* u, Tree* v, Tree* wartownik)
{
    if(u->pater==wartownik)
    {
        return v;
    }
    else
        if(u==(u->pater)->left)
            (u->pater)->left=v;
        else (u->pater)->right=v;
    v->pater=u->pater;
    return T;
}

Tree* DeleteFixupRBT(Tree* T, Tree* x,Tree* wartownik)
{
    cout<<"rozpoczynam delete fixup..."<<endl;
    /*if(x==Root(T,wartownik) || x->color==black)
    {
        //x->color=black;
        return T;
    }*/
    Tree* w;
    //cout<<".";
    while(x!=T /*Root(T, wartownik)*/ && x->color==false)
    {        
        cout<<".";
        if(x==x->pater->left)
        {
            w=x->pater->right;
            cout<<"x jest lewym synem swego ojca..."<<endl<<"w prawym synem ojca x "<<w->key<<"..."<<endl;
            if(w->color)
            {
                cout<<"kolor w zmieniony z czerwonego na czarny..."<<endl;
                w->color=false;
                x->pater->color=true;
                T=LeftRotate(T,x->pater,wartownik);
                cout<<"lewy obrot ojca x wykonany..."<<endl;
                w=x->pater->right;
            }
            if(w->left->color==false && w->right->color==false)
            {
                cout<<"synowie w czarni "<<w->left->key<<", "<<w->right->key<<"..."<<endl;
                w->color=true;
                x=x->pater;
            }
            else
            {
                if(w->right->color==black)
                {
                    cout<<"prawy syn w czarny, lewy czerwony..."<<w->left->key<<", "<<w->right->key<<"..."<<endl;
                    w->left->color=black;
                    w->color=red;
                    T=RightRotate(T,w,wartownik);
                    cout<<"prawy obrot w wykonany..."<<endl;
                    w=x->pater->right;
                }
                w->color=x->pater->color;
                x->pater->color=black;
                w->right->color=black;
                T=LeftRotate(T,x->pater,wartownik);
                cout<<"lewy obrot ojca x wykonany..."<<endl;
                x=T; //Root(T,wartownik);
                cout<<"ustawiono x na korzen drzewa..."<<endl;
            }
        }
        else
        {
            cout<<"x jest prawym synem swego ojca..."<<endl<<"w lewym synem ojca x"<<endl;
            w=x->pater->left;
            if(w->color)
            {
                w->color=false;
                x->pater->color=true;
                T=RightRotate(T,x->pater,wartownik);
                cout<<"prawy obrot ojca x wykonany..."<<endl;
                w=x->pater->left;
            }
            if(w->left->color==false && w->right->color==false)
            {
                cout<<"w nie ma obu czarnych synow..."<<endl;
                w->color=true;
                x=x->pater;
            }
            else
            {
                if(w->left->color==black)
                {
                    cout<<"w ma lewego czarnego, prawego czerwonego syna..."<<endl;
                    w->right->color=black;
                    w->color=red;
                    T=LeftRotate(T,w,wartownik);
                    cout<<"lewy obrot w wykonany..."<<endl;
                    w=x->pater->left;
                }
                w->color=x->pater->color;
                x->pater->color=black;
                w->left->color=black;
                T=RightRotate(T,x->pater,wartownik);
                cout<<"prawy obrot ojca x wykonany..."<<endl;
                x=T;//Root(T,wartownik);
                cout<<"ustawiono x na korzen drzewa..."<<endl;
            }
        }
        //x=Root(T,wartownik);
        //x->color=false;
    }
    //cout<<";";
    x->color=false;
    return T;
}

Tree* DeleteRBT(Tree* T, Tree* z,Tree* wartownik)
{
    cout<<"rozpoczynam kasowanie..."<<endl;
    Tree* y=z;
    Tree* x;
    bool YOriginalColor=y->color;
    if(z->left==wartownik)
    {
        cout<<"kasowany element nie ma lewego syna..."<<endl<<"x prawym synem usowanego..."<<endl;
        x=z->right;
        T=TransplantRBT(T,z,z->right,  wartownik);
    }
    else
        if(z->right==wartownik)
        {
            cout<<"kasowany element nie ma prawego syna..."<<endl<<"x lewym synem usuwaneo..."<<endl;
            x=z->left;
            T=TransplantRBT(T,z,z->left,wartownik);
            cout<<"transplantacja z i lewego syna z dokonana..."<<endl;
        }
        else
        {
            cout<<"kasowany element ma obu synow..."<<endl<<"x prawym synem nastepnika..."<<endl;
            y=Min(z->right,wartownik);
            cout<<"wyznaczylem minimum..."<<endl;
            YOriginalColor=y->color;
            x=y->right;
            if(y->pater==z)
            {
                x->pater=y;
                cout<<"nastepnik kasowanego jest jego synem..."<<endl;
            }
            else
            {
                cout<<"nastepnik kasowanego nie jest jego synem..."<<endl;
                T=TransplantRBT(T,y,y->right,wartownik);
                y->right=z->right;
                (y->right)->pater=y;
            }
            T=TransplantRBT(T,z,y,wartownik);
            cout<<"transplantacja nastepnika kasowanego dokonana..."<<endl;
            y->left=z->left;
            (y->left)->pater=y;
            y->color=z->color;
        }
    if(YOriginalColor==false)
    {
        cout<<"nastepnik kasowanego byl czarny..."<<endl;
        T=DeleteFixupRBT(T,x,wartownik);
        cout<<"przywrocono wlasnosc RB..."<<endl;
    }
    return T;
}

void Leveling(Tree* T, Tree* wartownik, int lev)
{
     if(T!=wartownik && T!=NULL)
     {
         T->level=lev;
         if(lev>MaxLevelRBT)
             MaxLevelRBT=lev;
         if(lev>MaxLevelBST)
             MaxLevelBST=lev;
         if(T->left!=wartownik && T->left!=NULL)
             Leveling(T->left,wartownik,lev+1);
         if(T->right!=wartownik&& T->right!=NULL)
             Leveling(T->right,wartownik,lev+1);
     }
}

void PreOrderWithLevel(int lev, Tree* x, Tree* wartownik,bool fin)
{
     if(x!=wartownik && x!=NULL/*&& N>=0*/)
     {
         bool finL=true;
         bool finP=true;
         if(x->left==wartownik)
             finL=false;
         PreOrderWithLevel(lev,x->left, wartownik,finL);

         if(fin==false)
             cout<<"o";
         int K=x->level;
         if(K==lev)
         {
             if(x->left!=wartownik && x->left!=NULL)
                 cout<<"/";
             if(x->color && wartownik!=NULL)
                 cout<<"(";
             if(!x->color && wartownik!=NULL)
                 cout<<"[";
             cout<<x->key;
             if(x->color && wartownik!=NULL)
                 cout<<")";
             if(!x->color && wartownik!=NULL)
                 cout<<"]";
             if(x->right!=wartownik && x->right!=NULL)
                 cout<<"\\";
             cout<<" ";
         }
         if(x->right==wartownik)
             finP=false;
         PreOrderWithLevel(lev,x->right,wartownik,finP);
     }
}

void DrawTree(Tree* T, int N, Tree* wartownik)
{
     int i=1;
     while(i<N+1)
     {
         PreOrderWithLevel(i,T,wartownik,true);
         i++;
         cout<<endl;
     }
}

int main()
{
    srand (time(NULL));
    Tree* T=NULL;
    MaxLevelRBT=0;
    MaxLevelBST=0;
    Tree* wartownik = new Tree;
    wartownik->left=T;
    wartownik->right=T;
    wartownik->color=false;
    wartownik->pater=wartownik;
    wartownik->level=0;
    wartownik->key=-1;
    int N;
    cout<<"podaj rozmiar tablicy: ";
    int exp=10;
    cin>>N;
    cout<<endl;
    int A[N];
    RandArray(A,N,exp);
    cout<<"tablica: "<<endl;
    WriteTab(A,N);
    T=TabToTree(T,A,N,wartownik);
    cout<<endl;
    cout<<"InOrder:"<<endl;
    InOrder(T,N,wartownik);
    Leveling(T,wartownik,1);
    cout<<endl<<"wysokosc RBT: "<<MaxLevelRBT<<endl<<"drzewo:"<<endl;
    DrawTree(T,MaxLevelRBT,wartownik);
//drzewo BST:
    Tree* BST=NULL;
    BST=TabToTreeBST(BST,A,N);
    Leveling(BST,wartownik,1);
    cout<<endl<<"wysokosc BST: "<<MaxLevelBST<<endl<<"drzewo: "<<endl;
    DrawTree(BST,MaxLevelBST,wartownik);      
    
    cout<<endl<<endl<<"Ktory element usunac? ";
    int K;
    cin>>K;
    bool exists=false;
    for(int j=0;j<N;j++)
        if(A[j]==K)
            exists=true;
    if(!exists)
    {
        cout<<endl<<"blad 5: brak wezla "<<K<<endl;
        system("Pause");
        return 1;
    }
    Tree* z;
    z=Search(T,K,wartownik);

    if(Predecessor(z,wartownik)!=z)
    {
        cout<<endl<<"Poprzednik: ";
        WriteF(Predecessor(z,wartownik),wartownik);
    }
    if(Successor(z,wartownik)!=z)
    {
        cout<<endl<<"Nastepnik: ";
        WriteF(Successor(z,wartownik),wartownik);
    }
    cout<<endl<<endl;
    T=DeleteRBT(T,z,wartownik);
    cout<<"skasowano."<<endl;
    int test=0;
    cout<<"podaj element: "<<endl;
    //while(test<N-1)
     while (test>-1)
    {
        cin>>test;
        //z=Search(T,A[test],wartownik);
        z=Search(T,test,wartownik);
        T=DeleteRBT(T,z,wartownik);
        MaxLevelRBT=0;
        Leveling(T,wartownik,1);
        //cout<<endl<<"wysokosc RBT: "<<MaxLevelRBT<<endl<<"drzewo:"<<endl;
        DrawTree(T,MaxLevelRBT,wartownik);
        //test++;
    }
    
    MaxLevelRBT=0;
    Leveling(T,wartownik,1);
    cout<<endl<<"wysokosc RBT: "<<MaxLevelRBT<<endl<<"drzewo:"<<endl;
    DrawTree(T,MaxLevelRBT,wartownik);
    //InOrder(T,N,wartownik);
    cout<<endl<<endl;  
    //T=Delete(T,z);
    //T=CormenDelete(T,z);
//tablica posortowana
    Tree* T2=NULL;
    Tree* BST2=NULL;
    MaxLevelRBT=0;
    MaxLevelBST=0;
    for(int i=0;i<N;i++)
        A[i]=i;
    T2=TabToTree(T2,A,N,wartownik);
    BST2=TabToTreeBST(BST2,A,N);
    Leveling(T2,wartownik,1);
    cout<<endl<<"RBT z posortowanej - wysokosc: "<<MaxLevelRBT<<endl;
    //DrawTree(T2,MaxLevelRBT,wartownik);
    Leveling(BST2,wartownik,1);
    cout<<"BST z posortowanej - wysokosc: "<<MaxLevelBST<<endl;
    //DrawTree(BST2,MaxLevelBST,wartownik);
 //tablica odwrotnie posortowana
    Tree* T3=NULL;
    Tree* BST3=NULL;
    MaxLevelRBT=0;
    MaxLevelBST=0;
    for(int i=N;i>0;i--)
        A[i]=i;
    T3=TabToTree(T3,A,N,wartownik);
    BST3=TabToTreeBST(BST3,A,N);
    Leveling(T3,wartownik,1);
    cout<<endl<<"RBT z odwrotnie posortowanej - wysokosc: "<<MaxLevelRBT<<endl;
    //DrawTree(T3,MaxLevelRBT,wartownik);
    Leveling(BST3,wartownik,1);
    cout<<"BST z odwrotnie posortowanej - wysokosc: "<<MaxLevelBST<<endl;    
    system("Pause");
    return 0;
}
