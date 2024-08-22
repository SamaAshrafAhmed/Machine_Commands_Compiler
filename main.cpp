#include <iostream>
#include "Machine.cpp"
#include <vector>
#include <fstream>

using namespace std;

ifstream Instructions;
Machine Mch;   
// Gets file name from user and opens it
void LoadFile()
{
 
   string fName;
   cout << "Enter The text file name: " ;
   cin>> fName;
   fName+=".txt";
   Instructions.open(fName, ios::in);
   if(!Instructions.is_open())
   {
    cout << "Error opening the file, Try again"<< endl;
    LoadFile();
   }
}
// stores the commands in a vector which contributes in creating the map of commands in the machine
void Start()
{

   vector <string> instrs;
   if(Instructions.is_open())
   {
    string line;
    while(getline(Instructions, line))
    {
        string word="";
        for(int i=0; i<=line.size(); i++)
        {
            if(line[i]==' '||i==line.size())
            {
                instrs.push_back(word);
                word = "";
                
            }
            else
            {
                word+=line[i];
            }

        }
    }

    Instructions.close();

    for(int i=0; i<instrs.size(); i+=3)
   {
    string s="";
     s+=instrs[i][2];
     s+=instrs[i+1][2];
     s+=instrs[i+2][2];
     s+= instrs[i+2][3];
     Mch.MachineCmnd(s);
   }

    Mch.InvokeMachine();
   }
}

int main(){
      LoadFile();
      Start();

    while(true)
    {
    int n;
    cout << endl;
    cout << "Machine Finished!"<< endl;
    cout << 
    "1- Display Registers status.\n"
    "2- Display PC Status.\n" 
    "3- Display IR Status.\n"
    "4- Display Memory Status\n"
    "0- End\n"; 
    
    cin>> n;
    cout << endl;
    if(n==1)
    {
      
        Mch.DisplayReg();
        cout << endl;
    }
    else if(n==2)
    {
        Mch.DisplayPC();
        cout << endl;
      
    }
    else if(n==3)
    {
        Mch.DisplayIR();
        cout << endl;
    }
    else if(n==4)
    {
        Mch.DisplayMem();
        cout << endl;
    }
  
    else if(n==0)
    {
        return 0;
    }
    }
}