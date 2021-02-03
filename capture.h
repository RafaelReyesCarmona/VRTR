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
  #include <PMU.h>
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
  #define MEGA328         // Defina si se utiliza Atmega328P XXduino pro o pro mini.
  #include <LowPower.h>

  // --------------------------------------------------------------------------
#endif

#define DEBUG           // Activar para obtener datos de depuración por Serial.

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

#define VCC 5.03           // Tensión VCC de alimentación. ~5V.
#define SIZE 85            // Número de muestras que se toman ADC.
#define alphaEMA_LOW 0.79   // Valor Alfa para filtrado EMA.
#define alphaEMA_HIGH 0.91 // Valor Alfa para filtrado EMA.
  
#ifdef MEGA328             // Solo para Arduino o ATMEL microcontrollers (mega328/p)
  #define VCC_DEBUG 0
  #define FASTADC 1           
  #define VccRef1 1.055      // Tensión de referencia interna 1.1
    
  #ifndef cbi
    #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
  #endif

  #ifndef sbi
    #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
  #endif
#endif

#if defined(LGT8)
  #define SERIALBAUD 19200   // Velocidad conexion UART serial.
#elif defined(MEGA328)
  #define SERIALBAUD 9600    // Velocidad conexion UART serial.
#endif

#if defined(LGT8)
  #define MAXADC 4095L      // 12 bits resolucion (2^12 - 1 LSB) = B111111111111 , (4095)
#elif defined(MEGA328)
  #define MAXADC 1023L      // 10 bits resolucion (2^10 - 1 LSB) = B1111111111 , (1023)
#endif

// Constante del divisor resistivo tension de baterias.
// Para calcular DIV = (R1+R2)/R2.
// R1 = 148.5 Kohm , R2 = 32.2 Kohm.
//#define DIV 5.611801242236
// R1 = 147.9 Kohm , R2 = 32.3 Kohm.
#define DIV 5.578947368421
// R1 = 148.2 Kohm , R2 = 32.3 Kohm.
//#define DIV 5.5882352941176
// R1 = 147.5 Kohm , R2 = 32.3 Kohm.
//#define DIV 5.56656346744922
/*
 * Constantes para calculo de temperatura utilizando la función steinhart().
 * La función utiliza la ecuación completa de Steinhart-Hart para cálculo de temperatura.
 * (Resultado en ºK)
 * 
 *    1                              2                3
 *    - = A + B * ln (R/NTC) + C * ln (R/NTC) + D * ln (R/NTC)
 *    T
 */
#define NTC 10000.0     // Valor resistivo (ohm)de NTC para de la Tª 25ºC.
#define A 0.003354016
#define B 0.0002569850  // Consultar los valores del fabricante.
#define C 0.000002620131 
#define D 0.00000006383091

/*
 * Constantes para calculo de temperatura utilizando la función steinhart_reduced() y temp_calc().
 * La función steinhart_reduced() utiliza la ecuación simplificada de Steinhart-Hart 
 * para cálculo de temperatura. (Resultado en ºK)
 *
 *    1                          3                        (beta *(1/T - 1/298.15))
 *    - = A + B * ln (R) + C * ln (R)  --->   R = NTC * e
 *    T                                       
 *    
 *     R     (beta/T - beta/298,15)                  beta   beta        ln(R/NTC)   1     1
 *    --- = e                         ,, ln(R/NTC) = ---- - ------  ,,  --------- = - - ------- ,,
 *    NTC                                             T     298,15        beta      T   298,15
 *    
 *    1      1     ln(R) - ln(NTC)        1     ln(R/NTC)
 *    - = ------ + ---------------  =  ------ + ---------
 *    T   298,15        beta           298,15     beta
 *    
 * La función temp_calc() utiliza una adaptación de la ecuación simplificada de Steinhart-Hart 
 * para cálculo de temperatura. (Resultado en ºK)
 * 
 *    1      1     ln(R) - ln(NTC)        1     ln(R/NTC)     beta + 298,15 * ln(R/NTC)
 *    - = ------ + ---------------  =  ------ + ---------  =  -------------------------
 *    T   298,15        beta           298,15     beta             beta * 298,15
 * 
 *                              beta * T0                    (T0 = 298,15)
 *                    T = ---------------------
 *                         beta + T0 + ln(R/NTC
 */
#define NTC_1R 21900L       // Valor de resistencia R1 del divisor de tension (ohm) NTC-R1.
#define NTC_2R 21800L       // Valor de resistencia R1 del divisor de tension (ohm) NTC-R2.
#define BETA_NTC_1 4190     // Valor de beta del primer termistor. (TS832)
#define BETA_NTC_2 4390     // Valor de beta del segundo termistor.(Ambiente)
#define NTC_1_25C 9950L     // Valor resistivo del termistor a 25ºC medición.
#define NTC_2_25C 97000L    // Valor resistivo del termistor a 25ºC medición.

#define ACS712_SENS 0.000185  // Definimos la sensibilidad del sensor de corriente. (mA.)

word capture(byte analog_input) {
  word EMA_LOW;

  EMA_LOW = analogRead(analog_input);
  
  for (byte i = 1; i < SIZE; i++) {
    EMA_LOW = (alphaEMA_LOW * analogRead(analog_input)) + ((1 - alphaEMA_LOW) * EMA_LOW);
  }
  
  return EMA_LOW;
}

word filtrado(byte analog_input, word item) {
  word EMA_HIGH;

  EMA_HIGH = capture(analog_input);

  EMA_HIGH = (alphaEMA_HIGH * item) + ((1 - alphaEMA_HIGH) * EMA_HIGH);
  
  return EMA_HIGH;
}

byte percent(float battery) {
  float percent_bat;
  /*
  if (battery < 15.0 ){
    percent_bat = (byte)map(battery, 13.5, 15.0, 0.0, 2.0);
  }
  else {
    percent_bat = (byte)map(battery, 15.0, 20.75, 2.0 ,100.0);
  }
  */
  
  /*
  percent_bat = map(battery*100, 1650, 2010, 0, 100);
  */
  
  percent_bat = (3.031559 * pow(battery,2)) - (84.12877 * battery) + 562.6043;
  
  return (percent_bat > 100 ? 100 : percent_bat < 0 ? 0 : (byte)percent_bat);
}

#ifdef MEGA328
float readVcc() {  
 // Read 1.1V reference against AVcc
 // set the reference to Vcc and the measurement to the internal 1.1V reference
 
 ADMUX = (0x01 << REFS0) | (0 << ADLAR) | (0x0e << MUX0);

 delayMicroseconds(300);
 ADCSRA |= _BV(ADSC); // Start conversion
 
 while (bit_is_set(ADCSRA,ADSC));
 if (ADCSRA & (0x01 << ADIF)) {

    #if VCC_DEBUG
    Serial.println(ADC); // For test and calibration.
    delay(10);
    #endif

    return (0x400 * VccRef1) / (ADCL + ADCH * 0x100);
  }
}
#endif

float steinhart(float R) { 
/*
 * Ecuacion Steinhart completa para obtener la Tª.
 * Tiempo de cálculo 380micros.
 */
  float E = log(R/NTC); 
  float T = A + (B*E) + (C*(E*E)) + (D*(E*E*E));
  T = pow(T,-1);
  return T-273.15; // ajuste para convertir a ºC.
}


float temp_calc(long R_NTC,int beta,long R_0) {
/*  
 *   Esta formula es deducida de la ecuacion simplificada de Steinhart, 
 *   Tiempo de calculo mas reducido (280micros)
 */

  float temp = log((float)R_NTC / (float)R_0);
  temp *= 298.15;
  temp += (float)beta;
  temp = ((float)beta * 298.15) / temp;
  return temp-273.15;       // Ajuste para pasar a ºC.
}
 
float steinhart_reduced(long R_NTC,int beta,long R_0) {
/* 
 *  Ecuacion simplificada de Steinhart.
 *  Tiempo de cálculo 310micros.
 */
  
  float steinhart = (float)R_NTC / (float)R_0;
  steinhart = log(steinhart);
  steinhart /= (float)beta;
  steinhart += 1.0 / 298.15;
  steinhart = 1.0 / steinhart;
  return steinhart-273.15;
}
