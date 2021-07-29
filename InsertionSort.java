class InsertionSort extends Sort
{
    public InsertionSort()
    {
    }
    public void insertionSort(int Tab[])
    {
	int x, j;
        for(int i=1; i<Tab.length;i++)
        {
	    compNum++;
            x=Tab[i];
            j=i-1;
            while(j>-1&&Tab[j]>x)
            {
                Tab[j+1]=Tab[j];
                j=j-1;
		compNum++;
            }
            Tab[j+1]=x;
        }
    }
}