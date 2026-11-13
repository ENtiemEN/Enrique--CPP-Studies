#include <string>
#include <iostream>
#include <vector>

struct Character{
    int x;
    int y;
    std::string name;
    Character(std::string _name) : name(_name){
        //name = _name;
    }

    void move(int _x, int _y){
        x = _x;
        y = _y;
    }
};

// `Command` is an abstract class - because it declares pure virtual functions using `=0`
class Command{
public:
    virtual ~Command(){
    }
    virtual void execute(Character& c) = 0;
    virtual void undo(Character& c) = 0;
};

// An empty body `{}` still counts as an implementation
class Move : public Command{
public:
    void execute(Character& c){
        std::cout << c.name << " moved\n";

    }
    void undo(Character& c){
        std::cout << c.name << " undo move\n";
    }

};

int main(){
    Character enrique("Enrique");

    std::vector<Command*> command_queue;

    Move* m1 = new Move;
    command_queue.push_back(m1);
    Move* m2 = new Move;
    command_queue.push_back(m2);
    Move* m3 = new Move;
    command_queue.push_back(m3);
    Move* m4 = new Move;
    command_queue.push_back(m4);

    for(int i=0; i < command_queue.size(); i++){
        command_queue[i]->execute(enrique);
    }

    for(int i=command_queue.size() - 1; i >= 0; i--){
        command_queue[i]->undo(enrique);
    }

    return 0;
}