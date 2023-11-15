#include <bits/stdc++.h>
using namespace std;

#include "Machine_language.h"

Machine_language::Machine_language() {
    cout<<"Welcome to our Machine Language Simulator\n";
    cout<<"_____________________________________________________________________\n"
          "The program in the file should be entered like this e.g.(0x1 0x0 0xFF)\n"
          "If there is any mistake in the program will not be executed correctly\n"
          "_____________________________________________________________________\n";
    start_address = 0;
}

void Machine_language::menu(){
    cout<<"Enter the address you want to start from (in hexadecimal):\n";
    string s;
    cin>>s;
    istringstream(s) >> hex >>start_address;
}

void Machine_language::fetch() {
    ifstream input_file("Input.txt");
    string s;
    int counter = start_address;
    while(getline(input_file,s)){
        mem[counter] += s[2];
        mem[counter++] += s[6];
        mem[counter++] = s.substr(10,2);
    }
    input_file.close();
}

void Machine_language::execute(){
    progCnt = start_address;
    int cnt_prnt = 1;
    string ir;
    while(mem[progCnt] != "c0"){
        ir = mem[progCnt] + mem[progCnt+1];
        if(mem[progCnt][0] == '1')
            load1(ir);
        else if(mem[progCnt][0] == '2')
            load2(ir);
        else if(mem[progCnt][0] == '3')
            store(ir);
        else if(mem[progCnt][0] == '4')
            move(ir);
        else if(mem[progCnt][0] == '5')
            add1(ir);
        else if(mem[progCnt][0] == 'B' || mem[progCnt][0] == 'b')
            jump(ir);
        else if(mem[progCnt][0] == 'C' || mem[progCnt][0] == 'c')//halt
            break;
        char c;
        cout<<"step "<<cnt_prnt++<< " finished\n";
        progCnt += 2;
        do{
            cout<<"Do you want to print any thing (y/n):\n";
            cin>>c;
            while(c != 'y' && c != 'n'){
                cout<<"Please enter a valid character (y/n):\n";
                cin>>c;
            }
            if(c == 'y')
                print(ir);
        } while (c == 'y');
    }
}

void Machine_language::print(string ir) {
    cout<<"1-Registers\n"
          "2-Address\n"
          "3-Screen\n"
          "4-PC (program counter)\n"
          "5-IR (Instruction register)\n"
          "Enter choice:\n";
    int x; cin>>x;
    if(x == 1){
        cout<<"Which register you want to print:\n";
        string ix;
        int idx;
        cin>>ix;
        istringstream(ix) >> hex >>idx;
        if(regis[idx].empty()){
            cout<<"register "<<ix<<" is empty\n";
        }
        if(idx < 16 && idx >= 0){
            cout<<"register "<<ix<< " = "<<regis[idx]<<" (in hexadecimal)\n";
            int dec_Val = stoi(regis[idx], 0, 16);
            cout<<"register "<<ix<< " = "<<dec_Val<<" (in decimal)\n";
        }
    }
    else if(x == 2){
        cout<<"Which address you want to print:\n";
        string ix;
        int idx;
        cin>>ix;
        istringstream(ix) >> hex >>idx;
        if(mem[idx].empty())
            cout<<"address "<<ix<<" is empty\n";

        if(idx < 256 && idx >= 0){
            cout<<"address "<<ix<< " = "<<mem[idx]<<" (in hexadecimal)\n";
            int dec_Val = stoi(mem[idx], 0, 16);
            cout<<"address "<<ix<< " = "<<dec_Val<<" (in decimal)\n";
        }

    }
    else if(x == 3){
        cout<<"screen = "<<mem[0]<<" (in hexadecimal)\n";
    }
    else if(x == 4){
        cout<<"program counter = "<<hex<<progCnt<<" (in hexadecimal)\n";
    }
    else if(x == 5){
        cout<<"instruction register = "<<ir<<'\n';
    }
    else{
        cout<<"invalid input\n";
    }
}

void Instructions::load1(string ir) {
    int idx,idx2;
    istringstream(ir.substr(1,1)) >> hex >> idx;
    istringstream(ir.substr(2,2)) >> hex >> idx2;
    regis[idx] = mem[idx2];
}

void Instructions::load2(string ir) {
    int idx;
    istringstream(ir.substr(1,1)) >> hex >> idx;
    regis[idx] = ir.substr(2,2);
}

void Instructions::store(string ir) {
    int idx,idx2;
    istringstream(ir.substr(1,1)) >> hex >> idx;
    istringstream(ir.substr(2,2)) >> hex >> idx2;
    mem[idx2] = regis[idx];
}

void Instructions::add1(string ir) {
    int idx,idx2,idx3;
    istringstream(ir.substr(1,1)) >> hex >> idx;
    istringstream(ir.substr(2,1)) >> hex >> idx2;
    istringstream(ir.substr(3,1)) >> hex >> idx3;
    int dec1 = stoi(regis[idx2], 0, 16) , dec2 = stoi(regis[idx3], 0, 16);
    if (dec1 > 128 || dec2 > 128){
        stringstream hexa;
        hexa<<hex<<(dec1+dec2);
        regis[idx] = hexa.str();
        regis[idx].erase(0,1);
    } else{
        stringstream hexa;
        hexa<<hex<<(dec1+dec2);
        regis[idx] = hexa.str();
    }
}

void Instructions::move(string ir) {
    if(ir[1] == '0'){
        int idx,idx2;
        istringstream(ir.substr(2,1)) >> hex >> idx;
        istringstream(ir.substr(3,1)) >> hex >> idx2;
        regis[idx2] = regis[idx];
    }
}

void Instructions::jump(string ir) {
    int idx;
    istringstream(ir.substr(1,1)) >> hex >> idx;
    if(regis[idx] == regis[0])
        istringstream(ir.substr(3,2)) >> progCnt;
}


