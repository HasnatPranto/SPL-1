#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main()
{
	string s,tm0="",tm1="", wo="";
	char ch;
	char ss;
	ifstream iFile;
	vector<string> author;
	vector<string> cAuthor;
	
	int i=0,ab=0,au=0,ti=0,j=0,fl=0,hbjb=0,k=1;
	
	iFile.open("/home/pranto/Desktop/New/SPL-1/rawtext3.txt");
	
	if(iFile.is_open())
	{
		getline(iFile,s);
		
		while(fl==0){
			
			hbjb=0;
			 
			 if(s=="ABSTRACT") {
			 	
			 	fl=1;
			 	break;
			 }
			 			 
			 string word; 
   			
   			 stringstream iss(s); 
  
    		 while (iss >> word) 
       		 {
       		 	for(i=0;word[i];i++)
       		 	{
       		 		if(word[i]=='@'){
       		 			
       		 			hbjb=1;
       		 			break;
       		 		}
       		 		if(hbjb==1) break;
       		 	}
       		 	if(word=="A"||word=="FOR"||word=="THE"||word=="OF"||word=="A"||word=="University"||word=="Department") {
       		 		hbjb=1;
       		 		break;
       		 	}
       		 	if(word[word.length()-1]==',')
       		 	{ 
       		 		hbjb=1;
       		 		break;
       		 	}
       		 	
       		 	
       		 		
       		 	else
       		 		tm0+=word+' ';
       		 	
       		} 
				if(hbjb==0){ 
				author.push_back(tm0);
				//cout<< tm0 << endl;   
       		 	tm0="";		
       		 	}
			       		 
       		 else tm0="";	
       		 
       		 getline(iFile,s);	 		
				
			}
			
			if((fl==1) || (s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
			{
				int cnt=0;
				
				while(!iFile.eof())
				{
					iFile >> s;
					
					if(s[0]=='[' && (s[3]==']'||s[2]==']') )
					{
						while(!iFile.eof()){
							
							iFile >> s;
							
							if(s[s.length()-1]=='.')
							tm0+=s+' ';
							else if(s[s.length()-1]==',')
							{
								tm0+=s+' ';
								tm0.erase (tm0.end()-2);
								cAuthor.push_back(tm0);
								//cout<< tm0 << endl;
								tm0="";
							}
							
							else if(s=="and") continue;
							else
							 break;	
						}/*
				
						while(true){
							
							iFile >> s;
							
							 if(s=="and"){
								
								au=1;
								cAuthor.push_back(tm0);
								tm0="";
								cnt=0;
							}
							
							else if(s[s.length()-1]==',')
							{
								tm0+=s+' ';
								tm0.erase (tm0.end()-2);
								cAuthor.push_back(tm0);
								tm0="";
								cnt=0;
								
								if(au==1)
								{
									au=0;
									cnt=0;
									break;
								}	
								
							}
							else if(s[s.length()-1]=='.')
							{
									tm0+=s+' ';
									cnt++;
							}
		
							
							else{
							 tm0+=s+' ';
							 cnt++;	 	
						}
						if(cnt>=3)
						{
							cnt=0;
							tm0="";
							au=0;
							break;
						}	
					}*/
					cnt=0;
				
				}
			}
			iFile >> s;		
		}	
		//getline(iFile,s);
	}
	iFile.close();
	
	vector<string>:: iterator it;
	
	cout<< "Name of the Authors:\n";
	
	for(it=author.begin();it!=author.end();it++)
		cout << *it << endl;
	cout<< endl;
	
	cout<< "Name of the Cited Authors:\n";
	
	for(it=cAuthor.begin();it!=cAuthor.end();it++)
		cout << *it << endl;
		
	return 0;
}
