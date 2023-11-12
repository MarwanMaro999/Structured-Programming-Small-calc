
#ifndef TASK_3_MACHINE_LANGUAGE_H
#define TASK_3_MACHINE_LANGUAGE_H



class Instructions {
protected:
    void load1();
    void load2();
    void store();
    void move();
    void add1();
    void add2();
    void jump();
    void halt();
};

class Machine_language : public Instructions{
private:
    int start_address;
    int regis[16];
    string mem[256];
public:
//    static int counter;
    Machine_language();
    void menu();
    void fetch();
    void execute();
    void print(int pc,string ir);
};


#endif //TASK_3_MACHINE_LANGUAGE_H
