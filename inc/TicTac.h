#ifndef MYLIB
#define MYLIB

#include <string>
#include <server.h>
#include <Cell.h>
#include <random>

class TicTac{
    public:
    TicTac(); //constructor
    TicTac(const TicTac&); //copy constructor
    int dim;
    int counter;
    int winner;
    bool computerP;
    //int col;
    void start();
    std::vector<Cell> Board;
    std::vector<int> oBoard;
    void neighborhood();
    ucm::json getBoard();
    ucm::json cellCheck(int, int);
    ucm::json winCon();
    ucm::json reset();
    ucm::json aiPs();
    int aiPlay();

   // ~TicTac(); //destructor

};
#endif