#ifndef CRYSTALCLOCK_H_
#define CRYSTALCLOCK_H_


#define CORE_CLOCK				 (48000000)
#define PERIPHERAL_BUS_CLOCK (CORE_CLOCK/2)

void ClockInit();

#endif /* CRYSTALCLOCK_H_ */
