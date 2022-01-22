#ifndef MICROSTEP_H
#define MICROSTEP_H

typedef enum Microstep
{
	Microstep_first,

	Microstep_0 = Microstep_first,
	Microstep_1,
	Microstep_2,
	Microstep_3,

	Microstep_count
} Microstep;

#endif
