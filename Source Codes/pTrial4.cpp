#include<bits/stdc++.h>

using namespace std;

ifstream iFile;
ofstream oFile;
int spc=0;
bool book=0, bChap=0, art=0,con=0,proc=0, electricB=0,electricJ=0;

void getNames(string s)
{
	bool name=0,ed=0,fn=0,ln=0; int hlprI=0;
	string w,tmp="",cs;
	stringstream iss(s);
	
	
Skip:while(iss >> w)
	{
		if(name==0)
		{
			oFile << "<name> ";
		}
		if(w=="and"){
			
			if(cs[cs.length()-1]==',')
			{
				name=1;
				fn=0;
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
				fn=0;
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
			else if(w=="Md."||w=="MD.")
			{
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
				if(w[w.length()-3]==46 || w[w.length()-3]=='-')
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
	}
}
void extractBChap(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && (int)w[0]!=-30 && w[0]!=34)
	{
		cout<< w[0] << endl;
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<chapterTitle> ";
	
	while((int)w[w.length()-1]!=-99 && w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	//tmp.erase(tmp.begin());
	//tmp.erase(tmp.end()-2,tmp.end());

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
	bool bn=1;
	string w,tmp="";
	stringstream iss(str);
	
	while(iss >> w)
	{
		if(w[0]=='"' || (int)w[0]==-30) 
		{
			bn=0;
			break;
		}
		
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
	
	if(bn) iss >> w;

	while(w[w.length()-1]!=46 && (int)w[w.length()-1]!=-99)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	//tmp.erase(tmp.end());

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
	
	while(iss >> w && w[0]!=34 && (int)w[0]!=-30)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<article> ";

	while(w[w.length()-1]!=34 && w[w.length()-1]!=-99)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	//tmp.erase(tmp.end()-2);

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
	
	while(iss >> w && w[0]!=34 && (int)w[0]!=-30)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<article> ";

	while(w[w.length()-1]!=34 && (int)w[w.length()-1]!=-99)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	//tmp.erase(tmp.end()-2);

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
	
	while(iss >> w && (int)w[0]!=-30 && w[0]!=34)
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";
	cout << tmp << endl;
	getNames(tmp);
	tmp="";
	oFile << "</authors>\n<paper> ";

	while(((int)w[w.length()-1]!=-99) && w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	tmp+=w;
	
	//tmp.erase(tmp.begin());
	//tmp.erase(tmp.end()-2,tmp.end());

	oFile << tmp << " </paper>\n";

	tmp="";
	
	/*while(iss >> w) 
	{
		if(w=="Rec.") break;
		if(w=="the" ) break;
	}*/
	
	oFile <<"<conference> ";
	
	while(iss >> w)
	{
		oFile << w << ' ';
	}
	oFile <<" </conference>\n";
	
	proc=0;

}
void extractEJ(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!='(')
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";

	getNames(tmp);
	
	tmp="";
	
	oFile << "</authors>\n<article> ";

	while(((int)w[0]!=-30) && w[0]!=34)
	{
		iss >> w;
	}
	
	while(((int)w[w.length()-1]!=-99) && w[w.length()-1]!=34)
	{
		tmp+=w+' ';
		iss >> w;
	}
	
	tmp+=w;
	//tmp.erase(tmp.begin());
	//tmp.erase(tmp.end()-2,tmp.end());

	oFile << tmp << " </article>\n";

	tmp="";
	
	while(iss >> w && w[0]!='[') 
	{
		tmp+=w+' ';
	}
	
	oFile <<"<journal> "+tmp+" </journal>\n";
	
	tmp="";
	
	while(iss >> w && w!="Available:"){}
	
	while(iss >> w && w[0]!='[')
	{
		tmp+=w+' ';
	}
	oFile <<"<source> "+tmp+" </source>\n";
	
	tmp="";
	electricJ=0;

}
void extractEB(string s)
{
	string w,tmp="";
	stringstream iss(s);
	
	while(iss >> w && w[0]!='(')
	{
		tmp+=w+' ';
	}
	
	oFile << "<authors>\n";

	getNames(tmp);
	
	tmp="";
	
	oFile << "</authors>\n<book> ";

	while(w[w.length()-1]!=')')
	{
		iss >> w;
	}
	
	while(iss >> w && w[0]!='[')
	{
		tmp+=w+' ';
	}
	
	//tmp.erase(tmp.begin());
	//tmp.erase(tmp.end()-2,tmp.end());

	oFile << tmp << " </book>\n";

	tmp="";
	
	while(iss >> w && w!="Available:"){}
	
	while(iss >> w)
	{
		tmp+=w+' ';
	}
	oFile <<"<source> "+tmp+" </source>\n";
	
	tmp="";
	electricB=0;


}
void getChunk(string str) // “=-30 ”=-99
{
	string store;
	store=str;
	bool brk=0;
	int loop=0;
	string words;
	stringstream iss(str);
	
	while(iss >> words)
	{
		if(words[0]=='(' && (words[1]>47 && words[1]<58 && words[2]>47 && words[2]<58 && words[3]>47 && words[3]<58))
		{
			while(iss >> words && loop <5) 
			{
				if((int)words[0]==-30 || words[0]==34)
				{
					electricJ=1;
					break;
				}
				loop++;
			}
			if(electricJ==0)electricB=1;
			brk=1;
			break;
		}
		if(brk) break;
	
		if(words[words.length()-1]==-99)
		{
			//cout<<words<<' ' <<words[0] <<' ' << (int)words[0] << endl;
			
			while(iss >> words){

			if(words=="in" || words=="on") { 
				
				while(iss >> words){

					if(words=="Proc."){
						proc=1;
						brk=1;
						break;
					}
					else if(words=="ed.,"||words=="vol."){
						bChap=1;
						brk=1;
						break;
					}
					else if(words=="Conf." || words=="Conference")
					{
						con=1;
						cout<< con << endl;
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
			if(brk) break;	
		}	
	}
	
	if(art==0 && bChap==0 && con==0 && proc==0 && electricJ==0 && electricB==0) book=1;
	
	if(bChap==1) extractBChap(store);
	if(book==1) extractBook(store);	
	if(art==1) extractArticle(store);
	if(proc==1) extractConferenceProc(store);
	if(con==1) extractConference(store);
	if(electricJ) extractEJ(store);
	if(electricB) extractEB(store);
	bChap=0;
	book=0;
	art=0;
	proc=0;
	con=0;
	electricB==0; 
	electricJ==0; 
}
bool rootAuthors(string s)
{
	string w;
	stringstream sr(s);
	
	while(sr >> w)
	{
		if(w=="and" || w[w.length()-1]==',')
		{
			getNames(s+'.');
			return true;
		}
	}
	return false;

}
bool getmail(string s)
{
	bool bt=0;
	string w;
	stringstream sr(s);
	
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==',')
		{
			bt=1;
			break;
		}
	}
	if(bt)
	{
		while(sr >> w)
		{
			oFile <<"<mail> "<< w << " </mail>\n";	
		}
		return true;
	}
	return false;


}
int main()
{
	string fileName,s,tm0="",newtmp="",oldtmp,title,author;
	int i=0,j=0,cit=1;
	bool fl=0,hbjb=0,t=0,f=1,ci=0,ad=0,m=0,ra=0,rm=0;
	
	cout<<"filename: ";
	cin >> fileName;
	
	iFile.open(fileName);
	
	for(int v=0;fileName[v];v++)
	{
		if(fileName[v]=='.') break;
		
		tm0+=fileName[v];
	}
	tm0+=".xml";
	
	oFile.open(tm0);
	
	tm0="";
	
	
	
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
				if(word=="Department" || word=="School" || word=="Institute")
				{
					oFile <<"<title> " << title << " </title>\n";
					oFile << "<authors>\n";
					oFile << "<author>\n";
					
					ra=rootAuthors(author);
					
					if(!ra){
					
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
					}
					
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
       		 			
       		 			rm=getmail(s);
       		 			
       		 			if(!rm){
       		 				newtmp+=("<mail>"+oldtmp+"</mail>");
       		 				oFile << newtmp << endl;
       		 				newtmp="";
       		 				hbjb=1;
       		 			}
       		 			else
       		 			{
       		 				hbjb=1;
       		 				break;
       		 			}	
       		 		}
  
       		 	}
				if(rm)
				{ 
					rm=0;
					break;
       		 	}
       		 	
       		 	if(word.substr(0,8)=="Abstract"|| word.substr(0,8)=="ABSTRACT-")
       		 	{
       		 		oFile << "</author>\n</authors>\n<article>\n" << s << endl;
			 		fl=1;
			 		hbjb=1;
			 		break;
       		 	}
       		 	
       		 	else if(word=="Department")
       		 	{
       		 		newtmp+=("<Department> "+oldtmp+" </Department>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word=="University")
       		 	{
       		 		newtmp+=("<University> "+oldtmp+" </University>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word=="School")
       		 	{
       		 		newtmp+=("<school> "+oldtmp+" </school>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 	else if(word=="Institute")
       		 	{
       		 		newtmp+=("<institute> "+oldtmp+" </institute>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			break;
       		 	}
       		 		
       		 	else if(word[word.length()-1]==',' && ad==0)
       		 	{ 
       		 		for(int i=0;i<word.length();i++)
       		 		{
       		 			if(word[i]=='@'){ m=1;break;}
       		 		}
       		 		if(!m){
       		 		
       		 		newtmp+=("<address>"+oldtmp+"</address>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 		}
       		 		else m=0;
       		 	}
       		 	
       		 	else if(word=="January"||word=="February"||word=="March"||word=="April"||word=="May"||word=="June"||word=="July"||word=="August"||
       		 		word=="September"||word=="October"||word=="November"||word=="December")
       		 	{
       		 		newtmp+=("<date>"+oldtmp+"</date>");
       		 			oFile << newtmp << endl;
       		 			newtmp="";
       		 			hbjb=1;
       		 			ad=1;

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
       		 
       		 ad=0;
       		 
       		 getline(iFile,s);
       		
       		 oldtmp=s;	 		
			}
		
			while(!iFile.eof()){
				
				getline(iFile,s);
				
				if((s=="References"||s=="Reference"||s=="REFERENCES"||s=="REFERENCE"))
					break;
				
				f=1,ci=0;
				tm0="";
				
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
								//int cnt=1;
								//int id=0;
								
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
				iFile >> s;
				
				while(!iFile.eof())
				{
					if(s[0]=='[' && s.length()<=4)
						oFile<< "<citationid> ["<< cit++ << "] </citationid>\n";
				
					
						while(iFile >> s && !iFile.eof()){
							
							if(s[0]!='[' || (s[0]=='[' && (s[1]<48 || s[1]>57))) 
								tm0+=s+' ';
							else 
								break;	
						}
						//cout<< tm0 << endl;
						getChunk(tm0);
						tm0="";
					}
				
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

