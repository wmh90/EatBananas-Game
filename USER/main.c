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
	delay_init();	    	                            //��ʱ������ʼ��	  
	uart_init(9600);  	                            //���ڳ�ʼ��Ϊ9600
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����2
	EXTIX_Init();	      	                          //�ⲿ�жϳ�ʼ��
	LED_Init();			                                //LED��ʼ��
	KEY_Init();                                     //��ʼ���밴�����ӵ�Ӳ���ӿ�
 	LCD_Init(); 	                                  //LCD��ʼ��					 
	delay_ms(1500);		                              //�ȴ�1.5��	  
	LCD_Clear(BLACK);
	 
	image_display(15,0,(u8*)gImage_geek);//��ָ����ַ��ʾͼƬ	
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
	image_display(200,16,(u8*)gImage_canno);         //��ʾ�Ϸ���*6
	
	image_display(100,0,(u8*)gImage_geeks);          //��ʾ�Ϸ�Geek
	 
	image_display(192,0,(u8*)gImage_heart);          //��ʾ����
	image_display(208,0,(u8*)gImage_heart);
	image_display(224,0,(u8*)gImage_heart);
	
	LCD_ShowString(0,0,200,16,16,"Score: ");        //��ʾScore�ַ���
	LCD_ShowxNum(60,0,score,2,16,0);                //��ʾ��������
	image_display(cookie_pos,280,(u8*)gImage_cokie);//��ʾ�۹�
	
	while(1) 
	{	
		
		rx=rand()%6;                                          //�����㽶���λ��
		for(i=56;i<=320;i++){                                 //ѭ����������
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //��ʾ�۹�
			image_display(rx*40,i,(u8*)gImage_bann);            //��ʾ�㽶
			if(i>=96){
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
				image_display(rx*40,i,(u8*)gImage_bblack);        //������Ч��
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //ˢ���۹���ʾ
				score+=1;
				LCD_ShowxNum(56,0,score,2,16,0);                  //ˢ�·���
				image_display(rx*40,240,(u8*)gImage_pone);        //��ʾ+1Ч��
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //ˢ���۹���ʾ
				delay_ms(500);                                    //+1Ч����ʾʱ��
				image_display(rx*40,240,(u8*)gImage_bblack);      //���+1Ч��
				break;
			}
			if(i==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie);  //������ʾ�۹�
			}
			delay_us(speed_level);	                            //���������ٶ�
		}
		delay_ms(600);                                        //������������֮����
		
		rx=rand()%6;                                          //����ը�����λ��
		for(j=56;j<=320;j++){                                 //ѭ����������
			image_display(cookie_pos,280,(u8*)gImage_cokie);    //��ʾ�۹�
			image_display(rx*40,j,(u8*)gImage_bomb);            //��ʾը��
			if(j>=96){
				image_display(rx*40,j-40,(u8*)gImage_bblack);     //�������
			}
			if(j==240){                                         //�ж��Ƿ�Ե�
				if(rx*40==cookie_pos){
					if(life==3) image_display(192,0,(u8*)gImage_blacks);
					if(life==2) image_display(208,0,(u8*)gImage_blacks);
					image_display(rx*40,240,(u8*)gImage_mone);      //��ʾ-1Ч��
					image_display(cookie_pos,280,(u8*)gImage_cokie);//ˢ���۹���ʾ
					delay_ms(500);                                  //-1Ч����ʾʱ��
					image_display(rx*40,240,(u8*)gImage_bblack);    //���-1Ч��
					if(life==1){
						image_display(224,0,(u8*)gImage_blacks);
						image_display(20,100,(u8*)gImage_gg);         //��ʾ��Ϸ��������
						for(;;);
					}
					life-=1;
					break;
				}
			}
			if(j>=241 && cookie_pos==rx*40){
				if(life==3) image_display(192,0,(u8*)gImage_blacks);
				if(life==2) image_display(208,0,(u8*)gImage_blacks);
				image_display(rx*40,j,(u8*)gImage_bblack);       //������Ч��
				image_display(cookie_pos,280,(u8*)gImage_cokie); //ˢ���۹���ʾ
				image_display(rx*40,240,(u8*)gImage_mone);       //��ʾ-1Ч��
				image_display(cookie_pos,280,(u8*)gImage_cokie); //ˢ���۹���ʾ
				delay_ms(500);                                   //-1Ч����ʾʱ��
				image_display(rx*40,240,(u8*)gImage_bblack);     //���-1Ч��
				if(life==1){
					image_display(224,0,(u8*)gImage_blacks);
					image_display(20,100,(u8*)gImage_gg);          //��ʾ��Ϸ��������
					for(;;);
				}
				life-=1;
				break;
			}
			if(j==320){
				image_display(cookie_pos,280,(u8*)gImage_cokie); //������ʾ�۹�
			}
			delay_us(speed_level);	                           //���������ٶ�
		}
		delay_ms(600);                                       //������������֮����
		
	}
	
}

