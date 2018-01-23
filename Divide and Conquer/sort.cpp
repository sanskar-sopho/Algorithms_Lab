#include<iostream>
#include<stdio.h>

using namespace std;

extern int registerme ( int );
extern void startsort ( );
extern int compareballs ( int, int );
extern void verifysort ( int*);
extern void startmatch ( int );
extern int fitsin ( int i, int j );
extern void verifymatch ( int*);

void mergesort(int*,int,int);
int* quicksort(int*,int*,int);

int main()
{
	int n;
	cout<<"Enter value of n\n";
	cin>>n;
	registerme(n);
	
	cout<<"Sorting the balls\n";
	startsort();
	int* S=new int[n];
	for(int i=0;i<n;i++) S[i]=i;
	mergesort(S,0,n);
	verifysort(S);

	cout<<"\n\nFinding the matching boxes\n";
	startmatch(1);
	int* M=new int[n];
	for(int i=0;i<n;i++) M[i]=i;
	M=quicksort(M,S,n);
	int *N=new int[n];


	for(int i=0;i<n;i++) //For rearranging boxes with respect to balls.
	{
		for(int j=0;j<n;j++)
		{
			if(S[j]==i) N[i]=M[j];
		}
	}

	verifymatch(N);
	cout<<endl;
}


void mergesort(int* A,int base,int n)
{
	if(n<=1) return;
	if(n==2)
	{
		if(compareballs(A[base],A[base+1])==1)
		{
			int temp=A[base];
			A[base]=A[base+1];
			A[base+1]=temp;
		}
		return;
	}

	int *B=new int[n];
	mergesort(A,base,n/2);
	mergesort(A,base+n/2,n-n/2);
	int i=0,j=0;
	int flag=0;
	while(i<n/2 && j<(n-n/2))
	{
		if(compareballs(A[base+i],A[base+n/2+j])>-1)
		{
			B[i+j]=A[base+n/2+j];
			j++;
		}
		else
		{
			B[i+j]=A[base+i];
			i++;
		}
	}
	if(i==n/2)
	{
		while(j<(n-n/2))
		{
			B[i+j]=A[base+n/2+j];
			j++;
		}
	}
	else if(j==n-n/2)
	{
		while(i<n/2)
		{
			B[i+j]=A[base+i];
			i++;
		}
	}

	for(i=0;i<n;i++)
		A[base+i]=B[i];
}



int* quicksort(int* M,int* S,int n)
{
	
	if(n==1) return M;
	if(n==2)
	{
		int fit=fitsin(S[0],M[0]);
		// cout<<"Fit "<<fit<<'\n';
		if(fit==0)
			return M;
		else
		{
			int temp=M[0];
			M[0]=M[1];
			M[1]=temp;
			return M;
		}
	}

	int pivot=n/2;
	// cout<<"pivot"<<pivot;
	int *L=new int[n/2+1];
	int *H=new int[n/2+1];
	int l=0,h=0;
	for(int i=0;i<n/2+1;i++) L[i]=H[i]=-1;
	for(int i=0;i<n;i++)
	{
		if(fitsin(S[pivot],M[i])<1) L[l++]=M[i];
		else H[h++]=M[i];
	}

	int* A=quicksort(L,S,l);
	int* B=quicksort(H,S+l,h);
	int* C=new int[n];
	for(int i=0;i<n;i++)
		C[i]=i<l?A[i]:B[i-l];
	return C;

}
