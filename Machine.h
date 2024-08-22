#ifndef MACHINE_H
#define MACHINE_H

#pragma once

#include<iostream>
#include <map>
using namespace std;



class Register
{
    int index;
    int content;
    bool used = 0;

    public:
        void SetIndex(int indx);
        void SetContent(string cont);
        void SetContent(int cont);
        int GetIndex();
        int GetContent();
        bool is_used();
        void set_used(int n);

};

class Memory
{
    int cells[256]; // max memory FF -> 255

    public:
        void SetMem(string indx, string cont); // mem[x] = y 
        void SetMem(string indx, int cont); // mem[x] = y 
        int GetMem(int indx);  //mem[x] = ?
};

class Machine 
{
    private:
    map <string,string>IR;
    string PC="0";
    string command;
    char opCode;
    string operand;
    Register R[16]; // array of registers 0 -> F
    Memory Mem;
    int cmndNo=0;


    void Load1();
    void Load2();
    void Store();
    void Print();
    void Move();
    void Add();
    void Jump();
    void Halt();
    void Display();

    void SetReg(char regnum, string cont);
    void SetReg(char regnum, int cont);
    void SetMemory(string mAdrs, string cont);
    void SetMemory(string mAdrs, int cont);
    int  GetMemory(int indx);
    int  GetOP();
    Register GetReg(char indx);
    Register GetReg(int indx);
    void ApplyCommand(string cmnd);
    
    public:
    
    Machine();
    void MachineCmnd(string inst);
    void InvokeMachine();
    void DisplayReg();
    void DisplayPC();
    void DisplayIR();
    void DisplayMem();

};



#endif