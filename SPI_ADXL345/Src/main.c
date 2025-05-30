//#define STM32F401xE

#include "stm32f4xx.h"
#include <stdint.h>
#include <ADXL345.h>


double xg,yg,zg;
int16_t x,y,z;
uint8_t data_rec[6];

int main(void)
{

	ADXL_init();
	while (1)
		{
		ADXL_Read(DATA_START_ADDR,data_rec);
		x= ((data_rec[1]<<8) | data_rec[0]);
		y=((data_rec[3]<<8) | data_rec[2]);
		z= ((data_rec[5]<<8) | data_rec[4]);
		xg= (x*0.0078);
		yg= (y*0.0078);
		zg = (z*0.0078);

			for (int i=0;i<100000;i++){}
//

		}
return 0;
}
