#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h" 
#include "image2lcd.h"
#include "stdlib.h"
#include "key.h"
#include "exti.h"



extern const u8 gImage_bann[];//����ͼƬ�����ļ�
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

void show_cookie(int show_cookie)                            //ˢ���۹�λ�ú���
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
	delay_init();	    	                            //��ʱ������ʼ��	  
	uart_init(9600);  	                            //���ڳ�ʼ��Ϊ9600
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����2
	EXTIX_Init();	      	                          //�ⲿ�жϳ�ʼ��
	LED_Init();			                                //LED��ʼ��
	KEY_Init();                                     //��ʼ���밴�����ӵ�Ӳ���ӿ�
 	LCD_Init(); 	                                  //LCD��ʼ��					 
	delay_ms(1500);		                              //�ȴ�1.5��	  
	LCD_Clear(BLACK);
	image_display(0,  0,(u8*)gImage_canno);         //
	image_display(40, 0,(u8*)gImage_canno);         //
	image_display(80, 0,(u8*)gImage_canno);         //
	image_display(120,0,(u8*)gImage_canno);         //
	image_display(160,0,(u8*)gImage_canno);         //
	image_display(200,0,(u8*)gImage_canno);         //��ʾ�Ϸ���*6
		
	LCD_ShowString(0,0,200,16,16,"Score: ");        //��ʾScore�ַ���
	LCD_ShowxNum(60,0,score,2,16,0);                //��ʾ��������
	image_display(cookie_pos,280,(u8*)gImage_cokie);//��ʾ�۹�
	
	while(1) 
	{	
		
		rx=rand()%6;                                          //�����㽶���λ��
		for(i=40;i<=320;i++){                                 //ѭ����������
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //��ʾ�۹�
			image_display(rx*40,i,(u8*)gImage_bann);            //��ʾ�㽶
			if(i>=80){
				image_display(rx*40,i-40,(u8*)gImage_bblack);     //�����һ����ʾ
			}
			if(i==240){                                         //�ж��Ƿ�Ե�
				if(rx*40==cookie_pos){
				  score+=1;
					LCD_ShowxNum(56,0,score,2,16,0);                //ˢ�·���
					image_display(rx*40,240,(u8*)gImage_pone);      //��ʾ+1Ч��
					image_display(cookie_pos,280,(u8*)gImage_cokie);//ˢ���۹���ʾ
					delay_ms(500);                                  //+1Ч����ʾʱ��
					image_display(rx*40,240,(u8*)gImage_bblack);    //���+1Ч��
					break;
				}
			}
			if(i>=241 && cookie_pos==rx*40){
				image_display(rx*40,i,(u8*)gImage_bblack);
				image_display(cookie_pos,280,(u8*)gImage_cokie);
				break;
			}
			if(i==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //������ʾ�۹�
			}
			delay_ms(10);	                                      //���������ٶ�
			show_cookie(show_cookie_en);
		}
		delay_ms(600);                                        //������������֮����
		
		rx=rand()%6;                                          //����ը�����λ��
		for(j=40;j<=320;j++){                                 //ѭ����������
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //��ʾ�۹�
			image_display(rx*40,j,(u8*)gImage_bomb);            //��ʾը��
			if(j>=80){
				image_display(rx*40,j-40,(u8*)gImage_bblack);     //�������
			}
			if(j==240){                                         //�ж��Ƿ�Ե�
				if(rx*40==cookie_pos){
				  score-=1;
					if(score<0) score=0;                            //��������С����
					LCD_ShowxNum(56,0,score,2,16,0);                //ˢ�·���
					image_display(rx*40,240,(u8*)gImage_mone);      //��ʾ-1Ч��
					image_display(cookie_pos,280,(u8*)gImage_cokie);//ˢ���۹���ʾ
					delay_ms(500);                                  //-1Ч����ʾʱ��
					image_display(rx*40,240,(u8*)gImage_bblack);    //���-1Ч��
					break;
				}
			}
			if(j>=241 && cookie_pos==rx*40){
				image_display(rx*40,j,(u8*)gImage_bblack);
				image_display(cookie_pos,280,(u8*)gImage_cokie);
				break;
			}
			if(j==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie); //������ʾ�۹�
			}
			delay_ms(10);	                                     //���������ٶ�
			show_cookie(show_cookie_en);
		}
		delay_ms(600);                                       //������������֮����
		
	}
	
}

