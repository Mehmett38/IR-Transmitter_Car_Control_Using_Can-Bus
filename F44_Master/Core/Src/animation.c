/*
 * animation.c
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */


#include "animation.h"
#include "string.h"
#include "stdio.h"
#include "canTask.h"


PAGE_SETTING pageSetting;

void MD_Intro(void)					// intro animation
{
	canTx(CAR_OPEN);
	ILI9341_SetRotation(3);
	ILI9341_FillScreen(BLACK);
	for(uint8_t i = 0; i < 10; i++)
	{
		ILI9341_DrawVLine(i*16, 0, 240, CYAN);
		ILI9341_DrawHLine(0, i*12, 320, CYAN);
		ILI9341_DrawVLine(320-i*16, 0, 240, CYAN);
		ILI9341_DrawHLine(0, 240-i*12, 320, CYAN);
		HAL_Delay(175);
	}

	MD_Start();
}

void MD_Start()						//first scren
{
	ILI9341_FillScreen(CYAN);

#define START_POINT			125
#define AUDI_DELAY			600

	char dateTx[20];
	sprintf(dateTx,"%02d/%02d/20%02d",sDate.Date,sDate.Month,sDate.Year);
	ILI9341_DrawText(dateTx, FONT3, 240, 10, BLACK, CYAN);

	ILI9341_DrawHollowCircle(125, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAY);
	ILI9341_DrawHollowCircle(START_POINT + 25, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAY);
	ILI9341_DrawHollowCircle(START_POINT + 50, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAY);
	ILI9341_DrawHollowCircle(START_POINT + 75, 100, 20, BLACK);
	HAL_Delay(800);
}

void MD_MainMenu()
{
	ILI9341_FillScreen(CYAN);

#define START_POINTMain		125
#define AUDI_DELAYMain		100

	char dateTx[20];
	sprintf(dateTx,"%02d/%02d/20%02d",sDate.Date,sDate.Month,sDate.Year);
	ILI9341_DrawText(dateTx, FONT3, 240, 10, BLACK, CYAN);

	ILI9341_DrawHollowCircle(125, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAYMain);
	ILI9341_DrawHollowCircle(START_POINT + 25, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAYMain);
	ILI9341_DrawHollowCircle(START_POINT + 50, 100, 20, BLACK);
	HAL_Delay(AUDI_DELAYMain);
	ILI9341_DrawHollowCircle(START_POINT + 75, 100, 20, BLACK);
	HAL_Delay(200);
}

void MD_TimeSet(void)			//set the time
{
	sTime.Hours = 12;
	sTime.Minutes = 30;
	sTime.Seconds = 0x0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_MAY;
	sDate.Date = 0x6;
	sDate.Year = 23;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

void MD_TimerConfig()
{
	ILI9341_FillScreen(CYAN);
	ILI9341_DrawText("ALARM KUR : ", FONT4, 50, 110, RED, CYAN);
	char txTime[20];
	sprintf(txTime,"%02d:%02d:%02d",pageSetting.hour, pageSetting.minute, pageSetting.minute);
	ILI9341_DrawText(txTime, FONT4, 190, 110, RED, CYAN);
	pageSetting.pageNumber = PAGE2;
}

void MD_SetAlarm()			//set alarm structure *Note interrupt does not work work in polling mode
{
	pageSetting.alarm = ALARM_ON;
	HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
	sAlarm.AlarmTime.Hours = pageSetting.hour;
	sAlarm.AlarmTime.Minutes = pageSetting.minute;
	sAlarm.AlarmTime.Seconds = pageSetting.second;
	sAlarm.AlarmTime.SubSeconds = 0x0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = 0x1;
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

uint8_t MD_IsAlarm()		//return 1 if come alarm time
{
	if(sTime.Hours == sAlarm.AlarmTime.Hours && sTime.Minutes == sAlarm.AlarmTime.Minutes && sAlarm.AlarmTime.Seconds == sTime.Seconds && pageSetting.alarm == ALARM_ON)
	{
		pageSetting.alarm = ALARM_OFF;
		return 1;
	}
	else
		return 0;
}
