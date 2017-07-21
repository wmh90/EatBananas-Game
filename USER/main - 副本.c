#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h" 
#include "image2lcd.h"
#include "stdlib.h"
#include "key.h"
#include "exti.h"



extern const u8 gImage_bann[];//加载图片数组文件
extern const u8 gImage_bomb[];
extern const u8 gImage_canno[];
extern const u8 gImage_cokie[];
extern const u8 gImage_bblack[];
extern const u8 gImage_pone[];
extern const u8 gImage_mone[];
extern const u8 gImage_bblackl[];

int show_cookie_en=0;
u8 cookie_pos=80;
int score=0;

void show_cookie(int show_cookie)                            //刷新蜜罐位置函数
{
	if(show_cookie_en==1){
		show_cookie_en=0;
	  image_display(0,280,(u8*)gImage_bblackl);
	  image_display(cookie_pos,280,(u8*)gImage_cokie);
	}
}

 int main(void)
 {
	  int i,j;
	  u8 rx;
	delay_init();	    	                            //延时函数初始化	  
	uart_init(9600);  	                            //串口初始化为9600
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组2
	EXTIX_Init();	      	                          //外部中断初始化
	LED_Init();			                                //LED初始化
	KEY_Init();                                     //初始化与按键连接的硬件接口
 	LCD_Init(); 	                                  //LCD初始化					 
	delay_ms(1500);		                              //等待1.5秒	  
	LCD_Clear(BLACK);
	image_display(0,  0,(u8*)gImage_canno);         //
	image_display(40, 0,(u8*)gImage_canno);         //
	image_display(80, 0,(u8*)gImage_canno);         //
	image_display(120,0,(u8*)gImage_canno);         //
	image_display(160,0,(u8*)gImage_canno);         //
	image_display(200,0,(u8*)gImage_canno);         //显示上方炮*6
		
	LCD_ShowString(0,0,200,16,16,"Score: ");        //显示Score字符串
	LCD_ShowxNum(60,0,score,2,16,0);                //显示分数数字
	image_display(cookie_pos,280,(u8*)gImage_cokie);//显示蜜罐
	
	while(1) 
	{	
		
		rx=rand()%6;                                          //生成香蕉随机位置
		for(i=40;i<=320;i++){                                 //循环控制下落
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //显示蜜罐
			image_display(rx*40,i,(u8*)gImage_bann);            //显示香蕉
			if(i>=80){
				image_display(rx*40,i-40,(u8*)gImage_bblack);     //清除上一格显示
			}
			if(i==240){                                         //判断是否吃到
				if(rx*40==cookie_pos){
				  score+=1;
					LCD_ShowxNum(56,0,score,2,16,0);                //刷新分数
					image_display(rx*40,240,(u8*)gImage_pone);      //显示+1效果
					image_display(cookie_pos,280,(u8*)gImage_cokie);//刷新蜜罐显示
					delay_ms(500);                                  //+1效果显示时间
					image_display(rx*40,240,(u8*)gImage_bblack);    //清除+1效果
					break;
				}
			}
			if(i>=241 && cookie_pos==rx*40){
				image_display(rx*40,i,(u8*)gImage_bblack);
				image_display(cookie_pos,280,(u8*)gImage_cokie);
				break;
			}
			if(i==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //重新显示蜜罐
			}
			delay_ms(10);	                                      //控制下落速度
			show_cookie(show_cookie_en);
		}
		delay_ms(600);                                        //控制两次下落之间间隔
		
		rx=rand()%6;                                          //生成炸弹随机位置
		for(j=40;j<=320;j++){                                 //循环控制下落
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //显示蜜罐
			image_display(rx*40,j,(u8*)gImage_bomb);            //显示炸弹
			if(j>=80){
				image_display(rx*40,j-40,(u8*)gImage_bblack);     //黑屏清除
			}
			if(j==240){                                         //判断是否吃到
				if(rx*40==cookie_pos){
				  score-=1;
					if(score<0) score=0;                            //分数不能小于零
					LCD_ShowxNum(56,0,score,2,16,0);                //刷新分数
					image_display(rx*40,240,(u8*)gImage_mone);      //显示-1效果
					image_display(cookie_pos,280,(u8*)gImage_cokie);//刷新蜜罐显示
					delay_ms(500);                                  //-1效果显示时间
					image_display(rx*40,240,(u8*)gImage_bblack);    //清除-1效果
					break;
				}
			}
			if(j>=241 && cookie_pos==rx*40){
				image_display(rx*40,j,(u8*)gImage_bblack);
				image_display(cookie_pos,280,(u8*)gImage_cokie);
				break;
			}
			if(j==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie); //重新显示蜜罐
			}
			delay_ms(10);	                                     //控制下落速度
			show_cookie(show_cookie_en);
		}
		delay_ms(600);                                       //控制两次下落之间间隔
		
	}
	
}

