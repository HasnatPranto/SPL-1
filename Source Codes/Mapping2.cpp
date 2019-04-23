#include <bits/stdc++.h>
 
using namespace std;

struct Node 
{ 
    string name;
    string linker=""; 
    vector<Node *>child;
};

vector<Node*> roots;
vector<Node*> tmpRoots;
vector<Node*> lev3roots;
bool f=0;

Node *newNode(string name) 
{ 
    Node *temp = new Node; 
    temp->name = name; 
    return temp; 
} 
void modNode(Node *n, string ref) 
{ 
    n->linker=ref; 
} 

void seeConnection(){

	string s,nul="";
	set<string>rs,ls;
	
	int i,j,n;
	Node* p;
	queue<Node*> q;
	getline(cin,s);
	getline(cin,s);
	
	for(int a=0;s[a];a++)
		nul+=' ';
	
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
				
				if(p->name==s)
				{
					for(int g=0; g<p->child.size(); g++)
					{
						rs.insert(p->child[g]->name);
					}
					
				}
				if(p->child.size()!=0)
				{
					for(j=0;j<p->child.size();j++)
					{
						if(s==p->child[j]->name)
						{
							ls.insert(p->name);
						}
						q.push(p->child[j]);
					}
				
				}
				n--;
				q.pop();
			}
		}
	}   		 
	
	vector<string> lv(ls.begin(),ls.end());
	vector<string> rv(rs.begin(),rs.end());
	
	ls.clear();
	rs.clear();
	
	bool spcl=0,spcr=0;
	
	if(!lv.empty()){
		cout << lv.back();
		lv.pop_back();
		spcl=1;
	}
	if(!spcl)cout<< nul;
	
	cout <<" ------>> " << s << " ------>> ";
	
	if(!rv.empty()){
		cout << rv.back()<<'\n';
		rv.pop_back();
		spcr=1;
	}
	
	if(!spcr)cout<< '\n';
	//lv.pop_back();rv.pop_back();
	
	while(!lv.empty() or !rv.empty())
	{
		if(!lv.empty() and !rv.empty())
		{
			cout<< lv.back()<< "          " << nul << "          " << rv.back() << endl;
			lv.pop_back();rv.pop_back();
		}
		if(lv.empty() and !rv.empty())
		{
			cout<< nul<< "          " << nul << "          "<< rv.back() << endl;
			rv.pop_back();
		}
		if(!lv.empty() and rv.empty())
		{
			cout<< lv.back() << "          " << nul << "          "<< nul << endl;
			lv.pop_back();
		}
	}
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
				
					//sort(p->child.begin(),p->child.end());
				
					for(j=0;j<p->child.size();j++)
					{
						cout<<'\t' << p->child[j]->name << endl <<"\tReferred Doc:\n\t"<< p->child[j]->linker << endl;
						q.push(p->child[j]);
					}
				
				}
				n--;
				q.pop();
			}
		}
	}   		 
}

void visualizeTree(Node *p,int dep)
{
	int i;
	
	if(p->child.size()==0){
		for(i=0;i<dep;i++)
				cout<<'\t';	
		cout<<p->name << " ("<<p->linker<<") "<< endl;
	}
	
	else
	{
		for(i=0;i<dep;i++)
				cout<<'\t';	
		dep++;
		cout<< p->name << " ("<<p->linker<<")" << endl;

		for(i=0;i<p->child.size();i++)
		{		
			visualizeTree(p->child[i],dep);
		}
	}

}

void tmpInsert(Node *p, Node *q)
{
	int i;
	bool rep;
	if(p->name==q->name && p->linker == q->linker)
	{
		f=1;
		
		for(int i=0;i<p->child.size();i++)
		{
			rep=0;
			
			for(int j=0;j<q->child.size();j++)
			{
				if(p->child[i]->name==q->child[j]->name && p->child[i]->linker==q->child[j]->linker)
				{
					rep=1;
					break;
				}
				
			}
			if(!rep){
				q->child.push_back(p->child[i]);
			}	
		}
	}
	
	else
	{	
		for(i=0;i<q->child.size();i++)
		{	
			tmpInsert(p,q->child[i]);
		}
	}
}
int main() 
{ 
	
	string str="", w, fullName="",file,book="";
	int pdf,dep=0;
	bool root=0,found=0,t;
	ifstream iFile;
	
	cout << "How many files: ";
	cin >> pdf;
	
	while(pdf--)
	{
		t=0;

		cout<<"filename: ";
		
		cin >> file;
		
		iFile.open(file);
	
		if(iFile.is_open())
		{
			getline(iFile,str);
			getline(iFile,str);
			
			if(!t)
			{
				getline(iFile,str);
				
				stringstream iss(str);
			
				while(iss >> w)
				{
					if(w=="<title>"||w=="</title>") continue;
					
					else 
						book+=w+' ';
				}
				cout<< book << endl;	
				t=1;		
			
			}
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
			
			for(int i=0;i<tmpRoots.size();i++)
			{
				tmpRoots[i]->linker=book;
			}
			book="";
			
			while(getline(iFile,str) && (str!="<reference>" || str!="<Reference>" ||str!="<REFERENCE>") )
			
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
							
							lev3roots.push_back(newNode(fullName));

							fullName="";
						}
						
						else if(str!="<name>" and str!= "<firstName>" and str!="</firstname>" and str!= "<lastname>" and 
						str!="</lastname>" and str!="</authors>")
							
							fullName+=str+' ';
					}
					while(true){
					
						getline(iFile,str);
						
						string w;
						bool marker=0;
						
						stringstream iss(str);
						
						while(iss >> w)
						{
							if(w=="<book>"||w=="<article>"||w=="<paper>")
							{
								while(iss >> w)
								{
									if(w=="</book>"||w=="</article>"||w=="</paper>") break;
									else book+=w+' ';
								
								}
								marker=1;
								break;
							}
							else
								break;
						}
						if(marker) break;
					}
					for(int i=0;i<lev3roots.size();i++)
					{
						lev3roots[i]->linker=book;
					}
					book="";
					
					for(int i=0;i<tmpRoots.size();i++)
					{
						for(int j=0;j<lev3roots.size();j++)
						
							(tmpRoots[i]->child).push_back(lev3roots[j]);
					}
					lev3roots.clear();
				}
			
			}
			if(roots.empty())
			{
				roots.insert(roots.begin(), tmpRoots.begin(), tmpRoots.end());
			}
			else
			{	
   				for(int r=0;r<tmpRoots.size();r++)
   				{
   					f=0;
   					for(int j=0;j<roots.size();j++)
   					{
   						tmpInsert(tmpRoots[r],roots[j]);
   					}
   					if(f==0)
   					{
   						roots.push_back(tmpRoots[r]);
   					}
   				}
   			}		
   			lev3roots.clear();
		
			tmpRoots.clear();	
		}
		iFile.close();
		
	}
   	
    cout << "Reference list\n"; 
    
  //traverseTree(roots);
   	
   	cout<< roots.size() << endl;
   	
   	for(int r=0;r<roots.size();r++)
   	{
   		visualizeTree(roots[r],dep);
   	}
   	seeConnection();
    
    return 0; 
} 
