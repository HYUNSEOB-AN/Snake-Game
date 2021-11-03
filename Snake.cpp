#include "Snake.h"
#include <wchar.h>
#include <clocale>
#include <locale.h>
#include <iostream>
using namespace std;

Pos::Pos(int col,int row)
{
    x=col;
    y=row;
}

Pos::Pos()
{
    x=0;
    y=0;
}
Snake::Snake()
{
    // nodelay(stdscr,true);
    keypad(stdscr,true);   // 키패드 생성
    noecho();
    curs_set(0);           // 커서 제거
    fail=false;
    for(int i = 0; i<maxheight; i++){
      for(int j = 0; j<maxwidth; j++){
        if(buffer[i][j] == '3')
        snake.push_back(Pos(j,i));
      }
    }
    point=0;
    len=3;
    growCnt=0;
    poisonCnt=0;
    gateCnt=0;
    delay=110000;
    getGrow=false;
    getPoison=false;
    gateNum = -1;
    dir='l';
    srand(time(NULL));
    putGate();
    for(int i = 0; i<3; i++){
      putGrow();  // growItem 생성
      putPoison();  // poisonItem 생성
  }
    for(int i=0;i<snake.size();i++) // snake 맵에 그리기
    {
        mvwprintw(Board_GAME,snake[i].y,snake[i].x,"●");
    }

}

Snake::~Snake() // Snake Destructor
{
    nodelay(stdscr,false);
    getch();
    endwin();
}
void Snake::putGate(){
  while(gate.size()<2)
  {
      int tmpX=rand()%maxwidth;
      int tmpY=rand()%maxheight;
      if(buffer[tmpY][tmpX] != '1')  // 벽에 게이트 생성
        continue;
      for(int i = 0; i<gate.size(); i++){
        if(gate[i].x == tmpX && gate[i].y == tmpY)
          continue;
      }
      buffer[tmpY][tmpX] = ' ';
      gate.push_back(Pos(tmpX,tmpY));
  }
  for(int i = 0; i<gate.size(); i++){
    mvwprintw(Board_GAME,gate[i].y,gate[i].x,"□");
  }
  wrefresh(Board_GAME);
}
void Snake::putGrow()
{
    int tmpX, tmpY;
    while(1)
    {
        tmpX=rand()%maxwidth+1;
        tmpY=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++)
            if(snake[i].x==tmpX && snake[i].y==tmpY){ // 스네이크 몸통에 Grow 생성불가
                continue;
        }
        if(buffer[tmpY][tmpX] == '1')  // 벽에 Grow 생성불가
            continue;
        growItem.push_back(Pos(tmpX,tmpY));
        break;
    }
    mvwprintw(Board_GAME,tmpY,tmpX,"★");
    wrefresh(Board_GAME);
}
void Snake::putPoison()
{
    int tmpX, tmpY;
    while(1)
    {
        tmpX=rand()%maxwidth+1;
        tmpY=rand()%maxheight+1;

        for(int i=0;i<snake.size();i++){
          if(snake[i].x==tmpX && snake[i].y==tmpY) // 스네이크 몸통에 Poison 생성불가
            continue;
          }
        if(buffer[tmpY][tmpX] == '1')  // 벽에 Poison 생성불가
          continue;
        poisonItem.push_back(Pos(tmpX,tmpY));
        break;
    }
    mvwprintw(Board_GAME,tmpY,tmpX,"♠");
    wrefresh(Board_GAME);
}
bool Snake::collision()
{
    // 벽과 충돌했을 때
    for(int i = 0; i<maxheight; i++){
      for(int j = 0; j<maxwidth; j++){
        if(buffer[i][j] == '1')
          if(snake[0].x == j && snake[0].y == i)
            return true;
      }
    }
    for(int i=2;i<snake.size();i++)
    {
        if(snake[0].x==snake[i].x && snake[0].y==snake[i].y) // 몸통과 충돌할 때 GameOver
            return true;
    }
    for(int i = 0; i<2; i++){
      if(snake[0].x == gate[i].x && snake[0].y == gate[i].y){ // gate와 마주쳤을 때
        gateNum = i;
        int gate1tmpX = gate[0].x;
        int gate1tmpY = gate[0].y;
        int gate2tmpX = gate[1].x;
        int gate2tmpY = gate[1].y;
        moveGate(); // 게이트안에서 이동
        wattron(Board_GAME,COLOR_PAIR(4));
        mvwprintw(Board_GAME,gate1tmpY,gate1tmpX,"■");
        mvwprintw(Board_GAME,gate2tmpY,gate2tmpX,"■");
        buffer[gate1tmpY][gate1tmpX] = '1';
        buffer[gate2tmpY][gate2tmpX] = '1';
        wrefresh(Board_GAME);
        wattroff(Board_GAME,COLOR_PAIR(4));
        gate.clear();
        putGate();
        gateCnt+=1;
        break;
      }
    }
    for(int i = 0; i<3; i++){
      if(snake[0].x==growItem[i].x && snake[0].y==growItem[i].y) // growItem과 마주쳤을 때
      {
        growItem.erase(growItem.begin()+i);
        getGrow=true;
        growCnt+=1;
        putGrow();
        point+=1;
        len+=1;
        break;
        }
      else if(snake[0].x==poisonItem[i].x && snake[0].y==poisonItem[i].y) // poisonItem과 마주쳤을 때
        {
        poisonItem.erase(poisonItem.begin()+i);
        getPoison=true;
        poisonCnt+=1;
        putPoison();
        point-=1;
        len-=1;
        break;
        }
      else{
        getGrow=false;
        getPoison=false;
      }
    }
    return false;
}
bool Snake::gameOver(){
    fail=true;
    return fail;
}
void Snake::kbhit(){ // 방향전환
  int tmp = getch();
  switch(tmp)
  {
      case KEY_LEFT:
          if(dir!='r')
              dir='l';
          else
              gameOver();
          break;
      case KEY_UP:
          if(dir!='d')
              dir='u';
          else
              gameOver();
          break;
      case KEY_DOWN:
          if(dir!='u')
              dir='d';
          else
              gameOver();
          break;
      case KEY_RIGHT:
          if(dir!='l')
              dir='r';
          else
              gameOver();
          break;
      case KEY_BACKSPACE:
          dir='q';
          break;
  }
}
void Snake::moveSnake(){
    kbhit();
    if(getGrow){ // grow item을 먹을 때
      if(dir=='l')
          snake.insert(snake.begin(),Pos(snake[0].x-1,snake[0].y));
      else if(dir=='r')
          snake.insert(snake.begin(),Pos(snake[0].x+1,snake[0].y));
      else if(dir=='u')
          snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y-1));
      else if(dir=='d')
          snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y+1));
    }
    else if(getPoison){ // poison item을 먹을 떄
      wmove(Board_GAME,snake[snake.size()-1].y,snake[snake.size()-1].x);
      wprintw(Board_GAME," ");
      wmove(Board_GAME,snake[snake.size()-2].y,snake[snake.size()-2].x);
      wprintw(Board_GAME," ");
      wrefresh(Board_GAME);
      snake.pop_back();
      snake.pop_back();
      if(dir=='l')
          snake.insert(snake.begin(),Pos(snake[0].x-1,snake[0].y));
      else if(dir=='r')
          snake.insert(snake.begin(),Pos(snake[0].x+1,snake[0].y));
      else if(dir=='u')
          snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y-1));
      else if(dir=='d')
          snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y+1));
    }

    else{  // 아무것도 먹지 않았을 때
    wmove(Board_GAME,snake[snake.size()-1].y,snake[snake.size()-1].x);
    wprintw(Board_GAME," ");
    wrefresh(Board_GAME);
    snake.pop_back();
    if(dir=='l')
        snake.insert(snake.begin(),Pos(snake[0].x-1,snake[0].y));
    else if(dir=='r')
        snake.insert(snake.begin(),Pos(snake[0].x+1,snake[0].y));
    else if(dir=='u')
        snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y-1));
    else if(dir=='d')
        snake.insert(snake.begin(),Pos(snake[0].x,snake[0].y+1));
  }
    mvwprintw(Board_GAME,snake[0].y,snake[0].x,"●");
    wrefresh(Board_GAME);
}
void Snake::moveGate(){ // 게이트안에서 움직일 때

    if(gateNum == 0){ // 진입 = 0, 진출 = 1
      if(gate[1].x == 0)
        dir = 'r';
      else if(gate[1].x == 59)
        dir = 'l';
      else if(gate[1].y == 0)
        dir = 'd';
      else if(gate[1].y == 29)
        dir = 'u';
      else{
        if(buffer[gate[1].y-1][gate[1].x] != '1' || buffer[gate[1].y+1][gate[1].x] != '1'){
          if(dir == 'u' || dir == 'l')
            dir = 'u';
          else
            dir = 'd';
        }
        else{
          if(dir == 'u' || dir == 'l')
            dir = 'l';
          else
            dir = 'r';
        }
      }
      for(int i = 0; i<snake.size(); i++){
      kbhit();
      wmove(Board_GAME,snake[snake.size()-1].y,snake[snake.size()-1].x);
      wprintw(Board_GAME," ");
      wrefresh(Board_GAME);
      snake.pop_back();
      if(dir=='l'){
        snake.insert(snake.begin(),Pos(gate[1].x-1,gate[1].y));
        gate[1].x = gate[1].x-1;
      }
      else if(dir=='r'){
        snake.insert(snake.begin(),Pos(gate[1].x+1,gate[1].y));
        gate[1].x = gate[1].x+1;
      }
      else if(dir=='u'){
        snake.insert(snake.begin(),Pos(gate[1].x,gate[1].y-1));
        gate[1].y = gate[1].y-1;
      }
      else if(dir=='d'){
        snake.insert(snake.begin(),Pos(gate[1].x,gate[1].y+1));
        gate[1].y = gate[1].y+1;
      }
      mvwprintw(Board_GAME,snake[0].y,snake[0].x,"●");
      wrefresh(Board_GAME);
      usleep(delay);
    }
  }

    else if(gateNum == 1){ // 진입 = 1, 진출 = 0
      if(gate[0].x == 0)
        dir = 'r';
      else if(gate[0].x == 59)
        dir = 'l';
      else if(gate[0].y == 0)
        dir = 'd';
      else if(gate[0].y == 29)
        dir = 'u';
      else{
          if(buffer[gate[0].y-1][gate[0].x] != '1' || buffer[gate[0].y+1][gate[0].x] != '1'){
            if(dir == 'u' || dir == 'l')
              dir = 'u';
            else
              dir = 'd';
          }
          else{
            if(dir == 'u' || dir == 'l')
              dir = 'l';
            else
              dir = 'r';
          }
        }
      for(int i = 0; i<snake.size(); i++){
        kbhit();
        wmove(Board_GAME,snake[snake.size()-1].y,snake[snake.size()-1].x);
        wprintw(Board_GAME," ");
        wrefresh(Board_GAME);
        snake.pop_back();
      if(dir=='l'){
        snake.insert(snake.begin(),Pos(gate[0].x-1,gate[0].y));
        gate[0].x = gate[0].x-1;
      }
      else if(dir=='r'){
        snake.insert(snake.begin(),Pos(gate[0].x+1,gate[0].y));
        gate[0].x = gate[0].x+1;
      }
      else if(dir=='u'){
        snake.insert(snake.begin(),Pos(gate[0].x,gate[0].y-1));
        gate[0].y = gate[0].y-1;
      }
      else if(dir=='d'){
        snake.insert(snake.begin(),Pos(gate[0].x,gate[0].y+1));
        gate[0].y = gate[0].y+1;
      }
      mvwprintw(Board_GAME,snake[0].y,snake[0].x,"●");
      wrefresh(Board_GAME);
      usleep(delay);
    }
  }
}

void Snake::play()
{
    while(1)
    {
        if(collision() || fail || len < 3) // 충돌 or 정반대 방향을 입력하면 return true;
        {
            break;
        }
        moveSnake();
        if(dir=='q')              // 백스페이스 입력시 게임 stop
            break;
        usleep(delay);            // delay
    }
}
