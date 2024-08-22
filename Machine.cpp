#include "Machine.h"

#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std; 

// Convert Hexadicimal number into Decimal number overloaded to work on strings or characters
int Hex_to_Dec(string Hx)
{

    int result = 0;
    reverse(Hx.begin(), Hx.end());
    for(int i = 0 ; i < Hx.size(); i++)
    {
    int x = 0;
        if (Hx[i]>64)
        x = Hx[i]-55;

        else 
        x = (Hx[i] - '0');

        result += x * pow(16,i);
    }
    return result;
}
int Hex_to_Dec(char Hx)
{    
    int x = 0;
        if (Hx > 64)
        x = Hx - 55;

        else 
        x = (Hx - '0');  
    return x;
}
// Converts Decimal number into Hexadecimal number
string Dec_to_Hex(int dec)
{
    char hex[5];
    sprintf(hex, "%X", dec);
    return hex;

}

string BalanceHex(string hx)
{
    while(hx.size()<2)
    {
        // reverse(hx.begin(); hx.end());
        hx+='0';
        reverse(hx.begin(), hx.end());

    }
    return hx;
}

// index setter of a register
void Register::SetIndex(int indx){
    index = indx;
}
// sets content of a register 
//overloaded to accept Hexadecimal and Decimal
void Register::SetContent(string cont)
{
        content = Hex_to_Dec(cont);
}

void Register::SetContent(int cont)
{
    content = cont;
}
// returns the number of a register
int Register::GetIndex()
{
    return index;
}
//reterns the content of the register
int Register::GetContent()
{
    return content;
}
// returns true if the register is used in the current program
bool Register::is_used()
{
    return used;
}
// set to true if the register is used in the current program
void Register::set_used(int n)
{
    used = n;
}
// stores the content of a memory cell
// overloaded to accept Hexadecimal and Decimal 
void Memory::SetMem(string indx, string cont)
{
    cells[Hex_to_Dec(indx)] = Hex_to_Dec(cont);
}

void Memory::SetMem(string indx, int cont)
{
   int ind = Hex_to_Dec(indx);
    cells[ind] = cont;
}
// returns the stored content in a memory cell
int Memory::GetMem(int indx)
{
    return cells[indx];
}

// stores number in register with certain index
// overloaded to accept Hexadecimal and Decimal 
void Machine::SetReg(char regnum, string cont)
{
    int num = Hex_to_Dec(regnum);

    R[num].SetIndex(num);
    R[num].SetContent(cont);
}
void Machine::SetReg(char regnum, int cont)
{
    
    int num = Hex_to_Dec(regnum);
    R[num].SetIndex(num);
    R[num].SetContent(cont);
}
//stores content into a certain memory address
// overloaded to accept Hexadecimal and Decimal
void Machine::SetMemory(string mAdrs, string cont)
{
    Mem.SetMem( mAdrs, cont);
}

void Machine::SetMemory(string mAdrs, int cont)
{
    Mem.SetMem(mAdrs, cont);
}
// returns the op-code
int Machine::GetOP()
{
    return command[0];
}
// returns a register with its index and content
// overloaded to accept Hexadecimal and decimal numbers
Register Machine::GetReg(char indx)
{
    int num = Hex_to_Dec(indx);

    return R[num];

}
Register Machine::GetReg(int indx)
{
   int num=indx;

    return R[num];

}

//returns the content stored in a certain memory index

int Machine::GetMemory(int indx)
{
    return Mem.GetMem(indx);
}
// executes the load from memory instruction
void Machine::Load1()
{
  
    string  mem = "";
    mem+=operand[1];
    mem+=operand[2];
        int m = Hex_to_Dec(mem);
     
     SetReg(operand[0], GetMemory(m));
     R[Hex_to_Dec(operand[0])].set_used(1);
    
}
// executes the load a number instruction
void Machine::Load2()
{
   
    string  mem = "";
    mem+=operand[1];
    mem+=operand[2];
        int x;
        int m = Hex_to_Dec(mem);
     SetReg(operand[0], m);
      R[Hex_to_Dec(operand[0])].set_used(1);
}
// stores a number found in the register to a certain memory address
void Machine::Store()
{
    string  mem = "";
    mem+=operand[1];
    mem+=operand[2];

    SetMemory(mem,R[Hex_to_Dec(operand[0])].GetContent());

    
}
// prints the content of a register
void Machine::Print()
{

    int z = R[Hex_to_Dec(operand[0])].GetContent();

    cout<< z << endl;
}
// copies content from a register to another
void Machine::Move()
{
    R[Hex_to_Dec(operand[2])].SetContent(R[Hex_to_Dec(operand[1])].GetContent());
    R[Hex_to_Dec(operand[2])].set_used(1);
}
// adds the contents of two registers and stores the result in third register
void Machine::Add()
{
    int added = R[Hex_to_Dec(operand[1])].GetContent()+R[Hex_to_Dec(operand[2])].GetContent();
    R[Hex_to_Dec(operand[0])].SetContent(added);
    R[Hex_to_Dec(operand[0])].set_used(1);
}
// if the current register's contents equals the content of register number zero 
//then the code will jump to a certain instruction
void Machine::Jump()
{
    if(R[Hex_to_Dec(operand[0])].GetContent() == R[0].GetContent())
    {
        int indx = Hex_to_Dec(operand.substr(1,2));
        PC = Dec_to_Hex(indx); 
        InvokeMachine();
    }
}
// Sets the PC to the last instruction for ending the program (terminates the while loop in InvokeMachine Function )
void Machine::Halt()
{
    PC = Dec_to_Hex(IR.size()-2);
}
// initializing constructor
Machine::Machine()
{
    command="";
    command[0]=0;
    operand ="";
}
// Stores the commands in the IR Map of instrucions to be executed
// ex: 00  21
//     01  03
//     02  22
//     03  0A
void Machine::MachineCmnd(string inst)
{
    command = inst;
    operand = command.substr(1,3);

    IR[Dec_to_Hex(cmndNo)] = command.substr(0,2);
    IR[Dec_to_Hex(cmndNo+1)] =  command.substr(2,2);

    Mem.SetMem(Dec_to_Hex(cmndNo),command.substr(0,2));
    Mem.SetMem(Dec_to_Hex(cmndNo+1),command.substr(2,2));


    cmndNo+=2;
}
// Starts the Machine
// Executes the instructions one by one
// Works as long as the program counter (PC) didn't reach the end of the IR
// Allows the user to display the current status of the machune registers and counter
void Machine::InvokeMachine()
{
    while(Hex_to_Dec(PC)<IR.size()-2)
    { 
    string cmd = IR[PC]+IR[Dec_to_Hex(Hex_to_Dec(PC)+1)];
     ApplyCommand(cmd);
     PC = Dec_to_Hex(Hex_to_Dec(PC)+2); 
     Display();
    }
}
// Invokes the suitable function according to the op-code of the current executed instruction
void Machine::ApplyCommand(string cmnd)
{
    command = cmnd;
    operand = command.substr(1,3);

    if(command[0] == '1')
    {
        Load1();
    }
    else if(command[0]=='2')
    {
        Load2();
    }
    else if(command[0]=='3')
    {
        if(operand[1] == '0' and operand[2] == '0')
        {
            Print();
        }
        else
        {
            Store();
        }
    }
    else if(command[0]=='4')
    {
        Move();
    }
    else if(command[0]=='5'|| command[0]=='6')
    {
        Add();
    }
    else if(command[0]=='B')
    {
        Jump();

    }
    else if(command[0]=='C')
    {
        Halt();
    }
}

// Displays the Registers status
void Machine::DisplayReg()
{
cout << "Registers (CPU): \n";
cout << "|-------------|\n";
     for(int i=0; i<16; i++)
        {
            if(GetReg(i).is_used())
            {
                cout  << "| " << BalanceHex(Dec_to_Hex(i)) << "  |   " << BalanceHex(Dec_to_Hex(GetReg(i).GetContent())) << "  |"<< endl;
                cout << "|-------------|\n";
            }
        }
}
// Displays PC Status
void Machine::DisplayPC()
{
    cout <<"PC is at " <<BalanceHex(Dec_to_Hex(Hex_to_Dec(PC)))<< endl;
}
// Displays the current Instruction Registered
void Machine::DisplayIR()
{
     int strt = Hex_to_Dec(PC)-2;
    cout << "IR: " << BalanceHex(IR[Dec_to_Hex(strt)]) << BalanceHex(IR[Dec_to_Hex(strt+1)]) << endl;
         
}
void Machine::DisplayMem()
{
    cout << "Memory: \n";
    for (int i=0; i<256; i++)
    {
        cout << "| " << BalanceHex(Dec_to_Hex(i)) << "   |   "<< BalanceHex(Dec_to_Hex(Mem.GetMem(i))) << "  |" << endl;
        cout << "|--------------|"<< endl;
    }
}
//Lets the user choose whether to display the current status of the program or to continue executing 
void Machine::Display()
{
   
    int n;
    cout<<
    "1- Display Status\n"
    "0- continue\n";
    cin>> n;
    cout << endl;
    if(n==1)
    {
       DisplayReg();
       cout << endl;
       DisplayIR();
       cout << endl;
       DisplayPC();
       cout << endl;
    }
}
