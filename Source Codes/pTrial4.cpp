#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>
#include<bits/stdc++.h>

using namespace std;

string s,tm0="",tm1="", wo="",newtmp="",oldtmp;
	char ch;
	char ss;
	ifstream iFile;
	ofstream oFile;
	vector<string> author;
	vector<string> cAuthor;
int book=0, bChap=0, art=0;

void extractBChap(string s)
{
	int name=0,ed=0,fn=0,ln=0,hlprI=0;
	string w,tmp="",firstName="<firstname> ", lastName="<lastname> ";
	stringstream iss(s);

	iss >> w;
	
	oFile << "<authors>\n";
	cout<< w;

	while(w[0]!=34)
	{
		if(name==0)
		{
			oFile << "<name> ";
		}
		if(w=="and"){
			
			string sub="</firstname> <lastname> ";
			for(int i=tmp.length()-2;;i--)
			{
				hlprI++;
				if(tmp[i]==' ')
				{
					tmp.insert(tmp.length()-hlprI,sub);
					break;
				}
			}
			tmp+=" </lastname>";

			//tmp.erase (tmp.end()-2);
			oFile << tmp << " </name>\n";
			tmp="";
			name=0;
			hlprI=0;
		}	
		
		else if(w[w.length()-1]==',')
		{	
			tmp+="</firstname> <lastname> "+w+' ';
			tmp.erase (tmp.end()-2);
			tmp+="</lastname>";
	
			oFile << tmp << " </name>\n";
			tmp="";
			name=0;
			fn=0;
		}
		
		else if(w[w.length()-1]==46)
		{
			if(w.length()==2){
				
				if(fn==0){
					tmp+=firstName+w+' ';
					fn=1;
					name=1;
				}
				else
				{
					tmp+=w+' ';
					name=1;	
				}
			}
			else
			{
				tmp+="</firstname> <lastname> "+w+' ';
				tmp.erase (tmp.end()-2);
				tmp+="</lastname>";
	
				oFile << tmp << " </name>\n";
				tmp="";
				name=0;
				fn=0;

			}

		}	
		else{
			if(fn==0){
				tmp+=firstName+w+' ';	
				name=1;
				fn=1;
			}
			else{
				tmp+=w+' ';	
				name=1;
			}
		}
		iss >> w;
		cout<< w << endl;

	}
	oFile << "</authors>\n";
	oFile << "<chapterTitle>";
	
	while(w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	tmp.erase(tmp.begin());
	tmp.erase(tmp.end()-2,tmp.end());

	oFile << tmp <<"</chapterTitle>\n";
	tmp="";

}
void getChunk(string str)
{
	string store;
	store=str;

	string words;
	stringstream iss(str);

	while(iss >> words)
	{
		if(words[words.length()-1]==34)
		{
			iss >> words;

			if(words=="in") { bChap=1; break;}

			else { art=1;break;}
		}

	}

	if(art==0 && bChap==0) book=1;
	cout<< store << endl;
	if(bChap==1) extractBChap(store);
	//if(book==1) extractBook(store);
	//else extractArt(store);


}
int main()
{
	int i=0,ab=0,au=0,ti=0,j=0,fl=0,hbjb=0,k=1,cit=1;
	
	iFile.open("/home/pranto/Desktop/New/SPL-1/rawtext3.txt");
	oFile.open("/home/pranto/Desktop/New/SPL-1/xml0.xml");
	
	if(iFile.is_open() && oFile.is_open())
	{
		getline(iFile,s);
		oldtmp=s;
		
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
       		 			
       		 			newtmp+=("<mail>"+oldtmp+"</mail>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 		}
  
       		 	}
       		 	if(word=="A"||word=="FOR"||word=="THE"||word=="OF") {
       		 		
       		 		newtmp+=("<title>"+oldtmp+"</title>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	if(word=="Department")
       		 	{
       		 		newtmp+=("<Department>"+oldtmp+"</Department>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	if(word=="University")
       		 	{
       		 		newtmp+=("<University>"+oldtmp+"</University>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	if(word[word.length()-1]==',')
       		 	{ 
       		 		newtmp+=("<address>"+oldtmp+"</address>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 	}
       		 	if(word=="January"||word=="February"||word=="March"||word=="April"||word=="May"||word=="June"||word=="July"||word=="August"||
       		 		word=="September"||word=="October"||word=="November"||word=="December")
       		 	{
       		 		newtmp+=("<date>"+oldtmp+"</date>");
       		 			oFile<< newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;

       		 	}
       		 		
       		 	else
       		 		tm0+=word+' ';
       		 	
       		} 
				if(hbjb==0){ 
				author.push_back(tm0);
				newtmp+=("<author>"+oldtmp+"</author>");
       		 	oFile<< newtmp << endl;
       		 	newtmp="";
			
       		 	tm0="";		
       		 	}
			       		 
       		 else tm0="";	
       		 
       		 getline(iFile,s);
       		 oldtmp=s;	 		
				
			}
			oFile<< "<article>" << endl;

			while(!iFile.eof()){
				
				getline(iFile,s);
				if((s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
					break;
				else
				oFile<< s << endl;
			}
			oFile<< "</article>" << endl;
			oFile<< "<reference>" << endl;

			if((s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
			{
				int cnt=0;
				iFile >> s;
				
				while(!iFile.eof())
				{
					if(s[0]=='[')
						oFile<< "<citationid>["<< cit++ << "]</citationid>\n";
				
					
						while(!iFile.eof()){
							iFile >> s;
							if(s[0]!='[')
								tm0+=s+' ';
							else 
								break;	
						}
						cout<< tm0 << endl;
						getChunk(tm0);
						tm0="";
					}
					cnt=0;
				
				}
			iFile >> s;		
	
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

