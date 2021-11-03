#include <iostream>
#include "CreateTerm.h"

using namespace std;

char buffer[30][60];
WINDOW *Board_GAME;
int growCnt;
int poisonCnt;
int len;
int gateCnt;

int main(){

  Terminals p;
  p.StartScreen();
  p.Start();

  endwin();
}
