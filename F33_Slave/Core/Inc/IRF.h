/*
 * IRF.h
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */

#ifndef INC_IRF_H_
#define INC_IRF_H_

#include "main.h"
#include "stm32f3xx_hal.h"

extern TIM_HandleTypeDef htim1;

/*Push state macros*/
#define IRF_FLAG_ON				(0x1)
#define IRF_FLAG_OFF			(0x0)

/*Remote controller buttons*/
#define IRF_0					(0xff9867)
#define IRF_1					(0xffa25d)
#define IRF_2					(0xff629d)
#define IRF_3					(0xffe21d)
#define IRF_4					(0xff22dd)
#define IRF_5					(0xff02fd)
#define IRF_6					(0xffc23d)
#define IRF_7					(0xffe01f)
#define IRF_8					(0xffa857)
#define IRF_9					(0xff906f)
#define IRF_STAR				(0xff6897)
#define IRF_SQUARE				(0xffb04f)
#define IRF_UP					(0xff18e7)
#define IRF_DOWN				(0xff4ab5)
#define IRF_LEFT				(0xff10ef)
#define IRF_RIGHT				(0xff5aa5)
#define IRF_OK					(0xff38c7)

		/*keep the push state and code information*/
typedef struct{
	uint8_t irfFlag;		//IRF_FLAG_ON/OFF
	uint32_t code;			//code value
}Irf_STATE;
extern Irf_STATE irfState;

		/* initialize the timer2*/
void IRF_Init();

#endif /* INC_IRF_H_ */
