#ifndef TASK_3_MACHINE_LANGUAGE_H
#define TASK_3_MACHINE_LANGUAGE_H



class Instructions {
protected:
    int start_address;
    string regis[16];
    string mem[256];
    int progCnt;
    void load1(string ir);
    void load2(string ir);
    void store(string ir);
    void move(string ir);
    void add1(string ir);
    void jump(string ir);
};

class Machine_language : public Instructions{

public:
//    static int counter;
    Machine_language();
    void menu();
    void fetch();
    void execute();
    void print(string ir);
};


#endif //TASK_3_MACHINE_LANGUAGE_H
