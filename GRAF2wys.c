//Jacek Mucha
//8 III 2012- lista 1
//15 IV 2012- lista 2
//dane z pliku test1
//do listy 2 dane z pliku test2
//kompilacja pod Linuksem: gcc GRAF2.c -o GREF2 -Wall -pedantic -std=c99
//uruchamianie: ./GRAF2< test1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//**************************STRUKTURY*******************************************************
typedef struct Wezel* AdresW;
typedef struct ListaW* Lista1;
typedef struct Luk* AdresL;
typedef struct ListaL* Lista2;
typedef struct Nuptias* Hestia;

//Struktura wierzcholek. trzy pola: identyfikator, lista wychodzacych, lista przychodzacych
struct Wezel
{
    char NazwaW[8]; //Identyfikator
    int NUMER;     // kazdy wezel ma swoj przyporzadkowany numer. potrzebne do algorytmu Warshalla
    Lista2 Wychodzace; //Adresy lukow, ktore wychodza
    Lista2 Przychodzace; //Adresy lukow, ktore przychodza
};
//Druga struktura- luk
struct Luk
{
    char NazwaL[8];//Identyfikator luku
    AdresW Od; //adres wierzcholka, od ktorego luk wychodzi
    AdresW Do; //adres wezla, do ktorego luk dochodzi
};
//Lista przechowujaca adresy wezlow
struct ListaW
{
    AdresW adresW; //Wskazuje adres wezla
    struct ListaW *kolejny;//Wskazuje adres wskazania adresu kolejnego wezla- kolejna pozycja na liscie
};
//Lista przechowujaca adresy lukow
struct ListaL
{
    AdresL adresL; //Wskazuje adres luku
    struct ListaL *nastepny; //Wskazuje adres wskazania adresu kolejnego luku- kolejna pozycja na liscie
};
//Struktura pomocnicza przechowujaca liste lukow i liste wezlow
//potrzebna, bo funkcja usuwajaca wezel zwraca nawa liste wezlow i nowa liste lukow
struct Nuptias
{
    Lista1 mal;
    Lista2 fem;
};
//deklaracje funkcji. opisy przy definicjach.
Lista2 delL(char *NazwaLu, Lista2 ptr,int M);
void vidL(Lista2 ptr, int U);
int invW(Lista1 ptr, char *NazwaWe);
int invL(Lista2 ptr, char *Nom);
int eqStr(char *radix, char *arbor);
//************************METODY-WEZLY************************************************************
//############################Funkcja dodajaca wezly do ListaW###################################
//Warunek brzegowy istnienia wezla o zadanej nazwie sprawdzany jest w mainie
Lista1 addW(Lista1 ptr, char *NazwaWe, int numer)
{
    //printf("%s\n",NazwaWe);
    if(invW(ptr,NazwaWe))
    {
        Lista1 nowyWLi;
        AdresW nowyW;
        nowyW=malloc(sizeof(struct Wezel));
        if(nowyW==NULL)
        {
            printf("\nZa malo pamieci\n");
            return ptr;
        }
        nowyWLi=malloc(sizeof(struct ListaW));
        if(nowyWLi==NULL)
        {
            printf("\nZa malo pamieci\n");
            return ptr;
        }
//przepisanie NazwaWe do nowego wektora
        int i=0;
        for(i=0; i<7&&NazwaWe[i]!='\0'; i++)
        {
            nowyW->NazwaW[i]=NazwaWe[i];
            nowyW->NazwaW[i+1]='\0';
        }
        nowyW->NUMER=numer;
        //printf("%s\n",nowyW->NazwaW);
//Lista lukow przychodzacych i wychodzacych musi byc pusta
        nowyW->Wychodzace=NULL;
        nowyW->Przychodzace=NULL;
        nowyWLi->adresW=nowyW;
        nowyWLi->kolejny=ptr;
        return nowyWLi;
    }
    else
    {
        printf("\n Taki wezel juz istnieje!\n");
        return ptr;
    }
}
//#################Funkcja usuwajaca wezly w ListaW################################
Hestia delW(char *NazwaWe, Lista1 ptr, Lista2 ptrL)//nie dziala
{
    Lista1 preWekt;
    Lista1 actWekt;
    Lista1 postWekt;
    Lista2 ptrLiW;
    AdresW adW;
    AdresL adL;
    preWekt=NULL;
    actWekt=ptr;
    if(ptr!=NULL)
        adW=ptr->adresW;
    Hestia votum;
    votum=malloc(sizeof(struct Nuptias));
    char NazwaLuku[7];
//Szukanie wezla na liscie
    while((actWekt!=NULL)&&(!eqStr(adW->NazwaW,NazwaWe)))
    {
        preWekt=actWekt;
        actWekt=actWekt->kolejny;
        if(actWekt!=NULL)
            adW=actWekt->adresW;
    }
    if(actWekt!=NULL)
    {
//Usuwanie lukow z wezla
        int i4=0;
        ptrLiW=adW->Przychodzace;
        if(ptrLiW!=NULL)
        {
            adL=ptrLiW->adresL;
            //przepisanie nazwy luku
            for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
            {
                NazwaLuku[i4]=adL->NazwaL[i4];
                NazwaLuku[i4+1]='\0';
            }
            while(ptrLiW!=NULL)
            {
                ptrL=delL(NazwaLuku,ptrL,2);
                ptrLiW=adW->Przychodzace;
                if(ptrLiW!=NULL)
                {
                    adL=ptrLiW->adresL;
                    for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
                    {
                        NazwaLuku[i4]=adL->NazwaL[i4];
                        NazwaLuku[i4+1]='\0';
                    }
                }
            }
        }
        ptrLiW=adW->Wychodzace;
        if(ptrLiW!=NULL)
        {
            adL=ptrLiW->adresL;
            //przepisanie nazwy luku
            for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
            {
                NazwaLuku[i4]=adL->NazwaL[i4];
                NazwaLuku[i4+1]='\0';
            }
            // NazwaLuku=adL->NazwaL;
            while(ptrLiW!=NULL)
            {
                ptrL=delL(NazwaLuku,ptrL,2);
                ptrLiW=adW->Wychodzace;
                if(ptrLiW!=NULL)
                {
                    adL=ptrLiW->adresL;
                    for(i4=0; i4<7&&adL->NazwaL[i4]!='\0'; i4++)
                    {
                        NazwaLuku[i4]=adL->NazwaL[i4];
                        NazwaLuku[i4+1]='\0';
                    }
                }
            }
        }
//Usuwanie wezla z lsty wezlow
        postWekt=actWekt->kolejny;
        //printf("post wekt przypisanu\n");
        if(preWekt==NULL)
        {
            ptr=postWekt;
            //printf("ostatni if\n");
        }
        else
        {
            preWekt->kolejny=postWekt;
        }
        free(actWekt);
        //printf("zwolnilem pamiec\n");
    }
    else
        printf("\nNie ma takiego wezla!\n");
    votum->fem=ptrL;
    votum->mal=ptr;
    return votum;
}
//###########Funkcja wyswietlajaca zawartosc ListaW, czyli drukujaca wszystkie wezly####
//od razu drukuje tez wszystkie luki, ktore przychodza i wychodza z danego wezla
void vidW(Lista1 ptr)
{
    if(ptr==NULL)
        printf("Nie ma zadnych wezlow\n");
    else
    {
        AdresW pom;
        printf("Istnieja nastepujace wezly: \n");
        while(ptr!=NULL)
        {
            pom=ptr->adresW;
            printf("\n%s \n", pom->NazwaW);
            printf("luki przychodzace: ");
            vidL(pom->Przychodzace,2);
            printf("luki wychodzace: ");
            vidL(pom->Wychodzace,2);
            ptr=ptr->kolejny;
        }
    }
}
//#############Funkcja sprawdzajaca, czy nazwa wezla sie nie powtarza#############
//zwraca 1, jesli wezel sie nie powtarza
int invW(Lista1 ptr, char *NazwaWe)
{
    int spr1=1;
    if(ptr!=NULL)
    {
        AdresW pom;
        while(ptr!=NULL)
        {
            //printf("szukam");
            pom=ptr->adresW;
            //if(NazwaWe[0]==pom->NazwaW[0])
            if(eqStr(NazwaWe,pom->NazwaW)==1)
            {
                //printf("%s i %s\n",NazwaWe,pom->NazwaW);
                spr1=0;
                return spr1;
            }
            ptr=ptr->kolejny;
        }
    }
    //printf("czy istnieje: %d\n",spr1);
    return spr1;
}
//**********************METODY-LUKI*****************************************************************
//#################Funkcja dodajaca luki########################
Lista2 addL(char *NazwaLu, char *Wp, char *Wk, Lista1 ptr1, Lista2 ptr2)                            //nie dziala po usunieciu wezla
{
    if(invL(ptr2,NazwaLu))
    {
//Warunek brzegowy 1: czy sa jakiekolwiek wezly?
        if(ptr1==NULL)
        {
            printf("\nNie ma zadnych wezlow\n");
            return ptr2;
        }
        else
        {
            Lista2 nowyLLi;
            AdresL nowyL;
            Lista1 ptr1pom,ptr1pom2;
            ptr1pom=ptr1;
//Szukanie wezla Wp
            AdresW pomWp;
            pomWp=ptr1->adresW;
            while((!eqStr(pomWp->NazwaW,Wp))&&ptr1!=NULL)
            {
                //printf("%s kontra %s=%d\n",pomWp->NazwaW,Wp,eqStr(pomWp->NazwaW,Wp));
                ptr1pom2=ptr1;
                ptr1=ptr1->kolejny;
                if(ptr1!=NULL)
                {
                    pomWp=ptr1->adresW;
                    //printf("%s-%s\n",pomWp->NazwaW,Wp);
                }
            }
//Warunek brzegowy 2: czy istnieje wezel poczatkowy?
            if(ptr1==NULL)
            {
                printf("\nNie ma takiego poczatkowego wezla. Koncowego juz nie sprawdzam.\n");
                return ptr2;
            }
            else
            {
//Szukanie wezla Wk
                AdresW pomWk;
                pomWk=ptr1pom->adresW;
                while(!eqStr(pomWk->NazwaW,Wk)&&ptr1!=NULL)
                {
                    ptr1pom2=ptr1pom;
                    if(ptr1pom2==NULL)
                        printf(" ");
                    ptr1pom=ptr1pom->kolejny;
                    if(ptr1pom!=NULL)
                    {
                        pomWk=ptr1pom->adresW;
                    }
                }
//Warunek brzegowy 3: czy istnieje wezel koncowy?
                if(ptr1pom==NULL)
                {
                    printf("\nNie ma takiego koncowego wezla\n");
                }
                else
                {
//Dodawanie luku do Lista2
                    int i5=0;
                    nowyLLi=malloc(sizeof(struct ListaL));
                    if(nowyLLi==NULL)
                    {
                        printf("\nZa malo pamieci\n");
                        return ptr2;
                    }
                    nowyL=malloc(sizeof(struct Luk));
                    if(nowyL==NULL)
                    {
                        printf("\nZa malo pamieci\n");
                        return ptr2;
                    }
                    //przepisanie nazwy luku
                    for(i5=0; i5<7&&NazwaLu[i5]!='\0'; i5++)
                    {
                        nowyL->NazwaL[i5]=NazwaLu[i5];
                        nowyL->NazwaL[i5+1]='\0';
                    }
                    nowyL->Od=pomWp;
                    nowyL->Do=pomWk;
                    nowyLLi->adresL=nowyL;
                    nowyLLi->nastepny=ptr2;
//Dodawanie informacji o luku do Wp
                    Lista2 Ab;
                    Lista2 Abadalter;
                    Abadalter=pomWp->Wychodzace;
                    Ab=malloc(sizeof(struct Luk));
                    Ab->adresL=nowyL;
                    Ab->nastepny=Abadalter;
                    pomWp->Wychodzace=Ab;
//Dodawanie informacji o luku do Wk
                    Lista2 Ad;
                    Lista2 Adadalter;
                    Adadalter=pomWk->Przychodzace;
                    Ad=malloc(sizeof(struct Luk));
                    Ad->adresL=nowyL;
                    Ad->nastepny=Adadalter;
                    pomWk->Przychodzace=Ad;
//Zwracany jest adres do pierwszego elementu w nowej liscie lukow
                    return nowyLLi;
                }
            }
        }
    }
    else
    {
//Jesli luk o zadanej nazwie juz istnieje, to zwracana jest lista wejsciowa
        printf("\nLuk o zadanej nazwie aktualnie istnieje\n");
        return ptr2;
    }
    return ptr2;
}
//###############Funkcja usuwajaca informacje o luku z wezla##########
void purLiW(AdresW adresW, Lista2 listaL,int k)
{
    Lista2 actL;
    Lista2 preL;
    Lista2 postL;
    AdresL adreswWekt;
    preL=NULL;
    if(k==1)
        actL=adresW->Przychodzace;
    else
        actL=adresW->Wychodzace;
    if(actL!=NULL)
        adreswWekt=actL->adresL;
    while((adreswWekt!=listaL->adresL)&&(actL!=NULL))
    {
        preL=actL;
        actL=actL->nastepny;
        if(actL!=NULL)
            adreswWekt=actL->adresL;
    }
    if(actL==NULL)
        printf("nie znalazlem luku\n");
    if(actL!=NULL)
    {
        //printf("purLiW if1");
        postL=actL->nastepny;
        if(preL==NULL)
        {
            if(k==1)
                adresW->Przychodzace=postL;
            else
                adresW->Wychodzace=postL;
        }
        else
            preL->nastepny=postL;
        //printf("koncze purLiW");
        free(actL);
    }
}
//#####################Funkcja usuwajaca luki#######################
//zlozonosc ok n(2n+1)
//Nalezy: 1. znalezc luk na liscie lukow 2.
Lista2 delL(char *NazwaLu, Lista2 ptr, int M)
{
    if(ptr!=NULL)
    {
        Lista2 pre;//poprzedni element listy
        Lista2 post;//nast\EApny element listy
        Lista2 hic;//aktualny element listy
        AdresL is;
        AdresW Od1;
        AdresW Do1;
        pre=NULL;
        hic=ptr;
        is=hic->adresL;
//Znajdz luk w Lista2
        while((hic!=NULL)&&(!eqStr(is->NazwaL,NazwaLu)))
        {
            pre=hic;
            hic=hic->nastepny;
            if(hic!=NULL)
                is=hic->adresL;
        }
        if(hic==NULL&&M==1)
            printf("\nNie ma takiego luku!\n");
        if(hic!=NULL)
        {
//Usuwanie informacji o luku w wezle, od ktorego luk wychodzi:
            Od1=is->Od;
            purLiW(Od1,hic,2);
//Usuwanie informacji o luku w wezle, do ktorego luk przyychodzi:
            Do1=is->Do;
            purLiW(Do1,hic,1);
//Usuwanie luku z Listy2 (listy lukow)
            post=hic->nastepny;
            if(pre==NULL)
            {
                ptr=post;
            }
            else
            {
                pre->nastepny=post;
            }
            free(hic);
        }
    }
    else
        printf("\nNie ma zadnych lukow, wiec nic nie moge usunac");
    return ptr;
}
//#################Funkcja drukujaca wszystkie luki###################
void vidL(Lista2 ptr, int U)
{
    if(ptr==NULL)
        printf("\nNie ma zadnych lukow\n");
    else
    {
        if(U==1)
            printf("\nIstnieja nastepujace luki: \n");
        AdresL pom;
        AdresW pomOd;
        AdresW pomDo;
        while(ptr!=NULL)
        {
            pom=ptr->adresL;
            pomOd=pom->Od;
            pomDo=pom->Do;
            printf("%s od %s do %s\n", pom->NazwaL, pomOd->NazwaW, pomDo->NazwaW);
            ptr=ptr->nastepny;
        }
    }
}
//#####################Metoda sprawdzajaca, czy nazwa luku sie nie powtarza#####################
int invL(Lista2 ptr, char *Nom)
{
    int spr2=1;
    if(ptr!=NULL)
    {
        AdresL pom;
        while(ptr!=NULL)
        {
            pom=ptr->adresL;
            if(eqStr(Nom,pom->NazwaL)==1)
            {
                spr2=0;
                return spr2;
            }
            ptr=ptr->nastepny;
        }
    }
    return spr2;
}
//*********************************************************************************************
//#######################Funkcja wypisujaca sasiedztwo zadanego wezla##########################
void consW(char *ID, Lista1 ptrw)
{
//czy taki wezel istnieje?
    if(invW(ptrw,ID)==0)
    {
//wyszukaj wezel
        int br=1;//zmienna logiczna dla petli while
        AdresW naszW;
        naszW=ptrw->adresW;
        if(eqStr(ID,naszW->NazwaW))
        {
            br=0;
        }
//sprawdzilismy, ze taki wezel istnieje, wiec w while wystarczy jeden warunek
        while(br)
        {
            ptrw=ptrw->kolejny;
            if(ptrw!=NULL)
            {
                naszW=ptrw->adresW;
                if(eqStr(ID,naszW->NazwaW))
                {
                    br=0;
                }//if(eqStr(Id,naszW->NazwaW)
            }//if(ptrw!=NULL)
        }//while(br)
//wypisywanie wezlow przychodzacych
        Lista2 ptrl;
        AdresW sasiad;
        AdresW sasiadPom;
        AdresL viaSasiad;
        AdresL viaSasiadPom;
        Lista2 ptrlPom;
        Lista2 ptrlPom2;
        ptrl=naszW->Przychodzace;
        if(ptrl==NULL)
            printf("brak wezlow przychodzacych\n");
        else
        {
            printf("wezly przychodzace:\n");
            int br2=1;
            ptrlPom2=ptrl;
            ptrlPom=ptrl;
            while(ptrl!=NULL)
            {
                viaSasiad=ptrl->adresL;
                sasiad=viaSasiad->Od;
                //sprawdzenie, czy dany wezel juz wystapil
                while(ptrlPom!=ptrl)
                {
                    viaSasiadPom=ptrlPom->adresL;
                    sasiadPom=viaSasiadPom->Od;
                    if(eqStr(sasiad->NazwaW,sasiadPom->NazwaW))
                    {
                        br2=0;
                    }
                    ptrlPom=ptrlPom->nastepny;
                }//while(ptrlPom!=ptrl)
                ptrl=ptrl->nastepny;
                if(br2)
                {
                    printf("%s", sasiad->NazwaW);
                    if(ptrl!=NULL)
                        printf(", ");
                }
                br2=1;
                ptrlPom=ptrlPom2;
            }//while(ptrl!=NULL)
            printf("\n");
        }// if(ptrl!=NULL)
//wypisywanie wezlow wychodzacych
        ptrl=naszW->Wychodzace;
        if(ptrl==NULL)
            printf("brak wezlow wychodzacych\n");
        else
        {
            printf("wezly wychodzace:\n");
            int br2=1;
            ptrlPom2=ptrl;
            ptrlPom=ptrl;
            while(ptrl!=NULL)
            {
                viaSasiad=ptrl->adresL;
                sasiad=viaSasiad->Do;
                //sprawdzenie, czy dany wezel juz wystapil
                while(ptrlPom!=ptrl)
                {
                    viaSasiadPom=ptrlPom->adresL;
                    sasiadPom=viaSasiadPom->Do;
                    if(eqStr(sasiad->NazwaW,sasiadPom->NazwaW))
                    {
                        br2=0;
                        //printf("natrafilem");
                    }
                    ptrlPom=ptrlPom->nastepny;
                }//while(ptrlPom!=ptrl)
                ptrl=ptrl->nastepny;
                if(br2)
                {
                    printf("%s", sasiad->NazwaW);
                    if(ptrl!=NULL)
                        printf(", ");
                }
                br2=1;
                ptrlPom=ptrlPom2;
            }//while(ptrl!=NULL)
            printf("\n");
        }// if(ptrl!=NULL)
    }//if(invW(ptrw,ID)==0)
    else
        printf("podany wezel nie istnieje\n");
}
//##############Funkcja sprawdzajaca, czy istnieje luk miedzy zadanymi wezlami#################
//Przeszukuje liste lukow
void votW( char *ID1, char *ID2, Lista2 ptr, Lista1 ptrw)
{
    if(invW(ptrw,ID1)==0&&invW(ptrw,ID2)==0)
    {
        if(ptr!=NULL)
        {
            int br=1;
            AdresL adL;
            AdresW Pocz;
            AdresW Kon;
            adL=ptr->adresL;
            Pocz=adL->Od;
            Kon=adL->Do;
//szukanie luku
            if(eqStr(ID1,Pocz->NazwaW)&&eqStr(ID2,Kon->NazwaW))
            {
                printf("luk laczacy %s i %s: %s\n",ID1,ID2,adL->NazwaL);
                br=0;
            }
            while(ptr!=NULL&&br)
            {
                ptr=ptr->nastepny;
                if(ptr!=NULL)
                {
                    adL=ptr->adresL;
                    Pocz=adL->Od;
                    Kon=adL->Do;
                    if(eqStr(ID1,Pocz->NazwaW)&&eqStr(ID2,Kon->NazwaW))
                    {
                        printf("luk laczacy %s i %s: %s\n",ID1,ID2,adL->NazwaL);
                        br=0;
                    }
                }
                else
                    printf("taki luk nie istnieje\n");
            }//while ptr!=NULL && br
        }// if ptr!=NULL
        else
            printf("taki luk nie istnieje\n");
    }//jesli takie wierzcholki istnieja
    else
        printf("co najmniej jeden z podanych wezlow nie istnieje\n");
}
//##########Funkcja wypisujaca droge miedzy zadanami wezlami#####################################
//wykorzystuje algorytm Roy-Warshalla
//@rozmiar liczba wszystkich wezlow wprowadzonych od uruchomienia programu. innymi slowy, usuniecie jakigos wezla nie zmniejsza rozmiar
void viaWW(Lista1 ptrw, int rozmiar, Lista2 ptrl, char *ID1, char *ID2)
{
    if(ptrw!=NULL)//wyjatek 1- brak wezlow
    {
        if(ptrl!=NULL)//wyjatek 2- brak lukow
        {
            if(invW(ptrw,ID1)==0)//wyjatek 3-brak poczatkowego wezla
            {
                if(invW(ptrw,ID2)==0)//wyjatek 4- brak koncowego wezla
                {
                    if(!eqStr(ID1,ID2))
                    {
//tworzenie macierzy polaczen wezlow
                        int M[rozmiar][rozmiar];
                        int M2[rozmiar][rozmiar];
                        int it1,it2;
//zerowanie macierzy
                        for(it1=0; it1<rozmiar; it1++)
                            for(it2=0; it2<rozmiar; it2++)
                            {
                                M[it1][it2]=0;
                                M2[it1][it2]=0;
                            }
//czytanie polaczen
                        AdresL adL;
                        AdresW WOd, WDo;
                        while(ptrl!=NULL)
                        {
                            adL=ptrl->adresL;
                            WOd=adL->Od;
                            WDo=adL->Do;
                            M[WOd->NUMER][WDo->NUMER]=WDo->NUMER;
                            M2[WOd->NUMER][WDo->NUMER]++;
                            ptrl=ptrl->nastepny;
                        }// while(ptrl!=NULL)
//Roy-Warshall
                        int it3;
                        //szukanie numerow wezlow
                        int Pocz;
                        int Kon;
                        int br=1;//zmienna logiczna dla petli while
                        AdresW WPocz;
                        AdresW WKon;
                        Lista1 ptrwP;
                        ptrwP=ptrw;
                        if(ptrwP!=NULL)
                        {
                            WPocz=ptrwP->adresW;
                            if(eqStr(ID1,WPocz->NazwaW))
                            {
                                br=0;
                                Pocz=WPocz->NUMER;
                            }
                            while(br&&ptrwP!=NULL)
                            {
                                ptrwP=ptrwP->kolejny;
                                if(ptrwP!=NULL)
                                {
                                    WPocz=ptrwP->adresW;
                                    if(eqStr(ID1,WPocz->NazwaW))
                                    {
                                        br=0;
                                        Pocz=WPocz->NUMER;
                                        //printf("%s %d \n",WPocz->NazwaW,Pocz);
                                    }//if(eqStr(Id,naszW->NazwaW)
                                }//if(ptrw!=NULL)
                            }//while(br)
                        }//if(ptrwP!=NULL)
                        ptrwP=ptrw;
                        if(ptrwP!=NULL)
                        {
                            br=1;
                            WKon=ptrwP->adresW;
                            if(eqStr(ID2,WKon->NazwaW))
                            {
                                br=0;
                                Kon=WKon->NUMER;
                            }
                            while(br)
                            {
                                ptrwP=ptrwP->kolejny;
                                if(ptrwP!=NULL)
                                {
                                    WKon=ptrwP->adresW;
                                    if(eqStr(ID2,WKon->NazwaW))
                                    {
                                        br=0;
                                        Kon=WKon->NUMER;
                                        //printf("%s %d \n",WKon->NazwaW,Kon);
                                    }//if(eqStr(Id,naszW->NazwaW)
                                }//if(ptrw!=NULL)
                            }//while(br)
                        }//if(ptrwP!=NULL)
//procedura route
                        for(it1=0; it1<rozmiar; it1++)
                            for(it2=0; it2<rozmiar; it2++)
                                if(M[it2][it1]!=0)//wiemy jak dojsc z it2 do it1
                                    for(it3=0; it3<rozmiar; it3++)
                                        if((M[it2][it3]==0)&&(M[it1][it3]!=0))
                                            M[it2][it3]=M[it2][it1];
                        printf("\n");
//procedura scribere
                        int br3;
                        br3=Pocz;
                        if(M[Pocz][Kon]==0)
                            printf("droga nie istnieje\n");
                        else
                        {
                            AdresW adWP;
                            printf("%s->",ID1);
                            while(br3!=Kon)
                            {
                                br3=M[br3][Kon];
                                ptrwP=ptrw;
                                adWP=ptrwP->adresW;
                                while(adWP->NUMER!=br3)
                                {
                                    ptrwP=ptrwP->kolejny;
                                    adWP=ptrwP->adresW;
                                }
                                printf("%s",adWP->NazwaW);
                                if(br3!=Kon)
                                    printf("->");
                            }
                        }
                        printf("\n");
                    }//ID1!=ID2
                    else
                        printf("wezel poczatkowy musi byc rozny od koncowego\n");
                }//if(!invW(ptrw,ID2)
                else
                    printf("taki koncowy wezel nie istnieje");
            }//if(!invW(ptrw, ID1)
            else
                printf("taki poczatkowy wezel nie istnieje\n");
        }//if(ptrl!=NULL)
        else
            printf("nie ma zadnych lukow\n");
    }//if(ptrl!=NULL)
    else
        printf("nie ma zadnych wezlow\n");
}
//*********************************************************************************************
//#####################Metoda sprawdzajaca, czy dwa stringi sa identyczne######################
//zwraca 1, gdy oba ciagi sa identyczne
int eqStr(char *radix, char *arbor)
{
    int eq=1,i2=0;
    if(strlen(radix)!=strlen(arbor))
    {
        eq=0;
        return eq;
    }
    for(i2=0; i2<7&&eq&&(arbor[i2]!='\0')&&(radix[i2]!='\0'); i2++)
    {
        if(arbor[i2]!=radix[i2])
        {
            eq=0;
        }
    }
    return eq;
}
//##########################Metoda sprawdzajaca, czy identyfikator jest typu [a-zA-Z0-9]#########
//Zwraca 1, gdy jest poprawnie zapisany
int qualitas(char *obrussa)
{
    int i3=0,spr3=1;
    for(i3=0; i3<7&&spr3&&obrussa[i3]!='\0'; i3++)
    {
        if(!((obrussa[i3]>47&&obrussa[i3]<58)||(obrussa[i3]>64&&obrussa[i3]<91)||(obrussa[i3]>96&&obrussa[i3]<123)||obrussa[i3]=='\0'))
        {
            spr3=0;
            printf("\nNiepoprawna nazwa. Identyfikator musi skladac sie wylacznie z liter i cyfr.\n");
            return spr3;
        }
    }
    return spr3;
}
//#####################Metoda kontrolujaca wpisywanie polecen############################
//parsuje char na cyfre
int daInt(char c)
{
    int n;
    switch(c)
    {
    case 48:
        n=0;
        break;
    case 49:
        n=1;
        break;
    case 50:
        n=2;
        break;
    case 51:
        n=3;
        break;
    case 52:
        n=4;
        break;
    case 53:
        n=5;
        break;
    case 54:
        n=6;
        break;
    case 55:
        n=7;
        break;
    case 56:
        n=8;
        break;
    case 57:
        n=9;
        break;
    }
    return n;
}
//###########################Funkcja glowna programu###################################
int main()
{
//deklaracja listy wezlow i listy lukow
    Lista1 ptrW;
    Lista2 ptrL;
    Hestia tau;
    ptrW=NULL;
    ptrL=NULL;
    int numerW=1;
    char wezel1[7];
    char wezel2[7];
    char luk[7];
    char poleceniePom;
    int polecenie=11;//zmienna kontrolna petli glownej proramu
    printf("Wpisz polecenie:\n 0- wyjscie z programu\n 1- dodaj nowy wezel\n 2- przegladaj wezly\n 3- usun wezel\n 4- dodaj nowy luk\n 5- przegladaj luki\n 6- usun luk\n 7- szukaj drogi od ID1 do ID2\n 8- czy istnieje luk od ID1 do ID2?\n 9- wypisz sasiedztwo zadanego wezla\n");
    while(polecenie!=0)
    {
        poleceniePom=getchar();
        polecenie=daInt(poleceniePom);
        if(polecenie==1)
        {
            scanf(" %s ", wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else //strlen(wezel1)<7
                if(qualitas(wezel1))
                {
                    ptrW=addW(ptrW,wezel1, numerW);
                    numerW++;
                }
        }//if(polecenie==1)
        if(polecenie==2)
        {
            vidW(ptrW);
        }
        if(polecenie==3)
        {
            scanf(" %s",wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else if(qualitas(wezel1))
            {
                tau=delW(wezel1,ptrW,ptrL);
                ptrW=tau->mal;
                ptrL=tau->fem;
            }
        }//if(polecenie==3)
        if(polecenie==4)
        {
            scanf(" %s od %s do %s",luk,wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7||strlen(luk)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                ptrL=addL(luk,wezel1,wezel2,ptrW,ptrL);
        }//if(polecenie==4)
        if(polecenie==5)
        {
            vidL(ptrL,1);
        }
        if(polecenie==6)
        {
            scanf(" %s",luk);
            if(strlen(luk)>7)
            {
                printf("niewlasciwa nazwa");
            }
            else
                ptrL=delL(luk, ptrL,1);
        }//if(polecenie==6)
        if(polecenie==7)
        {
            scanf(" od %s do %s",wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                viaWW(ptrW, numerW+1, ptrL, wezel1, wezel2);
            //printf("jestem w 7");
        }
        if(polecenie==8)
        {
            scanf(" od %s do %s",wezel1,wezel2);
            if(strlen(wezel1)>7||strlen(wezel2)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
                votW(wezel1,wezel2,ptrL,ptrW);
        }//if(polecenie==8)
        if(polecenie==9)
        {
            scanf(" %s",wezel1);
            if(strlen(wezel1)>7)
            {
                printf("niewlasciwa nazwa\n");
            }
            else
            {
                consW(wezel1,ptrW);
            }
        }
    }//    while(polecenie!=0)
}

