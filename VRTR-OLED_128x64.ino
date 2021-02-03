/* Copyrigth (c), 2020, Francisco Rafael Reyes Carmona.
 * Reservados todos los derechos.
 *  
 *     Queda totalmente prohibida la distribución, reproducción, copia, almacenamiento o
 * transcripción total o parcial de ésta obra en cualquier soporte físico o electrónico sin el
 * consentimiento expreso del propietario del copyrigth.
 *
 *     Este código se distribuye “tal cual” sin garantía implícita, incluso mercantil, o
 * de uso, así como la adecuación para un propósito concreto.
 *
 *     El autor no se hace responsable de cualquier tipo de daño derivado del uso, así como
 * pérdidas económicas o de información.
 */

#if defined(__LGT8F__)
  #define LGT8              // Define si se utiliza LGT8F328P.
//  #include <PMU.h>
/* 
 *  Usage PMU.sleep(pmu_t mode, period_t period);
 *  
 *    Power mode defintion:
 * PM_IDLE: disable core_clock only
 * PM_POWERDWN: disalbe most clocks and switch main clock to rc32k
 * PM_POFFS0: power off all core functions (digial and analog)
 *     wake up by external interrupt or periodly
 * PM_POFFS1: the lowest power mode which close all modules and clocks 
 *    wake up by external interrupt only
 *    
 *    Periods available: 
 * SLEEP_64MS,
 * SLEEP_128MS,
 * SLEEP_256MS,
 * SLEEP_512MS,
 * SLEEP_1S,
 * SLEEP_2S,
 * SLEEP_4S,
 * SLEEP_8S,
 * SLEEP_16S,
 * SLEEP_32S,
 * SLEEP_FOREVER
 */
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
  #define MEGA328         // Defina si se utiliza Atmega328P XXduino pro o pro mini.
  /* ------------------------------------------------
  #include <avr/sleep.h>
  #include <avr/wdt.h>
  #include <LowPower.h>

  */ // --------------------------------------------------------------------------
#endif

#define SDD1306_128X64        // Define para usar pantalla OLED 0.96" I2C 128x64 pixels
//#define HX1230_96X68        // Define para usar pantalla HX1230 96x68 pixels LCD SPI(Nokia simil.) 


#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include "capture.h"  
#include "display.h"

float VCC_CAL = VCC; // Tension de referencia VCC calibrada.
word battery_sensor;  // Declaramos variables globales.
word battery_amp_sensor;
word ts832_temp_sensor;
word temp_amb_sensor;
word rev_cooler_sensor;
volatile bool pwr_switch = false;
volatile bool standby = true;
volatile bool needcharge = true;
float battery_value;
float battery_amp_value;
byte battery_percent;
float ts832_temp_value;
float temp_amb_value;

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

#ifdef LGT8
//  analogReference(INTERNAL4V096);
//  #define VREF_4096
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

#ifdef MEGA328
  #if FASTADC
    // set prescale to 16
    sbi(ADCSRA,ADPS2);
    cbi(ADCSRA,ADPS1);
    cbi(ADCSRA,ADPS0);
  #endif
#endif
  
  delay(400);

  mesg("Wait...");
    
  battery_sensor = capture(BATT);     // Captura inicial datos valor en pasos.
  battery_amp_sensor = capture(AMP);  // Rango de valores 0 ... MAXADC.

#if defined(LGT8)
    if (battery_sensor > 2400) { // 2400 -> 16,543 V.
#elif defined(MEGA328)
    if (battery_sensor > 600) { // 600 -> 16,556 V.
#endif
      power_ts832();
      standby = false;
      needcharge = false;
    }
}

void capturedata() {
  
  //VCC_CAL = readVcc();
  /* for (byte i = 1; i < SIZE; i++) {
    VCC_CAL = (alphaEMA_LOW * readVcc()) + ((1 - alphaEMA_LOW) * VCC_CAL);
  }*/
  //VCC_CAL = VCC;
  
  ts832_temp_sensor = filtrado(TEMP,ts832_temp_sensor);   // Captura datos valor en pasos.
  temp_amb_sensor = filtrado(TEMP_AMB,temp_amb_sensor);   // Rango de valores 0 ... MAXADC.
  
#ifdef DEBUG
  unsigned long timecalc = micros();
#endif
  
// Primera forma de calcular la Tª con función steinhart completa. (370-380micros) NTC-GND
//  float ts832_temp_NTC = (float)ts832_temp_sensor / 1023.0 * (VCC_CAL);
//  ts832_temp_NTC = ts832_temp_NTC * NTC_R1 / (VCC_CAL - ts832_temp_NTC);
//  float ts832_temp_value = steinhart(ts832_temp_NTC);
  
// Segunda forma de calcular la Tª con función steinhart completa. (370-380micros) NTC-GND
//  float ts832_temp_NTC = (ts832_temp_sensor * VCC_CAL / 1023.0 * NTC_R1) / ( VCC_CAL - (ts832_temp_sensor * VCC_CAL / 1023.0));
//  float ts832_temp_value = steinhart(ts832_temp_NTC);

// Tercera forma de calcular la Tª con función steinhart completa. (370-380micros) NTC-GND
//  float ts832_temp_NTC = (ts832_temp_sensor / 1023.0 * NTC_R1) / ( 1.0 - (ts832_temp_sensor / 1023.0));
//  float ts832_temp_NTC = (ts832_temp_sensor * NTC_R1) / ( 1023.0 - ts832_temp_sensor);
//  float ts832_temp_value = steinhart(ts832_temp_NTC);

// Cuarta forma de calcular la Tª con función steinhart completa. (330micros) NTC-VCC
//*  float ts832_temp_NTC = NTC_R1 * ((1023.0 / ts832_temp_sensor) -1.0); // Dos formas de calcular:
//*  float ts832_temp_NTC = ((1023.0 - ts832_temp_sensor) * NTC_R1) / ts832_temp_sensor;
//  float ts832_temp_value = steinhart(ts832_temp_NTC);

// Cáculo de la Tª con la funcion temp_calc(float R_NTC,int beta,float R_0) (280micros) NTC-VCC 
//  long ts832_temp_NTC = (((MAXADC - (long)ts832_temp_sensor) * (long)NTC_1R) / (long)ts832_temp_sensor);
  /*
   *  Calculo del valor NTC cuando se configura como VCC usando como referencia el voltaje.
   *
#if defined(LGT8)
  float ts832_temp_NTC = (float)ts832_temp_sensor * PWR_TEMP / (float)MAXADC;
  ts832_temp_NTC = PWR_TEMP * (float)NTC_1R / ts832_temp_NTC;
#elif defined(MEGA328)
  float ts832_temp_NTC = (float)ts832_temp_sensor * VCC / (float)MAXADC;
  ts832_temp_NTC = VCC * (float)NTC_1R / ts832_temp_NTC;
#endif
  ts832_temp_NTC -= NTC_1R;
  */
  
  /*
   *  Calculo del valor NTC cuando se configura como VCC.
   */ 
  float ts832_temp_NTC = (float)MAXADC  * (float)NTC_1R;
  ts832_temp_NTC -= (float)ts832_temp_sensor * (float)NTC_1R;
  ts832_temp_NTC /= (float)ts832_temp_sensor;
 
   
  /*
   *  Calculo del valor NTC cuando se configura con GND. 
   *
  float ts832_temp_NTC = (float)ts832_temp_sensor * VCC / (float)MAXADC;
  ts832_temp_NTC = ts832_temp_NTC / (VCC - ts832_temp_NTC);
  ts832_temp_NTC *= (float)NTC_1R;
  */
  ts832_temp_value = temp_calc((long)ts832_temp_NTC , BETA_NTC_1 , (long)NTC_1_25C);

#ifdef DEBUG
  timecalc = micros() - timecalc;
  Serial.print(timecalc);
  Serial.println(" micros. to calc TS832 tempºC.");

  timecalc = micros();
#endif
  
//  long temp_amb_NTC = (((MAXADC - (long)temp_amb_sensor) * (long)NTC_2R) / (long)temp_amb_sensor);
  /*
   *  Calculo del valor NTC cuando se configura como VCC.
   */
  float temp_amb_NTC = (float)MAXADC  * (float)NTC_2R;
  temp_amb_NTC -= (float)temp_amb_sensor * (float)NTC_2R;
  temp_amb_NTC /= (float)temp_amb_sensor;
  /*
   *  Calculo del valor NTC cuando se configura con GND. 
   *
  float temp_amb_NTC = (float)temp_amb_sensor * VCC / (float)MAXADC;
  temp_amb_NTC = temp_amb_NTC / (VCC - temp_amb_NTC);
  temp_amb_NTC *= (float)NTC_2R;
  */
  temp_amb_value = temp_calc(temp_amb_NTC , BETA_NTC_2 , NTC_2_25C);

// Simplificando en una sola línea de codigo las dos anteriores.
//  float temp_amb_value = temp_calc(21800L * ((1023L / (long)temp_amb_sensor) -1L) , 4390 , 97000.0);
// Podemos simplificar en una linea usando el calculo de steinhart_reduced.
//  float temp_amb_value = (1/((log(((21800.0 * (1023.0 - temp_amb_sensor)) / temp_amb_sensor)/97000.0)/4390.0) + (1/298.15))) - 273.15;

#ifdef DEBUG
  timecalc = micros() - timecalc;
  Serial.print(timecalc);
  Serial.println(" micros. to calc tempºC amb.");

  timecalc = 0;
#endif


      printdata(battery_value, battery_amp_value, battery_percent,
                temp_amb_value, ts832_temp_value);

  // rebuild the picture after some delay
  //delay(200);  
}

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
      ts832_temp_sensor = capture(TEMP);
      temp_amb_sensor = capture(TEMP_AMB);
  }
}

bool stand_by(byte battery_percent) {
  bool standby;
  battery_percent < 0 ? standby = true : standby = false;
  return standby;
}

void loop() {
  battery_sensor = filtrado(BATT,battery_sensor);
  /*
   * Calculamos el valor en voltios del divisor resistivo V = (R1 + R2)/R2 * Vint
   *                                                           R1 = 148.5 Kohm , R2 = 32.2 Kohm.
   * 
   * Esta fórmula puede causar un resualtado inesperado ya que si el valor battery_sensor
   * es muy pequeño al dividir por un numero mas grande obtenemos un numero cercano a cero (0).
   * El compilador puede no hacer bien la conversión y devolver un valor con un error acumulado.
   * Al multiplicar por el valor de VCC obtendremos un mayor error.
   * 
   *   battery_value = (float)battery_sensor / (float)MAXADC * (VCC_CAL);
   *   battery_value = (battery_value)*DIV;
   */
#ifdef VREF_4096
  battery_value =  (float)battery_sensor * DIV;   // DIV = (R1+R2)/R2.
  battery_value /= 1000.0;                        // Calculamos el valor en voltios.
#else
  battery_value =  (float)battery_sensor * DIV * VCC;   // DIV = (R1+R2)/R2.
  battery_value /= (float)MAXADC;                       // Calculamos el valor en voltios.
#endif

  battery_percent = percent(battery_value);  // Realizamos el calculo del porcentaje de bat.
  battery_value < 16.5 ? standby = true : standby = stand_by(battery_percent);
  
  battery_amp_sensor = filtrado(AMP,battery_amp_sensor);
  /*
   * Calculamos el valor en mA. del sensor ACS712 -5A. I = (V - (Vcc/2)) / sensibilidad.
   *                                                        sensibilidad = 185 mV/A (0.185)
   * Al igual que la fórmula anterior, si el resultado de battery_amp_sensor - (MAXADC/2) se
   * aproxima a cero, se puede producir un error y devolver 0 cuando no sea realmente así.
   * 
   *   battery_amp_value = ((float)(battery_amp_sensor)-(MAXADC/2)) * (VCC / MAXADC) / ACS712_SENS;
   */
#ifdef VREF_4096
  battery_amp_value = (float)(battery_amp_sensor) / 1000.0;
  battery_amp_value -= (float)(VCC * 0.5);
  battery_amp_value /= ACS712_SENS;
#else
  battery_amp_value = (float)(battery_amp_sensor) * VCC / (float)MAXADC;
  battery_amp_value -= VCC / 2.0;
  battery_amp_value /= ACS712_SENS;
#endif
  if (standby &&  battery_amp_value > 0) needcharge = true;
  else if (!standby && battery_amp_value < -1000 && battery_value > 17.0) needcharge = false;
  
  if (pwr_switch && !standby && !needcharge) {
      digitalWrite(PWR_TS832, HIGH);
      digitalWrite(PWR_TEMP, HIGH);
      digitalWrite(PWR_TEMP_AMB, HIGH);
      #if defined(HX1230_96X68) 
          digitalWrite(LCD_BL, HIGH);
        #endif
      
      capturedata();
        
      #if defined(LGT8)
        PMU.sleep(PM_IDLE, SLEEP_512MS);
      #elif defined(MEGA328)
        LowPower.powerStandby(SLEEP_500MS,ADC_ON,BOD_ON);
      #endif
      } else if (!pwr_switch && !standby && !needcharge) {

        drawlogo();
        
        #if defined(HX1230_96X68) 
          delay(2000);
          digitalWrite(LCD_BL, LOW);
        #endif
        
        #if defined(LGT8)
        PMU.sleep(PM_POFFS0, SLEEP_16S);
        #elif defined(MEGA328)
        LowPower.powerDown(SLEEP_8S,ADC_OFF,BOD_OFF);
        #endif
        
      } else if (standby || needcharge) {
        digitalWrite(PWR_TS832, LOW);
        digitalWrite(PWR_TEMP, LOW);
        digitalWrite(PWR_TEMP_AMB, LOW);
        
        drawlowbat();
//        capturedata();   // For test display.
        
        #if defined(LGT8)
        PMU.sleep(PM_POFFS0, SLEEP_8S);
        #elif defined(MEGA328)
        LowPower.powerDown(SLEEP_2S,ADC_OFF,BOD_OFF);
        #if defined(HX1230_96X68) 
          digitalWrite(LCD_BL, LOW);
        #endif
        LowPower.powerDown(SLEEP_8S,ADC_OFF,BOD_OFF);
        #endif
              
      } else {
        mesg("ERROR!!!");
        
        #if defined(LGT8)
        PMU.sleep(PM_POFFS1, SLEEP_FOREVER);
        #elif defined(MEGA328)
        LowPower.powerDown(SLEEP_2S,ADC_OFF,BOD_OFF);
        #if defined(HX1230_96X68) 
          digitalWrite(LCD_BL, LOW);
        #endif
        LowPower.powerDown(SLEEP_FOREVER,ADC_OFF,BOD_OFF);
        #endif
      }
      
#ifdef DEBUG
  Serial.print(battery_value,4);
  Serial.print(" V, ");
  Serial.print(battery_sensor);
  Serial.print(" ADC, ");
  Serial.print(battery_amp_value, 0);
  Serial.print(" mA, ");
  Serial.print(battery_amp_sensor);
  Serial.print(" ADC, ");
  Serial.print(battery_percent);
  Serial.print(" %. Vcc, ");
  if(pwr_switch && !standby && !needcharge) {
     Serial.print(temp_amb_value);
     Serial.print(" ºC Amb., ");
     Serial.print(temp_amb_sensor);
     Serial.print(" ADC, ");
     Serial.print(ts832_temp_value);
     Serial.print(" ºC TS832, ");
     Serial.print(ts832_temp_sensor);
     Serial.print(" ADC, ");
     Serial.print("-> TS832 PWR: ON , ");
  } else {
    Serial.print("-> TS832 PWR: OFF, ");
  }
  standby ? Serial.print("STANDBY: ON") : Serial.print("STANDBY: OFF");
  Serial.println("");
#endif
}
