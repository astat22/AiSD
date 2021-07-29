class QuickSort extends Sort
{
    public int Partition(int A[], int k, int l)
    {
        int i=k-1,j=l+1,x=A[k],pom;
        while(true)
        {
            i++;
            while(A[i]<x)
            {
                ++i;
		compNum++;
            }//while A[i]>=x
            j--;
            while(A[j]>x)
            {
                --j;
		compNum++;
            }//while A[j]<=x
            if(i<j)
            {
                pom=A[i];
                A[i]=A[j];
                A[j]=pom;
		compNum++;
            }//if i<j
            else
	    {
		compNum++;
                return j;
	    }
        }//while(true)
        //return j;
    }//Partition

    public void QuickSort(int A[], int k, int l)
    {
        int m;
        if(k<l)
        {
	    compNum++;
            m=Partition(A,k,l);
            QuickSort(A,k,m);
            QuickSort(A,m+1,l);
        }
    }//QuickSort
}