#include "LPC17xx.H"
#include "Keypad.H"
#include "GLCD.h"
#include "LPC1768_utility.h"
#include "stdlib.h"
#include "time.h"

uint8_t array[9] = {1,2,3,4,5,6,7,8,9};		// array for 3x3 entries
uint8_t count = 0;		// play count
uint8_t pos = 16; // pos*(0~19)
uint8_t ppos = 4;
int speed = 50;
	
void intro(){		// GUI for Intro Display
	GLCD_clear(Black);
	GLCD_setBackColor(Black);
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0,"*  Counting People *");
	GLCD_displayStringLn(Line1,"                    ");
	GLCD_displayStringLn(Line2,"      ***           ");
	GLCD_displayStringLn(Line3,"      ***           ");		
	GLCD_displayStringLn(Line4,"  **********        ");
	GLCD_displayStringLn(Line5," ****HOME****       ");
  GLCD_displayStringLn(Line6,"**************      ");		
	GLCD_displayStringLn(Line7," *     *   **       ");
	GLCD_displayStringLn(Line8," *     *   **       ");
	GLCD_displayStringLn(Line9," ************       ");

	GLCD_displayStringLn(Line2,"     ***            ");
	GLCD_displayStringLn(Line3,"     ***            ");		
	GLCD_displayStringLn(Line4," **********         ");
	GLCD_displayStringLn(Line5,"****HOME****        ");
  GLCD_displayStringLn(Line6,"*************       ");		
	GLCD_displayStringLn(Line7,"*     *   **        ");
	GLCD_displayStringLn(Line8,"*     *   **        ");
	GLCD_displayStringLn(Line9,"************        ");

	GLCD_displayStringLn(Line2,"    ***             ");
	GLCD_displayStringLn(Line3,"    ***             ");		
	GLCD_displayStringLn(Line4,"**********          ");
	GLCD_displayStringLn(Line5,"***HOME****         ");
  GLCD_displayStringLn(Line6,"************        ");		
	GLCD_displayStringLn(Line7,"     *   **         ");
	GLCD_displayStringLn(Line8,"     *   **         ");
	GLCD_displayStringLn(Line9,"***********         ");

	GLCD_displayStringLn(Line2,"   ***              ");
	GLCD_displayStringLn(Line3,"   ***              ");		
	GLCD_displayStringLn(Line4,"*********           ");
	GLCD_displayStringLn(Line5,"**HOME****          ");
  GLCD_displayStringLn(Line6,"***********         ");		
	GLCD_displayStringLn(Line7,"    *   **          ");
	GLCD_displayStringLn(Line8,"    *   **          ");
	GLCD_displayStringLn(Line9,"**********          ");
	
	
	GLCD_displayStringLn(Line2,"  ***               ");
	GLCD_displayStringLn(Line3,"  ***               ");		
	GLCD_displayStringLn(Line4,"********            ");
	GLCD_displayStringLn(Line5,"*HOME****           ");
  GLCD_displayStringLn(Line6,"**********          ");		
	GLCD_displayStringLn(Line7,"   *   **           ");
	GLCD_displayStringLn(Line8,"   *   **           ");
	GLCD_displayStringLn(Line9,"*********           ");
	
	GLCD_displayStringLn(Line2," ***                ");
	GLCD_displayStringLn(Line3," ***                ");		
	GLCD_displayStringLn(Line4,"*******             ");
	GLCD_displayStringLn(Line5,"HOME****            ");
  GLCD_displayStringLn(Line6,"*********           ");		
	GLCD_displayStringLn(Line7,"  *   **            ");
	GLCD_displayStringLn(Line8,"  *   **            ");
	GLCD_displayStringLn(Line9,"********            ");

	GLCD_displayStringLn(Line2,"***                 ");
	GLCD_displayStringLn(Line3,"***                 ");		
	GLCD_displayStringLn(Line4,"******              ");
	GLCD_displayStringLn(Line5,"OME****             ");
  GLCD_displayStringLn(Line6,"********            ");		
	GLCD_displayStringLn(Line7," *   **             ");
	GLCD_displayStringLn(Line8," *   **             ");
	GLCD_displayStringLn(Line9,"*******             ");
	
	
	GLCD_displayChar(pos*18,Line5,0x50);
	GLCD_displayChar(pos*19,Line5,0x31);
	GLCD_displayChar(pos*18,Line6,0x80+6);
	GLCD_setTextColor(Red);
	GLCD_displayChar(pos*18,Line7,0x80+1);
  Delay(SEC_2);
}

void print_stage(int stage){
	GLCD_clear(Black);
	
	for(int i=0;i<3;i++){
		GLCD_setTextColor(White);
		GLCD_displayStringLn(Line0,"*     Stage        *");
		GLCD_displayChar(pos*12,Line0,0x30+stage);
		Delay(SEC_1/3);
	
		GLCD_setTextColor(Yellow);
		GLCD_displayStringLn(Line0,"*     Stage        *");
		GLCD_displayChar(pos*12,Line0,0x30+stage);
		Delay(SEC_1/3);
	}
	
	
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0,"*     Stage 1      *");
	GLCD_displayChar(pos*12,Line0,0x30+stage);
	
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line2,"***                 ");
	GLCD_displayStringLn(Line3,"***                 ");		
	GLCD_displayStringLn(Line4,"******              ");
	GLCD_displayStringLn(Line5,"OME****             ");
  GLCD_displayStringLn(Line6,"********            ");		
	GLCD_displayStringLn(Line7," *   **             ");
	GLCD_displayStringLn(Line8," *   **             ");
	GLCD_displayStringLn(Line9,"*******             ");
	
}

void print_come_in(){
  int i=0;
	GLCD_setTextColor(Red);
	
	for(i=19;i>3;i--){
		if(i<6){
			GLCD_setTextColor(White);
			GLCD_displayChar(pos*(i+1),Line7,'*');
		}
		else{
			GLCD_setTextColor(Red);
			GLCD_displayChar(pos*(i+1),Line7,' ');
		}
		GLCD_setTextColor(Red);
		GLCD_displayChar(pos*i,Line7,0x80+1);
		Delay(SEC_1/speed);
	}
	GLCD_displayChar(pos*4,Line7,' ');
}

void print_leave(){
  int i;
	GLCD_setTextColor(Red);
	
	for(int i=4; i<19;i++){
		if(i>5&&i<8){
			GLCD_setTextColor(White);
			GLCD_displayChar(pos*(i-1),Line7,'*');
		}
		else{
			GLCD_setTextColor(Red);
			GLCD_displayChar(pos*(i-1),Line7,' ');
		}
		GLCD_setTextColor(Red);
		GLCD_displayChar(pos*i,Line7,0x80+1);
		Delay(SEC_1/speed);
	}
	GLCD_displayChar(pos*18,Line7,' ');
}

void question(int* answer){		// GUI for Intro Display
	int i=0;
	int j=0;
	int c[3];
	int l[3];
	int buf[2];
	
	int come_in = (rand()%3)+10;
	buf[0]=come_in;
	int leave = come_in - *answer ;
	buf[1]=leave;
	
	for(i=0;i<2;i++){
		c[i] = rand()%4+1;
		buf[0] = buf[0]-c[i];
		
		l[i] = rand()%4+1;
		buf[1] = buf[1]-l[i];
	}
	c[2]=buf[0];
	l[2]=buf[1];
	
	
	for(i=0;i<3;i++){
		for(j=0;j<c[i];j++){
			print_come_in();
			Delay(SEC_1);
		}
		for(j=0;j<l[i];j++){
			print_leave();
			Delay(SEC_1);
		}
	}
}

int printOX(int* answer,int* score){
	GLCD_clear(Black);
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0,"*     Answer:      *");
	GLCD_displayStringLn(Line2,"***                 ");
	GLCD_displayStringLn(Line3,"***                 ");		
	GLCD_displayStringLn(Line4,"******              ");
	GLCD_displayStringLn(Line5,"OME****             ");
  GLCD_displayStringLn(Line6,"********            ");		
	GLCD_displayStringLn(Line7," *   **             ");
	GLCD_displayStringLn(Line8," *   **             ");
	GLCD_displayStringLn(Line9,"*******             ");
	uint8_t Keypad_Value=0;
	
	while(1){
		Keypad_Value = Keypad('C');
		GLCD_displayChar(pos*13,Line0,0x30+Keypad_Value);

		if(*answer==Keypad_Value&&Keypad_Value!=0){
				Delay(SEC_2);
   			GLCD_setTextColor(White);
			  GLCD_displayStringLn(Line9,"*******             ");
				GLCD_displayStringLn(Line2,"      ********      ");
				GLCD_displayStringLn(Line3,"     **********     ");		
				GLCD_displayStringLn(Line4,"    ************    ");
				GLCD_displayStringLn(Line5,"    ************    ");
				GLCD_displayStringLn(Line6,"    ************    ");		
				GLCD_displayStringLn(Line7,"     **********     ");
				GLCD_displayStringLn(Line8,"      ********      ");
				GLCD_displayStringLn(Line9,"                    ");
			  Delay(SEC_4);
			  *score= *score+1 ;
				return 1;			
			break;
			
		}
		else if(*answer!=Keypad_Value&&Keypad_Value!=0){
				Delay(SEC_2);
			  GLCD_setTextColor(White);
				GLCD_displayStringLn(Line2,"   **          **   ");
				GLCD_displayStringLn(Line3,"   ***        ***   ");		
				GLCD_displayStringLn(Line4,"    ***      ***    ");
				GLCD_displayStringLn(Line5,"      ********      ");
				GLCD_displayStringLn(Line6,"      ********      ");		
				GLCD_displayStringLn(Line7,"    ***      ***    ");
				GLCD_displayStringLn(Line8,"   ***        ***   ");
				GLCD_displayStringLn(Line9,"   **          **   ");
			  Delay(SEC_4);			
				return 0;
			break;
			
		}
	}
}
void ending(int* score){
	int tmpp = *score;
	int i=7;
	
	GLCD_clear(Black);
	GLCD_setBackColor(Black);
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0,"*    Your Record   *");
	GLCD_displayStringLn(Line1,"*                  *");
	GLCD_displayStringLn(Line2,"*                  *");
	GLCD_displayStringLn(Line3,"*                  *");		
	GLCD_displayStringLn(Line4,"*          Point   *");
	GLCD_displayStringLn(Line5,"*                  *");
  GLCD_displayStringLn(Line6,"*                  *");		
	GLCD_displayStringLn(Line7,"*                  *");
	GLCD_displayStringLn(Line8,"*                  *");
	GLCD_displayStringLn(Line9,"********************");
	if(tmpp==0){
		GLCD_setTextColor(Red);
	  GLCD_displayChar(pos*i,Line4,'0');
	}
	else{
		while(tmpp>0){
			char tmp = (char)(tmpp%10+'0');
			GLCD_setTextColor(Red);
			GLCD_displayChar(pos*i,Line4,tmp);
			i--;
			tmpp=tmpp/10;
		}
	}
}




int main(void){
	int stage = 1 ;
	int answer = 0;
	int score = 0;
	int qq = 1;
	SystemInit();		// System Init
	EXT_IO_init();
	Keypad_DIR_Input();
	GLCD_init();
	
	intro();
	while(1){
	  print_stage(stage);
		//srand(time(NULL));
		answer=rand()%9+1; // between 1 ~ 9
		question(&answer);
		qq = printOX(&answer,&score);
		if(qq==0){
			break;	
	  }
		else{
			stage++;
		}
	}
	ending(&score);
}
