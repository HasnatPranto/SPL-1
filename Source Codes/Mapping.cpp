/* To show the name of the persons who has been cited by a author using 2D vector */ 
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

vector< vector<string>> citmap;
vector<string> authors;
vector<string> citedAuthors;
set<string> q;

void ExpandMapFromReferred(vector<string> authors,vector<string>citedAuthors)
{
	bool f=0;
	sort(citedAuthors.begin(), citedAuthors.end());
	
	while(!authors.empty()){
	
		string s= authors.back();
		
		for(int i=0,j=0;i<citmap.size();i++)
		{
			if(citmap[i][j]==s)
			{
				citmap[i].insert(citmap[i].end(), citedAuthors.begin(), citedAuthors.end());
				
				q.insert(citmap[i].begin()+1, citmap[i].end());
				
				citmap[i].erase(citmap[i].begin()+1,citmap[i].end());
				
				citmap[i].insert(citmap[i].begin()+1,q.begin(),q.end());
				
				f=1;
				
				authors.pop_back();
				
				q.clear();
				
				break;
			}
			else continue;
		}
		
		if(f==0)
		{
			citedAuthors.insert(citedAuthors.begin(),s);
			
			citmap.pb(citedAuthors);
		
			citedAuthors.erase(citedAuthors.begin());
		
			authors.pop_back();
		}
		f=0;
	}
	ofstream oFile;
	oFile.open("newtext1.txt");
		
	for (int i = 0; i < citmap.size(); i++) {
		//cout<< citmap[i][0] << " Refers->\n";
		oFile<< citmap[i][0] << " Refers->\n";
		 
    for (int j = 1; j < citmap[i].size(); j++) 
            //cout <<'\t' << citmap[i][j] << endl;
            oFile <<'\t' << citmap[i][j] << endl;  
    }
    citedAuthors.clear();
    oFile.close(); 
}
int main()
{

	string str="", w, fullName="",file;
	int pdf=0;
	ifstream iFile;
	
	while(pdf<=1)
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
							
							authors.push_back(fullName);
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
							
							citedAuthors.pb(fullName);
							
							fullName="";
							
						}
						
						else if(str!="<name>" and str!= "<firstName>" and str!="</firstname>" and str!= "<lastname>" and str!="</lastname>" and str!="</authors>")
							
							fullName+=str+' ';
					}
				
				}
			
			}
			ExpandMapFromReferred(authors,citedAuthors);
				
		}
		iFile.close();
		pdf++;
		citedAuthors.clear();
		authors.clear();
	}
}
