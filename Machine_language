#include <bits/stdc++.h>
using namespace std;

#include "Machine_language.h"

Machine_language::Machine_language() {
    cout<<"Welcome to our Machine Language Simulator\n";
    cout<<"_____________________________________________________________________\n"
          "The program in the file should be entered like this e.g.(0x1 0x0 0xFF)\n"
          "If there is any mistake in the program will not be executed correctly\n"
          "_____________________________________________________________________\n";
}

void Machine_language::menu(){
    cout<<"Enter the address you want to start from(hexadecimal):\n";
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
    int cnt = start_address,cnt_prnt = 1;
    string ir;
    while(mem[cnt] != "c0"){
        ir = mem[cnt] + mem[cnt+1];
        if(mem[cnt][0] == '1')
            load1();
        else if(mem[cnt][0] == '2')
            load2();
        else if(mem[cnt][0] == '3')
            store();
        else if(mem[cnt][0] == '4')
            move();
        else if(mem[cnt][0] == '5')
            add1();
        else if(mem[cnt][0] == '6')
            add2();
        else if(mem[cnt][0] == 'B' || mem[cnt][0] == 'b')
            jump();
        else if(mem[cnt][0] == 'C' || mem[cnt][0] == 'c')
            halt();
        char c;
        cout<<"step "<<cnt_prnt++<< " finished\n";
        cnt += 2;
        do{
            cout<<"Do you want to print any thing (y/n):\n";
            cin>>c;
            if(c == 'y')
                print(cnt,ir);
        } while (c == 'y');
    }
}

void Machine_language::print(int pc,string ir) {
    cout<<"1-Registers\n"
          "2-Address\n"
          "3-Screen\n"
          "4-PC (program counter)\n"
          "5-IR (Instruction register)\n"
          "Enter choice:\n";
    int x; cin>>x;
    switch (x) {
        case 1:{
            cout<<"Which register you want to print:\n";
            int idx; cin>>idx;
            if(idx < 16 && idx >= 0)
                cout<<"register "<<idx<< " = "<<hex<<regis[idx]<<'\n';
            break;
        }
        case 2:{
            cout<<"Which address you want to print:\n";
            int idx; cin>>idx;
            if(idx < 256 && idx >= 0)
                cout<<"address "<<idx<< " = "<<mem[idx]<<'\n';
            break;
        }
        case 3:{
            cout<<"screen = "<<mem[0]<<'\n';
            break;
        }
        case 4:{
            cout<<"program counter = "<<hex<<pc<<'\n';
            break;
        }
        case 5:{
            cout<<"instruction register = "<<ir<<'\n';
            break;
        }
        default:{
            cout<<"invalid input\n";
            break;
        }
    }
}

void Instructions::load1() {}

void Instructions::load2() {}

void Instructions::store() {}

void Instructions::add1() {}

void Instructions::add2() {}

void Instructions::move() {}

void Instructions::jump() {}

void Instructions::halt() {}

