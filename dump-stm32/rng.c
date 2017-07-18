#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/stm32/f2/rng.h>

#include "rng.h"

uint32_t random32(void)
{
	static uint32_t last = 0, new = 0;
	while (new == last) {
		if (((RNG_SR & (RNG_SR_SEIS | RNG_SR_CEIS)) == 0) && ((RNG_SR & RNG_SR_DRDY) > 0)) {
			new = RNG_DR;
		}
	}
	last = new;
	return new;
}

