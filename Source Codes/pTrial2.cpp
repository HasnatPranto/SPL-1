//successfully tested with "sample.pdf", which was NOT FILTERED
#include<iostream>
#include<fstream>

using namespace std;

int main (void)
{
	ifstream iFile;
	ofstream oFile;
	
	string s,tmp="";
	int i;
	
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
				tmp.erase(tmp.begin());
				tmp.erase(tmp.end()-2);
				
				oFile << tmp << endl;
				
				tmp="";	
				
			}
			iFile >> s;
		}
	  } 
	    
	
	iFile.close(); 
	oFile.close();
	
	return 0;	
}	
