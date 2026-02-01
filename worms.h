#ifndef WORMS_H
#define WORMS_H

#include "worm.h"

#define NUM_WORMS 4

typedef struct Worms
{
	Direction wantedNextDirection[NUM_WORMS];
	Direction nextDirection[NUM_WORMS];
	Microstep headStep[NUM_WORMS];
	Microstep tailStep[NUM_WORMS];

	bool hasNextStep[NUM_WORMS];
	Direction nextStepDirection[NUM_WORMS];
	uint16_t nextStepPosition[NUM_WORMS];

	uint8_t tailBegin[NUM_WORMS];
	uint8_t tailEnd[NUM_WORMS];
	Direction tailDirections[NUM_WORMS][0x100];
	uint16_t tailPositions[NUM_WORMS][0x100];
} Worms;

extern Worms worms;
extern uint8_t wormColors[NUM_WORMS];

#endif
