//============================================================================
//****************************************************************************
//**																		**
//**  PROJECT  :	AS350 ATS版												**
//**  PRODUCT  :	AS350													**
//**  FILE	   : 	Main.c													**
//**  MODULE   :	main()													**
//**  VERSION  : 	V1.00													**
//**  DATE	   : 	2009/04/20												**
//**  EDITOR   :	James Hsieh												**
//** 																		**
//**  Copyright(C) 2009 SymLink Corporation. All rights reserved.			**
//**																		**
//****************************************************************************
//============================================================================
#include <string.h>
#include "posapi.h"
#include "dss.h"
#include "GlobalVar.h"
#include "option.h"
#include "constxp0.h"
#include "constxp1.h"
#include "emvkdata.h"
#include "DSS2API.H"
#include "func.h"
#include "LITEAPI_EX.h"	//	Black	2016/10/21
#include "LCDTFTAPI.h"
#include "Global.h"

//#include "Thonk-CCW.c"

/* --------------------------------------------------------------------------
Name:     Main Program Entry
--------------------------------------------------------------------------*/

//-------------------Global Var---------------------------------
UCHAR direction = 0; // 0=up 1=down 2=left 3=right
UCHAR speedvar = 10;
//--------------------------------------------------------------



struct snakebody                    // Steven 2019/08/08  貪食蛇Struct
{
    UINT x,y;                        //待移除，新增(X,Y)
    struct snakebody *next;
}__attribute__((packed));;
typedef struct snakebody Snakebody;

struct snakebody_Manager              // Steven 2019/08/08   queue管理員
{
    UINT         count;
    Snakebody   *front;  
    Snakebody   *rear;  
}__attribute__((packed));;
typedef struct snakebody_Manager Snakebody_Manager; 

void ok_delay(UCHAR *OK_str, UINT tick_num,UCHAR *status)    //Steven 顯示OK順序
{
	DispText(OK_str,LINE15,6,4,FONT0);
	DispText(status,LINE15,12,1,FONT0);
	delay(tick_num); //1sec
}

void AddSnakebody(Snakebody_Manager *p,UINT x,UINT y)  // Steven 2019/08/08 +蛇身體
{	
    Snakebody *pSnake;
    pSnake = (Snakebody *) malloc (sizeof(Snakebody));

    pSnake->x = x;
    pSnake->y = y;
       
    //printf("p->count : %d \n",p->count);

    if (p->count == 0)		//Queue管理邏輯
    {		
		p->front = pSnake;			
	}       								
    else
	{		
       p->rear->next = pSnake;      
	} 

    p->rear = pSnake;
    p->count ++;
    
}

/*void Del_Snakebody(Snakebody_Manager *p,UINT x,UINT y)
{
	p->front;
	p->rear;

}*/

void putsnake()
{
	for(UINT i=0;i<5;i++)		//預設蛇的長度6單位
	{
		AddSnakebody(Snakebody_Manager *p,UINT x,UINT y);
	}
	
}

void Play()
{
	putsnake();

	UCHAR key;

	delay(speedvar); //控制遊戲速度  default為10

	move(x,y);
	if(GetKey())
	{	            
	    switch(key=GetKey())         
  	    {           
	       case UP:
	       	if(y>0)                      //邊界 注意每單位行2px
			   	ChangeDirection(UP);        
	       break;
		           
	       case DOWN:
	       	if(y<160)                      //邊界 
			   	ChangeDirection(DOWN);             
	       break; 
		          
	       case LEFT:
	       	if(x>0)                       //邊界 
			   	ChangeDirection(LEFT);              
	       break; 
		          
	       case RIGHT:
	       	if(x<120)                       //邊界 
			   	ChangeDirection(RIGHT);               
	       break; 
		}
	}
		

	result();
}

void Option()
{
	ClrDisplay();
	DispText((UCHAR*)"            speed:1       ",LINE8,12,32,FONT0);
	//DispText((UCHAR*)"            ?????????????       ",LINE8,12,32,FONT0);
	//DispText((UCHAR*)"            ?????????????       ",LINE8,12,32,FONT0);
}

void About()
{
	ClrDisplay();

	DispText((UCHAR*)"            Author:Steven       ",LINE8,12,32,FONT0);
	DispText((UCHAR*)"            Author:Steven       ",LINE8,12,32,FONT0);
	DispText((UCHAR*)"            Author:Steven       ",LINE8,12,32,FONT0);
}		 

void menu()
{
	ClrDisplay();

	UCHAR location = 0;

	putpicture();	//snake_picture
	DispText((UCHAR*)"            =>Start             ",LINE8,12,32,FONT0);	//Default select

	DispText((UCHAR*)"              Menu              ",LINE6,12,32,FONT0);	//font? MAX 32Bytes
	DispText((UCHAR*)"              Start             ",LINE8,12,32,FONT0);	//0
	DispText((UCHAR*)"              Option            ",LINE9,12,32,FONT0);	//1
	DispText((UCHAR*)"              About             ",LINE10,12,32,FONT0);//2
	
	
	switch(GetKey())
	{
		case UP:
			if(location>0)
				switch(location)
			    {
			    	case 1:
			    		ClearLine(LINE9);
			    		DispText((UCHAR*)"              Option            ",LINE9,12,32,FONT0);
			    		location--;
			    		DispText((UCHAR*)"            =>Start             ",LINE8,12,32,FONT0);              			
		    		break;

		    		case 2:
			    		ClearLine(LINE10);
			    		DispText((UCHAR*)"              About             ",LINE10,12,32,FONT0);
			    		location--;
			    		DispText((UCHAR*)"            =>Option            ",LINE9,12,32,FONT0);              			
		    		break;
			    }		    		   	      
	    break;

	    case DOWN:
	    	if(location<2)
	    		switch(location)
			    {
			    	case 0:
			    		ClearLine(LINE8);
			    		DispText((UCHAR*)"              Start             ",LINE8,12,32,FONT0);
			    		location++;
			    		DispText((UCHAR*)"            =>Option            ",LINE9,12,32,FONT0);              			
		    		break;

		    		case 1:
			    		ClearLine(LINE9);
			    		DispText((UCHAR*)"              Option            ",LINE9,12,32,FONT0);
			    		location++;
			    		DispText((UCHAR*)"            =>About             ",LINE10,12,32,FONT0);              			
		    		break;
			    }             			
	    break;

	    case Confirm:
	    	switch(location)
			    {
			    	case 0:
			    		Play();             			
		    		break;

			    	case 1:
			    		Option();              			
		    		break;

		    		case 2:
			    		About();             			
		    		break;
			    }      			
	    break;

	}
	
}

void print(){

	gl_patch = ???;
	patDATA():
	patCHAR();
	printtxmsg_new();
}

void result()
{
	DispText((UCHAR*)"            Result              ",LINE8,12,32,FONT0); 
	DispText((UCHAR*)"            Score:80            ",LINE8,12,32,FONT0); 
	DispText((UCHAR*)"            ?????:80            ",LINE8,12,32,FONT0); 
	DispText((UCHAR*)"            FoodEaten:10        ",LINE8,12,32,FONT0);
	if(GetKey())
	{
		if(GetKey()==Confirm)
			print();
			menu();
	}
}


void ChangeDirection(UCHAR signal)
{	            
    switch(signal)  //why?        
	{           
       case UP:
       	direction = 0;       
       break;
	           
       case DOWN:
       	direction = 1;            
       break; 
	          
       case LEFT:
       	direction = 2;             
       break; 
	          
       case RIGHT:
       	direction = 3;               
       break; 
	}         
		      
}


void	APP_main( void )
{
	UCHAR	keyin, tmp[2];
	UCHAR 	result;			// alex 2003/09/09 Add 'EMVin';
	UCHAR	kbdSet[5] = {0x1c,0x3c,0x1c,0x00,0x00}; // for close mode
	UCHAR	sbuf[10];
	UCHAR	init_no[3]= {0,0,0};
	UCHAR	ADset_check;
	UCHAR	CUP_LOGON_RetryTimes;	//alex 08/06/13 CUP
	/*steven 自訂變數*/
	UCHAR	str_success[] = {0xA6,0xA8,0xA5,0x5C};
	UCHAR	str_welcome[] = {"Processing KBD Detection"};  /*"正在執行按鍵偵測"0xA5,0xBF,0xA6,0x62,0xB0,0xF5,0xA6,0xE6,0xAB,0xF6
,0xC1,0xE4,0xB0,0xBB,0xB4,0xFA*/


//	api_lan_setup_DHCP(0);	//rex 2018/06/13 強制關閉 DHCP功能 
//remark by rex 2019/02/01 [I-FES]
	if (gl_DHCP_mode == 1)
	
		api_lan_setup_DHCP(1);
	else
		api_lan_setup_DHCP(0);

	AP_INIT();	// ==== [TMS再造]-檢查之前是否有AP被啟動 ====

	//api_lcdtft_open( UCHAR deviceid, UCHAR rgbmode );

	SystemInit();		//Varios of api_opens
	SetupPageTable();
	SetupFont();		//alex 2013/02/01 DCC一段式 整合設定字型
//	api_sys_backlight(1,0xFFFFFFFF);	//	Black	2016/01/19	背光恆亮

	//DispText((UCHAR *)" 這是測試 ", LINE4, 0, 16, FONT2);
	//DispText(UCHAR *data, UCHAR line_mode, UCHAR pos, UCHAR len, UCHAR attr)

	
	forever
	{	
		menu();

			
	}

}

