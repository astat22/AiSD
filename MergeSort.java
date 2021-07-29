class MergeSort extends Sort
{
    public void merge(int A[], int k, int m, int l)
    {
        int i, j, x; 
        int B[]=new int[l];
        i=k;
        j=m+1;
        x=0;
        while(i<=m||j<=l)
        {
	    compNum+=2;
            if(i>m)
            {
                B[x]=A[j];
                j++;
		compNum++;
            }//if i>m
            else
            {
		compNum++;
                if(j>l)
                {
                    B[x]=A[i];
                    i++;
		    compNum++;
                }//if j>l,i<=m
                else
                {
		    compNum++;
                    if(A[i]<A[j])
                    {
                        B[x]=A[i];
                        i++;
			compNum++;
                    }//if j<=l,i<=m,A[i]<A[j]
                    else
                    {
                        B[x]=A[j];
                        j++;
			compNum++;
                    }//j<=l,i<=m,A[i]>=A[j]
                }//else j<=l,i<=m
            }//else i<=m
            x++;
        }//while
        for(i=k;i<l+1;i++)
        {
            A[i]=B[i-k];
	    compNum++;
        }
    }//Merge
//sortowanie przez scalanie
    public void mergeSort(int A[], int k, int l)
    {
        int m;
        if(k<l)
        {
	    compNum++;
            m=(k+l)/2;
	    //System.out.println(k+" "+l);
            mergeSort(A,k,m);
            mergeSort(A,m+1,l);
            merge2(A,k,m,l);
        }
    }//MergeSort
    public void merge2(int A[], int p, int q, int r)
    {
	int B[]=new int[r-p+1];
	int i=p, j=q+1, k=0;
	while(i<=q && j<=r)
	{
	    compNum+=2;
	    if(A[i]<=A[j])
	    {
		B[k]=A[i];
		i++;
		compNum++;
	    }
	    else
	    {
		B[k]=A[j];
		j++;
		compNum++;
	    }
	    k++;
	}
	while(i<=q)
	{
	    B[k]=A[i];
	    i++;
	    k++;
	    compNum++;
	}
	while(j<=r)
	    {
		B[k]=A[j];
		j++;
		k++;
		compNum++;
	    }
	/*for(int o=0;o<B.length;o++)
	    System.out.print(B[o]+" ");
	System.out.println("");*/
	for(int k2=0; k2<B.length; k2++)
	{
	    A[p+k2]=B[k2];
	    compNum++;
	}	
    }
}