#ifndef SERVO_H_
#define SERVO_H_

#include"../../LIB/LSTD_TYPES.h"

void H_ServoInit(void);
void H_ServoSetAngle(u16);
void H_ServoStart(void);
void H_ServoStop(void);

#endif /* SERVO_H_ */
