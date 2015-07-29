#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  int x; 
  ifstream infile;
  string line;
  infile.open("Moon.dat", ios::binary | ios::in);

  if (infile.is_open())
  {
  	infile.read(&x, 7);
  }
  else cout << "Unable to open file";
  return 0;
}
