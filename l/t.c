#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include"l.h"

main()(
 struct termios old_tio,new_tio;tcgetattr(STDIN_FILENO,&old_tio);
 new_tio=old_tio;new_tio.c_lflag&=(~ICANON & ~ECHO);
 tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);I chr;S p="> ";K x;

 //k_(S*),rl1();

 rl2();rlprmt(p);do{if(rlchar(getchar())>=0){x=rl();
  O("%.*s xr %d ws %d\n",xn,xG,xr,WS);rlprmt(p);}}W(1);

 rl0();tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);}
