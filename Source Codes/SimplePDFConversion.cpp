#include<iostream>

#include<fstream>

using namespace std;

int main (void)
{
	ifstream iFile;
	ofstream oFile;
	
	string s;
	
	iFile.open("/home/pranto/Downloads/sample.pdf");
	oFile.open("/home/pranto/Desktop/t.txt");
	
	if(oFile.is_open() && iFile.is_open())
	{
		iFile >> s;
		
		while(!iFile.eof())
		{
			if(s=="(")
			{
				iFile >> s;
				
				while(s!=")"){
					oFile << s <<' ';
					iFile >> s;
				}	 
			}
			iFile >> s;
		}
	  } 
	    
	
	iFile.close(); 
	oFile.close();
	
	return 0;	
}	
