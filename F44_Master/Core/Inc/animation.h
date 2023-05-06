/*
 * animation.h
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */

#ifndef INC_ANIMATION_H_
#define INC_ANIMATION_H_

#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "stm32f4xx_hal.h"

#define PAGE1				(0x0)
#define PAGE2				(0x1)
#define HOUR				(0x0)
#define MINUTE				(0x1)
#define SECOND				(0x2)
#define LOCK_OFF			(0x0)
#define LOCK_ON				(0x1)
#define ALARM_OFF			(0x0)
#define ALARM_ON			(0x1)

typedef struct{
	uint8_t lock;
	uint8_t pageNumber;
	uint8_t location;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t alarm;
}PAGE_SETTING;

extern PAGE_SETTING pageSetting;

		/*Timer variables*/
extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_AlarmTypeDef sAlarm;

void MD_Intro(void);
void MD_Start();
void MD_TimeSet(void);
void MD_SetAlarm();
void MD_TimerConfig();
void MD_MainMenu();
uint8_t MD_IsAlarm();




#endif /* INC_ANIMATION_H_ */
