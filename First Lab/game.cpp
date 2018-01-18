#include<iostream>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

using namespace std;

extern void registerme ( );
extern void startgame ( int );
extern int guess ( int );
extern void verifysoln ( int );

unsigned long long playgame1();
unsigned long long playgame2();
unsigned long long playgame3();
unsigned long long playgame4();

int main()
{
  registerme();
 jmp:
  cout<<"Enter the game number you want to play(1-4)\n";
  int n;
  cin>>n;
  if(n<1 || n>4){
    cout<<"Enter valid game number\n";
    goto jmp;
  }
  clock_t t1,t2;
  unsigned long long a;
  t1=clock();
  switch(n)
    {
    case 1 : a = playgame1();
      t2=clock();
       break; 
    case 2 : a = playgame2();
      t2=clock();
      break;
    case 3 : a = playgame3();
      t2=clock();
      break;
    case 4 : a = playgame4();
      t2=clock();
      break;
    }
  cout<<"\nGame "<<n<<"\na1 = "<<a;
  cout<<"\nTime Taken = "<<(double)(t2 - t1)/(double)CLOCKS_PER_SEC<<endl;
  return 0;
}

unsigned long long playgame1()
{
  startgame(1);
  unsigned long long a;
  for(a = 0;a <= pow(10,8);a++)
    {
      if(guess(a) == 1)
	break;
    }
  verifysoln(a);
  return a;
}

unsigned long long playgame2()
{
  startgame(2);
  unsigned long long a=0;
  while(guess(a)!=1)
    {
      a=random()%100000000;
    }
  verifysoln(a);
  return a;
}
 unsigned long long playgame3()
 {
   startgame(3);
   unsigned long long a=0,L=1,R=pow(10,8),prev=0;
   int templ,tempr;
   while(L!=R)
     {
       templ=guess(L);
       tempr=guess(R);
       //cout<<templ<<' '<<tempr<<endl;
       if(tempr==3) R=(L+R)/2;
       if(tempr==2) L=(L+R)/2;
       if(templ==1 || tempr==1) break;
     }
   verifysoln(templ==1?L:R);
   return templ==1?L:R;
 }
 unsigned long long playgame4()
 {
   startgame(3);
   unsigned long long a=0,L=-100000000/3,R=pow(10,8),prev=0;
   int templ=0,tempr=0;
   char flag='l',lastguess='r';
   templ=guess(L);
   tempr=guess(R);
   while(L!=R)
     {
       cout<<templ<<' '<<tempr<<endl;
       if(templ==1 || tempr==1) break;
       if(lastguess=='r')
	 {
	   templ=guess(L);
	   if(templ==2)
	     {
	       R=(L+R)/2;
	     }
	   else{
	     L=(L+R)/2;
	     R=R+(R-L)/3;
	   }
	   lastguess='l';
	 }
       else if(lastguess=='l')
	 {
	   tempr=guess(R);
	   if(tempr==2)
	     {
	       L=(L+R)/2;
	     }
	   else
	     {
	       R=(L+R)/2;
	       L=L-(R-L)/3;
	     }
	   lastguess='r';
	 }
     }
   verifysoln(templ==1?L:R);
   return templ==1?L:R;
 }
