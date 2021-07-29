class HeapSort extends Sort
{
    public void Heapify(int A[], int i, int n)
    {
        int l=2*i;
        int r=2*i+1;
        int max=i;
        if(l<n&&A[l]>A[max])
        {
            max=l;
	    compNum+=2;
        }//if A[l]>A[max]
        if(r<n&&A[r]>A[max])
        {
            max=r;
	    compNum+=2;
        }//if A[r]>A[max]
        if(max!=i)
        {
            int pom=A[i];
            A[i]=A[max];
            A[max]=pom;
	    compNum++;
            Heapify(A,max,n);
        }//if max!=i
    }//Heapify

    public void Buildheap(int A[], int n)
    {
        int heapsizeA = n;
        for(int i=(heapsizeA/2)+1;i>=0;i--)
        {
	    compNum++;
            Heapify(A,i,n);
        }//for i=heapsize/2 downto 0
    }//Buildheap

    public void heapSort(int A[], int n)
    {
        int heapsizeA=n;
        Buildheap(A,heapsizeA);
        for(int i=n-1;i>=1;i--)
        {
	    compNum++;
            int pom;
            pom=A[0];
            A[0]=A[i];
            A[i]=pom;
            heapsizeA--;
            Heapify(A,0,heapsizeA);
        }//for i=n-1
    }//Heapsort
}