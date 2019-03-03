#include<bits/stdc++.h>

using namespace std;

ifstream iFile;
ofstream oFile;
bool book=0, bChap=0, art=0,con=0,proc=0;

void getNames(string s)
{
	bool name=0,ed=0,fn=0,ln=0; int hlprI=0;
	string w,tmp="",cs;
	stringstream iss(s);
	
	iss >> w;
	
	while(true)
	{
		if(name==0)
		{
			oFile << "<name> ";
		}
		if(w=="and"){
			
			if(cs[cs.length()-1]==',')
			{
				name=1;
				goto Skip;
			}
			else{
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

				oFile << tmp << " </name>\n";
				tmp="";
				name=0;
				hlprI=0;
			}
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
					tmp+="<firstName> "+w+' ';
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
				if(w[w.length()-3]==46)
				{
					tmp+="<firstName> "+w+' ';
					fn=1;
					name=1;
				}
				else{
				
					tmp+="</firstname> <lastname> "+w+' ';
					tmp.erase (tmp.end()-2);
					tmp+="</lastname>";
	
					oFile << tmp << " </name>\n";
					tmp="";
					name=0;
					fn=0;
					break;
				}	
			}

		}	
		else{
			if(fn==0){
				tmp+="<firstName> "+w+' ';	
				name=1;
				fn=1;
			}
			else{
				tmp+=w+' ';	
				name=1;
			}
		}
		
		cs=w;

Skip:	iss >> w;

	}
}
void extractBChap(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!=34)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<chapterTitle> ";
	
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

	oFile<< "<book> ";

	iss >> w;

	iss >> w;

	while(true)
	{
		if(w=="vol."|| w=="Vol.")
		{
			tmp+=w+' ';
			iss >> w;
			tmp+=w;
			break;
		}
		else{
			tmp+=w+' ';
		}
		iss >> w;
	}

	oFile << tmp <<" </book>\n";
	tmp="";

	oFile << "<editors>\n";

	while(iss >> w && w!="Ed.")
	{
		tmp+=w+' ';
	}
	
	tmp.erase(tmp.end()-2);
	tmp.insert(tmp.end()-1,'.');
	
	getNames(tmp);
	
	tmp="";
	
	oFile << "</editors>\n";

	oFile<< "<publisher> " << w <<' ';

	while(iss >> w)
	{
		oFile << w <<' ';
	}
	
	oFile <<"</publisher>\n";
	
	bChap=0;
}

void extractBook(string str)
{
	string w,tmp="";
	stringstream iss(str);
	
	while(iss >> w)
	{
		if(w.length()>2 && (w[w.length()-1]==46 && w[w.length()-3]!=46))
		{
			tmp+=w+' ';
			break;
		}
		else
			tmp+=w+' ';
	}
	//cout<< tmp << endl;
	oFile << "<authors>\n";
	
	getNames(tmp);
	
	oFile << "</authors>\n<book> ";
	
	tmp="";
	
	iss >> w;

	while(w[w.length()-1]!=46)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	tmp.erase(tmp.end()-1);

	oFile << tmp << " </book>\n";

	tmp="";

	oFile<<"<publisher> ";

	while(iss >> w)
	{
		oFile << w << ' ';
	}
	oFile <<"</publisher>\n";
	book=0;

}

void extractArticle(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!=34)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<article> ";

	while(w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	tmp.erase(tmp.end()-2);

	oFile << tmp << " </article>\n";

	tmp="";

	oFile<<"<journal> ";

	while(iss >> w)
	{
		oFile << w << ' ';
	}
	oFile <<"</journal>\n";
	art=0;

}

void extractConferenceProc(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!=34)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<article> ";

	while(w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	tmp.erase(tmp.end()-2);

	oFile << tmp << " </article>\n";

	tmp="";

	oFile<<"<proceedings> ";
	
	while(iss >> w && w!="Proc.") continue;
	
	while(iss >> w)
	{
		oFile << w << ' ';
	}
	oFile <<"</proceedings>\n";
	proc=0;

}

void extractConference(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!=34)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<paper> ";

	while(w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	tmp.erase(tmp.begin());
	tmp.erase(tmp.end()-2,tmp.end());

	oFile << tmp << " </paper>\n";

	tmp="";
	
	while(iss >> w) 
	{
		if(w=="Rec.") break;
		if(w=="the" ) break;
	}
	
	oFile <<"<conference> ";
	
	while(iss >> w)
	{
		oFile << w << ' ';
	}
	oFile <<" </conference>\n";
	
	proc=0;

}
void getChunk(string str)
{
	string store;
	store=str;
	bool brk=0;
	
	string words;
	stringstream iss(str);

	while(iss >> words)
	{
		if(words[words.length()-1]==34)
		{
			iss >> words;

			if(words=="in") { 
				
				while(iss >> words){

					if(words=="Proc."){
						proc=1;
						brk=1;
						break;
					}
					else if(words=="ed.,"){
						bChap=1;
						brk=1;
						break;
					}
					else if(words=="Conf.")
					{
						con=1;
						brk=1;
						break;
					}
				}
				
				if(brk==1) break;
			}
			if(words=="presented")
			{
				con=1;
				break;
			}
			else { 
				art=1;
				break;
				}
			}
	}



	if(art==0 && bChap==0 && con==0 && proc==0) book=1;
	
	if(bChap==1) extractBChap(store);
	if(book==1) extractBook(store);
	if(art==1) extractArticle(store);
	if(proc==1) extractConferenceProc(store);
	if(con==1) extractConference(store);
	bChap=0;
	book=0;
	art=0;
	proc=0;
	con=0;
}

int main()
{
	string s,tm0="",newtmp="",oldtmp,title,author,w;
	int i=0,j=0,cit=1;
	bool fl=0,hbjb=0,t=0,au=0, f=1,ci=0,ic=1,b=0,e=0;
	vector<int> citations;
	
	iFile.open("/home/pranto/Desktop/New/SPL-1/rawtext4.txt");
	oFile.open("/home/pranto/Desktop/New/SPL-1/xml1.xml");
	
	if(iFile.is_open() && oFile.is_open())
	{
		oFile << "<xml>\n<document>\n";
		
		string word; 
		
		getline(iFile,s);
			
			title = s;
			
			getline(iFile,s);
			
			author = s;
			
		while(true)
		{
			
			getline(iFile,s);
			
			stringstream iss(s);
			
			while(iss >> word)
			{
				if(word=="Department")
				{
					oFile <<"<title> " << title << " </title>\n";
					oFile << "<authors>\n";
					oFile << "<author>\n";
					
					stringstream ias(author);
					
					oFile<< "<name> <firstname> ";
					
					while(ias >> word)
					{
						tm0+=word+' ';
					}
					int hlprI=0;
					
					string sub="</firstname> <lastname> ";
					
					for(int i=tm0.length()-2;;i--)
					{
						hlprI++;
						
						if(tm0[i]==' ')
						{
							tm0.insert(tm0.length()-hlprI,sub);
							break;
						}
					}	
					tm0+=" </lastname> </name>\n";
					
					oFile << tm0;
					
					tm0="";
					
					hlprI=0;
					
					oFile <<"<Department> "+ s +" </Department>\n";
					t=1;
					break;
				}
			}
			
			if(t==1)
			{
				break;
			}
			else
			{
				title+=' '+author;
				author=s;
			}
		}
		
		getline(iFile,s);
		
		oldtmp=s;
		
		while(fl==0){
			
			hbjb=0;
			 
			 if(s=="ABSTRACT"||s=="Abstract") {
			 	
			 	oFile << "</author>\n</authors>\n<article>\n" << s << endl;
			 	fl=1;
			 	break;
			 }
			 			 
			 stringstream iss(s);
  		
    		 while (iss >> word) 
       		 {
       		 	for(i=0;word[i];i++)
       		 	{
       		 		if(word[i]=='@'){
       		 			
       		 			newtmp+=("<mail>"+oldtmp+"</mail>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 		}
  
       		 	}
       		 	
       		 	if(word=="Department")
       		 	{
       		 		newtmp+=("<Department>"+oldtmp+"</Department>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word=="University")
       		 	{
       		 		newtmp+=("<University>"+oldtmp+"</University>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word=="School")
       		 	{
       		 		newtmp+=("<school>"+oldtmp+"</school>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word[word.length()-1]==',')
       		 	{ 
       		 		newtmp+=("<address>"+oldtmp+"</address>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 	}
       		 	else if(word=="January"||word=="February"||word=="March"||word=="April"||word=="May"||word=="June"||word=="July"||word=="August"||
       		 		word=="September"||word=="October"||word=="November"||word=="December")
       		 	{
       		 		newtmp+=("<date>"+oldtmp+"</date>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;

       		 	}
       		 		
       		 	else
       		 		tm0+=word+' ';
       		 	
       		} 
				if(hbjb==0){ 

				oFile << "</author>\n<author>\n";
				
				stringstream ias(tm0);
					
					oFile<< "<name> <firstname> ";
					
					int hlprI=0;
					
					string sub="</firstname> <lastname> ";
					
					for(int i=tm0.length()-2;;i--)
					{
						hlprI++;
						
						if(tm0[i]==' ')
						{
							tm0.insert(tm0.length()-hlprI,sub);
							break;
						}
					}	
					tm0+=" </lastname> </name>\n";
					
					oFile << tm0;
					
					tm0="";
					
					hlprI=0;
       
       		 		newtmp="";	
       		 	}
			       		 
       		 else tm0="";	
       		 
       		 getline(iFile,s);
       		
       		 oldtmp=s;	 		
			}
		
			while(!iFile.eof()){
				
				getline(iFile,s);
				
				if((s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
					break;
				
				f=1,ci=0,ic=1,b=0,e=0;
				tm0="";
				newtmp="";
				
				istringstream ics(s);
				
					for(i=0;i<s.length();i++)
					{
						if(s[i]=='['){
						
							while(i<s.length() && s[i]!=']')	
							{
								tm0+=s[i];
								i++;
							}
							if(s[i]==']')
							{
								ci=1;
								tm0+=s[i];
							}
							else
							{
								oFile << tm0 << endl;
								tm0="";
							}		
						}
						else 
							oFile << s[i];
							
						if(ci==1)
						{
							for(int c=1;c<tm0.length()-1;c++)
							{
								if(tm0[c]==',' || tm0[c]==' ') continue;
								
								else if(tm0[c]<48 || tm0[c]>57)
								{
									f=0;
									break;
								}
							}
							if(f==0)
								oFile << tm0 <<' ';
								
							if(f==1)
							{
								int cnt=1;
								int id=0;
								
								for(int c=1; c <tm0.length();c++)
								{
								
									if(tm0[c]==',' || tm0[c]==']'){
									
										oFile << "<citationid> ["<< newtmp << "] </citationid> ";
										newtmp="";	
									}
									else if(tm0[c]==' ')
										continue;
										
									else
										newtmp+=tm0[c];
								}
								
							}
						}
						ci=0;f=1; tm0="";
						
					}		
					oFile << endl;	
			}
			oFile << "</article>" << endl;
			oFile << "<reference>" << endl;

			if((s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
			{
				int cnt=0;
				iFile >> s;
				
				while(!iFile.eof())
				{
					if(s[0]=='[')
						oFile<< "<citationid> ["<< cit++ << "] </citationid>\n";
				
					
						while(iFile >> s && !iFile.eof()){
							
							if(s[0]!='[')
								tm0+=s+' ';
							else 
								break;	
						}
						//cout<< tm0 << endl;
						getChunk(tm0);
						tm0="";
					}
					cnt=0;
				
				}
			iFile >> s;		
	
		//getline(iFile,s);
	}
	oFile<< "</reference>\n</document>\n</xml>\n";
	iFile.close();
	oFile.close();
	
	cout<< "parsing completed\n";
		
	return 0;
}

