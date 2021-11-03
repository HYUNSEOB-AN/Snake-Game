#ifndef __SNAKE__
#define __SNAKE__
#include <iostream>
#include <vector>
#include <ncursesw/ncurses.h>
#include <cstdlib>
#include <clocale>
#include <string>
#include <unistd.h>
#include "CreateTerm.h" // edit

class Terminals; // edit

extern char buffer[30][60];
extern WINDOW *Board_GAME;
extern int len;
extern int poisonCnt;
extern int growCnt;
extern int gateCnt;

struct Pos{
  int x,y;
  Pos(int col, int row);
  Pos();
};

class Snake{
public:
  int point;
//  int len = 3;
  int delay;
  int maxwidth = 60;
  int maxheight = 30;
  //int poisonCnt = 0;
  //int growCnt = 0;
  //int gateCnt = 0;
  char dir;
  bool fail;
  bool getGrow;
  bool getPoison;
  int gateNum;
  std::vector<Pos> growItem;
  std::vector<Pos> poisonItem;
  std::vector<Pos> snake;
  std::vector<Pos> gate;

  void kbhit();
  void moveGate();
  void putGate();
  void putGrow();
  void putPoison();
  bool collision();
  bool gameOver();
  void moveSnake();

  Snake();
  ~Snake();
  void play();
};
#endif
