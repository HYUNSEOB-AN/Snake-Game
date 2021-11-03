#ifndef __CREATETERM__
#define __CREATETERM__

#include <ncurses.h>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include "Snake.h"

class Snake;

extern char buffer[30][60];
extern WINDOW *Board_GAME;
extern int len;
extern int poisonCnt;
extern int growCnt;
extern int gateCnt;

class Terminals{
private:
  WINDOW *Board_Score;
  WINDOW *Board_Mission;

public :
  Terminals();
  std::string mapstr;
  int RoundCount = 1;
  int MissionGrow = 5;
  int MissionLen = 10;
  int MissionGate = 1;
  int MissionPoison = 3;
  void Start();
  void ScoreBoard();
  void GameBoard();
  void MissionBoard();
  void RefreshTerminal();
  void StartScreen();
  void SetStage(){
    std::fstream setting("mapfile.txt");
    std::fstream map;
    for(int i =0; getline(setting, mapstr) && i < RoundCount-1; i++){
    }
    map.open(mapstr);
    for(int i = 0; i<30; i++){
      for(int j = 0; j<60; j++){
        map >> buffer[i][j];
      }
    }
  }
  void EndStage();
};
#endif
