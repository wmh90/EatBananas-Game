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
extern const u8 gImage_heart[];
extern const u8 gImage_blacks[];
extern const u8 gImage_gg[];
extern const u8 gImage_geek[];
extern const u8 gImage_geeks[];

u8 cookie_pos=80;
int score=0;
u32 speed_level=3000;

 int main(void)
 {
	 	u8 q=2;
	  u8 s=50; 
  	u8 size1=16;
	  int i,j;
	  u8 rx;
	  int life=3;
	delay_init();	    	                            //延时函数初始化	  
	uart_init(9600);  	                            //串口初始化为9600
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组2
	EXTIX_Init();	      	                          //外部中断初始化
	LED_Init();			                                //LED初始化
	KEY_Init();                                     //初始化与按键连接的硬件接口
 	LCD_Init(); 	                                  //LCD初始化					 
	delay_ms(1500);		                              //等待1.5秒	  
	LCD_Clear(BLACK);
	 
	image_display(15,0,(u8*)gImage_geek);//在指定地址显示图片	
	LCD_ShowChar(s,265,'E',size1,1);	
	LCD_ShowChar(s+(size1/2)+1,265,'a',size1,1);	
	LCD_ShowChar(s+(((size1/2)+1)*q),265,'t',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'B',size1,1);	q++;			
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'a',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'n',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'a',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'n',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'a',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'s',size1,1);	q++;q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'G',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'a',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'m',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'e',size1,1);	q++;
  LCD_ShowChar(s+(((size1/2)+1)*q),265,'s',size1,1);			
	delay_ms(3000);
  delay_ms(3000);	
	LCD_Clear(BLACK);
	 
	image_display(0,  16,(u8*)gImage_canno);         //
	image_display(40, 16,(u8*)gImage_canno);         //
	image_display(80, 16,(u8*)gImage_canno);         //
	image_display(120,16,(u8*)gImage_canno);         //
	image_display(160,16,(u8*)gImage_canno);         //
	image_display(200,16,(u8*)gImage_canno);         //显示上方炮*6
	
	image_display(100,0,(u8*)gImage_geeks);          //显示上方Geek
	 
	image_display(192,0,(u8*)gImage_heart);          //显示生命
	image_display(208,0,(u8*)gImage_heart);
	image_display(224,0,(u8*)gImage_heart);
	
	LCD_ShowString(0,0,200,16,16,"Score: ");        //显示Score字符串
	LCD_ShowxNum(60,0,score,2,16,0);                //显示分数数字
	image_display(cookie_pos,280,(u8*)gImage_cokie);//显示蜜罐
	
	while(1) 
	{	
		
		rx=rand()%6;                                          //生成香蕉随机位置
		for(i=56;i<=320;i++){                                 //循环控制下落
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //显示蜜罐
			image_display(rx*40,i,(u8*)gImage_bann);            //显示香蕉
			if(i>=96){
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
				image_display(rx*40,i,(u8*)gImage_bblack);        //减生命效果
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //刷新蜜罐显示
				score+=1;
				LCD_ShowxNum(56,0,score,2,16,0);                  //刷新分数
				image_display(rx*40,240,(u8*)gImage_pone);        //显示+1效果
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //刷新蜜罐显示
				delay_ms(500);                                    //+1效果显示时间
				image_display(rx*40,240,(u8*)gImage_bblack);      //清除+1效果
				break;
			}
			if(i==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //重新显示蜜罐
			}
			delay_us(speed_level);	                            //控制下落速度
		}
		delay_ms(600);                                        //控制两次下落之间间隔
		
		rx=rand()%6;                                          //生成炸弹随机位置
		for(j=56;j<=320;j++){                                 //循环控制下落
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //显示蜜罐
			image_display(rx*40,j,(u8*)gImage_bomb);            //显示炸弹
			if(j>=96){
				image_display(rx*40,j-40,(u8*)gImage_bblack);     //黑屏清除
			}
			if(j==240){                                         //判断是否吃到
				if(rx*40==cookie_pos){
					if(life==3) image_display(192,0,(u8*)gImage_blacks);
					if(life==2) image_display(208,0,(u8*)gImage_blacks);
					image_display(rx*40,240,(u8*)gImage_mone);      //显示-1效果
					image_display(cookie_pos,280,(u8*)gImage_cokie);//刷新蜜罐显示
					delay_ms(500);                                  //-1效果显示时间
					image_display(rx*40,240,(u8*)gImage_bblack);    //清除-1效果
					if(life==1){
						image_display(224,0,(u8*)gImage_blacks);
						image_display(20,100,(u8*)gImage_gg);         //显示游戏结束画面
						for(;;);
					}
					life-=1;
					break;
				}
			}
			if(j>=241 && cookie_pos==rx*40){
				if(life==3) image_display(192,0,(u8*)gImage_blacks);
				if(life==2) image_display(208,0,(u8*)gImage_blacks);
				image_display(rx*40,j,(u8*)gImage_bblack);       //减生命效果
				image_display(cookie_pos,280,(u8*)gImage_cokie); //刷新蜜罐显示
				image_display(rx*40,240,(u8*)gImage_mone);       //显示-1效果
				image_display(cookie_pos,280,(u8*)gImage_cokie); //刷新蜜罐显示
				delay_ms(500);                                   //-1效果显示时间
				image_display(rx*40,240,(u8*)gImage_bblack);     //清除-1效果
				if(life==1){
					image_display(224,0,(u8*)gImage_blacks);
					image_display(20,100,(u8*)gImage_gg);          //显示游戏结束画面
					for(;;);
				}
				life-=1;
				break;
			}
			if(j==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie); //重新显示蜜罐
			}
			delay_us(speed_level);	                           //控制下落速度
		}
		delay_ms(600);                                       //控制两次下落之间间隔
		
	}
	
}

