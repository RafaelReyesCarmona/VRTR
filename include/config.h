/*
config.h - Video Remoto en Tiempo Real. Config file.
v1.0

Copyright © 2020-2022 Francisco Rafael Reyes Carmona.
All rights reserved.
rafael.reyes.carmona@gmail.com
_______________________________________________________________________
|                                                                     |
|  No part of this work may be distributed, reproduced, copied,       |
|  stored in a retrieval system, or transcribed in any form or        |
|  by any means, electronic or mechanical, beyond the terms of the    |
|  License.                                                           |
|                                                                     |
|  This code is distributed "as is" without warranty of any kind,     |
|  including warranties of merchantability, fitness for a particular  |
|  purpose, or fitness for a particular purpose.                      |
|                                                                     |
|  The author shall not be liable for any damages of any kind arising |
|  out of the use, including loss of business or loss of data.        |
|_____________________________________________________________________|

  This file is part of VRTR Project.

  VRTR Project is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  VRTR Project is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with VRTR Project.  If not, see <https://www.gnu.org/licenses/>.

*/

#define SDD1306_128X64        // Define para usar pantalla OLED 0.96" I2C 128x64 pixels
//#define HX1230_96X68        // Define para usar pantalla HX1230 96x68 pixels LCD SPI(Nokia simil.) 

//#define DEBUG           // Activar para obtener datos de depuración por Serial.

// Definiciones para cálculo del Batt%, TempºC, Corriente y Temp.AmbºC.
#define BATT        A0
#define AMP         A1
#if defined(__LGT8F_SSOP20__)
  #define TEMP      A6
  #define TEMP_AMB  A7
#else
  #define TEMP        A2
  #define TEMP_AMB    A3
#endif
                          // A4 -> SDA ; A5 -> SCL for display.
#define PWR           3   // Pin para attachInterrupt.
#define PWR_TS832     2   // Definimos pin para controlar encendido transmisor.
#define PWR_TEMP      8   // Definimos pin para controlar encendido del sensor temperatura interna.
#define PWR_TEMP_AMB  7   // Definimos pin para controlar encendido del sensor temperatura ambiente.
#define PWM           5   // Definimos pin para controlar PWM del ventilador.
#define PWM_REV       6   // Definimos pin para conocer revoluciones del ventilador,
#define CHANNEL       17  // Definimos canal del transmisor TS832.

#define VCC 5.035           // Tensión VCC de alimentación. ~5V.

#define SERIALBAUD 57600   // Velocidad conexion UART serial.

