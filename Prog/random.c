#include <htc.h>
#include "const.h"

static long randx;

void initRandom(){
	//Load last saved random seed
	char* pRandx = (char*)&randx;

	pRandx[0] = eeprom_read(EEPROM_RAND_SEED_ADDR_B0);
	pRandx[1] = eeprom_read(EEPROM_RAND_SEED_ADDR_B1);
	pRandx[2] = eeprom_read(EEPROM_RAND_SEED_ADDR_B2);
	pRandx[3] = eeprom_read(EEPROM_RAND_SEED_ADDR_B3);
}

/**
 * Returns an number between 0 and 32767
 */
int random() {
	//Compute next random number
	randx = (randx * 1103515245L + 12345) >> 16;

	//Save random seed
	char* pRandx = (char*)&randx;
	eeprom_write(EEPROM_RAND_SEED_ADDR_B0, pRandx[0]);
	eeprom_write(EEPROM_RAND_SEED_ADDR_B1, pRandx[1]);
	eeprom_write(EEPROM_RAND_SEED_ADDR_B2, pRandx[2]);
	eeprom_write(EEPROM_RAND_SEED_ADDR_B3, pRandx[3]);

	return(int)(randx & 077777);
}