/*
VRTR.cpp - Video Remoto en Tiempo Real.
v1.0

Copyright © 2019-2022 Francisco Rafael Reyes Carmona.
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

#include <Arduino.h>
#include <LowPower.h>
#include <Vcc.h>
#include <ACS712_Hall.h>
#include <ThermistorNTC.h>
#include <TinyBattery.h>
#include "config.h"  
#include "display.h"

Vcc vcc(1.0);
ACS712 sensor_acs712(AMP, ACS712_05B, VCC);
Thermistor thermistor0(/* PIN */      TEMP,
                      /* RESISTOR */  21900L,
                      /* NTC 25ºC */  9950L,
                      /* A */         3354016e-9,
                      /* B */         2569850e-10,
                      /* C */         2620131e-12,
                      /* D */         6383091e-14,
                      /* Vref */      VCC);

Thermistor thermistor1(/* PIN */      TEMP_AMB,
                      /* RESISTOR */  21900L,
                      /* NTC 25ºC */  9950L,
                      /* BETA */      4190.0,
                      /* Vref */      VCC);

TinyBattery Battery(/* PIN */           BATT,
                    /* VccREF */        VCC,
                    /* RESISTOR_VDD */  147900,
                    /* RESISTOR_GND */  32300,
                    /* MIN_VOLT */      16.00,
                    /* MAX_VOLT */      25.90);

// Declaramos variables globales.
volatile bool pwr_switch = false;
volatile bool standby = true;
volatile bool needcharge = true;

float battery_value;
float battery_amp_value;
byte battery_percent;
float ts832_temp_value;
float temp_amb_value;

float vcc_value = VCC;

void power_ts832() {
  pwr_switch = digitalRead(PWR);
  digitalWrite(PWR_TS832, pwr_switch);
  digitalWrite(PWR_TEMP, pwr_switch);
  digitalWrite(PWR_TEMP_AMB, pwr_switch);
/*  #if defined(HX1230_96X68) 
      digitalWrite(LCD_BL, pwr_switch);
  #endif
 */
  if (pwr_switch) {
    ts832_temp_value = thermistor0.fastTempCelsius();
    temp_amb_value = thermistor1.fastTempCelsius();
  }
}

bool stand_by(byte battery_percent) {
  bool standby;
  (!battery_percent) ? standby = true : standby = false;
  return standby;
}

void setup() {
  u8g2.begin();
#if defined(HX1230_96X68)
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  u8g2.setContrast(150);
#endif
  // Logo de inicio.
  drawlogo();

#ifdef DEBUG  
  Serial.begin(SERIALBAUD);
#endif

  pinMode(BATT, INPUT);
  pinMode(AMP, INPUT);

#if defined(__LGT8F_SSOP20__)     // Para inicializar SWC (A6) y SWD (A7) como entradas analógicas (ADC).
  pinMode(D22, INPUT);            // Inicia el pin ADC6 -> TEMP.
  pinMode(D23, INPUT);            // Inicia el pin ADC7 -> TEMP_AMB.
#else
  pinMode(TEMP, INPUT);
  pinMode(TEMP_AMB, INPUT);
#endif

  pinMode(PWR_TS832, OUTPUT);
  digitalWrite(PWR_TS832, LOW);

//  pinMode(PWR, INPUT_PULLUP);
  pinMode(PWR, INPUT);
  attachInterrupt(digitalPinToInterrupt(PWR), power_ts832, CHANGE);

  pinMode(PWR_TEMP, OUTPUT);
  digitalWrite(PWR_TEMP, LOW);
  pinMode(PWR_TEMP_AMB, OUTPUT);
  digitalWrite(PWR_TEMP, LOW);
  //pinMode(PWM, OUTPUT);
  //digitalWrite(PWM, LOW);

  //pinMode(PWM_REV, INPUT);
  
  delay(500);

  mesg("Setting...");

  for(uint8_t i = 32; i--;){
    vcc_value = vcc.Read_Volts();
  }
  Battery.setVref(vcc_value);
  sensor_acs712.setVref(vcc_value);
  thermistor0.setVref(vcc_value);
  thermistor1.setVref(vcc_value);
  
  delay(400);

  mesg("Wait...");
  
  for(uint8_t i = 8;i--;) {
    battery_value = Battery.GetVoltage();
    battery_amp_value = sensor_acs712.getCurrent_DC_LowNoise();
    battery_percent = Battery.GetChargeLevel();
    ts832_temp_value = thermistor0.fastTempCelsius();
    temp_amb_value = thermistor1.fastTempCelsius();
  }
  
  if (battery_value > 16.5) {
      power_ts832();
      standby = false;
      needcharge = false;
    }
}

void loop() {
  battery_value = Battery.GetVoltage();
  battery_percent = Battery.GetChargeLevel();
  battery_amp_value = sensor_acs712.getCurrent_DC_LowNoise();

  //battery_value < 16.5 ? standby = true : standby = stand_by(battery_percent);
  standby = stand_by(battery_percent);

  if (standby &&  battery_amp_value > 0) needcharge = true;
//  else if ((!standby) && (battery_amp_value < -1000) && (battery_value > 17.0)) needcharge = false;
  else if ((!standby) && (battery_value > 17.0)) needcharge = false;
  
  if (pwr_switch && !standby && !needcharge) {
      digitalWrite(PWR_TS832, HIGH);
      digitalWrite(PWR_TEMP, HIGH);
      digitalWrite(PWR_TEMP_AMB, HIGH);
      #if defined(HX1230_96X68) 
          digitalWrite(LCD_BL, HIGH);
        #endif
      
      ts832_temp_value = thermistor0.fastTempCelsius();
      temp_amb_value = thermistor1.fastTempCelsius();

      printdata(battery_value, battery_amp_value, battery_percent,
                temp_amb_value, ts832_temp_value);
              
      LowPower.idle(SLEEP_500MS,ADC_ON,TIMER2_OFF,TIMER1_OFF,TIMER0_OFF,SPI_ON,USART0_ON,TWI_ON);
      } else if (!pwr_switch && !standby && !needcharge) {

        drawlogo();
        
        #if defined(HX1230_96X68) 
          delay(2000);
          digitalWrite(LCD_BL, LOW);
        #endif
        
        LowPower.idle(SLEEP_500MS,ADC_ON,TIMER2_OFF,TIMER1_OFF,TIMER0_OFF,SPI_ON,USART0_ON,TWI_ON);
      } else if (standby || needcharge) {
        digitalWrite(PWR_TS832, LOW);
        digitalWrite(PWR_TEMP, LOW);
        digitalWrite(PWR_TEMP_AMB, LOW);
        
        drawlowbat();
//        capturedata();   // For test display.
        
        #if defined(HX1230_96X68) 
          delay(2000);
          digitalWrite(LCD_BL, LOW);
        #endif
        LowPower.idle(SLEEP_500MS,ADC_ON,TIMER2_OFF,TIMER1_OFF,TIMER0_OFF,SPI_ON,USART0_ON,TWI_ON);
      } else {
        mesg("ERROR!!!");
        
        #if defined(HX1230_96X68) 
          delay(2000);
          digitalWrite(LCD_BL, LOW);
        #endif
        LowPower.idle(SLEEP_FOREVER,ADC_ON,TIMER2_OFF,TIMER1_OFF,TIMER0_OFF,SPI_ON,USART0_ON,TWI_ON);
      }
      
#ifdef DEBUG
  Serial.print(battery_value,4);
  Serial.print(" V, ");
  Serial.print(battery_amp_value, 0);
  Serial.print(" mA, ");
  Serial.print(battery_percent);
  Serial.print(" %. Vcc, ");
  if(pwr_switch && !standby && !needcharge) {
     Serial.print(temp_amb_value);
     Serial.print(" ºC Amb., ");
     Serial.print(ts832_temp_value);
     Serial.print(" ºC TS832, ");
     Serial.print("-> TS832 PWR: ON , ");
  } else {
    Serial.print("-> TS832 PWR: OFF, ");
  }
  standby ? Serial.print("STANDBY: ON") : Serial.print("STANDBY: OFF");
  Serial.println("");
#endif
}
