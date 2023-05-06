/*
 * canTask.c
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */


#include "canTask.h"


void irfCanTask(uint32_t code)
{
	/*Close and back command*/
	switch(code)
	{
	case(IRF_STAR):									//start command
		MD_Intro();									//intro animation
		pageSetting.lock = LOCK_OFF;				// unlock the main screen
	break;

	/*close the screen and back*/
	case(IRF_SQUARE):								//if page == 1 close else back to main menu
		if(pageSetting.pageNumber == PAGE1)
		{
			ILI9341_FillScreen(BLACK);				//close command
			pageSetting.lock = LOCK_ON;
			canTx(CAR_CLOSE);
		}
		else
		{
			MD_MainMenu();
			pageSetting.pageNumber = PAGE1;			//back command
		}
	break;

	/*alarm page and alarm page*/
	case(IRF_OK):									//if page == 1 open alarm screen else save alar
		if(pageSetting.pageNumber == PAGE1)
			MD_TimerConfig();						//alarm page
		else
		{
			MD_SetAlarm();
			pageSetting.pageNumber = PAGE1;			//alarm save
			pageSetting.alarm = ALARM_ON;
			MD_MainMenu();

		}
	break;

	case(IRF_UP):									//using to set timer
		if(pageSetting.location == HOUR)
		{
			char txTime[20];
			pageSetting.hour = (pageSetting.hour + 1) % 13;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
		else if(pageSetting.location == MINUTE)
		{
			char txTime[20];
			pageSetting.minute = (pageSetting.minute + 1) % 61;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
		else{
			char txTime[20];
			pageSetting.second = (pageSetting.second + 1) % 61;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
	break;

	case(IRF_DOWN):									//using to set timer
		if(pageSetting.location == HOUR)
		{
			char txTime[20];
			if(pageSetting.hour != 0)
				pageSetting.hour--;
			else
				pageSetting.hour = 12;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
		else if(pageSetting.location == MINUTE)
		{
			char txTime[20];
			if(pageSetting.minute != 0)
				pageSetting.minute--;
			else
				pageSetting.minute = 60;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
		else{
			char txTime[20];
			if(pageSetting.second != 0)
				pageSetting.second--;
			else
				pageSetting.second = 60;
			sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour,pageSetting.minute, pageSetting.second);
			ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
		}
	break;

	case(IRF_RIGHT):								//using to set timer
				pageSetting.location = (pageSetting.location + 1) % 3;
	break;

	case(IRF_LEFT):									//using to set timer
		if(pageSetting.location != 0)
			pageSetting.location -= 1;
		else
			pageSetting.location = SECOND;
	break;

	}
}

void canTx(uint8_t msg)		// can transmit line
{
	txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;	//standart can
	txMessage.frame.id = 0x0A;
	txMessage.frame.dlc = 1;
	txMessage.frame.data0 = msg;
	CANSPI_Transmit(&txMessage);
}


