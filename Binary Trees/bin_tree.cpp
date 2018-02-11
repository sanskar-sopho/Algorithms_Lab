//I have implemented a recursive way of computing tree from binary encoding (buildtree2) but i am getting segmentation fault, so 
//i have commentef the call statement of that function.


#include<iostream>

using namespace std;

struct treenode{
	treenode *L;
	treenode *R;
	treenode *P;
};

treenode* buildtree1(int n,char *S);
void printtree(treenode*,int);
char* genec1(treenode*,char*);
char* genec2(treenode*,char*);
void destroytree(treenode*);
int buildtree2(treenode* orig_node,treenode* root,char* E,int index,int n);

int main()
{
	int n;
	cout<<"Enter number of nodes\n";
	cin>>n;
	char *E=new char[2*n-1];
	cout<<"Enter Encoding\n";
	cin>>E;
	cout<<endl;
	// cout<<endl<<E<<endl;
	treenode *root=buildtree1(n,E);
	printtree(root,0);
	char* S=new char[100];
	genec1(root,S);
	cout<<"\nOriginal Encoding : "<<E;
	cout<<"\nFinal Encoding : "<<S<<endl;
	genec2(root,S);
	cout<<"\nBinary Encoding : "<<S;
	destroytree(root);
	cout<<"\nTree Destroyed\n";

	// cout<<"*********PART 2**********\n\n";
	

	cout<<"\nEnter binary Encoding\n";
	cin>>E;
	treenode* root2 = new treenode;
	root2->L = root2->R = root2->P = NULL;
	// buildtree2(root2,root2,E,0,n);

}

treenode* buildtree1(int n,char* S)
{
	if(n==0) return NULL;

	treenode* root=new treenode;
	root->L = root->R = root->P = NULL;
	int i=0;
	treenode* temp;
	temp=root;
	while(S[i] != '\0')
	{
		if(S[i] == '0')
		{
			treenode *node = new treenode;
			node->L = node->R = node->P = NULL;
			temp->L = node;
			node->P = temp;
			temp = temp->L;
		}
		else if(S[i] == '1')
		{
			treenode *node = new treenode;
			node->L = node->R = node->P = NULL;
			temp->R = node;
			node->P = temp;
			temp = temp->R;	
		}
		else
		{
			temp = temp->P;
		}
		i++;
	}


	return root;
}

void printtree(treenode* root,int L)
{
	if(L==0)
		cout<<"X\n";

	if(root==NULL)
	{
		for(int i=0;i<L;i++) cout<<"    ";
		cout<<"+---|\n";
		return;
	}

	for(int i=0;i<L;i++) cout<<"    ";
	cout<<"+---X\n";
	
	printtree(root->L,L+1);
	printtree(root->R,L+1);
	return;
}

char* genec1(treenode* root,char* E)
{
	static int index=0;
	if(root==NULL)
	{
		return E;
	}
	if(root->L != NULL)
	{
		E[index++] = '0';
		genec1(root->L,E);
	}
	if(root->R != NULL)
	{
		E[index++] = '1';
		genec1(root->R,E);
	}
	if(root->P != NULL)
		E[index++]='2';
	return E;

}

char* genec2(treenode* root,char* E)
{
	static int index=0;
	if(root == NULL) return E;

	if(root->L != NULL)
	{
		E[index++] = '0';
		genec2(root->L,E);
	}
	if(root->R != NULL)
	{
		E[index++] = '1';
		genec2(root->R,E);
	}

	if(root->P != NULL)
	{
		if(root->P->L == root) E[index++] = '0';
		else E[index++] = '1';
	}
	return E;
}

void destroytree(treenode* root)
{
	if(root == NULL) return;

	destroytree(root->L);
	destroytree(root->R);

	delete root;
}


//I have tried a recursive way but segmentation fault is coming.

int buildtree2(treenode* orig_root,treenode* root,char* E,int index,int n)
{
	if(n == 0) return 0;
	if(index>=2*n-3)
	{
		if(orig_root==root)
			return 1;
		else return 0;
	}
	// treenode* root = new treenode;
	// root->L = root->R = root->P = NULL;
	// treenode* temp=root;
	if(E[index]=='0')
	{
		if(root->P == NULL)
		{
			treenode* node = new treenode;
			node->L = node->R = node->P = NULL;
			root->L = node;
			node->P = root;
			buildtree2(orig_root,root->L,E,index++,n);	
		}
		else if(root->P->L != root)
		{
			treenode* node = new treenode;
			node->L = node->R = node->P = NULL;
			root->L = node;
			node->P = root;
			buildtree2(orig_root,root->L,E,index++,n);
		}
		else
		{
			if(buildtree2(orig_root,root->P,E,index++,n)==1);
			else
			{
				treenode* node = new treenode;
				node->L = node->R = node->P = NULL;
				root->L = node;
				node->P = root;
				buildtree2(orig_root,root->L,E,index++,n);
			}
		}
	}
	else
	{
		if(root->P == NULL)
		{
			treenode* node = new treenode;
			node->L = node->R = node->P = NULL;
			root->R = node;
			node->P = root;
			buildtree2(orig_root,root->R,E,index++,n);	
		}
		else if(root->P->R != root)
		{
			treenode* node = new treenode;
			node->L = node->R = node->P = NULL;
			root->R = node;
			node->P = root;
			buildtree2(orig_root,root->R,E,index++,n);
		}
		else
		{
			if(buildtree2(orig_root,root->P,E,index++,n)==1);
			else
			{
				treenode* node = new treenode;
				node->L = node->R = node->P = NULL;
				root->R = node;
				node->P = root;
				buildtree2(orig_root,root->R,E,index++,n);
			}
		}
	}
	return 1;

}
