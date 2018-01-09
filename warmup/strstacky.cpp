#include<iostream>
#include<stdio.h>
#include<stack>

using namespace std;

int stackystr(char A[],int pos,int N)
{
  if(pos==2*N)
    {
      for(int i=0;i<2*N;i++)
	cout<<A[i]<<' ';
      cout<<'\n';
      return 1;
    }
  int count=0;
  int c_pos=0,c_neg=0;
  for(int i=0;i<pos;i++)
    {
      if(A[i]=='+') c_pos++;
      if(A[i]=='-') c_neg++;
    }
  
  if(c_pos>c_neg && (c_pos<N && c_neg<N))
    {
      A[pos]='+';
      count+=stackystr(A,pos+1,N);
      A[pos]='-';
      count+=stackystr(A,pos+1,N);
    }
  else if(c_pos>c_neg)
    {
      A[pos]='-';
      count+=stackystr(A,pos+1,N);
    }
  else
    {
      A[pos]='+';
      count+=stackystr(A,pos+1,N);
    }
  pos++;
  return count;
}

unsigned long long nCk( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    unsigned long long result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

int stackystrformula(int N)
{
  unsigned long long num=nCk(2*N,N)/(N+1);
  return num;
}

int stackyperm(char A[],int pos,int N)
{
  if(pos==2*N)
    {
      stack<int> s;
      int element=1;
      for(int i=0;i<2*N;i++)
	{
	  if(A[i]=='+') s.push(element++);
	  if(A[i]=='-')
	    {
	      if(i==2*N-1) cout<<s.top();
	      else cout<<s.top()<<',';
	      s.pop();
	    }
	}
      cout<<endl;
      return 1;
    }
  int count=0;
  int flag=0;
  int c_pos=0,c_neg=0;
  for(int i=0;i<pos;i++)
    {
      if(A[i]=='+') c_pos++;
      if(A[i]=='-') c_neg++;
    }
  
  if(c_pos>c_neg && (c_pos<N && c_neg<N))
    {
      A[pos]='+';
      count+=stackyperm(A,pos+1,N);
      A[pos]='-';
      count+=stackyperm(A,pos+1,N);
    }
  else if(c_pos>c_neg)
    {
      A[pos]='-';
      count+=stackyperm(A,pos+1,N);
    }
  else
    {
      A[pos]='+';
      count+=stackyperm(A,pos+1,N);
    }
  pos++;
  return count;
}

void isstacky(int A[],int N)
{
  int flag=0;
  stack<int> s;
  int num_push=1;
  int num_pop=0;
  int element=2;
  s.push(1);
  for(int i=0;i<N;i++)
    {
      if(s.size()==0)
	{
	  if(element>A[i])
	    {
	      flag=1;
	      break;
	    }
	}
      if((A[i]>s.top() && element>A[i]) || num_push>N || num_pop>N)
	{
	  flag=1;
	  break;
	}
      if(A[i]==s.top())
	{
	  //cout<<s.top()<<' ';
	  s.pop();
	  num_pop++;
	}
      else if(A[i]>s.top())
	{
	  while(A[i]>s.top())
	    {
	      s.push(element++);
	      num_push++;
	    }
	  //cout<<s.top();
	  s.pop();
	  num_pop++;
	}
      else if(A[i]<s.top())
	{
	  while(A[i]<s.top())
	    {
	      s.pop();
	      num_pop++;
	    }
	  //cout<<s.top()<<' ';
	  s.pop();
	  num_pop++;
	}
    }
if(flag==1)
  {
    cout<<"\nIt is Not stacky\n";
  }
 else cout<<"\nStacky\n";
}

int main()
{
  int n;
  cout<<"Enter n\n";
  cin>>n;
  char *A;
  A=new char[2*n+1];
  
  cout<<"All Stacky Strings are \n";
  int count=stackystr(A,0,n);
  cout<<"There are "<<count<<" of them\n";
  
  cout<<"\nAll Stacky Permutations are \n";
  count=stackyperm(A,0,n);
  cout<<"There are "<<count<<" of them\n";
  
  cout<<"\nNow checking for stacky permutation\n";
  cout<<"Enter n\n";
  cin>>n;
  cout<<"Enter permutation to be checked\n";
  int *B;
  B=new int[n];
  for(int i=0;i<n;i++)
    cin>>B[i];
  isstacky(B,n);

  cout<<"Enter parameter n\n";
  cin>>n;
  cout<<stackystrformula(n)<<endl;
  return 0;
}
