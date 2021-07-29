class Statistics
{
    public double average(int[] A)
    {
	double sum=0.0;
	for(int i=0;i<A.length;i++)
	    sum+=(double)A[i];
	return sum/(double)A.length;
    }
    public double variance(int[] A)
    {
	double average = average(A);
	double sum = 0.0;
	for(int i=0;i<A.length;i++)
	    sum+=((double)A[i]-average)*((double)A[i]-average);
	return sum/((double)A.length-1.0);
    }
    public double standardDeviation(int[] A)
    {
	return Math.sqrt(variance(A));
    }
    public double[] conditionalAverage(int[] A, int[] B)
    {
	double[] T = new double[max(B)+1];
	double[] counter = new double[T.length];
	for(int i=0;i<B.length;i++)
	{
	    for(int j=0;j<T.length;j++)
		if(B[i]==j)
		{
		    T[j]+=(double)A[i];
		    counter[j]+=1.0;
		}
	}   
	for(int k=0;k<T.length;k++)
	    T[k]=T[k]/counter[k];
	return T;
    } 
    public int min(int[] Tab)
    {
	int minimum=Tab[0];
	for(int i=1;i<Tab.length;i++)
	    if(Tab[i]<minimum)
		minimum = Tab[i];
	return minimum;
    }
    public int max(int[] Tab)
    {
	int maximum=Tab[0];
	for(int i=1;i<Tab.length;i++)
	    if(Tab[i]>maximum)
		maximum = Tab[i];
	return maximum;
    }
}