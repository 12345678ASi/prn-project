import java.util.*;
public class SortDemo
{
	public static void main(String[] args)
	{
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter the number of elements:\n");
		int n=sc.nextInt();
		int s[]=new int[n];
		System.out.println("Enter the elememts");
		for(int i=0;i<n;i++)
		s[i]=sc.nextInt();
		System.out.println("The elements Before Sorting are:\n");
		for(int i=0;i<s.length;i++)
		System.out.println(s[i] + " ");
		for(int i=0;i<s.length;i++)
		{
			for(int j=i+1;j<s.length;j++)
			{
				if(s[i] > s[j])
				{
					int temp=s[i];
					s[i]=s[j];
					s[j]=temp;
				}
			}
		}
		System.out.println("The elements After Sorting are:\n");
		for(int i=0;i<s.length;i++)
		System.out.println(s[i] + " ");
	}
}