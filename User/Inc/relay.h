/*
 * relay.h
 *
 *  Created on: Oct 16, 2026
 *      Author: jiangjikang
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_
#include <stdint.h>

#if 0
    #define MAX_RANGE  50
#elif 1
    #define MAX_RANGE  85
#else
    #define MAX_RANGE  150
#endif

uint16_t flowV_to_relayV(uint8_t flowV, float *relayV);








#endif /* INC_RELAY_H_ */
