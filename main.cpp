
// ****************************************************************************************************************** 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year  : Trimester 1, 2022/23 (T2215) 
// Lab   : TT5L 
// Names : NUR AISYAH NABILA BINTI NAHAR | ASYRANI SYAZWAN BIN YUHANIS   | LUQMAN HAKIM BIN NOORAZMI 
// IDs   : 1211104230                    | 1211103222                    | 1211101583
// Emails: 1211104230@student.mmu.edu.my | 1211103222@student.mmu.edu.my | 1211101583@student.mmu.edu.my 
// Phones: 0107662837                    | 0162117400                    | 0132874100
// ******************************************************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <unistd.h>
#include <fstream>
#include <math.h>

using namespace std;

class gameBoard
{
private:
    vector< vector<char> > map_;
    int dimX_, dimY_;
public:
    gameBoard(int dimX = 5, int dimY = 7);
    void init(int dimX, int dimY);
    void init2(int dimX, int dimY);
    void display() const;

    int getDimX() const; 
    int getDimY() const;

    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);
    void checkRowCol(int &userInput, string a){
        bool valid=false;
        if(a=="Rows"||a=="Columns"){
            while(not valid){
                cout << "Please enter an ODD number of " << a << " = ";
                cin >> userInput;
                if(userInput%2==0){
                    cout<<"Invalid Input!"<<endl;
                }
                else{
                    valid=true;
                }
            }
        }
        else if(a=="Zombies"){
            while(not valid){
                cout << "Please enter a number of "<<a<< " = ";
                cin >> userInput;
                if(userInput<1 || userInput>9){
                    cout<<"Invalid Input!"<<endl;
                }
                else{
                    valid=true;
                }
            }   
        }
    }
};

class Alien{
private:
    int x_, y_;
    int health_;
    int attack_;
    char alien;
    char z_;
public:
    Alien(int life = 0, int attack = 0);
    void land(gameBoard &gameBoard);
    int getLife();
    int getAttack();
    int getX() const;
    int getY() const;    
    void up(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow);
    void down(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow);
    void left(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow);
    void right(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow);
    void setMove();
    void setMove2(){
        z_='K';
    }
    char getMove();
    void resetTrail(gameBoard &gameBoard);
    void addAttack(int attack);
    void resetAttack(int attack){
        attack_ = attack;
    };
    void addHealth(int life);
    int reduceHealth(int n){
        return health_ = health_ - n;
    }
    void rockSpawn(gameBoard &gameBoard, int x, int y);
    void resumeMove(gameBoard &gameBoard);
    void podAttack(gameBoard &gameBoard, Alien &alien, int &whichArrow, int &whichZombie);
};

class Zombie: public gameBoard{

    private:
        int x_, y_, health_, attack_, range_;
        char heading_;

    public:
        Zombie(){};
            void setZombieAttributes(int n, gameBoard &gameBoard);
            void setZombieAttributes2(int n, gameBoard &gameBoard, int zomb[]);

            void print(){
                cout << "------------------" << endl;
                cout << "Position: " << "(" << getZX() << "," << getZY() << ")" << endl;
                cout << "Health  : " << getZHealth() << endl;
                cout << "Attack  : " << getZAttack() << endl;
                cout << "Range   : " << getZRange() << endl;
                cout << "------------------" << endl;
            }
            void print2(){
                cout << "#===================#" << endl;
                cout << "||"<< " Pos.   :" << setw(2) << "(" << setw(2) << getZX() << "," << setw(2) << getZY() << ")" << "||"<< endl;
                cout << "||"<< " Health :" << setw(8) << getZHealth()   << "||"<< endl;
                cout << "||"<< " Attack :" << setw(8) << getZAttack()   << "||"<< endl;
                cout << "||"<< " Range  :" << setw(8) << getZRange()    << "||"<< endl;
                cout << "#===================#" << endl;
            }
            int getZX(){
                return x_;
            }
            int getZY(){
                return y_;
            }
            int getZHealth();
            int getZAttack();
            int getZRange();
            char getZHeading();
            void setZHealth(int health){
                health_ = health;
            }
            int reduceZHealth(int n){
                return health_=health_-n;
            }
            void resetZHeading(gameBoard &gameBoard){
                heading_=' ';
                gameBoard.setObject(x_,y_,heading_);
            }
            char checkZombie(int x, int y, gameBoard &gameBoard);
            bool returnRange(Zombie &zombie, gameBoard &gameBoard, Alien &alien);
            void checkRange(Zombie &zombie, gameBoard &gameBoard, Alien &alien);
            void checkReturnRange(bool &inRange, Zombie &zombie, gameBoard &gameBoard, Alien &alien); // ONLY USED ON returnRange()
            void checkZombieRange(int &oneDirection, int &rangeFromZombie, Zombie &zombie, gameBoard &gameBoard, Alien &alien); // ONLY USED ON checkRange()
            void moveZombie(int n, Zombie &zombie, gameBoard &gameBoard); 
            void displayZombieTemplate(int n, Zombie &zombie, gameBoard &gameBoard, Alien &alien){
                gameBoard.display();
                cout << "Zombie " << n+1 << " 's turn" << endl;
                zombie.print();
            }
        
};

class Arrow{
    private:
    int x_, y_;
    char heading_;
    char arrow;

public:
    Arrow();
    int getX() const;
    int getY() const;
    char getHeading() const;
    void left(gameBoard &gameBoard, Alien &alien);
    void right(gameBoard &gameBoard, Alien &alien);
    void up(gameBoard &gameBoard, Alien &alien);
    void down(gameBoard &gameBoard, Alien &alien);
    void setPosition(gameBoard &gameBoard, int x, int y);    
};

Alien::Alien(int life, int attack){
    health_ = 100;
    attack_ = 0;
    z_ = 'M';
}

Arrow::Arrow(){}

char Zombie::checkZombie(int x, int y, gameBoard &gameBoard){
    const char zomb[]={'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int n = sizeof(zomb);

    char j = '0';
    for (int i=0; i<n; i++){
        if (gameBoard.getObject(x,y)==zomb[i]){
            j = zomb[i];
        }
    }
    return j;
}

void Alien::rockSpawn(gameBoard &gameBoard, int x, int y){
    cout << endl;
    cout << endl << "Removing the rock..." << endl;
    sleep(2);
    
    char objects[] =  {' ', '^', 'v', '>', '<', 'h', 'p' };
    int noOfObjects = sizeof(objects);

    int objNo = rand() % noOfObjects;
    char obj = objects[objNo];
    
    gameBoard.setObject(x,y,obj);
    
    gameBoard.display();
}

void Alien::addAttack(int attack){
    attack_ = attack+20;
}

void Alien::addHealth(int life){
    health_ = life+20;
    // if (life < 100){
    //     health_ = life+20;
    // }
    // else{
    //     cout << "Alien's health is maximum." << endl;
    // }
}

void Arrow::left(gameBoard &gameBoard, Alien &alien){
    char oriArrow = gameBoard.getObject(x_,y_);
    gameBoard.setObject(x_,y_, '<');
    cout << "Arrow succesfully changed from " << oriArrow << " to <." << endl;
    system("read -n 1 -s -p \"Press any key to continue...\"");
}

void Arrow::right(gameBoard &gameBoard, Alien &alien){
    char oriArrow = gameBoard.getObject(x_,y_);
    gameBoard.setObject(x_,y_, '>');
    cout << "Arrow succesfully changed from " << oriArrow << " to >." << endl;
    system("read -n 1 -s -p \"Press any key to continue...\"");
}

void Arrow::up(gameBoard &gameBoard, Alien &alien){
    char oriArrow = gameBoard.getObject(x_,y_);
    gameBoard.setObject(x_,y_, '^');
    cout << "Arrow succesfully changed from " << oriArrow << " to ^." << endl;
    system("read -n 1 -s -p \"Press any key to continue...\"");
}

void Arrow::down(gameBoard &gameBoard, Alien &alien){
    char oriArrow = gameBoard.getObject(x_,y_);
    gameBoard.setObject(x_,y_, 'v');
    cout << "Arrow succesfully changed from " << oriArrow << " to v." << endl;
    system("read -n 1 -s -p \"Press any key to continue...\"");
}

int Alien::getLife(){
    return health_;
}

int Alien::getAttack(){
    return attack_;
}

void Alien::setMove(){
    z_ = 'M';
}

char Alien::getMove(){
    return z_;
}

void Alien::resetTrail(gameBoard &gameBoard){
    cout << "Resetting trail..." << endl;
    sleep(1);

    int y = gameBoard.getDimX();
    int x = gameBoard.getDimY();

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '>', '<', 'h', 'r', 'p'};
    int noOfObjects = sizeof(objects);
    

    for (int i=1; i<=x; i++){
        for (int j=1; j<=y; j++){
            int objNo = rand() % noOfObjects;
            char obj = objects[objNo];
            if (gameBoard.getObject(j, i) == '.'){
                cout << "trail at " << j << "," << i << endl;
                gameBoard.setObject(j,i,obj);
            }
        }
    }
    gameBoard.display();
}

void Alien::up(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow){
    Zombie zombie;
    gameBoard.setObject(x_,y_,' ');
    int y = gameBoard.getDimY();

    while ((y_+1 <= y) && (gameBoard.isEmpty(x_,y_+1) || (gameBoard.getObject(x_,y_+1)=='.') || (gameBoard.getObject(x_,y_+1)=='^') || 
           (gameBoard.getObject(x_,y_+1)=='v') || (gameBoard.getObject(x_,y_+1)=='<') || (gameBoard.getObject(x_,y_+1)=='>')|| 
           (gameBoard.getObject(x_,y_+1)=='h') || (gameBoard.getObject(x_,y_+1)=='p'))){
        if (y_!= y && gameBoard.isEmpty(x_,y_+1)){
            y_=y_+1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_+1)=='.'){
            y_=y_+1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_+1)=='^'){
            y_=y_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20" << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_+1)=='v'){
            y_=y_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20" << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
            alien.down(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_+1)=='>'){
            y_=y_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20" << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
            alien.right(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_+1)=='<'){
            y_=y_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20" << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
            alien.left(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_+1)=='h'){
            y_=y_+1;
            int life = alien.getLife();
            if (life < 100){
                alien.addHealth(life);
                cout << "Alien has found a health pack!" << endl;
                cout << "Alien's life has increased by 20." << endl;
                cout << endl;
            }
            else{
                cout << "Alien's health is maximum." << endl;
                cout << "No health is added." << endl;
            }
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
            break;
        }
        else if (gameBoard.getObject(x_,y_+1)=='p'){
            y_=y_+1;
            cout << "Alien has found a pod!" << endl;
            // the alien will find the closest zombie 
            // the zombie's life will decrease by 10
            // the alien's attack is not increased
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_-1, '.');
            gameBoard.display();
            whichArrow = 1;
            z_='P';
            break;
        }
        // else{
        //     gameBoard.setObject(x_,y_,'A');
        //     z_='S';
        //     break;
        // }
    }

    if (y_+1 > y){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit the border" << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        cout << endl;
        gameBoard.display();
        z_='S';
    } 
    else if (zombie.checkZombie(x_,y_+1,gameBoard)!='0'){
        gameBoard.setObject(x_,y_,'A');
        z_no = zombie.checkZombie(x_,y_+1, gameBoard) - '0';
        cout << "Alien attacks zombie " << zombie.checkZombie(x_,y_+1, gameBoard)
             << " with attack of " << alien.getAttack() << '.' << endl;
        z_='S';
    }
    else if (gameBoard.getObject(x_,y_+1)=='r'){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit a rock." << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        alien.rockSpawn(gameBoard,x_,y_+1);
        cout << endl;
        gameBoard.display();
        z_='S';
    }
}

void Alien::down(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow){
    Zombie zombie;
    gameBoard.setObject(x_,y_,' ');
    int y = gameBoard.getDimY();

    while ((y_-1 > 0) && (gameBoard.isEmpty(x_,y_-1) || (gameBoard.getObject(x_,y_-1)=='.')  || (gameBoard.getObject(x_,y_-1)=='^') || 
           (gameBoard.getObject(x_,y_-1)=='v') || (gameBoard.getObject(x_,y_-1)=='>') || (gameBoard.getObject(x_,y_-1)=='<')|| 
           (gameBoard.getObject(x_,y_-1)=='h') || (gameBoard.getObject(x_,y_-1)=='p'))){
        if (gameBoard.isEmpty(x_,y_-1)){
            y_=y_-1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_-1)=='.'){
            y_=y_-1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_-1)=='v'){
            y_=y_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_-1)=='^'){
            y_=y_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
            alien.up(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_-1)=='>'){
            y_=y_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
            alien.right(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_-1) == '<'){
            y_=y_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
            alien.left(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_,y_-1)=='h'){
            y_=y_-1;
            int life = alien.getLife();
            if (life < 100){
                alien.addHealth(life);
                cout << "Alien has found a health pack!" << endl;
                cout << "Alien's life has increased by 20." << endl;
                cout << endl;
            }
            else{
                cout << "Alien's health is maximum." << endl;
                cout << "No health is added." << endl;
            }
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_,y_-1)=='p'){
            y_=y_-1;
            cout << "Alien has found a pod!" << endl;
            // the alien will find the closest zombie 
            // the zombie's life will decrease by 10
            // the alien's attack is not increased
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_,y_+1, '.');
            gameBoard.display();
            whichArrow = 2;
            z_='P';
            break;
        }
        // else{
        //     gameBoard.setObject(x_,y_,'A');
        //     z_='S';
        // }   
    }

    if (y_-1 == 0){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit the border" << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        cout << endl;
        gameBoard.display();
        z_='S';
    }
    else if (zombie.checkZombie(x_,y_-1,gameBoard)!='0'){
        gameBoard.setObject(x_,y_,'A');
        z_no = zombie.checkZombie(x_,y_-1, gameBoard) - '0';
        cout << "Alien attacks zombie " << zombie.checkZombie(x_,y_-1, gameBoard)
             << " with attack of " << alien.getAttack() << '.' << endl;
        z_='S';
    }
    else if (gameBoard.getObject(x_,y_-1)=='r'){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit a rock." << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        alien.rockSpawn(gameBoard,x_,y_-1);
        cout << endl;
        gameBoard.display();
        z_='S';
    }
} 

void Alien::left(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow){
    Zombie zombie;
    gameBoard.setObject(x_,y_, ' ');
    int x = gameBoard.getDimX();

    while ((x_-1 > 0) && ( gameBoard.isEmpty(x_-1,y_) || (gameBoard.getObject(x_-1,y_)=='.') || (gameBoard.getObject(x_-1,y_)=='^') || 
           (gameBoard.getObject(x_-1,y_)=='v') || (gameBoard.getObject(x_-1,y_)=='<') || (gameBoard.getObject(x_-1,y_)=='>') || 
           (gameBoard.getObject(x_-1,y_)=='h') || (gameBoard.getObject(x_-1,y_)=='p'))){
        if ((x_-1 > 0) && gameBoard.isEmpty(x_-1,y_)){
            x_=x_-1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_,'A');
            gameBoard.setObject(x_+1, y_, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_-1,y_)=='.'){
            x_=x_-1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_,'A');
            gameBoard.setObject(x_+1, y_, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_-1,y_)=='<'){
            x_=x_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);            
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_,'A');
            gameBoard.setObject(x_+1, y_, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_-1,y_)=='^'){
            x_=x_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_,'A');
            gameBoard.setObject(x_+1, y_, '.');
            gameBoard.display();
            alien.up(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_-1,y_)=='v'){
            x_=x_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_+1,y_, '.');
            gameBoard.display();
            alien.down(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_-1,y_)=='>'){
            x_=x_-1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_, y_,'A');
            gameBoard.setObject(x_+1, y_,'.');
            gameBoard.display();
            alien.right(gameBoard, alien, z_no, whichArrow);
            break;
        }
        else if (gameBoard.getObject(x_-1,y_)=='h'){
            x_=x_-1;
            int life = alien.getLife();
            if (life < 100){
                alien.addHealth(life);
                cout << "Alien has found a health pack!" << endl;
                cout << "Alien's life has increased by 20." << endl;
                cout << endl;
            }
            else{
                cout << "Alien's health is maximum." << endl;
                cout << "No health is added." << endl;
            }
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_+1,y_, '.');
            gameBoard.display();
        }
        else if (gameBoard.getObject(x_-1,y_)=='p'){
            x_=x_-1;
            cout << "Alien has found a pod!" << endl;
            // the alien will find the closest zombie 
            // the zombie's life will decrease by 10
            // the alien's attack is not increased
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_,y_,'A');
            gameBoard.setObject(x_+1,y_, '.');
            gameBoard.display();
            whichArrow = 3;
            z_='P';
            break;
        }
        // else{
        //     gameBoard.setObject(x_,y_,'A');
        //     z_='S';
        // }
    }

    if (x_-1 == 0){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit the border" << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        cout << endl;
        gameBoard.display();
        z_='S';
    }
    else if (zombie.checkZombie(x_-1,y_,gameBoard)!='0'){
        gameBoard.setObject(x_,y_,'A');
        z_no = zombie.checkZombie(x_-1,y_, gameBoard) - '0';
        cout << "Alien attacks zombie " << zombie.checkZombie(x_-1,y_, gameBoard) 
             << " with attack of " << alien.getAttack() << '.' << endl;
        z_='S';
    }
    else if (gameBoard.getObject(x_-1,y_)=='r'){
            gameBoard.setObject(x_,y_,'A');
            cout << "Alien has hit a rock." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            alien.rockSpawn(gameBoard,x_-1,y_);
            cout << endl;
            gameBoard.display();
            z_='S';
    }
}

void Alien::right(gameBoard &gameBoard, Alien &alien, int &z_no, int &whichArrow){
    Zombie zombie;
    gameBoard.setObject(x_,y_,' ');
    int x = gameBoard.getDimX();

    while ((x_+1 <= x) && (gameBoard.isEmpty(x_+1,y_) || (gameBoard.getObject(x_+1,y_)=='.') || (gameBoard.getObject(x_+1,y_)=='^') || (gameBoard.getObject(x_+1,y_)=='v') || (gameBoard.getObject(x_+1,y_)=='<') || (gameBoard.getObject(x_+1,y_)=='>') || (gameBoard.getObject(x_+1,y_)=='h') || (gameBoard.getObject(x_+1,y_)=='p'))){
        if (gameBoard.isEmpty(x_+1,y_)){
            x_=x_+1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();
        } 
        else if (gameBoard.getObject(x_+1,y_)=='.'){
            x_=x_+1;
            cout << "Alien has found an empty space." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();           
        }
        else if (gameBoard.getObject(x_+1,y_)=='>'){
            x_=x_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();            
        }
        else if (gameBoard.getObject(x_+1,y_)=='^'){
            x_=x_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();
            alien.up(gameBoard,alien,z_no, whichArrow);            
            break;
        }
        else if (gameBoard.getObject(x_+1,y_)=='v'){
            x_=x_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();
            alien.down(gameBoard,alien,z_no, whichArrow);            
            break;
        }
        else if (gameBoard.getObject(x_+1,y_)=='<'){
            x_=x_+1;
            int attack = alien.getAttack();
            alien.addAttack(attack);
            cout << "Alien has found an arrow." << endl;
            cout << "Alien's attack has increased by 20." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();
            alien.left(gameBoard,alien,z_no, whichArrow);            
            break;
        }
        else if (gameBoard.getObject(x_+1,y_)=='h'){
            x_=x_+1;
            int life = alien.getLife();
            if (life < 100){
                alien.addHealth(life);
                cout << "Alien has found a health pack!" << endl;
                cout << "Alien's life has increased by 20." << endl;
                cout << endl;
            }
            else{
                cout << "Alien's health is maximum." << endl;
                cout << "No health is added." << endl;
            }
            cout << endl;;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();            
        }
        else if (gameBoard.getObject(x_+1,y_)=='p'){
            x_=x_+1;
            cout << "Alien has found a pod!" << endl;
            // the alien will find the closest zombie 
            // the zombie's life will decrease by 10
            // the alien's attack is not increased
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            cout << endl;
            gameBoard.setObject(x_, y_, 'A');
            gameBoard.setObject(x_-1, y_, '.');
            gameBoard.display();
            whichArrow = 4;
            z_='P';
            break;          
        }
        // else{
        //     gameBoard.setObject(x_,y_,'A');
        //     z_='S';
        // }
    }

    if (x_+1 > x){
        gameBoard.setObject(x_,y_,'A');
        cout << "Alien has hit the border" << endl;
        cout << endl;
        system("read -n 1 -s -p \"Press any key to continue...\"");
        cout << endl;
        gameBoard.display();
        z_='S';
    }
    else if (zombie.checkZombie(x_+1,y_,gameBoard)!='0'){
        gameBoard.setObject(x_,y_,'A');
        z_no = zombie.checkZombie(x_+1,y_, gameBoard) - '0';
        cout << "Alien attacks zombie " << zombie.checkZombie(x_+1,y_, gameBoard)
             << " with attack of " << alien.getAttack() << '.' << endl;
        z_='S';
    }
    else if (gameBoard.getObject(x_+1,y_)=='r'){
            gameBoard.setObject(x_,y_,'A');
            cout << "Alien has hit a rock." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            alien.rockSpawn(gameBoard,x_+1,y_);
            cout << endl;
            gameBoard.display();
            z_='S';
    }
}

void Alien::land(gameBoard &gameBoard)
{ 
    x_ = (gameBoard.getDimX() + 1)/2;
    y_ = (gameBoard.getDimY() + 1)/2;
    char A = 'A';

    gameBoard.setObject(x_, y_, A);
}

void Alien::podAttack(gameBoard &gameBoard, Alien &alien, int &whichArrow, int &whichZombie){
    int x = gameBoard.getDimX();
    int y = gameBoard.getDimY();

    const char letters[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    double rangeFromAlien=0.0;
    char nearestZombie;

    vector <int> xVal;
    vector <int> yVal;
    vector <char> head;
    
    int alienX = x_, alienY = y_;

    for(int i=1;i<=x;i++){
        for(int j=1;j<=y;j++){
            //[dimY_-y][x-1]
            // cout<<i-1<<" "<<y_-y<<endl;
            // cout <<  i << "," <<  j <<gameBoard.getObject(i,j) << endl;
            for(int l=0;l<9;l++){
                if(gameBoard.getObject(i,j)==letters[l]){
                    // cout<<letters[l]<<endl;
                    xVal.push_back(i);
                    yVal.push_back(j);
                    head.push_back(letters[l]);
                }
            }
        }
    }
    for(int i=0;i<xVal.size();i++){
        for(int j=0;j<yVal.size();j++){
            if(i==j){
                double distanceX = pow(abs(alienX - xVal[i]), 2.0);
                double distanceY = pow(abs(alienY - yVal[j]), 2.0);
                double hypothenus = sqrt(distanceX+distanceY);
                if(rangeFromAlien==0||hypothenus<rangeFromAlien){
                    rangeFromAlien=hypothenus;
                    nearestZombie=head[i];
                }
            }
        }
    }
    int newNearest = int(nearestZombie) - '0';
    whichZombie=newNearest;
}

void Alien::resumeMove(gameBoard &gameBoard){
    ifstream fin2;
    fin2.open("alien.txt");
    int a,b;
    char A = 'A';
    fin2 >> a >> b >> health_ >> attack_;
    x_=a;
    y_=b;
    gameBoard.setObject(x_, y_, A);
    fin2.close();
}

int Arrow::getX() const{
    return x_;
}
int Arrow::getY() const{
    return y_;
}
char Arrow::getHeading() const{
    return heading_;
}

int Alien::getX() const{
    return x_;
}
int Alien::getY() const{
    return y_;
}

gameBoard::gameBoard(int dimX, int dimY){
    init(dimX, dimY);
}

void Arrow::setPosition(gameBoard &gameBoard, int x, int y){
    x_ = x;
    y_ = y;
}

int gameBoard::getDimX() const{
    return dimX_;
}

int gameBoard::getDimY() const{
    return dimY_;
}

char gameBoard::getObject(int x, int y) const
{
    return map_[dimY_-y][x-1];
}

void gameBoard::setObject(int x, int y, char ch)
{
    map_[dimY_-y][x-1] = ch;
}

bool gameBoard::isEmpty(int x, int y){
    return map_[dimY_-y][x-1] == ' ';
}

bool gameBoard::isInsideMap(int x, int y)
{
    return x >= 1 && x <= dimX_ && y >= 1 && y <= dimY_;
}

void gameBoard::init(int dimX, int dimY){
    dimX_ = dimX;
    dimY_ = dimY;
    //char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '>', '<', 'h', 'h', 'p', 'p','r','r','r', ' ', ' ', ' ', ' ', ' '};
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '>', '<', 'h', 'r', 'p'};
    //char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int noOfObjects = sizeof(objects);

    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            if (j == (dimX_-1)/2 && i == (dimY_-1)/2){
                map_[i][j] = 'A';
            }
            else{
                map_[i][j] = objects[objNo];
            }
        }
    }
}

void gameBoard::init2(int dimX, int dimY){
    dimX_ = dimX;
    dimY_ = dimY;
    // char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^', 'v', '>', '<', 'h', 'r', 'p'};
    // int noOfObjects = sizeof(objects);
    // char zombieIndex[]={'1','2','3','4','5','6','7','8','9'};
    // int zombieNo = sizeof(zombieIndex);
    int r = 0; //row
    int c;
    char dim[dimX_];
    ifstream fin;
    fin.open("gameboard.txt");

    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }

    for(r = 0; r < dimY_; ++r){
        for (c = 0; c < dimX_; ++c){
            fin >> dim[c];
            if (dim[c]=='s'){
                map_[r][c] =' ';
            }
            else{
                map_[r][c] = dim[c];
            }
            //cout<<map_[r][c]<<' '; // checking the right map
        }
        cout << endl;
    }

    fin.close();
}

void gameBoard::display() const{
    ofstream fout;
    fout.open("gameboard.txt");
    system("clear");
    cout << endl;
    cout << " __________________________________________" << endl;
    cout << "|                                          |" << endl;
    cout << "|            = Alien vs Zombies =          |" << endl;
    cout << "|__________________________________________|" << endl;
    cout << endl;


    for (int i = 0; i < dimY_; ++i)
    {
         // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;

    gameBoard showAttributes(Alien &alien, Zombie &zombie);        

    //save in text file
    for (int i = 0; i < dimY_; ++i)
    {
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j]==' '){
                fout << 's' << ' ';
            }
            else{
                fout << map_[i][j] << ' ';
            }
        }
        fout << endl;
    } 

    fout.close();
}

int Zombie::getZHealth(){
    return health_;
}

int Zombie::getZAttack(){
    return attack_;
}

int Zombie::getZRange(){
    return range_;
}

char Zombie::getZHeading(){
    return heading_;
}

void Zombie::setZombieAttributes(int n, gameBoard &gameBoard){
    {
            // set Positions
            const char letters[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

            x_ = rand() % gameBoard.getDimX()+1;
            y_ = rand() % gameBoard.getDimY()+1;
            
            heading_ = letters[n];
            // set Health, Attack and Attack Range

            health_ = rand() % 150 + 50;
            attack_ = rand() % 70 + 10;


            if (gameBoard.getDimX() > gameBoard.getDimY()){
                range_ = rand() % x_ + 1;
            }
            else{
                range_ = rand() % y_+ 1;
            }

            bool exists = false;
            for (int i=0; i<n; i++){
                if (gameBoard.getObject(x_, y_) == letters[i]){
                    exists = true;
                }
            }
            if ((x_ == (gameBoard.getDimX()+1)/2 && y_ == (gameBoard.getDimY()+1)/2) || exists){

                bool same = false;
                while (not same){
                    srand(time(NULL));
                    x_ = rand() % gameBoard.getDimX()+1;
                    y_ = rand() % gameBoard.getDimY()+1;
                    for (int i=0; i<n; i++){
                        if (gameBoard.getObject(x_, y_) == letters[i]){
                            exists = true;
                        }
                        else{
                            exists = false;
                        }
                    }
                    if ((x_ == (gameBoard.getDimX()+1)/2 && y_ == (gameBoard.getDimY()+1)/2) || exists){
                    }
                    else{
                        same=true;
                    }
                    
                }
                gameBoard.setObject(x_, y_, heading_);    
            }

            else{
                gameBoard.setObject(x_, y_, heading_);
            }
        }
}

void Zombie::setZombieAttributes2(int n, gameBoard &gameBoard, int zomb[]){
    ifstream fin;
    fin.open("zombies.txt");

    x_ = zomb[1];
    y_ = zomb[2];
    
    //char c = zomb[0];

    char heading_ = zomb[0] + 48;
    health_ = zomb[3];
    attack_ = zomb[4];
    range_ = zomb[5];
    
    gameBoard.setObject(x_, y_, heading_);    

    fin.close();
}

void Zombie::moveZombie(int n, Zombie &zombie, gameBoard &gameBoard){

    int randMove;
    bool valid = false;
    while (not valid){
        randMove = rand() % 4+1;
        int y = gameBoard.getDimY();
        int x = gameBoard.getDimX();
        const char letters[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        
        // cout << "randMove before: " << randMove << endl;
        // cout << "x              : " << zombie.getZX() << endl;
        // cout << "y              : " << zombie.getZY() << endl;
        // cout << "dimX           : " << x << endl;
        // cout << "dimY           : " << y << endl;

        bool exists = false;

        // cant go up if y==dimY
        // cant go down if y==1
        // cant go left if x==1
        // cant go right if x==dimX

        if (randMove==1 && zombie.getZY()!=y){    
            if (
               gameBoard.getObject(x_,y_+1)=='1'
            || gameBoard.getObject(x_,y_+1)=='2' 
            || gameBoard.getObject(x_,y_+1)=='3'
            || gameBoard.getObject(x_,y_+1)=='4' 
            || gameBoard.getObject(x_,y_+1)=='5'
            || gameBoard.getObject(x_,y_+1)=='6' 
            || gameBoard.getObject(x_,y_+1)=='7'
            || gameBoard.getObject(x_,y_+1)=='8' 
            || gameBoard.getObject(x_,y_+1)=='9'
            || gameBoard.getObject(x_,y_+1)=='A'){
                // cout << "Zombie cannot move UP" << endl;
            } // problem arise when && changed to || (same for all 4 cases)
            else{
                valid=true;
                gameBoard.setObject(x_, y_, ' ');
                y_++;
                gameBoard.setObject(x_, y_, heading_);
                cout << "Moves Up" << endl;
            }
        }
        
        if (randMove==2 && zombie.getZY()!=1){
            if (
               gameBoard.getObject(x_,y_-1)=='1'
            || gameBoard.getObject(x_,y_-1)=='2' 
            || gameBoard.getObject(x_,y_-1)=='3'
            || gameBoard.getObject(x_,y_-1)=='4' 
            || gameBoard.getObject(x_,y_-1)=='5'
            || gameBoard.getObject(x_,y_-1)=='6' 
            || gameBoard.getObject(x_,y_-1)=='7'
            || gameBoard.getObject(x_,y_-1)=='8' 
            || gameBoard.getObject(x_,y_-1)=='9'
            || gameBoard.getObject(x_,y_-1)=='A'){
                // cout << "Zombie CANNOT move DOWN" << endl;
            } 
            else{
                valid=true;
                gameBoard.setObject(x_, y_, ' ');
                y_--;
                gameBoard.setObject(x_, y_, heading_);
                cout << "Moves Down" << endl;
            }
        }
        
        if (randMove==3 && zombie.getZX()!=1){
            if (
               gameBoard.getObject(x_-1,y_)=='1'
            || gameBoard.getObject(x_-1,y_)=='2' 
            || gameBoard.getObject(x_-1,y_)=='3'
            || gameBoard.getObject(x_-1,y_)=='4' 
            || gameBoard.getObject(x_-1,y_)=='5'
            || gameBoard.getObject(x_-1,y_)=='6' 
            || gameBoard.getObject(x_-1,y_)=='7'
            || gameBoard.getObject(x_-1,y_)=='8' 
            || gameBoard.getObject(x_-1,y_)=='9'
            || gameBoard.getObject(x_-1,y_)=='A'){
                // cout << "Zombie CANNOT move LEFT" << endl;
            } 
            else{
                valid=true;
                gameBoard.setObject(x_, y_, ' ');
                x_--;
                gameBoard.setObject(x_, y_, heading_);
                cout << "Moves Left" << endl;
            }
        }  
        
        if (randMove==4 && zombie.getZX()!=x){
            if (
               gameBoard.getObject(x_+1,y_)=='1'
            || gameBoard.getObject(x_+1,y_)=='2' 
            || gameBoard.getObject(x_+1,y_)=='3'
            || gameBoard.getObject(x_+1,y_)=='4' 
            || gameBoard.getObject(x_+1,y_)=='5'
            || gameBoard.getObject(x_+1,y_)=='6' 
            || gameBoard.getObject(x_+1,y_)=='7'
            || gameBoard.getObject(x_+1,y_)=='8' 
            || gameBoard.getObject(x_+1,y_)=='9'
            || gameBoard.getObject(x_+1,y_)=='A'){
                // cout << "Zombie CANNOT move RIGHT" << endl;
            } 
            else{
                valid=true;
                gameBoard.setObject(x_, y_, ' ');
                x_++;
                gameBoard.setObject(x_, y_, heading_);
                cout << "Moves Right" << endl;
            }
        } 
    }
    cout << "------------------" << endl;
    // cout << "randMove after: " << randMove << endl;  
}

void Zombie::checkReturnRange(bool &inRange, Zombie &zombie, gameBoard &gameBoard, Alien &alien){


    if(zombie.getZY()+zombie.getZRange()<=zombie.getDimY()){
        // cout << "checking for top 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()+i==alien.getY())){
                // cout << "alien is on the top, " << i << "tiles away"  << "(" << x_ << "," << y_+i << ")" << endl;
                inRange=true;
            }
        }
    }
    else if(zombie.getZY()+zombie.getZRange()>zombie.getDimY()){
        // cout << "checking for top 2..." << endl;
        int n=zombie.getDimY()-zombie.getZY();
        for(int i=1;i<=n;i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()+i==alien.getY())){
                // cout << "alien is on the top, " << i << "tiles away"  << "(" << x_ << "," << y_+i << ")" << endl;
                inRange=true;
            }
        }
    }

    if(zombie.getZY()-zombie.getZRange()>=1){
        // cout << "checking for down 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()-i==alien.getY())){
                // cout << "alien is on the bottom, " << i << "tiles away"  << "(" << x_ << "," << y_-i << ")" << endl;
                inRange=true;
            }
        }
    }
    else if(zombie.getZX()-zombie.getZRange()<1){
        // cout << "checking for down 2..." << endl;
        int n=zombie.getZY()-1;
        for(int i=1;i<=n;i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()-i==alien.getY())){
                // cout << "alien is on the bottom, " << i << "tiles away" << "(" << x_ << "," << y_-i << ")" << endl;
                inRange=true;
            }
        }
    } 

    if(zombie.getZX()-zombie.getZRange()>=1){
        // cout << "checking for left 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()-i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the left, " << i << "tiles away" << "(" << x_-i << "," << y_ << ")" << endl;
                inRange=true;
            }
        }
    } 
    else if(zombie.getZX()-zombie.getZRange()<1){
        // cout << "checking for left 2..." << endl;
        int n=zombie.getZX()-1;
        for(int i=1;i<=n;i++){
            if((zombie.getZX()-i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the left, " << i << " tiles away at " << "(" << x_-i << "," << y_ << ")" << endl;
                inRange=true;
            }
        }
    }

    if(zombie.getZX()+zombie.getZRange()<=zombie.getDimX()){
        // cout << "checking for right 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()+i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the right, " << i << "tiles away" << "(" << x_+i << "," << y_ << ")" << endl;
                inRange=true;

            }
        }
    }
    else if(zombie.getZX()+zombie.getZRange()>zombie.getDimX()){
        // cout << "checking for right 2..." << endl;
        int n=zombie.getDimX()-zombie.getZX();
        for(int i=1;i<=n;i++){
            if((zombie.getZX()+i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the right, " << i << "tiles away" << "(" << x_+i << "," << y_ << ")" << endl;
                inRange=true;
            }
        }
    }
}

bool Zombie::returnRange(Zombie &zombie, gameBoard &gameBoard, Alien &alien){

    // predict if position+range is out of bound
    
    // cout<< "Range: "<<zombie.getZRange()<<endl;
    // cout<< "Position: " << "(" << zombie.getZX() << "," <<zombie.getZY() << ")" <<endl;
    bool inRange=false;

    checkReturnRange(inRange, zombie, gameBoard, alien); 
    return inRange;
}

void Zombie::checkZombieRange(int &oneDirection, int &rangeFromZombie, Zombie &zombie, gameBoard &gameBoard, Alien &alien){
    if(zombie.getZY()+zombie.getZRange()<=zombie.getDimY()){
        // cout << "checking for top 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()+i==alien.getY())){
                // cout << "alien is on the top, " << i << "tiles away"  << "(" << x_ << "," << y_+i << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 1;
            }
        }
    }
    else if(zombie.getZY()+zombie.getZRange()>zombie.getDimY()){
        // cout << "checking for top 2..." << endl;
        int n=zombie.getDimY()-zombie.getZY();
        for(int i=1;i<=n;i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()+i==alien.getY())){
                // cout << "alien is on the top, " << i << "tiles away"  << "(" << x_ << "," << y_+i << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 1;
            }
        }
    }

    if(zombie.getZY()-zombie.getZRange()>=1){
        // cout << "checking for down 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()-i==alien.getY())){
                // cout << "alien is on the bottom, " << i << "tiles away"  << "(" << x_ << "," << y_-i << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 2;
            }
        }
    }
    else if(zombie.getZY()-zombie.getZRange()<1){
        // cout << "checking for down 2..." << endl;
        int n=zombie.getZY()-1;
        for(int i=1;i<=n;i++){
            if((zombie.getZX()==alien.getX())&&(zombie.getZY()-i==alien.getY())){
                // cout << "alien is on the bottom, " << i << "tiles away" << "(" << x_ << "," << y_-i << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 2;
            }
        }
    } 

    if(zombie.getZX()-zombie.getZRange()>=1){
        // cout << "checking for left 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()-i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the left, " << i << "tiles away" << "(" << x_-i << "," << y_ << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 3;
            }
        }
    } 
    else if(zombie.getZX()-zombie.getZRange()<1){
        // cout << "checking for left 2..." << endl;
        int n=zombie.getZX()-1;
        for(int i=1;i<=n;i++){
            if((zombie.getZX()-i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the left, " << i << " tiles away at " << "(" << x_-i << "," << y_ << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 3;
            }
        }
    }

    if(zombie.getZX()+zombie.getZRange()<=zombie.getDimX()){
        // cout << "checking for right 1..." << endl;
        for(int i=1;i<=zombie.getZRange();i++){
            if((zombie.getZX()+i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the right, " << i << "tiles away" << "(" << x_+i << "," << y_ << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 4;
            }
        }
    }
    else if(zombie.getZX()+zombie.getZRange()>zombie.getDimX()){
        // cout << "checking for right 2..." << endl;
        int n=zombie.getDimX()-zombie.getZX();
        for(int i=1;i<=n;i++){
            if((zombie.getZX()+i==alien.getX())&&(zombie.getZY()==alien.getY())){
                // cout << "alien is on the right, " << i << "tiles away" << "(" << x_+i << "," << y_ << ")" << endl;
                rangeFromZombie=i;
                oneDirection = 4;
            }
        }
    }
}

void Zombie::checkRange(Zombie &zombie, gameBoard &gameBoard, Alien &alien){
    int oneDirection;
    int rangeFromZombie;

    checkZombieRange(oneDirection, rangeFromZombie, zombie, gameBoard, alien);

    cout << "Alien is in range, " << rangeFromZombie << " tiles away from the ";
    
    if(oneDirection==1){
        cout << "top." << endl;
    }
    if(oneDirection==2){
        cout << "bottom." << endl;
    }
    if(oneDirection==3){
        cout << "left." << endl;
    }
    if(oneDirection==4){
        cout << "right." << endl;
    }
    cout << "Zombie attacks Alien! Zombie deals "<< zombie.getZAttack() << " damage to Alien."<< endl;
}

void test()
{
    gameBoard gameBoard;
    Alien alien;
    Arrow arrow;
    
    int col = 7, row =5;
    string command;
    int x,y;
    string direction;
    int numOfZombies = 2;
    int z = 0;
    int z_no;
    int oriHealth, health;
    int whichZombie, whichArrow;

    //Zombie zombies[numOfZombies];

    char s;
    s = 'M'; //M = Alien's turn/move

    ifstream fin;
    fin.open("dimension.txt");

    cout << "----------Welcome Player----------" << endl;
    cout << "Number of Rows = " << row << endl;
    cout << "Number of Columns = " << col << endl;
    cout << "Number of Zombies = " << numOfZombies << endl;
    cout << "----------------------------------" << endl;
    sleep(1);

    char ed;
    char choice;
    //bool validyesNo = false;
    // while(not validyesNo){
    //     cout << "Do you want to resume your game (y/n)? = ";
    //     cin >> choice;

    //     if(choice=='y' || choice =='n'){
    //         validyesNo=true;
    //     }
    //     else{
    //         cout << "Please enter the correct input" << endl;
    //     }
    // }
    cout << "Do you want to resume your game (y/n)? = ";
    cin >> choice;
    if (choice == 'y'){
        fin >> row >> col >> numOfZombies;
    }
    else if (choice =='n'){
        //Zombie zombies[numOfZombies];
        numOfZombies = numOfZombies;
        cout << "Do you want to edit the Game Board (y/n)? = ";
        cin >> ed;
        //gameBoard.checkRowCol(row, "Rows");
        //gameBoard.checkRowCol(col, "Columns");
        //gameBoard.checkRowCol(numOfZombies, "Zombies");
    }

    Zombie zombies[numOfZombies];
    
    if (choice == 'n'){
        // cout << "Do you want to edit the Game Board (y/n)? = ";
        // cin >> ed;

        ofstream fout;
        fout.open("dimension.txt");

        if (ed == 'y'){
            gameBoard.checkRowCol(row, "Rows");
            gameBoard.checkRowCol(col, "Columns");
            gameBoard.checkRowCol(numOfZombies, "Zombies");
            fout << row << ' ' << col << ' ' << numOfZombies << endl;
            system("clear");
            cout << "-----------Game Board------------" << endl;
            cout << "Number of Rows = " << row << endl;
            cout << "Number of Columns = " << col << endl;
            cout << "Number of Zombies = " << numOfZombies << endl;
            cout << "---------------------------------" << endl;
            cout << "Let's Play!" << endl;
            cout << endl;
        }
        else if (ed == 'n'){
            cout << endl;
            cout << "Let's Play!" << endl;
            cout << endl;
            row = 5;
            col = 7;
        }
        gameBoard.init(col,row);
        alien.land(gameBoard);
        fout.close();

        //Zombie zombies[numOfZombies];
        for(int i=0; i<numOfZombies; i++){
            zombies[i].setZombieAttributes(i, gameBoard);
        }
    }
    else{
        fin >> row >> col >> numOfZombies;
        gameBoard.init2(col,row);

        fin.close();

        ifstream read;
        read.open("zombies.txt");
        int c;
        int zomb[numOfZombies][6];
        int w = 0;

        while (read.good()){
            for (c=0; c<6; ++c){
                read >> zomb[w][c];
            }
            w++;
        }
        for(int i=0; i<numOfZombies; i++){
            zombies[i].setZombieAttributes2(i, gameBoard, zomb[i]);
        }
        alien.resumeMove(gameBoard);

        fin.close();
    }
    
    while (alien.getMove()!='S'){
        if(z==0){
            system("read -n 1 -s -p \"Press any key to continue...\"");
        }
        gameBoard.display();
        cout << "Alien's Life" << setw(5) << ": " << setw(3) << alien.getLife() << " Attack:" << setw(3) << alien.getAttack() << endl;
        for(int i=0; i<numOfZombies; i++){
            cout << "Zombie " << i+1 << " Status: ";
            if(zombies[i].getZHealth()>0){
                cout << "Alive" <<endl;
            }
            else if(zombies[i].getZHealth()<=0){
                cout << "Dead" <<endl;
            }
            
            if(z!=0){
                if(i ==z-1){
                    zombies[i].print2();     
                }
            }
        }
        cout << endl;
        z=0;
        cout << "Enter command: ";
        cin >> command;
        toupper(command[0]);
        cout << endl;

        if (command == "Up" || command == "up"){
            alien.up(gameBoard,alien,z_no, whichArrow);
        }
        else if (command == "Down" || command == "down"){
            alien.down(gameBoard,alien,z_no, whichArrow);
        }
        else if (command == "Left" || command == "left"){
            alien.left(gameBoard,alien,z_no, whichArrow);
        }
        else if (command == "Right" || command == "right"){
            alien.right(gameBoard,alien,z_no, whichArrow);
        }
        else if (command == "Arrow" || command == "arrow"){
            cout << "Enter row, column and direction = ";
            cin >> y >> x >> direction;
            arrow.setPosition(gameBoard, x, y);
            if (direction == "left"){
                arrow.left(gameBoard, alien);
            }
            else if (direction == "right"){
                arrow.right(gameBoard, alien);
            }
            else if (direction == "up"){
                arrow.up(gameBoard, alien);
            }
            else if (direction == "down"){
                arrow.down(gameBoard, alien);
            }
            gameBoard.display();
        }
        else if (command == "Quit" || command == "quit"){
            cout << "Goodbye!" << endl;
            cout << endl;
            break;
        }
        else if (command == "1" 
        || command == "2"
        || command == "3"
        || command == "4"
        || command == "5"
        || command == "6"
        || command == "7"
        || command == "8"
        || command == "9"
        || command == "0"
        ){  
            z = stoi(command);
            if(command=="0"){
                z=0;
            }        
        }
        else if (command == "Help" || command == "help"){
            cout <<"________________________________" << endl;
            cout << endl;
            cout << "Valid Commands: " << endl;
            cout <<"________________________________" << endl;
            cout << endl;
            cout << "Up = Move upwards" << endl;
            cout << "Down = Move downwards" << endl;
            cout << "Left = Move left" << endl;
            cout << "Right = Move right" << endl;
            cout << "Quit = Quit" << endl;
            cout << "Save = Save" << endl;
            cout << "Zombie's number (1-9) = Show zombie attributes" << endl;
            cout << "0 = Hide zombie attributes" << endl;
            cout <<"________________________________" << endl;
            cout << endl;
        }
        else if (command == "Save" || command == "save"){
            ofstream fout2;
            fout2.open("zombies.txt");

            for(int k=0; k<numOfZombies; ++k){
                fout2 << zombies[k].getZHeading()
                     << ' ' << zombies[k].getZX() 
                     << ' ' << zombies[k].getZY()
                     << ' ' << zombies[k].getZHealth()
                     << ' ' << zombies[k].getZAttack()
                     << ' ' << zombies[k].getZRange()
                     << endl;
            }
            fout2.close();
            ofstream write;
            write.open("alien.txt");
            write << alien.getX() << ' ' << alien.getY() << ' ' << alien.getLife() << ' ' << alien.getAttack() <<endl;
            write.close();
            cout << "Your game has been saved!" << endl;
            //break;
        }
        else{
            cout << "Invalid command. Enter in valid command." << endl;
            cout << endl;
        }

        if (alien.getMove()=='S'){
        
            for(int i=0;i<numOfZombies;i++){
                if(zombies[i].getZHealth()<=0){
                    zombies[i].resetZHeading(gameBoard);
                }
            }
            oriHealth = zombies[z_no-1].getZHealth();
            health = zombies[z_no-1].getZHealth() - alien.getAttack(); 
            zombies[z_no-1].setZHealth(health);
            if (health == oriHealth){
                cout << "Zombie " << z_no << " has no reduced health." << endl;
                cout << "Zombie " << z_no << " is still alive." << endl;
            }
            else if (health == -health){
                cout << "Zombie " << z_no << " is DEAD";
            }
            else{
                cout << "Zombie " << z_no << " has reduced life of " << oriHealth << " to " << health << '.' << endl;
                cout << "Zombie " << z_no << " is still alive." << endl;
                cout << endl;
            }
            // int attack = 0;
            // alien.resetAttack(attack);
            cout << "Alien's turn has ended." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"");
            int attack = 0;
            alien.resetAttack(attack);
            gameBoard.display();
            alien.resetTrail(gameBoard);
            gameBoard.display();
            for(int i=0; i<numOfZombies; i++){
                if(zombies[i].getZHealth()<=0){
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    cout<< "Zombie " << zombies[i].getZHeading() << " is DEAD." << endl;
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                    alien.setMove();
                }
                else{
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    cout << "Zombie ";
                    zombies[i].moveZombie(i, zombies[i], gameBoard);
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    if(zombies[i].returnRange(zombies[i], gameBoard, alien)){
                        zombies[i].checkRange(zombies[i], gameBoard, alien);
                        if(alien.reduceHealth(zombies[i].getZAttack())<=0){
                            cout << "Alien is DEAD. you lose. good day sir" << endl;
                        }
                        else{
                            cout << "Alien's life is down to " << alien.getLife() << "." << endl;
                        }
                    }
                    else{
                        cout<<"Alien is NOT in range. Alien is safe."<<endl;
                    }
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                }
            }
            gameBoard.display();
            cout << "\nThis round has ended" << endl;
            alien.setMove();
        }
        else if(alien.getMove()=='K'){
            for(int i=0;i<numOfZombies;i++){
                if(zombies[i].getZHealth()<=0){
                    zombies[i].resetZHeading(gameBoard);
                }
            }
            cout << "Alien's turn has ended." << endl;
            cout << endl;
            system("read -n 1 -s -p \"Press any key to continue...\"\n");
            int attack = 0;
            alien.resetAttack(attack);
            gameBoard.display();
            alien.resetTrail(gameBoard);
            gameBoard.display();
            for(int i=0; i<numOfZombies; i++){
                if(zombies[i].getZHealth()<=0){
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    cout<< "Zombie " << zombies[i].getZHeading() << " is DEAD." << endl;
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                    alien.setMove();
                }
                else{
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    cout << "Zombie ";
                    zombies[i].moveZombie(i, zombies[i], gameBoard);
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                    zombies[i].displayZombieTemplate(i, zombies[i], gameBoard, alien);
                    if(zombies[i].returnRange(zombies[i], gameBoard, alien)){
                        zombies[i].checkRange(zombies[i], gameBoard, alien);
                        if(alien.reduceHealth(zombies[i].getZAttack())<=0){
                            cout << "Alien is DEAD. you lose. good day sir" << endl;
                        }
                        else{
                            cout << "Alien's life is down to " << alien.getLife() << "." << endl;
                        }
                    }
                    else{
                        cout<<"Alien is NOT in range. Alien is safe."<<endl;
                    }
                    system("read -n 1 -s -p \"Press any key to continue...\"\n");
                }
            }
            gameBoard.display();
            cout << "\nThis round has ended" << endl;
            alien.setMove();
            }

        else if(alien.getMove()=='P'){
            alien.podAttack(gameBoard, alien, whichArrow, whichZombie);
            whichZombie=whichZombie-1;
            zombies[whichZombie].reduceZHealth(10);
            cout << "Alien attacks Zombie " << whichZombie+1 << ". \nZombie's HP is reduced by 10." <<endl;
            system("read -n 1 -s -p \"Press any key to continue...\"\n");
            if(whichArrow==1){
                alien.up(gameBoard, alien, z_no, whichArrow);
            }
            if(whichArrow==2){
                alien.down(gameBoard, alien, z_no, whichArrow);
            }
            if(whichArrow==3){
                alien.left(gameBoard, alien, z_no, whichArrow);
            }
            if(whichArrow==4){
                alien.right(gameBoard, alien, z_no, whichArrow);
            }
            
            alien.resetTrail(gameBoard);
            alien.setMove();
        }
    }  
}

int main(){
    srand(5);
    //srand(time(NULL));
    test();
}
