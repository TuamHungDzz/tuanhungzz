#include<stdio.h>
#include<windows.h>
int snake[1000];
int vx=0,vy=-1;
int highscore=0;
int dodai;
int tg;
int level;
int apple=11510;
int ct;
int i;
char name1[100];
int score = 0;
enum state{MENU,GAMEOVER,INGAME,SETTING,INFO,PLAY}state;
void Color(int color)
{	WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);  }
}
void gotoxy(int x, int y){
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
int Random(int a,int b){
	return a + rand()%(b-a+1);
}
void printfScore(){
	
	gotoxy(8,24);
	printf("%d ",0);
	gotoxy(9,24);
	printf("%d ",0);
	gotoxy(10,24);
	printf("%d ",0);
	gotoxy(11,24);
	printf("%d ",0);
	gotoxy(12,24);
	printf("%d ",0);
	int tg= score;
	int n=0;
	int a[5];
	for(n;n<5;n++){
		a[n]=tg%10;
		tg=tg/10;
	}
	gotoxy(8,24);
	printf("%d ",a[4]);
	gotoxy(9,24);
	printf("%d ",a[3]);
	gotoxy(10,24);
	printf("%d ",a[2]);
	gotoxy(11,24);
	printf("%d ",a[1]);
	gotoxy(12,24);
	printf("%d ",a[0]);
}
void nhapName(char name1[100]){
	gotoxy(43,5);
	printf("__________GAME RAN SAN MOI__________");
	gotoxy(43,7);
	printf("NHAP TEN NHAN VAT :");
	gets(name1);
	system("cls");
}
void xuatName(char name1[100]){
	puts(name1);
}
void recreatApple(){
	int bl=0;
	int i;
	for(;;){
		apple = 10000 + Random(1,118)*100;
		apple = apple + Random(1,20);
		for(i=0;i<dodai;i++){
			if(apple==snake[i]){
				bl=1;
			}
		}if(!bl) break;
	}
	
}
void box(){
	gotoxy(0,0);
	int i =0;
	for(i;i<119;i++){printf("#");}
	int j=0;
	for(j;j<22;j++){
		printf("\n");
		i=0;
		for(i;i<119;i++){
			if(i==0||i==118){
				printf("#");
			}
			else{printf(" ");
			}	
	}
	}printf("\n");
	i=0;
	for(i;i<119;i++){
		printf("#");
	}
}
int getX(int a){
	return (a-10000)/100;
}
int getY(int a){
	return a%100;
}
void initgame(){
	dodai= 3;
	snake[0]=11210;
	snake[1]=11211;
	snake[2]=11212;
}

void play(){
	int luachon1;
	Color(6);
	box();
	gotoxy(43,5);
	printf("__________GAME RAN SAN MOI__________");
	gotoxy(43,7);
	printf("1.EASY ");
	gotoxy(43,8);
	printf("2.MEDIUM ");
	gotoxy(43,9);
	printf("3.HARD ");
	gotoxy(43,10);
	printf("NHAP LUA CHON CUA BAN :");
	scanf("%d",&luachon1);
	
	switch(luachon1){
		case 1:
			level = 12000;
			state = INGAME;
			break;
		case 2:
			level = 9000;
			state = INGAME;
			break;
		case 3:
			level = 3000;
			state = INGAME;
			break;
			
	}
}
void menu(){
	Color(6);
	box();
	nhapName(name1);
	int luachon;
	Color(6);
	box();
	gotoxy(30,19);
	printf("TEN NHAN VAT :");
	xuatName(name1);
	gotoxy(43,5);
	printf("__________GAME RAN SAN MOI__________");
	gotoxy(93,19);
	printf("DESIGN BY : 6251071041 ");
	gotoxy(43,7);
	printf("1.PLAY ");
	gotoxy(43,8);
	printf("2.SETTING");
	gotoxy(43,9);
	printf("3.INFO");
	gotoxy(43,10);
	printf("4.EXIT");
	gotoxy(43,11);
	printf("NHAP LUA CHON CUA BAN: ");
	scanf("%d",&luachon);
	switch(luachon){
		case 1:
			state = PLAY;
			break;
		case 2:
			state = SETTING;
			break;
	}
}
void ingame(){
	initgame();
	int key=0;
	box();
	gotoxy(1,24);
	printf("SCORE:");
	int j=1;
	gotoxy(getX(snake[0]),getY(snake[0]));
		printf("#");
	for(j;j<dodai-1;j++){
		gotoxy(getX(snake[j]),getY(snake[j]));
		printf("o");
	}
	while(state==INGAME){
		if(kbhit()){
			key = getch();
			switch(key){
				case 72://len
					if(vx!=0){
						vx=0;
						vy=-1;}
				break;
				case 80://xuong
					if(vx!=0){
						vx=0;
						vy=1;}
				break;
				case 75://trai
					if(vy!=0){
						vx=-1;
						vy=0;}
				break;
				case 77://phai
					if(vy!=0){
					vx=1;
					vy=0;}
				break;
			}
		}
		if((ct%level)==0){
		gotoxy(getX(snake[dodai-1]),getY(snake[dodai-1]));
		printf(" ");
		int i = dodai-1;
		for(i;i>0;i--){	
			snake[i]=snake[i-1];}	
		snake[0]=snake[0]+vy; 
		snake[0]=snake[0]+vx*100;
		if(getY(snake[0])==0) snake[0]=snake[0]+22;
		if(getY(snake[0])==23) snake[0]=snake[0]-22;
		if(getX(snake[0])==0) snake[0]=snake[0]+11500;
		if(getX(snake[0])==116) snake[0]= snake[0]-11500;
		if(snake[0]==apple){
			gotoxy(getX(apple),getY(apple));
			printf("#");
			dodai++;
			recreatApple();
			score=score+5;
			printfScore();
		}
		gotoxy(getX(snake[0]),getY(snake[0]));
		printf("#");
		gotoxy(getX(snake[1]),getY(snake[1]));
		printf("o");
		gotoxy(getX(apple),getY(apple));
		printf("o");
		
		for(i=1;i<dodai;i++){
			int diem=0;
			if(snake[0]==snake[i])
			state = GAMEOVER;
			score == highscore;
		}
		}
		ct++;
	}
}
void setting(){
	system("cls");
	box();
	gotoxy(43,5);
	printf("__________GAME RAN SAN MOI__________");
	gotoxy(93,19);
	printf("DESIGN BY : 6251071041 ");
	gotoxy(43,7);
	printf("1.PLAY ");
	gotoxy(43,8);
	printf("2.SETTING");
	gotoxy(43,9);
	printf("3.INFO");
	printf("SETTING");
	state = 10;
}
void gameover(){
	system("cls");
	box();
	gotoxy(43,5);
	printf("GAMEOVER:\n");
	
	
	state= 10;
}
void info(){
}
int main(){
	box();
	while(1){
		switch(state){
			case MENU:
			menu();
			break;
			case INGAME:
			ingame();
			break;
			case SETTING:
			setting();
			break;
			case INFO:
			break;
			case GAMEOVER:
			gameover();
			break;
			case PLAY:
			play();
			break;
			
		}
	}
	
	return 0;
}
