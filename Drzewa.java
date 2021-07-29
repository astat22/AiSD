//Jacek Mucha
//29 grudnia 2013
//Eksperymenty na drzewie RB i BST

import java.util.*;
import java.io.*;

public class Drzewa
{
    public TreeRBT wartownik;
    
    public TreeRBT drzewoRBT;
    public Tree drzewoBST;
    public int[] array; 
    public int arraySize = 10000;
    public int exponent = 19;
    public File fileBST, fileRBT, delBST, delRBT;
    public Drzewa()
    {
	RBT rbt = new RBT();
	BST bst = new BST();
	boolean c1,c2;
	fileBST = new File("insertBST.txt");
	fileRBT = new File("insertRBT.txt");
	delBST = new File("deleteBST.txt");
	delRBT = new File("deleteRBT.txt");
	fileBST.delete();
	fileRBT.delete();
	delBST.delete();
	delRBT.delete();
	fileBST = new File("insertBST.txt");
	fileRBT = new File("insertRBT.txt");
	delBST = new File("deleteBST.txt");
	delRBT = new File("deleteRBT.txt");
	try { 
	try {
	    RandomAccessFile bstRAF = new RandomAccessFile(fileBST,"rw");
	    RandomAccessFile rbtRAF = new RandomAccessFile(fileRBT,"rw");
	    RandomAccessFile bstDelRAF = new RandomAccessFile(delBST,"rw");
	    RandomAccessFile rbtDelRAF = new RandomAccessFile(delRBT,"rw");	
	    array = new int[arraySize];
	    for(int test = 0; test<100;test++)
	    {
		System.out.print(".");
		if((test+1)%10==0)
		    System.out.print("|");
	        bst.RandArray(array,arraySize,exponent);
	        for(int k=0;k<arraySize;k++)
	        {
		    bst.licznik = 0;
		    rbt.licznik = 0;
		    bst.root = bst.Insert(bst.root,array[k]);
		    rbt.root = rbt.InsertRBT(rbt.root,array[k],rbt.wartownik);
		    if((k+1)%10==0)
		    {
			bstRAF.writeBytes(Integer.toString(k+1)+"\t"+Integer.toString(bst.licznik)+"\n");
			rbtRAF.writeBytes(Integer.toString(k+1)+"\t"+Integer.toString(rbt.licznik)+"\n");
		    }
	        }
	        //bst.root = bst.TabToTree(bst.root,array,arraySize);
	        //rbt.root = rbt.TabToTree(rbt.root,array,arraySize);

    	        betterRandPermutation(arraySize);
	        for(int i=0;i<arraySize;i++)
	        {
		    if(bst.Search(bst.root, array[i])!=null)
		    {
			bst.licznik = 0;
	                bst.root = bst.TreeDelete(bst.root,bst.Search(bst.root, array[i]));
			c1 = true;
		    }
		    else
			c1=false;
		    if(rbt.Search(rbt.root,array[i],rbt.wartownik)!=null)
			c2=true;
		    else c2=false;
		    if(c2)
		    {
	                rbt.licznik = 0;
			rbt.root = rbt.DeleteRBT(rbt.root,rbt.Search(rbt.root,array[i],rbt.wartownik),rbt.wartownik);
		    }
		    if((arraySize-i)%10==0)
		    {
			if(c1) bstDelRAF.writeBytes(Integer.toString(arraySize-i)+"\t"+Integer.toString(bst.licznik)+"\n");
			if(c2) 
			{
			    //System.out.print(".");
			    rbtDelRAF.writeBytes(Integer.toString(arraySize-i)+"\t"+Integer.toString(rbt.licznik)+"\n");
			}
		    }
	        }
	    }
	    bstRAF.close();
	    rbtRAF.close();
	    bstDelRAF.close();
	    rbtDelRAF.close();
        }
	catch(FileNotFoundException e1)
	{
	}}
	catch(IOException e2)
	{
	}
    }
/** Szybka metoda generuj¹ca losowe permutacje */
    public void betterRandPermutation(int dataLength)
    {
	Random r = new Random();
	int pos;	
	for(int j=0;j<dataLength;j++)
	{
	    pos = Math.abs(r.nextInt())%(dataLength-j)+j;
	    swap(array,j,pos);  
	}//zamien j z losowym miejscem od j do dataLength
    }
/** Metoda zamieniaj¹ca dwa elementy w tablicy */
    public void swap(int T[], int first, int second)
    {
	int x=T[first];
	T[first]=T[second];
	T[second]=x;
    }
    public static void main(String args[])
    {
	Drzewa test = new Drzewa();
    }
}

class Tree
{
   public Tree pater;
   public int key;
   public Tree left;
   public Tree right;
   public int level; //pietro drzewa
}
class TreeRBT
{
   public TreeRBT()
   {
	pater = null;
	left = null;
	right = null;
	key = -1;
	int level = 0;
	color = false;
   }
   public TreeRBT pater;
   public int key;
   public TreeRBT left;
   public TreeRBT right;
   public int level; //pietro drzewa
   public boolean color; //0 czarny 1 czerwony
}

class RBT
{
    public int licznik = 0;
    public boolean red = true;
    public boolean black = false;
    public int MaxLevelRBT = 0;
    public int MaxLevelBST = 0;
    public TreeRBT root;
    public TreeRBT wartownik;
    public RBT()
    {
	wartownik = new TreeRBT();
	wartownik.left = root;
	wartownik.right = root;
	wartownik.color = false;
	wartownik.pater = wartownik;
	wartownik.level = 0;
	wartownik.key = -1;
    }
//przepisz tablice do drzewa
    public TreeRBT TabToTree(TreeRBT T, int A[], int N)
    {
         for(int i=0;i<N;i++)
             T=InsertRBT(T,A[i],wartownik);
         return T;
    }//TabToTree
    public void InOrder(TreeRBT x, int N, TreeRBT wartownik)
    {
	licznik++;
        if(x!=wartownik && x!=null)
        {
             InOrder(x.left, N-1, wartownik);
             int K=x.key;
             System.out.print(K+" ");
             InOrder(x.right, N-1,wartownik);
        }
    }//InOrder
    TreeRBT Search(TreeRBT x, int k, TreeRBT wartownik)
    {
        if(x==wartownik || x.key==k || x==null)
	{
	    licznik+=2;
            return x;
	}
        else
        {
	    licznik+=2;
            if(k<x.key)
                return Search(x.left,k,wartownik);
            else
                return Search(x.right,k,wartownik);
            //return x;
        }      
    }//SearchRBT
    TreeRBT Min(TreeRBT T, TreeRBT wartownik)
    {
	licznik++;
        if(T!=wartownik && T!=null)
	{
            while(T.left!=wartownik && T.left!=null)
	    {
		licznik++;
                T=T.left;
	    }
	}
        return T;
    }//MinRBT
    TreeRBT Max(TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x!=wartownik && x!=null)
	{
            while(x.right!=wartownik  && x.right!=null)
	    {
		licznik++;
                x=x.right;
	    }
	}
        return x;    
    }//MaxRBT
    TreeRBT Root(TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x==wartownik || x==null)
            return x;
        else 
	{
	    while(x.pater!=wartownik && x.pater!=null)
	    {
		licznik++;
        	x=x.pater;
	    }
    	    return x; 
        }
    }//Root
    TreeRBT Successor(TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x!=Max(Root(x,wartownik),wartownik))
        {
	    licznik++;
            TreeRBT ret;
            if(x.right!=wartownik)
    	    {
        	ret=Min(x.right,wartownik);
        	return ret;
    	    }
    	    TreeRBT y=x.pater;
    	    while(y!=wartownik && x.pater!=wartownik && x==x.pater.right)
            {
		licznik+=3;
        	y=y.pater;
        	x=x.pater;
    	    }
    	    return y;
        }
        else 
	    return x;
    }//Successor2
    TreeRBT Predecessor(TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x!=Min(Root(x,wartownik),wartownik))
        {
	    licznik++;
            if(x.left!=wartownik)
	    {
                return Max(x.left,wartownik);
	    }
            TreeRBT y=x.pater;
    	    while(y!=wartownik && x==y.left)
            {
		licznik+=2;
                x=y;
                y=y.pater;
            }
            return y;
        }
        else 
	    return x;
    }//Predecessor2
    
    public TreeRBT RightRotate(TreeRBT T, TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x.left==wartownik)
        {
            System.out.println("brak lewego syna x przy prawej rotacji");
            return T;
        }
        TreeRBT y=x.left;
        x.left=y.right;
	licznik++;
        if(y.right!=wartownik)
	{
            (y.right).pater=x;
	}
        y.pater=x.pater;
        TreeRBT ret=T;
	licznik++;
        if(x.pater==wartownik)
            ret=y;
        else
	{
	    licznik++;
            if(x==(x.pater).left)
                (x.pater).left=y;
            else
                (x.pater).right=y;
	}
        x.pater=y;
        y.right=x;
        return ret;            
    }//RightRotate
    TreeRBT LeftRotate(TreeRBT T, TreeRBT x, TreeRBT wartownik)
    {
	licznik++;
        if(x.right==wartownik)
        {
             System.out.println("brak prawego syna x przy lewej rotacji");
            return T;
        }
        TreeRBT y=x.right;
        x.right=y.left;
	licznik++;
        if(y.left!=wartownik)
            (y.left).pater=x;
        y.pater=x.pater;
        TreeRBT ret=T;
	licznik++;
        if(x.pater==wartownik)
            ret=y;
        else
	{
	    licznik++;
            if(x==(x.pater).left)
                (x.pater).left=y;
            else
                (x.pater).right=y;
	}
        y.left=x;
        x.pater=y;
        return ret;
    }//LeftRotate
    TreeRBT InsertRBT(TreeRBT T, int kz, TreeRBT wartownik)
    {
        TreeRBT y=wartownik;
        TreeRBT x=Root(T,wartownik);
        TreeRBT z = new TreeRBT();
        z.pater=wartownik;
        z.left=wartownik;
        z.right=wartownik;
        z.key=kz;
	licznik++;
        if(x==null || x==wartownik)
        {
            z.color=false;
            return z;
        }
        while(x!=wartownik)
        {
	    licznik++;
            y=x;
            if(z.key<x.key)
                x=x.left;
            else
                x=x.right;
	    licznik++;
        }          
        z.pater=y;
	licznik++;
        if(y==wartownik)
        {
            z.color=false;
            return z;
        }
        else
	{
            if(z.key<y.key)
                y.left=z;
            else
                y.right=z;
	    licznik++;
	}
        z.color=true;
        T=FixupRBT(T,z,wartownik);
        return T;
    }//InsertRBT
    TreeRBT FixupRBT(TreeRBT T, TreeRBT z, TreeRBT wartownik)
    {
        TreeRBT y;
        while(z.pater.color)
        {
	    licznik+=2;
            if(z.pater==z.pater.pater.left)
            {
                y=z.pater.pater.right;
		licznik++;
                if(y.color)
                {
                    z.pater.color=black;
                    y.color=false;
                    z.pater.pater.color=true;
                    z=z.pater.pater;
                }// if y red
                else
                {
		    licznik++;
                    if(z==z.pater.right)
                    {
                        z=z.pater;
                        T=LeftRotate(T,z,wartownik);
                    }// z prawym synem swego ojca
                    z.pater.color=false;
                    z.pater.pater.color=true;
                    T=RightRotate(T,z.pater.pater,wartownik);
                }// if y black
            }
            else
            {
                y=z.pater.pater.left;
		licznik++;
                if(y.color)
                {
                    z.pater.color=false;
                    y.color=false;
                    z.pater.pater.color=true;
                    z=z.pater.pater;
                }
                else
                {
		    licznik++;
                    if(z==z.pater.left)
                    {
                        z=z.pater;
                        T=RightRotate(T,z,wartownik);
                    }
                    z.pater.color=false;
                    z.pater.pater.color=true;
                    T=LeftRotate(T,z.pater.pater,wartownik);
                }
            }
        }
        y=Root(T,wartownik);
        y.color=false;
        return T;
    }//FixupRBT
    TreeRBT TransplantRBT(TreeRBT T, TreeRBT u, TreeRBT v, TreeRBT wartownik)
    {
	licznik++;
        if(u.pater==wartownik)
        {
            return v;
        }
        else
	{
	    licznik++;
            if(u==u.pater.left)
                u.pater.left=v;
            else u.pater.right=v;
	}
        v.pater=u.pater;
        return T;
    }//TransplantRBT
    TreeRBT DeleteFixupRBT(TreeRBT T, TreeRBT x,TreeRBT wartownik)
    {
        TreeRBT w;
        while(x!=T && x.color==false)
        {        
	    licznik+=3;
            if(x==x.pater.left)
            {
                w=x.pater.right;
		licznik++;
                if(w.color)
                {
                    w.color=false;
                    x.pater.color=true;
                    T=LeftRotate(T,x.pater,wartownik);
                    w=x.pater.right;
                }
		licznik+=2;
                if(w.left.color==false && w.right.color==false)
                {
                    w.color=true;
                    x=x.pater;
                }
                else
                {
		    licznik++;
                    if(w.right.color==black)
                    {
                        w.left.color=black;
                        w.color=red;
                        T=RightRotate(T,w,wartownik);
                        w=x.pater.right;
                    }
                    w.color=x.pater.color;
                    x.pater.color=black;
                    w.right.color=black;
                    T=LeftRotate(T,x.pater,wartownik);
                    x=T; //Root(T,wartownik);
                }
            }
            else
            {
                w=x.pater.left;
		licznik++;
                if(w.color)
                {
                    w.color=false;
                    x.pater.color=true;
                    T=RightRotate(T,x.pater,wartownik);
                    w=x.pater.left;
                }
		licznik+=2;
                if(w.left.color==false && w.right.color==false)
                {
                    w.color=true;
                    x=x.pater;
                }
                else
                {
		    licznik++;
                    if(w.left.color==black)
                    {
                        w.right.color=black;
                        w.color=red;
                        T=LeftRotate(T,w,wartownik);
                        w=x.pater.left;
                    }
                    w.color=x.pater.color;
                    x.pater.color=black;
                    w.left.color=black;
                    T=RightRotate(T,x.pater,wartownik);
                    x=T;//Root(T,wartownik);
                }
            }
        }
        x.color=false;
        return T;
    }//DeleteFixup
    /*TreeRBT DeleteRBT(TreeRBT T, TreeRBT z, TreeRBT wartownik)
    {
        TreeRBT y=z;
        TreeRBT x;
        boolean YOriginalColor=y.color;
	licznik++;
        if(z.left==wartownik)
        {
            x=z.right;
            T=TransplantRBT(T,z,z.right,  wartownik);
        }
        else
	{
	    licznik++;
            if(z.right==wartownik)
            {
                x=z.left;
                T=TransplantRBT(T,z,z.left,wartownik);
            }
            else
            {
                y=Min(z.right,wartownik); //istnieje prawy syn z 
                YOriginalColor=y.color;
                x=y.right;
		licznik++;
                if(y.pater==z)
                {
                    x.pater=y;
                }
                else
                {
                    T=TransplantRBT(T,y,y.right,wartownik);
                    y.right=z.right;
                    y.right.pater=y;
                }
                T=TransplantRBT(T,z,y,wartownik);
                y.left=z.left;
                y.left.pater=y;
                y.color=z.color;
            }
	}
	licznik++;
        if(YOriginalColor==false)
        {
            T=DeleteFixupRBT(T,x,wartownik);
        }
        return T;
    }*///RBTDelete
//algorytm z wyk³adu
    public TreeRBT DeleteRBT(TreeRBT T, TreeRBT z, TreeRBT wartownik)
    {
	TreeRBT y,x,newRoot = T;
	licznik+=2;
	if(z.left==wartownik || z.right==wartownik)
	{
	    y=z;   
	}
	else
	{
	    y=Successor(z,wartownik);
	}
	licznik++;
	if(y.left!=wartownik)
	{
	    x = y.left;
	}
	else
	{
	    x = y.right;
	}
	x.pater = y.pater;
	licznik++;
	if(y.pater == wartownik)
	{
	    newRoot = x;
	}
	else
	{
	    licznik++;
	    if(y== y.pater.left)
	    {
		y.pater.left = x;
	    }    
	    else
	    {
		y.pater.right = x;
	    }
	}
	licznik++;
	if(y!=z)
	{
	    z.key = y.key;
	}
	if(y.color == false)
	{
	    newRoot = DeleteFixupRBT(newRoot,x,wartownik);//RB-Delete-Fixup(newRoot,x,wartownik);
	}
	return newRoot;
    }
    public TreeRBT RBDeleteFixup(TreeRBT T, TreeRBT x, TreeRBT wartownik)
    {
	return T;
    }
    public void Leveling(TreeRBT T, TreeRBT wartownik, int lev)
    {
         if(T!=wartownik && T!=null)
         {
             T.level=lev;
             if(lev>MaxLevelBST)
                 MaxLevelBST=lev;
             if(lev>MaxLevelRBT)
                 MaxLevelRBT=lev;
             if(T.left!=wartownik && T.left!=null)
                 Leveling(T.left,wartownik,lev+1);
             if(T.right!=wartownik&& T.right!=null)
                 Leveling(T.right,wartownik,lev+1);
         }
    }//Levelling
    public void PreOrderWithLevel(int lev, TreeRBT x, TreeRBT wartownik,boolean fin)
    {
        if(x!=wartownik && x!=null)
        {
            boolean finL=true;
            boolean finP=true;
            if(x.left==wartownik)
                finL=false;
            PreOrderWithLevel(lev,x.left, wartownik,finL);
             if(fin==false)
                 System.out.print("o");
             int K=x.level;
             if(K==lev)
             {
                 if(x.left!=wartownik && x.left!=null)
                 System.out.print("/");
                 if(x.color && wartownik!=null)
                     System.out.print("(");
                 if(!x.color && wartownik!=null)
                     System.out.print("[");
                 System.out.print(x.key);
                 if(x.color && wartownik!=null)
                     System.out.print(")");
                 if(!x.color && wartownik!=null)
                     System.out.print("]");
                 if(x.right!=wartownik && x.right!=null)
                     System.out.print("\\");
                 System.out.print(" ");
             }
             if(x.right==wartownik)
                 finP=false;
             PreOrderWithLevel(lev,x.right,wartownik,finP);
         }
    }//PreOrderWithLevel
    public void DrawTree(TreeRBT T, int N, TreeRBT wartownik)
    {
        int i=1;
        while(i<N+1)
        {
            PreOrderWithLevel(i,T,wartownik,true);
            i++;
            System.out.println("");
        }
    }//DrawTree
}

class BST
{
    public Tree root;
    public int licznik = 0;
    public int MaxLevelBST = 0;
    //przepisywanie tablicy
    public void Rewrite( int A[],  int B[],  int N)
    {
        for( int i=0;i<N;i++)
        {
            B[i]=A[i];
        }
    }//Rewrite
//wypisz elementy drzewa w porzadku rosnacym
    public void DrawCresc(Tree x, int N)
    {
         if(x!=null)
         {
             DrawCresc(x.left, N-1);
             int K=x.key;
             System.out.print(K+" ");
             DrawCresc(x.right, N-1);
         }
    }//DrawCresc
//przepisz do tablicy w porzadku rosnacym
    public void ToTabInOrder(Tree x, int ptr, int B[], int N)
    {
        if(x!=null)
        {
            ToTabInOrder(x.left, ptr, B, N);
            int K=x.key;
            B[N-ptr]=K;
            ptr--;
            ToTabInOrder(x.right, ptr, B, N);
        }
    }//ToTabInOrder
    //BSTSort
    public void Sort(int B[], int N)
    {
        int ptr=N;
        Tree T=null;
        T=TabToTree(T,B,N);
        ToTabInOrder(T,N,B,N);
        System.out.println("");
        WriteTab(B,N);
   }//BSTSort
//wyszukaj adres elementu o zadanym kluczu
    public Tree Search(Tree x, int k)
    {
	licznik++;
        if(x==null || x.key==k)
            return x;
        else
        {
	    licznik++;
            if(k<x.key)
		if(x.left==null)
		    return null;
		else
                    return Search(x.left,k);
            else
		if(x.right == null)
		    return null;
                else
		    return Search(x.right,k);
        }     
    }//Search
//wyszukaj adres minimum
    public Tree Min(Tree T)
    {
	licznik++;
        if(T!=null)
            while(T.left!=null)
	    {
		licznik++;
                T=T.left;
	    }
        return T;
    }//Min
//wyszukaj adres maksimum
    public Tree Max(Tree x)
    {
	licznik++;
        if(x!=null)
            while(x.right!=null)
	    {
		licznik++;
                x=x.right;
	    }
        return x;    
    }//Max
//wyszukaj adres korzenia elementu x
    public Tree Root(Tree x)
    {
	licznik++;
        if(x==null)
            return x;
        else 
        {
    	    while(x.pater!=null)
	    {
		licznik++;
                x=x.pater;
	    }
            return x; 
	}
    }//Root
//wyszukaj adres nastepnika
    public Tree Successor(Tree x)
    {
	licznik++;
        if(x!=Max(Root(x)))
        {
            Tree ret;
	    licznik++;
    	    if(x.right!=null)
    	    {
        	ret=Min(x.right);
        	return ret;
    	    }
    	    Tree y=x.pater;
    	    while(y!=null && x.pater!=null && x==(x.pater).right)
    	    {
		licznik++;
        	y=y.pater;
        	x=x.pater;
    	    }
    	    return y;
    	}
    	else 
	    return x;
    }//Successor
//wyszukaj adres poprzednika
    public Tree Predecessor(Tree x)
    {
	licznik++;
        if(x!=Min(Root(x)))
        {
	    licznik++;
            if(x.left!=null)
        	return Max(x.left);
    	    Tree y=x.pater;
    	    while(y!=null && x==y.left)//x==(x->pater)->left)
    	    {
		licznik+=2;
        	x=y;
        	y=y.pater;
    	    }
    	    return y;
    	}
        else 
	    return x;
    }//Predecessor
//wstaw nowy element do drzewa
    public Tree Insert(Tree T, int kz)
    {
        Tree z = new Tree();
        z.pater=null;
        z.left=null;
        z.right=null;
        z.key=kz;
        Tree x=Root(T);
        Tree y;
	licznik++;
        if(x==null)
            return z;
        else
        {
	    y = x;
            while(x!=null)
            {
		licznik++;
                y=x;
		licznik++;
                if(z.key<x.key)
                    x=x.left;
                else 
                    x=x.right;
            }
            z.pater=y;
	    licznik++;
            if(z.key<y.key)
                y.left=z;
            else
                y.right=z;
            return T;
        }
    }//Insert
//podepnij poddrzewo v do ojca u
    public Tree Transplant(Tree T,Tree u, Tree v)
    {
	licznik++;
        if(u.pater==null)//u nkorzeniem => korzeniem v
            return v;
        else       //u ma ojca
	{
	    licznik++;
            if(u==(u.pater).left) //u jest lewym synem
                (u.pater).left=v; //lewym synem ojca u niech bedzie v
            else
                (u.pater).right=v; //u jest prawym synem. prawym synem niech bedzie teraz v
	}
	licznik++;
        if(v!=null)
            v.pater=u.pater; //jesli v nie jest pusty, niechze jego ojcem bedzie ojciec u
        return T;
    }//Transplant
//usun element
    public Tree CormenDelete(Tree T, Tree z)
    {
	licznik++;
        if(z.left==null)// nie ma mniejszych od siebie
            T=Transplant(T,z,z.right);//po prostu prawego syna podepnij do ojca z
    	else //z ma lewego syna
	{
	    licznik++;
            if(z.right==null)//z nie ma prawego, ale ma lewego
                Transplant(T,z,z.left);//po prostu podepnij lewego syna do ojca z
            else//ma obu synow
            {
                Tree y=Min(z.right); //ustaw y jako minimum prawego syna
		licznik++;
                if(y.pater!=z)//moze sie zdarzyc, ze y to nie jest syn z
                {
                    T=Transplant(T,y,y.right);//podmieniamy
                    y.right=z.right;//pocmien synow prawych
                    (y.right).pater=y;//zmien ojca prawego syna
                }
                T=Transplant(T,z,y);//podmieniamy y z z
                y.left=z.left;//podmieniamy lewego syna
                (y.left).pater=y;   //ustawiamy lewemu synowi nowego ojca
            }
            return T;//zwracamy korzen
	}
        return T;//zwracamy korzen
    }//Delete
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
/** Java nie udostêpnia metody int pow(int n, int m) */
    public int MyPow(int base, int exponent)
    {
	int pow = 1;
	for(int i=exponent;i>0;i--)
            pow=pow*base;
        return pow;
    }
//wypelnij losowo tablice
    public void RandArray(int Array[], int A_length, int exponent)
    {
        for(int j=0;j<A_length;j++)
        {
            Array[j]=randomInt(exponent);
        }//for cala tablica
    }//RandArray
//wypisz tablice
    public void WriteTab(int A[], int N)
    {
        for(int i=0;i<N;i++)
            System.out.print(A[i]+" ");
        System.out.println("");
    }
//przepisz tablice do drzewa
    public Tree TabToTree(Tree T, int A[], int N)
    {
         for(int i=0;i<N;i++)
             T=Insert(T,A[i]);
         return T;
    }//TabToTree
//wypisz klucz wezla x
    public void WriteF(Tree x)
    {
        if(x!=null)
            System.out.print(x.key);
        else
            System.out.print("brak");
    }
    public Tree TreeDelete(Tree T, Tree z)
    {
	Tree y,x,newRoot = T;
	licznik+=2;
	if(z.left==null || z.right==null)
	{
	    y = z;
	}
	else
	{
	    y = Successor(z);
	}
	licznik++;
	if(y.left!=null)
	{
	    x = y.left;
	}
	else
	    x = y.right;
	licznik++;
	if(x!=null)
	{
	    x.pater = y.pater;
	}
	licznik++;
	if(y.pater == null)
	{
	    newRoot = x;
	}
	else
	{
	    licznik++;
	    if(y==y.pater.left)
	    {
		y.pater.left = x;
	    }
	    else
	    {
		y.pater.right = x;
	    }
	    if(y!=z)
	    {
		z.key = y.key;
	    }
	}
	return newRoot;
    }
}