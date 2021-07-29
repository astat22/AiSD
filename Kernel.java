import java.util.Random.*;
import java.util.*;
import java.lang.Math.*;
import java.io.*;

/** J¹dro programu, tutaj wykonuje siê wszystkie ogólne operacje w programie. Uwaga - nie jest to klasa g³ówna. */
public class Kernel
{
/** Obiekt wykonuj¹cy obliczenia statystyczne. */
    public Statistics statistics;
/** Obiekt z metodami sortowania przez wstawianie. */
    public InsertionSort insSort;
/** Obiekt z metodami sortowania przez scalanie. */
    public MergeSort mrgSort;
/** Obiekt z metodami sortowania przez kopcowanie. */
    public HeapSort hpSort;
/** Obiekt z metodami szybkiego. */
    public QuickSort qckSort;
/** Tablica danych do posortowania dla algorytmu insertionSort*/
    public static int[] insertionSortData;
/** Tablica danych do posortowania dla algorytmu mergeSort*/
    public static int[] mergeSortData;
/** Tablica danych do posortowania dla algorytmu heapSort*/
    public static int[] heapSortData;
/** Tablica danych do posortowania dla algorytmu quickSort*/
    public static int[] quickSortData;
/** Wyniki obliczeñ (otrzymane punkty p³aszczyzny) dla sortowania przez wstawianie */
    //public static PointIC[] insertionSortResults;
    public static int[] insertionSortResults;
/** Wyniki obliczeñ (otrzymane punkty p³aszczyzny) dla sortowania przez scalanie */
    //public static PointIC[] mergeSortResults;
    public static int[] mergeSortResults;
/** Wyniki obliczeñ (otrzymane punkty p³aszczyzny) dla sortowania przez kopcowanie */
    //public static PointIC[] heapSortResults;
    public static int[] heapSortResults;
/** Wyniki obliczeñ (otrzymane punkty p³aszczyzny) dla sortowania szybkiego */
    //public static PointIC[] quickSortResults; 
    public static int[] quickSortResults;
    public static int[] inversions;
    public int invControl;
/** Konstruktor g³ówny. Obs³uguje funkcjonalne wykonanie programu.
* @param Switches - prze³¹cznik obs³ugiwania konkretnych rodzajów sortowania.
* @see Aplikacja#Switches
*/
    public Kernel(boolean Switches[], String fileName, int numOfTests, int dataSize, int dataKind, int inversionCountingKind)
    {
	inversions = new int[numOfTests];
	invControl = inversionCountingKind;
	statistics = new Statistics();
	if(Switches[0])
	{
	    insertionSortData = new int[dataSize];
	    insertionSortResults = new int[numOfTests]; //PointIC[numOfTests];
	    insSort = new InsertionSort();
	}
	if(Switches[1])
	{
	    mergeSortData = new int[dataSize];
	    //mergeSortResults = new PointIC[numOfTests];
	    mergeSortResults = new int[numOfTests];
	    mrgSort = new MergeSort();
	}
	if(Switches[2])
	{
	    heapSortData = new int[dataSize];
	    //heapSortResults = new PointIC[numOfTests];
	    heapSortResults = new int[numOfTests];
	    hpSort = new HeapSort();
	}
	if(Switches[3])
	{
	    quickSortData = new int[dataSize];
	    //quickSortResults = new PointIC[numOfTests];
	    quickSortResults = new int[numOfTests];
	    qckSort = new QuickSort();
	}

	if(Switches[4])
	{
	    int dataBase[][] = new int[numOfTests][];
	    for(int i=0;i<numOfTests;i++)
		dataBase[i] = new int[dataSize];
	}
	for(int testNr=0;testNr<numOfTests;testNr++)
	{
	    if(dataKind==1)
	        //randPermutation(getMinSwitch(Switches),dataSize);
		betterRandPermutation(getMinSwitch(Switches),dataSize);
	    else if(dataKind==2)
	        createData(getMinSwitch(Switches),12);
	    //POZOSTAJE STWORZYÆ METODY DLA DATAKIND 3 i 4
	    //int inv = numOfInversions(dataName(getMinSwitch(Switches)));
	    if(inversionCountingKind==1)
	        inversions[testNr] = numOfInversions(dataName(getMinSwitch(Switches)));
	    else if(inversionCountingKind==2)
	    {
	        inversions[testNr] = inversionsNumberModified(dataName(getMinSwitch(Switches)));
		//System.out.println(inversions[testNr]);
	    }
	    else if(inversionCountingKind==3)
	    {
	        inversions[testNr] = inversionsNumberModified2(dataName(getMinSwitch(Switches)));
		//System.out.println(inversions[testNr]);
	    }

	    rewrite(Switches);
	    if(Switches[4])
	    {
		readData(dataName(getMinSwitch(Switches)));
		//System.out.println("");
	    }
	    //System.out.print("inv = "+inversions[testNr]+" ");
	    if(Switches[0])
	    {
		//insertionSortResults[testNr] = new PointIC();
		insSort.insertionSort(insertionSortData);
		insertionSortResults[testNr]=insSort.readCompNum(); //setPoint(inv,insSort.readCompNum());
		insSort.clearCompNum();
		//readData(insertionSortData);
		//System.out.print("ins = "+insertionSortResults[testNr].getComparisons()+" ");
		//System.out.print("ins = "+insertionSortResults[testNr]+" ");
	    }
	    if(Switches[1])
	    {
		//readData(mergeSortData); 
		//mergeSortResults[testNr] = new PointIC();
		mrgSort.mergeSort(mergeSortData,0,dataSize-1);
		//dataBase[1][testNr] = mrgSort.readCompNum();
		mergeSortResults[testNr] = mrgSort.readCompNum();//.setPoint(inv,mrgSort.readCompNum());
		mrgSort.clearCompNum();
		//readData(mergeSortData);
		//System.out.print("mrg = "+mergeSortResults[testNr].getComparisons()+" ");
		//System.out.print("mrg = "+mergeSortResults[testNr]+" ");
	    }
	    if(Switches[2])
	    {
		//heapSortResults[testNr] = new PointIC();
		hpSort.heapSort(heapSortData,dataSize);
		//dataBase[2][testNr] = hpSort.readCompNum();
		heapSortResults[testNr] = hpSort.readCompNum(); //.setPoint(inv,hpSort.readCompNum());
		hpSort.clearCompNum();
		//readData(heapSortData);
		//System.out.print("hp = "+heapSortResults[testNr].getComparisons()+" ");
		//System.out.print("hp = "+heapSortResults[testNr]+" ");
	    }
	    if(Switches[3])
	    {
		//quickSortResults[testNr] = new PointIC();
		qckSort.QuickSort(quickSortData,0,dataSize-1);
		//dataBase[3][testNr] = qckSort.readCompNum();
		quickSortResults[testNr] = qckSort.readCompNum(); //.setPoint(inv,qckSort.readCompNum());
		qckSort.clearCompNum();
		//readData(quickSortData);
		//System.out.print("qck = "+quickSortResults[testNr].getComparisons()+" ");
		//System.out.print("qck = "+quickSortResults[testNr]+" ");
	    }
	    //System.out.println("");
	}
	if(Switches[5])
	{
	    if(fileName == "")
		fileName = "dane"+dataSize+".txt";
	    File file = new File(fileName);
	    if(file.exists())
	    {
		
	    }
	    else
	    {
		RandomAccessFile raf = null;
		try
		{
		    raf = new RandomAccessFile(file,"rw");
		    for(int lineCounter = 0; lineCounter<numOfTests; lineCounter++)
		    {
			raf.writeBytes(Integer.toString(inversions[lineCounter]));
			if(Switches[0])
			{
			    raf.writeBytes("\t");
			    //raf.writeInt(insertionSortResults[lineCounter]);
			    raf.writeBytes(Integer.toString(insertionSortResults[lineCounter]));
			}
			if(Switches[1])
			{
			    raf.writeBytes("\t");
			    //raf.writeInt(mergeSortResults[lineCounter]);
			    raf.writeBytes(Integer.toString(mergeSortResults[lineCounter]));
			}
			if(Switches[2])
			{
			    raf.writeBytes("\t");
			    //raf.writeInt(heapSortResults[lineCounter]);
			    raf.writeBytes(Integer.toString(heapSortResults[lineCounter]));
			}
			if(Switches[3])
			{
			    raf.writeBytes("\t");
			    //raf.writeInt(quickSortResults[lineCounter]);
			    raf.writeBytes(Integer.toString(quickSortResults[lineCounter]));
			}
			raf.writeBytes("\n");
		    }
		    raf.close();
		}
		catch(FileNotFoundException e1)
		{
		}
		catch(IOException e2)
		{
		}
	    }
	}
    }
/** Metoda zliczaj¹ca liczbê inwersji w tablicy danych
* @param Tab[] tablica danych, w której zliczane s¹ inwersje.
* @return inversions Liczba inwersji w tablicy.
*/
    public int numOfInversions(int Tab[])
    {
	int inversions = 0;
	for(int i=0;i<Tab.length-1;i++)
	    for(int j=i+1;j<Tab.length;j++)
		if(Tab[j]<Tab[i])
		    inversions++;
	return inversions;
    }
/** */
    public void readData(int sortData[])
    {
	for(int i=0;i<sortData.length;i++)
	    System.out.print(sortData[i]+" ");
	System.out.println("");
    }
/** Metoda wybieraj¹ca tabelê danych danego sortowania.
* @param sortKind Numer sortowania. 0 - insertionSort, 1 - mergeSort, 2 - heapSort, poza tym quickSort
* @return Zwraca dane dla danego sortowania.
*/
    public int[] dataName(int sortKind)
    {
	if(sortKind==0)
	    return insertionSortData;
	else if(sortKind==1)
	    return mergeSortData;
	else if(sortKind==2)
	    return heapSortData;
	else
	    return quickSortData;	    
    }
/** Metoda wybieraj¹ca najmniejszy w tablicy Switches[] z wybranych rodzajów sortowania
*/
    public int getMinSwitch(boolean Switches[])
    {
	for(int i=0; i<4; i++)
	    if(Switches[i])
		return i;
	return -1; //nie zdarzy siê. przechwytuje to wyj¹tek w Aplikacja.class
    }
/** Metoda do generowania losowych danych w tablicy 
* @param dataKind Mówi, w której tablicy chcemy utworzyæ dane.
* @param exp Mówi, z jak¹ potêg¹ maj¹ byæ generowane dane.
* @see dataName(int)
*/
    public void createData(int dataKind, int exp)
    {
	int a;
	Random r = new Random();
	for(int i=0;i<dataName(dataKind).length;i++)
	    for(int j=0;j<=exp;j++)
	    {
		a= r.nextBoolean() ? 0 : 1;
		dataName(dataKind)[i]+=a*MyPow(2,j);
	    }
    }
/** Java nie udostêpnia metody int pow(int n, int m) */
    public int MyPow(int base, int exponent)
    {
	int pow = 1;
	for(int i=exponent;i>0;i--)
            pow=pow*base;
        return pow;
    }
/** Metoda generuj¹ca losow¹ permutacjê */
    public void randPermutation(int dataKind, int dataLength)
    {
	Random r = new Random();
	boolean control=true;
	int pos;
	for(int i=0;i<dataLength;i++)
	{
	    dataName(dataKind)[i]=0;
	}
	for(int i=0;i<dataLength;i++)
	{
	    control=true;
	    while(control)
	    {
		pos=Math.abs(r.nextInt()) % dataLength;
	        if(dataName(dataKind)[pos]==0)
		{
		    dataName(dataKind)[pos]=i+1;
		    control = false;
		}
	    }
	}//for i=0 upto dataLength
    }
/** Szybka metoda generuj¹ca losowe permutacje */
    public void betterRandPermutation(int dataKind, int dataLength)
    {
	Random r = new Random();
	int pos;
	for(int i=0;i<dataLength;i++)
	{
	    dataName(dataKind)[i]=i+1;
	}	
	for(int j=0;j<dataLength;j++)
	{
	    pos = Math.abs(r.nextInt())%(dataLength-j)+j;
	    swap(dataName(dataKind),j,pos);  
	}//zamien j z losowym miejscem od j do dataLength
    }
/** Metoda zamieniaj¹ca dwa elementy w tablicy */
    public void swap(int T[], int first, int second)
    {
	int x=T[first];
	T[first]=T[second];
	T[second]=x;
    }
/** Metoda kopiuj¹ca tablice. */
    private void rewrite(boolean[] sw)
    {
	for(int i=getMinSwitch(sw)+1;i<4;i++)
	    if(sw[i])
		for(int j=0;j<dataName(i).length;j++)
		    dataName(i)[j]=dataName(getMinSwitch(sw))[j];
    }
/** Metoda zwracaj¹ca tablicê wyników. */
    public int[] resultsName(int sortKind)
    {
	if(sortKind==0)
	    return insertionSortResults;
	else if(sortKind==1)
	    return mergeSortResults;
	else if(sortKind==2)
	    return heapSortResults;
	else
	    return quickSortResults;	    
    }
/** Metoda zliczaj¹ca liczbê inwersji postaci (i,i+1) */
    public int inversionsNumberModified(int[] data)
    {
/** Licznik */
	int counter = 0;
	for(int i=0;i<data.length-1;i++)
	    if(data[i]==data[i+1]-1)
		counter++;
	return counter;
    }
/** Metoda zliczaj¹ca liczbê inwersji postaci (i,i+1) II */
    public int inversionsNumberModified2(int[] data)
    {
/** Licznik */
	int counter = 0;
	for(int i=0;i<data.length;i++)
	    if(data[i]==i+2) //bo nr w tablicy +1
		counter++;
	return counter;
    }
}