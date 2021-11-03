#include "CreateTerm.h"
#include <clocale>
#include <locale.h>
#include <wchar.h>

Terminals::Terminals(){
  setlocale(LC_ALL, "");
  initscr();
  resize_term(80, 130);
  refresh();
  noecho();
  nodelay(stdscr, false);
  start_color();
  init_color(COLOR_MAGENTA, 50, 0 , 350);
  init_color(COLOR_BLACK, 0, 0, 0);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_WHITE);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  bkgd(COLOR_PAIR(8));
  attron(COLOR_PAIR(8));
}

void Terminals::GameBoard(){
  Board_GAME = newwin(30, 60, 1,1); // column, row, point y, point x;
  nodelay(stdscr, true);
  wbkgd(Board_GAME, COLOR_PAIR(8));
  wattron(Board_GAME,COLOR_PAIR(8));
  for(int i = 0; i<30; i++){
    wattron(Board_GAME,COLOR_PAIR(4));
    move(i, 2);
    for(int j = 0; j< 60; j++){
      if(buffer[i][j] == '0')
        wprintw(Board_GAME, " ");
      else if(buffer[i][j] == '1'||buffer[i][j] == '\0')
        wprintw(Board_GAME,"■");
      else
        wprintw(Board_GAME, " ");
    }
    wattroff(Board_GAME,COLOR_PAIR(4));
  }
  Snake snake;
  snake.play();
}

void Terminals::ScoreBoard(){
  Board_Score = newwin(20, 35, 1, 63);
  curs_set(0);
  wbkgd(Board_Score, COLOR_PAIR(5));
  wattron(Board_Score,COLOR_PAIR(5));
  mvwprintw(Board_Score, 1, 8, " :: Score Board :: \n");
  mvwprintw(Board_Score, 2, 3, "─────────────────────────────");
  mvwprintw(Board_Score, 3, 2, "Current Length : ");
  mvwprintw(Board_Score, 3, 19, "%d", len);
  mvwprintw(Board_Score, 5, 2, "Grow Item : ");
  //mvwprintw(Board_Score, 5, 14, "%d", growCnt);
  mvwprintw(Board_Score, 7, 2, "Poison Item : ");
//  mvwprintw(Board_Score, 7, 16, "%d", getSnake->getpoisoncnt());
  mvwprintw(Board_Score, 9, 2, "Number of Used Gate : ");
  //mvwprintw(Board_Score, 9, 24, "%d", gateCnt);
  wattroff(Board_Score, COLOR_PAIR(5));
  box(Board_Score, '|', '-');
  wrefresh(Board_Score);
  delwin(Board_Score);
  }

void Terminals::MissionBoard(){
  Board_Mission = newwin(8, 60, 32, 2);
  //curs_set(0);
  wbkgd(Board_Mission, COLOR_PAIR(5));
  wattron(Board_Mission,COLOR_PAIR(5));
  box(Board_Mission, '|', '-');
  mvwprintw(Board_Mission, 1, 20, " :: Mission Board :: ");
  mvwprintw(Board_Mission, 2, 2, "───────────────────────────────────────────────────────");
  mvwprintw(Board_Mission, 3, 2, "Snake Length : ");
  mvwprintw(Board_Mission, 3, 17, "%d", MissionLen);
  mvwprintw(Board_Mission, 4, 2, "Grow Item : ");
  mvwprintw(Board_Mission, 4, 14, "%d", MissionGrow);
  mvwprintw(Board_Mission, 5, 2, "Poison Item : ");
  mvwprintw(Board_Mission, 5, 16, "%d", MissionPoison);
  mvwprintw(Board_Mission, 6, 2, "Number of Used Gate : ");
  mvwprintw(Board_Mission, 6, 24, "%d", MissionGate);
  wrefresh(Board_Mission);
  delwin(Board_Mission);
}

// void Terminals::RefreshTerminal(){
//   wrefresh(Board_Score);
//   wrefresh(Board_Mission);
//   wrefresh(Board_GAME);
//   getch();
// }

void Terminals::Start(){
  clear();
  SetStage();
  noecho();
  getch();
  ScoreBoard();
  MissionBoard();
  GameBoard();
  // RefreshTerminal();
  EndStage();
}

void Terminals::StartScreen(){
  noecho();
  attron(COLOR_PAIR(6));
  mvprintw(13, 20, "   _  _  _  _         _           _              _              _           _        _  _  _  _  _");
  mvprintw(14, 20, " _(_)(_)(_)(_)_      (_) _       (_)           _(_)_           (_)       _ (_)      (_)(_)(_)(_)(_)");
  mvprintw(15, 20, "(_)          (_)     (_)(_)_     (_)         _(_) (_)_         (_)    _ (_)         (_)            ");
  mvprintw(16, 20, "(_)_  _  _  _        (_)  (_)_   (_)       _(_)     (_)_       (_) _ (_)            (_) _  _          ");
  mvprintw(17, 20, "  (_)(_)(_)(_)_      (_)    (_)_ (_)      (_) _  _  _ (_)      (_)(_) _             (_)(_)(_)         ");
  mvprintw(18, 20, "             (_)     (_)      (_)(_)      (_)(_)(_)(_)(_)      (_)   (_) _          (_)               ");
  mvprintw(19, 20, "(_)_  _  _  _(_)     (_)         (_)      (_)         (_)      (_)      (_) _       (_) _  _  _  _    ");
  mvprintw(20, 20, "  (_)(_)(_)(_)       (_)         (_)      (_)         (_)      (_)         (_)      (_)(_)(_)(_)(_)   ");
  mvprintw(22, 23, "       _  _  _                 _              _           _        _  _  _  _  _    ");
  mvprintw(23, 23, "    _ (_)(_)(_) _            _(_)_           (_) _     _ (_)      (_)(_)(_)(_)(_)   ");
  mvprintw(24, 23, "   (_)         (_)         _(_) (_)_         (_)(_)   (_)(_)      (_)               ");
  mvprintw(25, 23, "   (_)    _  _  _        _(_)     (_)_       (_) (_)_(_) (_)      (_) _  _          ");
  mvprintw(26, 23, "   (_)   (_)(_)(_)      (_) _  _  _ (_)      (_)   (_)   (_)      (_)(_)(_)         ");
  mvprintw(27, 23, "   (_)         (_)      (_)(_)(_)(_)(_)      (_)         (_)      (_)               ");
  mvprintw(28, 23, "   (_) _  _  _ (_)      (_)         (_)      (_)         (_)      (_) _  _  _  _    ");
  mvprintw(29, 23, "      (_)(_)(_)(_)      (_)         (_)      (_)         (_)      (_)(_)(_)(_)(_)   ");
  attron(COLOR_PAIR(5));
  mvprintw(34, 50, "Press any key to start game");
  attroff(COLOR_PAIR(5));
  attroff(COLOR_PAIR(6));
  refresh();
  getch();
  clear();
}

void Terminals::EndStage(){
  if(RoundCount < 4){
  noecho();
  //cbreak();
  nodelay(stdscr, true);
  char input;
  clear();
  mvprintw(21, 55, "자동으로 게임이 종료됩니다.");
  mvprintw(22, 52, "게임 종료 : Q | 다음 라운드 시작 : R");
  for(int i = 7, j = 51, k = 8; i>-1; i--, j=j+4, k--){
//    cbreak();
    if(getch()=='q' || getch()=='Q'){
        clear();
        mvprintw(28, 47, "게임을 종료합니다.");
        break;
    }
    if(getch()=='r' || getch() == 'R'){
      RoundCount++;
      Start();
      clear();
    }
    usleep(1000*1000);
    mvprintw(24, 51, " □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ □ ");
    mvprintw(24, j, " ■ ■ ");
    mvprintw(26, 60, "남은 시간 : ");
    std::string time = std::to_string(k);
    const char * time2 = time.c_str();
    mvprintw(26, 72, time2);
    refresh();
    }
    RoundCount++;
  }
  else{
    endwin();
  }
  refresh();
}
