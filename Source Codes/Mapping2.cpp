/***To create a tree of the cited authors***/

/**Took help from "//https://www.geeksforgeeks.org/generic-tree-level-order-traversal/" & got the base idea for creating nodes & traversing the tree**/
    
#include <bits/stdc++.h>
 
using namespace std;

struct Node 
{ 
    string name; 
    vector<Node *>child;
};

vector<Node*> roots;
vector<Node*> tmpRoots;

Node *newNode(string name) 
{ 
    Node *temp = new Node; 
    temp->name = name; 
    return temp; 
} 

void traverseTree(vector<Node*> roots) 
{ 
   	int i,j,n;
	Node* p;
	queue<Node*> q;
	
	if(roots.empty()) return;
	
	for(i=0;i<roots.size();i++)
	{
		q.push(roots[i]);
		
		while(!q.empty())
		{
			n=q.size();
			
			while(n>0)
			{
				p=q.front();
				
				if(p->child.size()!=0)
				{
					cout<< p->name <<" Refers:\n";
				
					sort(p->child.begin(),p->child.end());
				
					for(j=0;j<p->child.size();j++)
					{
						cout<<'\t' << p->child[j]->name << endl;
						q.push(p->child[j]);
					}
				
				}
				n--;
				q.pop();
			}
		}
	}   		 
}
bool r=0;
bool crossCheck(Node* a, Node *b)
{
	bool repeat;
	Node *p;
	int j;
	
	if(a->name == b->name)
	{
		for(int j=0;j < b->child.size();j++)
		{	
			repeat=0;
			
			for(int k=0;k< a->child.size();k++)
			{
	 			if(b->child[j]->name == a->child[k]->name)
	 			{
	 				repeat=1; break;
	 			}	
	 		}
	 		if(repeat==0)
	 			a-> child.push_back(b->child[j]);
	 	}
	 	
	 	r=1;
	 			
	 	return r;
	}
	if(b->child.empty()) return 0;
	
	else
	{
		for(int i=0;i<b->child.size();i++)
		{
			if(b->child[i]->name == a->name)
			{
				p = b->child[i];
				
				for(int k=0;k< p->child.size(); k++)
				{
					repeat=0;
					
					for(j=0; j< a->child.size();j++)
					{
						if(p->child[k]->name == a->child[j]->name)
						{
							repeat=1; break;
						}
					}
					if(repeat==0)	
						a->child.push_back(p->child[k]);
				}	
				b->child.erase(b->child.begin()+i);
			}
		}
		
		for(int i=0;i<b->child.size();i++)
		{
			r=crossCheck(a,b->child[i]);
			
			if(r){
				b->child.erase(b->child.begin()+i);
				r=0;				
			}	
		}	
		
	}
	
}
void interCheck(Node* n, Node* m)
{
	if(n->child.empty()) return;
	
	for(int i=0;i<n->child.size();i++)
	{
		interCheck(n->child[i],m);
		
		crossCheck(n->child[i],m);
		
	}
}
void check()
{
	for(int a=0;a < roots.size()-1;a++)
	{
		for(int b=a+1;b< roots.size();b++)
		{
			r=crossCheck(roots[a],roots[b]);
			
			if(r)
			{
				roots.erase(roots.begin()+b);
				r=0;
			}
			
			for(int c=0;c < roots[a]->child.size(); c++)
			{	
				interCheck(roots[a]->child[c], roots[b]);
			}
		}
	}
}   

int main() 
{ 
	
	string str="", w, fullName="",file;
	int pdf=0;
	bool root=0;
	ifstream iFile;
	
	while(pdf<=2)
	{
		cout<<"filename: ";
		
		cin >> file;
		
		iFile.open(file);
	
		if(iFile.is_open())
		{
			while(str!="</authors>")
			{
				getline(iFile,str);
			
				stringstream iss(str);
			
				while(iss >> w)
				{
					if(w=="<name>")
					{
						iss >> w;
					
						while(iss >> w && w!="</firstname>")
							
							fullName+=w+' ';
					
							iss >> w;	
							
							iss >> w;
						
							fullName+=w;
							
							tmpRoots.push_back(newNode(fullName));
							
							fullName="";
					}
					else
						break;
				}
			}
			
			while(getline(iFile,str) && str!="<reference>" )
			
			while(!iFile.eof())
			{
				iFile >> str;
				
				if(str=="<authors>")
				{
					while(str!="</authors>")
					{
						iFile >> str;
						
						if(str=="</name>"){
						
							fullName.erase(fullName.end()-1);	
							
							for(int i=0;i<tmpRoots.size();i++)
							{
								(tmpRoots[i]->child).push_back(newNode(fullName));
							}

							fullName="";
							
						}
						
						else if(str!="<name>" and str!= "<firstName>" and str!="</firstname>" and str!= "<lastname>" and str!="</lastname>" and str!="</authors>")
							
							fullName+=str+' ';
					}
				
				}
			
			}
			roots.insert(roots.end(), tmpRoots.begin(), tmpRoots.end());
			tmpRoots.clear();	
		}
		iFile.close();
		pdf++;
	}
   	check();
   	
    cout << "Reference list\n"; 
    
    traverseTree(roots); 
    
    return 0; 
}  
