//successfully tested with "sample.pdf", which was NOT FILTERED
#include<iostream>
#include<fstream>

using namespace std;

int main (void)
{
	ifstream iFile;
	ofstream oFile;
	
	string s,tmp="",tmp2="";
	char ch;
	int i=0;
	
	iFile.open("/home/pranto/Downloads/sample.pdf");
	oFile.open("/home/pranto/Desktop/New/SPL-1/text.txt");
	
	if(oFile.is_open() && iFile.is_open())
	{
		iFile >> s;
		
		while(!iFile.eof())
		{
			if(s=="Td")
			{
				iFile >> s; //(
				
				iFile >> s; //fisrt str
				
				while(s!="Tj")
				{
					tmp+=(s+' ');
					iFile >> s;
				}
				
				for(i=0;i<tmp.length()-2;i++)
					tmp2+=tmp[i];
				
				oFile << tmp2 << endl;
				
				tmp="";tmp2="";	
				
			}
			iFile >> s;
		}
	  } 
	    
	
	iFile.close(); 
	oFile.close();
	
	return 0;	
}	
