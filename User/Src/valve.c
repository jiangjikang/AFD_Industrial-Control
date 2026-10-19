/*
 * valve.c
 *
 *  Created on: Oct 15, 2026
 *      Author: jiangjikang
 */
#include "valve.h"


void open_valve(void)
{
    Y0BALLVALVE_ON();
    AIRCYLINDER_ON();
    Y4BALLVALVE_ON();
}

void close_valve(void)
{
    Y0BALLVALVE_OFF();
    AIRCYLINDER_OFF();
    Y4BALLVALVE_OFF();
}


void angle_valve_blow(void)
{
    Y2ANGLEVALVE_ON();
    Y3ANGLEVALVE_ON();
    HAL_Delay(5000);
    Y2ANGLEVALVE_OFF();
    Y3ANGLEVALVE_OFF();

}

