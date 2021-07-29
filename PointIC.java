class PointIC
{
    private int inversions = -1;
    private int comparisons = -1;
    public void setPoint(int inversions, int comparisons)
    {
	this.inversions = inversions;
	this.comparisons = comparisons;
    }
    public int getInversions()
    {
	return inversions;
    }
    public int getComparisons()
    {
	return comparisons;
    }
}