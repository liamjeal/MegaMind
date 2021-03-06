/*
  Copyright (c) 2013 MegaMind.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern int pinMode( uint32_t ulPort, uint32_t ulPin, uint32_t ulMode )
{
	uint32_t mode = 0;
	switch(ulMode)
	{
		case INPUT:
//			mode = xGPIO_DIR_MODE_IN;
			mode = GPIO_TYPE_IN_FLOATING | GPIO_IN_SPEED_FIXED;
		break;

		case INPUT_PULLUP:
			mode = GPIO_TYPE_IN_WPU_WPD | GPIO_IN_SPEED_FIXED;
			digitalWrite(ulPort, ulPin, HIGH);
		break;

		case INPUT_PULLDOWN:
			mode = GPIO_TYPE_IN_WPU_WPD | GPIO_IN_SPEED_FIXED;
			digitalWrite(ulPort, ulPin, LOW);
		break;

		case OUTPUT:
			mode = GPIO_TYPE_OUT_STD | GPIO_OUT_SPEED_50M;
		break;

		//wrong mode
		default:
			return 0;
		break;
	}

	xSysCtlPeripheralEnable(g_APinDescription[ulPort][ulPin].ulPeripheralPortId);
	GPIODirModeSet(
			g_APinDescription[ulPort][ulPin].ulPortBase,
			ulPin,
			mode & 0xC, mode & 0x3);

	return 1;
}

extern void digitalWrite( uint32_t ulPort, uint32_t ulPin, uint32_t ulVal )
{
	xGPIOPinWrite(
			g_APinDescription[ulPort][ulPin].ulPortBase,
			g_APinDescription[ulPort][ulPin].ulPin,
			ulVal);
}

extern int digitalRead( uint32_t ulPort, uint32_t ulPin )
{
	return bitRead(xGPIOPinRead(
			g_APinDescription[ulPort][ulPin].ulPortBase,
			g_APinDescription[ulPort][ulPin].ulPin), ulPin);
}

#ifdef __cplusplus
}
#endif

