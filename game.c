#include "itcfunc.h"
#include <stdlib.h>

void game(){

	volatile int *counter_reg = (int*)0x010c;
	volatile char *key_reg = (char*)0x0110;
	volatile char key_val = *key_reg;

	int st_flag=0,rem=0,time_ctrl=0,clock=0;
	int a,b,c,d,e;
	int fin_flag=0,score=0;
	
	struct ziki {  // 自機の構造体
	int x;
    int direct;
	};
	struct ziki z1;
	z1.x=21;
	z1.direct=0;
	
	struct obj {  // 障害物の構造体
	int x;
	int y;
	};
	struct obj o0;
	o0.x = 0;
	o0.y = 0;
	struct obj o1;
	o1.x = 0;
	o1.y = 1;
	struct obj o2;
	o2.x = 0;
	o2.y = 2;
	struct obj o3;
	o3.x = 0;
	o3.y = -1;
    struct obj o4;
	o4.x = 0;
	o4.y = -2;
	
	srand(*(int*)0x010c);     // 乱数生成
	a=(int)(rand()%31);
	b=(int)(rand()%31);
	c=(int)(rand()%31);
	d=(int)(rand()%31);
	e=(int)(rand()%31);
	
void time_c(){  //描写スピード調整用の関数
while(1){
	time_ctrl++;
	if(time_ctrl >= 26000)break;
	}
	time_ctrl=0;
}

void check(){
if(o0.y == 12 && z1.x == o0.x){fin_flag = 1;}
if(o1.y == 12 && z1.x == o1.x){fin_flag = 1;}
if(o2.y == 12 && z1.x == o2.x){fin_flag = 1;}
if(o3.y == 12 && z1.x == o3.x){fin_flag = 1;}
if(o4.y == 12 && z1.x == o4.x){fin_flag = 1;}

}
	
while(fin_flag == 0){
	
	volatile int counter_val = *counter_reg;
	
    while(st_flag==0){    //GameStartの入力待ち
	key_val = *key_reg;
	lcd_locate(7,7);
	lcd_printf("Push 'W' then Game Start !");
	if(key_val & 0x20){st_flag=1; rem = counter_val; lcd_cls();}
	}
	
	if(st_flag==1){     //スコアの表示
	lcd_locate(34,0);
	lcd_printf("SCORE");
	lcd_locate(32,1);
	lcd_printf("%6d",score);
	clock = counter_val - rem;
	}
	
	
	lcd_locate(21,12);  //自機を動かす
	key_val = *key_reg;
	
	
	if(key_val & 0x02) {  //左入力J
	z1.direct=0x02;
	if(z1.x<=0){z1.x=0;}
	}
	
	else if(key_val & 0x01) {  //右入力K
	z1.direct=0x01;
	if(z1.x>=30){z1.x=30;}
	}
	
	else if(z1.direct==0){  //初期から入力がないとき
	lcd_locate(21,12);
	lcd_printf("A");
	}
	
	else if(z1.direct==0x02){  //Jの慣性
	if(z1.x<=0){z1.x=0; lcd_locate(0,12); lcd_printf("A");}
	else{
	lcd_locate(z1.x--,12);     //Aの描写
	lcd_printf("A");
	}
	}
	
	else if(z1.direct==0x01){  //Kの慣性
	if(z1.x>=30){z1.x=30; lcd_locate(30,12); lcd_printf("A");}
	else{
	lcd_locate(z1.x++,12);     //Aの描写
	lcd_printf("A");
	}
	}
	
	o0.x = a; o1.x = b; o2.x = c; o3.x = d; o4.x = e;
	lcd_locate(o0.x,o0.y++); lcd_printf("*");
	lcd_locate(o1.x,o1.y++); lcd_printf("*");
	lcd_locate(o2.x,o2.y++); lcd_printf("*");
	lcd_locate(o3.x,o3.y++); lcd_printf("*");
	lcd_locate(o4.x,o4.y++); lcd_printf("*");
	time_c();                  //表示時間操作
	
	lcd_locate(o0.x,o0.y-1); lcd_printf(" ");
	lcd_locate(o1.x,o1.y-1); lcd_printf(" ");
	lcd_locate(o2.x,o2.y-1); lcd_printf(" ");
	lcd_locate(o3.x,o3.y-1); lcd_printf(" ");
	lcd_locate(o4.x,o4.y-1); lcd_printf(" ");
	
	if(z1.direct==0x02){
	lcd_locate(z1.x+1,12);     //A消去操作
	lcd_printf(" ");
	}
	else if(z1.direct==0x01){
	lcd_locate(z1.x-1,12);     //A消去操作
	lcd_printf(" ");
	}
	
	
	if(o0.y >= 15){           //オブジェクト初期化
	o0.x=a=(int)(rand()%31);
	score+=5;
	o0.y=0;
	}
	if(o1.y >= 15){
	o1.x=b=(int)(rand()%31);
	o1.y=1;
	score+=5;
	}
	if(o2.y >= 15){
	o2.x=c=(int)(rand()%31);
	o2.y=2;
	score+=5;
	}
	if(o3.y >= 15){
	o3.x=c=(int)(rand()%31);
	o3.y=-1;
	score+=5;
	}
	if(o4.y >= 15){
	o4.x=c=(int)(rand()%31);
	o4.y=-2;
	score+=5;
	}
	
	check();                   //当たり判定関数
	}   // while終了

	
	
	lcd_cls();
	lcd_locate(15,7);
	lcd_printf("GameOver !");
	lcd_locate(10,8);
	lcd_printf("Your score is %d.",score);
	lcd_locate(10,9);
	lcd_printf("passed time is %d.",clock);
	
	}   // game()終了
	