#include <iostream>
#include <fstream>
using namespace std;
 
int main()
{
    string curLine;
    ifstream fileIn;
 
    
    fileIn.open("help.txt");
 
   
    while(fileIn.good())
    {
        
        getline(fileIn, curLine);
 
        
        cout  << curLine << endl;
    }
 
   
    fileIn.close();
 
    return 0;
}
