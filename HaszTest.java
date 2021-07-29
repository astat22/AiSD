//Jacek Mucha
//29 listopada 2013
//Eksperymenty na tablicy haszowanej

import java.util.*;
import java.io.*;

public class HaszTest
{
    public int[][] linearTab; 
    int[] sitoEr;
    public HaszTest()
    {
	System.out.println("Usuwanie starych plikow...");
	prepareSpace();
	sitoEr = sitoEratostenesa();
	linearTab=new int[100][]; 		//tablica dla adresowania liniowego
	for (int i=0;i<100;i++)
	{
	    linearTab[i]=new int[100*(i+1)];	//tworze tablice rozmiaru m \in {100,200,...10000}
	    clearLinearTab(i);			//bede wstawiac liczby nieujemne, wiec chce "oproznic" tablice
	}
	System.out.println("Testowanie adresowania liniowego...");
	linearTesting(1);			//adresowanie liniowe. testy.
	System.out.println("Zakonczono testowanie adresowania liniowego...\nUsrednianie po m i n...");
	analysis(1);				//usrednianie
        for(int i=0;i<100;i++)			//teraz ta tablica zostanie wykorzystana do adresowania kwadratowego
	{
	    linearTab[i]=new int[4*d(i)];
	    clearLinearTab(i);
	}
	System.out.println("Testowanie adresowania kwadratowego...");
	linearTesting(2);			//adresowanie kwadratowe. testy.
	System.out.println("Zakonczono testowanie adresowania kwadratowego...\nUsrednianie...");
	analysis(2);
	//int[] M=sitoEratostenesa();
	linearTab = new int[sitoEr.length][];	//teraz ta tablica zostanie wykorzystana do adresowania podwojnego
	//System.out.println("Sito utworzone...");
	for(int i=0;i<sitoEr.length;i++)
	{
	    linearTab[i]=new int[sitoEr[i]];
	    clearLinearTab(i);
	}
	System.out.println("Testowanie adresowania podwojnego...");
	linearTesting(3);
	System.out.println("Zakonczono testowanie adresowania podwojnego...\nAnaliza statystyczna...");
	analysis(3);
	System.out.println("Program poprawnie zakonczyl dzialanie.");
    }
    public void clearLinearTab(int numOfTab)	//oproznianie tablicy o rozmiarze (numOfTab+1)*100 do adresowania liniowego
    {
	for(int i=0;i<linearTab[numOfTab].length;i++)
	    linearTab[numOfTab][i]=-1;		//klucze sa nieujemne, wiec wstawiam cos ujemnego
    }
    public int d(int i)
    {
	return (i+1)*25;
    }
    public int hLin(int k, int m)		//adresowanie liniowe
    {
	boolean done = false;			//zmienna kontrolna: czy element zostal wstawiony?
	int i=1;
	while(!done)				//powtarzaj, dopoki nie znajdziesz pustego miejsca
	{
	    if(linearTab[(m/100)-1][(hPrim(k,m)+i)%m]<0)  //puste miejsce
	    {
		linearTab[(m/100)-1][(hPrim(k,m)+i)%m]=k; //wstaw klucz w puste miejsce
		done = true;				  //ustaw warunek przerwania petli
	    }
	    i++;					  //zliczaj liczbe prob wstawienia
	}
	return i-1;					  //zwroc liczbe prob (a nie miejsce)
    }
    public int modul(int k)
    {
	return k>=0? k:-k;
    }
    public int hSquare(int k, int j)
    {
        boolean done = false;
	int i=1, c2=2*d(j), c1=1, m = 4*d(j);
	while(!done)
	{
	    if(linearTab[j][modul((int)((long)(hPrim(k,m)+c1*i+(long)(c2*i*i))%(m)))]<0)
	    {
		linearTab[j][modul((int)((long)(hPrim(k,m)+c1*i+(long)(c2*i*i))%(m)))]=k;
		done = true;
	    }
	    i++;
	}
	return i-1;
    }
    public int hDb(int k, int j)
    {
	int i=1;
	boolean done = false;
	int m = linearTab[j].length;
	while(!done)
	{
	    if(linearTab[j][modul((hPrim(k,m)+i*hBis(k,m))%m)]<0)
	    {
		done = true;
		linearTab[j][modul((hPrim(k,m)+i*hBis(k,m))%m)]=k;
	    }
	    i++;
	}
	return i-1;
    }
    public int hPrim(int k, int m)			//funkcja h'(k) = k mod m 
    {
	return k%m;
    }
    public int hBis(int k,int m)
    {
        return 1+(k%(m-1));
    }
/** Java nie udostêpnia metody int pow(int n, int m) */
    public int MyPow(int base, int exponent)
    {
	int pow = 1;
	for(int i=exponent;i>0;i--)
            pow=pow*base;
        return pow;
    }
    public int randomInt(int exp)
    {
	int a,number=0;
	Random r = new Random();
	for(int j=0;j<=exp;j++)
	{
	    a= r.nextBoolean() ? 0 : 1;
	    number+=a*MyPow(2,j);
	}
        return number;
    }
    public void linearTesting(int chose)
    {
	int m,t=0;
	try 
	{
	    File file;
	    if(chose==1)
	        file = new File("linear.dat");
	    else
		if(chose==2)
		    file = new File("sqr.dat");
		else 
		    file = new File("db.dat");
	    RandomAccessFile raf = null;
	    try
	    {
                raf = new RandomAccessFile(file,"rw");
		System.out.println("Otworzono plik...");
	        for(int i=0; i<linearTab.length; i++)
	        {
	            m=linearTab[i].length;
                    for(int j=0;j<50;j++)
	            {
		        for(int n=0;n<linearTab[i].length;n++)
		        {
			    if(chose==1)
		                t=hLin(randomInt(18),m);   
			    else
				if(chose==2)
				    t=hSquare(randomInt(18), i);
				else
				    t=hDb(randomInt(18),i);
			    if(n%(Math.ceil((double)m/50))==0)
				//raf.writeBytes(Integer.toString(m)+" "+Integer.toString(n)+" "+Integer.toString(t)+"\n");
				raf.writeBytes(m+" "+n+" "+t+"\n");

		        }
		        clearLinearTab(i);
			//System.out.println(m+" "+j);
    	            }
	        }
	        raf.close();
	    }
	    catch(FileNotFoundException e1)
	    {
	    }
	}
	catch(IOException e2)
	{
	}
    }
    public void analysis(int kind)
    {
	double[][] analysis = new double[linearTab.length][10001];
	int[][] counter = new int[linearTab.length][10001];
	Scanner s = null;
	String line;
	int m,n;
	double t;
	try
	{
	   if(kind==1)
	   {
		s = new Scanner(new BufferedReader(new FileReader("linear.dat")));
	   }   
	   else
		if(kind==2)
		{
		    s = new Scanner(new BufferedReader(new FileReader("sqr.dat")));
		}
		else
		{
		    s = new Scanner(new BufferedReader(new FileReader("db.dat")));
		}
	    while(s.hasNextInt())
	    {
		m=s.nextInt();
		m=getIndex(m,kind);
		if(s.hasNextInt())
		{
		    n=s.nextInt();
		    if(s.hasNextInt())
		    {
		        t=(double)s.nextInt();
			if(0<=m && m<analysis.length)
			{
			    if(0<=n && n<analysis[m].length)
			    {
		                analysis[m][n]+=t;
		                counter[m][n]++;
			    }
			}
		        //System.out.print(".");
		    }
		}
	    }
	    System.out.println("Odczytano dane z pliku...");
	}
	catch(FileNotFoundException e3)
	{
	}
	File file;
	RandomAccessFile raf = null;

	try
	{
	    try
	    { 
	        if(kind==1)
	            file = new File("lA.dat");
	        else
		    if(kind==2)
		        file = new File("sA.dat");
		    else 
		        file = new File("dA.dat");
		int X;
                raf = new RandomAccessFile(file,"rw");
		for(int i=0;i<linearTab.length;i++)
		{
		    for(int j=0;j<10001;j++)
		    {
			if(counter[i][j]>0)
			{
			    if(kind<3)
				X=100*(i+1);
			    else
				X=sitoEr[i];
			    raf.writeBytes(X+" "+j+" "+(double)(analysis[i][j]/counter[i][j])+"\n");  
			}
		    }
		}
		raf.close();
		System.out.println("Zakonczono analizowanie danych - wynikowy plik zamkniety...");
	    }
	    catch(FileNotFoundException e5)
	    {
	    }
	}
	catch(IOException e4)
	{
	}
    }
    public int getIndex(int m, int kind)
    {
	if(kind==1)
	    return modul(m/100-1);
	else
	    if(kind==2)
		return modul((m/4)/25-1);
	    else
	    {
		int i=0;
		while(i<linearTab.length && m<linearTab[i].length)
		{
		    i++;
		}
		return i;
            }
    }
    public static void main(String[] args)
    {
        HaszTest mainObject = new HaszTest();
    }
    public int[] sitoEratostenesa()
    {
	int counter=0;
	boolean[] sito = new boolean[10001];
	for(int i=2;i<10001;i++)
	    sito[i]=true;
	sito[0]=false; sito[1]=false;
	for(int i=2;i<10001;i++)
	{
	    if(sito[i])
	    {
		if(i>=100)
		{
		    counter++;
		    //System.out.print(i+" ");
		}
		for(int j=2*i;j<10001;j+=i)
		{
		    sito[j]=false;
		}
	    }
	}
	int[] M = new int[counter/10+1];
	int j=0;
	for(int i=100;i<10001;i++)
	{
	    if(sito[i])
	    {
		if(j%10==0)
		{
		    M[j/10]=i;
		    //System.out.print(M[j/10]+" ");
		}
		j++;
	    }
	}
	//System.out.println("Sito koniec.");
	return M;
    }
	public void prepareSpace()
	{
	    File file = new File("linear.dat");
	    file.delete();
	    file = new File("sqr.dat");
	    file.delete();
	    file = new File("db.dat");
	    file.delete();
	    file = new File("lA.dat");
	    file.delete();
	    file = new File("sA.dat");
	    file.delete();
	    file = new File("dA.dat");
	    file.delete();
	    System.out.println("Procedura usuwania starych plikow zakonczona...");
	}
}
