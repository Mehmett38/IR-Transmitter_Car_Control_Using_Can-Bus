/*
 * canTask.h
 *
 *  Created on: May 5, 2023
 *      Author: Mehmet Dincer
 */

#ifndef INC_CANTASK_H_
#define INC_CANTASK_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include "IRF.h"
#include "animation.h"
#include "string.h"
#include "stdio.h"
#include "CANSPI.h"

extern uCAN_MSG txMessage;
extern uCAN_MSG rxMessage;

/*Can message macros*/
#define CAR_CLOSE			(0x5)
#define CAR_OPEN			(0x6)
#define ALARM_ENABLE		(0x7)

void irfCanTask(uint32_t code);
void canTx(uint8_t msg);


#endif /* INC_CANTASK_H_ */
