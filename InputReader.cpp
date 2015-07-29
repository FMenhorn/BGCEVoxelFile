#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
  int x=1;
  int linecounter=0;
  char buffer[1];
  ifstream infile;
  string line;
  infile.open("STLFiles/Moon.dat", ios::binary | ios::in);

  if (infile.is_open())
  {
	while(!infile.eof()){
		infile.read(buffer, 1);
		cout << buffer << endl;
  		x = atoi(buffer);
  		cout << linecounter++ << ": "<< x << endl;
	}
	if(infile.eof()){
		cout << "Reached end of file\n";
	}
  }
  else cout << "Unable to open file";
  return 0;
}
