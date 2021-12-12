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
 
#if defined(SDD1306_128X64)
static const unsigned char AmpVolt[] PROGMEM = {
  // Image 28x43
  B11111110, B11111111, B01111111,
  B11111111, B11111111, B11111111,
  B00000001, B00000000, B10000000,
  B00000001, B10000001, B10000000,
  B00000001, B01000010, B10000000,
  B00000001, B01000010, B10000000,
  B00000001, B00100100, B10000000,
  B00000001, B00100100, B10000000,
  B00000001, B00100100, B10000000,
  B00000001, B00011000, B10000000,
  B00000001, B00001000, B10000000,
  B00000001, B00000000, B10000000,
  B11111101, B11111111, B10111111,
  B00000001, B00000000, B10000000,
  B00000001, B00000000, B10000110,
  B00000001, B00000000, B10000110,
  B00000001, B00000000, B10001111,
  B10010001, B00000100, B10001001,
  B11011001, B00000110, B10001001,
  B10110001, B10000101, B10011111,
  B10010001, B10000100, B10010000,
  B10010001, B11001100, B10110000,
  B00000001, B00000000, B10000000,
  B11111111, B11111111, B11111111,
  B00000001, B00000000, B10000000,
  B00000001, B00000000, B10000000,
  B00000001, B00111100, B10000000,
  B00000001, B11111111, B10000000,
  B11000001, B11111111, B10000011,
  B11000001, B01111111, B10000010,
  B11100001, B00111111, B10000110,
  B11100001, B00011111, B10000111,
  B11110001, B10001111, B10001111,
  B11110001, B11000111, B10001111,
  B11110001, B11100011, B10001111,
  B11110001, B11110001, B10001111,
  B11100001, B11111000, B10000111,
  B01100001, B11111100, B10000111,
  B01000001, B11111110, B10000011,
  B11000001, B11111111, B10000011,
  B00000001, B11111111, B10000000,
  B00000001, B00111100, B10000000,
  B00000001, B00000000, B10000000
};
#endif

static const unsigned char LogoStart[] PROGMEM = {
// 'Captura de pantalla de 2020-10-03 19-49-28, 64x48px
/*
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x80, 
  0x60, 0x00, 0x33, 0xff, 0xff, 0xff, 0x3f, 0xff, 
  0x60, 0x00, 0x35, 0x00, 0x30, 0x61, 0x00, 0x7d, 
  0x60, 0x00, 0x2e, 0xff, 0xfc, 0x61, 0x00, 0x37, 
  0x60, 0x00, 0x2f, 0x80, 0x1f, 0xf9, 0x3f, 0xf7, 
  0x60, 0x00, 0x09, 0x30, 0x00, 0x01, 0x00, 0x1f, 
  0x60, 0x00, 0x09, 0x7f, 0xff, 0xff, 0x1f, 0x8b, 
  0x60, 0x00, 0x09, 0xc0, 0x00, 0x01, 0x00, 0x6b, 
  0x60, 0x00, 0x09, 0xc0, 0x00, 0x01, 0x00, 0x6b, 
  0x60, 0x00, 0x09, 0xc0, 0x00, 0x01, 0x00, 0x6b, 
  0x60, 0x00, 0x09, 0xc0, 0x00, 0x01, 0x00, 0x6b, 
  0x7f, 0xff, 0xe8, 0xc0, 0x00, 0x01, 0x00, 0x6b, 
  0x7f, 0xff, 0xee, 0xc0, 0x00, 0x00, 0x00, 0x6b, 
  0x60, 0x00, 0x2e, 0xc0, 0x00, 0x00, 0x00, 0x6b, 
  0x60, 0x00, 0x0a, 0xc0, 0x00, 0x00, 0x00, 0x6f, 
  0x60, 0x70, 0x2a, 0xc0, 0x01, 0x00, 0x00, 0x6f, 
  0x60, 0xd8, 0x2a, 0xc0, 0x03, 0x00, 0x00, 0x6b, 
  0x60, 0xf8, 0x2a, 0xc0, 0x04, 0x20, 0x00, 0x6b, 
  0x60, 0xd8, 0x2a, 0xc0, 0x08, 0x80, 0x00, 0x6b, 
  0x60, 0xf8, 0x2a, 0xc0, 0x11, 0x00, 0x00, 0x6b, 
  0x60, 0xf8, 0x2e, 0xc0, 0x62, 0x00, 0x00, 0x6b, 
  0x7f, 0xff, 0xee, 0xc0, 0xc4, 0x00, 0x00, 0x6b, 
  0x7f, 0xff, 0xea, 0xc1, 0x80, 0x00, 0x00, 0x6f, 
  0x60, 0x00, 0x2a, 0xc0, 0x00, 0x00, 0x00, 0x6f, 
  0xe7, 0x07, 0x2a, 0xc0, 0x00, 0x00, 0x00, 0x6b, 
  0xe8, 0x8c, 0xaa, 0xc0, 0x00, 0x00, 0x00, 0x7b, 
  0xef, 0x8f, 0xba, 0xc0, 0x00, 0x00, 0x00, 0x1b, 
  0xef, 0x8d, 0xba, 0xc0, 0x00, 0x00, 0x00, 0x1b, 
  0xef, 0x8f, 0xba, 0x7f, 0xff, 0xe0, 0x00, 0x5b, 
  0xef, 0x0f, 0xbd, 0x00, 0x00, 0x7f, 0xff, 0xd3, 
  0xe0, 0x00, 0x2d, 0xff, 0xff, 0xfc, 0x00, 0x3f, 
  0xff, 0xff, 0xeb, 0x00, 0xff, 0xff, 0xff, 0xef, 
  0xc0, 0xf8, 0x0f, 0xff, 0xe0, 0x40, 0xc0, 0x3f, 
  0xe1, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 
  0xe6, 0xef, 0x0a, 0x01, 0xff, 0xf7, 0xfe, 0xff, 
  0xeb, 0xff, 0x1b, 0x1f, 0xff, 0x1f, 0x13, 0xe7, 
  0xe9, 0xfb, 0x1b, 0xff, 0xf7, 0xfb, 0x3b, 0xf7, 
  0xee, 0xff, 0x15, 0xf7, 0xfd, 0x36, 0x3b, 0xf7, 
  0xe4, 0xef, 0x1f, 0x7f, 0xbf, 0x17, 0xfb, 0xff, 
  0xe0, 0xe0, 0x0e, 0x1f, 0xff, 0x1f, 0xff, 0xff, 
  0xbf, 0xff, 0xfe, 0x01, 0x8d, 0x3b, 0xef, 0xcf, 
  0xbc, 0x3f, 0xff, 0xff, 0x8f, 0xf8, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x8f, 0xf8, 0xff, 0xff, 
  0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfb, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
*/
B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
B00000000, B00000000, B00000000, B00000000, B00000000, B10000000, B00000000, B00000000,
B11111100, B11111111, B11111111, B11111111, B11111111, B11111111, B11111000, B00000001,
B00000110, B00000000, B11001100, B11111111, B11111111, B11111111, B11111100, B11111111,
B00000110, B00000000, B10101100, B00000000, B00001100, B10000110, B00000000, B10111110,
B00000110, B00000000, B01110100, B11111111, B00111111, B10000110, B00000000, B11101100,
B00000110, B00000000, B11110100, B00000001, B11111000, B10011111, B11111100, B11101111,
B00000110, B00000000, B10010000, B00001100, B00000000, B10000000, B00000000, B11111000,
B00000110, B00000000, B10010000, B11111110, B11111111, B11111111, B11111000, B11010001,
B00000110, B00000000, B10010000, B00000011, B00000000, B10000000, B00000000, B11010110,
B00000110, B00000000, B10010000, B00000011, B00000000, B10000000, B00000000, B11010110,
B00000110, B00000000, B10010000, B00000011, B00000000, B10000000, B00000000, B11010110,
B00000110, B00000000, B10010000, B00000011, B00000000, B10000000, B00000000, B11010110,
B11111110, B11111111, B00010111, B00000011, B00000000, B10000000, B00000000, B11010110,
B11111110, B11111111, B01110111, B00000011, B00000000, B00000000, B00000000, B11010110,
B00000110, B00000000, B01110100, B00000011, B00000000, B00000000, B00000000, B11010110,
B00000110, B00000000, B01010000, B00000011, B00000000, B00000000, B00000000, B11110110,
B00000110, B00001110, B01010100, B00000011, B10000000, B00000000, B00000000, B11110110,
B00000110, B00011011, B01010100, B00000011, B11000000, B00000000, B00000000, B11010110,
B00000110, B00011111, B01010100, B00000011, B00100000, B00000100, B00000000, B11010110,
B00000110, B00011011, B01010100, B00000011, B00010000, B00000001, B00000000, B11010110,
B00000110, B00011111, B01010100, B00000011, B10001000, B00000000, B00000000, B11010110,
B00000110, B00011111, B01110100, B00000011, B01000110, B00000000, B00000000, B11010110,
B11111110, B11111111, B01110111, B00000011, B00100011, B00000000, B00000000, B11010110,
B11111110, B11111111, B01010111, B10000011, B00000001, B00000000, B00000000, B11110110,
B00000110, B00000000, B01010100, B00000011, B00000000, B00000000, B00000000, B11110110,
B11100111, B11100000, B01010100, B00000011, B00000000, B00000000, B00000000, B11010110,
B00010111, B00110001, B01010101, B00000011, B00000000, B00000000, B00000000, B11011110,
B11110111, B11110001, B01011101, B00000011, B00000000, B00000000, B00000000, B11011000,
B11110111, B10110001, B01011101, B00000011, B00000000, B00000000, B00000000, B11011000,
B11110111, B11110001, B01011101, B11111110, B11111111, B00000111, B00000000, B11011010,
B11110111, B11110000, B10111101, B00000000, B00000000, B11111110, B11111111, B11001011,
B00000111, B00000000, B10110100, B11111111, B11111111, B00111111, B00000000, B11111100,
B11111111, B11111111, B11010111, B00000000, B11111111, B11111111, B11111111, B11110111,
B00000011, B00011111, B11110000, B11111111, B00000111, B00000010, B00000011, B11111100,
B10000111, B11000111, B11111111, B11111111, B11111111, B11111111, B11111111, B11011111,
B01100111, B11110111, B01010000, B10000000, B11111111, B11101111, B01111111, B11111111,
B11010111, B11111111, B11011000, B11111000, B11111111, B11111000, B11001000, B11100111,
B10010111, B11011111, B11011000, B11111111, B11101111, B11011111, B11011100, B11101111,
B01110111, B11111111, B10101000, B11101111, B10111111, B01101100, B11011100, B11101111,
B00100111, B11110111, B11111000, B11111110, B11111101, B11101000, B11011111, B11111111,
B00000111, B00000111, B01110000, B11111000, B11111111, B11111000, B11111111, B11111111,
B11111101, B11111111, B01111111, B10000000, B10110001, B11011100, B11110111, B11110011,
B00111101, B11111100, B11111111, B11111111, B11110001, B00011111, B11111111, B11111111,
B11111111, B11111111, B11111111, B11111111, B11110001, B00011111, B11111111, B11111111,
B11100011, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
B10000000, B00000001, B00000000, B00000000, B00000000, B00000000, B10000000, B11011111,
B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111
};
static const unsigned char IconLowBattery[] PROGMEM = {
  // 'OIP (2), 56x48px
/*  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x06, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x0c, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x38, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0xe0, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0xc0, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x0f, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x1b, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x73, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x01, 0xc3, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x03, 0x83, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x0e, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x38, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x70, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc1, 0xc0, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc3, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xce, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xd8, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xf0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x03, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x07, 0xc0, 0x00, 0x1b, 0x00, 0x00, 
  0x00, 0x1c, 0xc0, 0x00, 0x7b, 0x00, 0x00, 
  0x00, 0x30, 0xc0, 0x01, 0xfb, 0x00, 0x00, 
  0x00, 0x60, 0xc0, 0x07, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x0f, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x3f, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0xff, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xc3, 0xff, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xcf, 0xff, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xdf, 0xff, 0xfb, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
*/
B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000,
B00000000,  B00000000,  B10000000,  B11111111,  B00000001,  B00000000,  B00000000,
B00000000,  B00000000,  B10000000,  B11111111,  B00000001,  B00000000,  B00000000,
B00000000,  B00000000,  B10000000,  B11111111,  B00000001,  B00000000,  B00000000,
B00000000,  B00000000,  B11111111,  B11111111,  B11111111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B01100000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00110000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00011100,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000111,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000011,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11110000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11011000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11001110,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B10000000,  B11000011,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B11000000,  B11000001,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B01110000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00011100,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00001110,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B10000011,  B00000011,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B11000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B01110011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00011011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00001111,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B11000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B11100000,  B00000011,  B00000000,  B11011000,  B00000000,  B00000000,
B00000000,  B00111000,  B00000011,  B00000000,  B11011110,  B00000000,  B00000000,
B00000000,  B00001100,  B00000011,  B10000000,  B11011111,  B00000000,  B00000000,
B00000000,  B00000110,  B00000011,  B11100000,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B11110000,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B11111100,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B11111111,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B11000011,  B11111111,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B11110011,  B11111111,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B11111011,  B11111111,  B11011111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000011,  B00000000,  B11000000,  B00000000,  B00000000,
B00000000,  B00000000,  B11111111,  B11111111,  B11111111,  B00000000,  B00000000,
B00000000,  B00000000,  B11111110,  B11111111,  B01111111,  B00000000,  B00000000,
B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000,  B00000000


  /* Option 2 
// 'OIP (1), 48x48px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 
  0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x01, 0xf8, 0xc0, 0x00, 
  0x00, 0x03, 0x01, 0x08, 0xc0, 0x00, 0x00, 0x03, 0x02, 0x10, 0xc0, 0x00, 0x00, 0x03, 0x02, 0x10, 
  0xc0, 0x00, 0x00, 0x03, 0x04, 0x20, 0xc0, 0x00, 0x00, 0x03, 0x04, 0x00, 0xc0, 0x00, 0x00, 0x03, 
  0x08, 0x78, 0xc0, 0x00, 0x00, 0x03, 0x08, 0x08, 0xc0, 0x00, 0x00, 0x03, 0x10, 0x10, 0xc0, 0x00, 
  0x00, 0x03, 0x10, 0x30, 0xc0, 0x00, 0x00, 0x03, 0x02, 0x20, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x40, 
  0xc0, 0x00, 0x00, 0x03, 0x04, 0x80, 0xc0, 0x00, 0x00, 0x03, 0x05, 0x00, 0xc0, 0x00, 0x00, 0x03, 
  0x0a, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x0c, 0x00, 0xc0, 0x00, 
  0x00, 0x03, 0x18, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 
  0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 
  0x7f, 0xfe, 0xc0, 0x00, 0x00, 0x03, 0x7f, 0xfe, 0xc0, 0x00, 0x00, 0x03, 0x7f, 0xfe, 0xc0, 0x00, 
  0x00, 0x03, 0x7f, 0xfe, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x90, 0x51, 
  0xc0, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   */
};

// Definifiones para 
static const unsigned char LT[] PROGMEM = {
  B00011100,
  B00011110,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111
};
static const unsigned char UB[] PROGMEM = {
  B00011111,
  B00011111,
  B00011111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
static const unsigned char RT[] PROGMEM = {
  B00000111,
  B00001111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111
};
static const unsigned char LL[] PROGMEM = {
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011110,
  B00011100
};
static const unsigned char LB[] PROGMEM = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011111,
  B00011111,
  B00011111
};
static const unsigned char LR[] PROGMEM = {
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00001111,
  B00000111
};
static const unsigned char UMB[] PROGMEM = {
  B00011111,
  B00011111,
  B00011111,
  B00000000,
  B00000000,
  B00000000,
  B00011111,
  B00011111
};
static const unsigned char LMB[] PROGMEM = {
  B00011111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011111,
  B00011111,
  B00011111
};
static const unsigned char BLOCK[] PROGMEM = {
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111,
  B00011111
};
static const unsigned char FULL_BAT[] PROGMEM = {
  B00110000, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00111100, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00111100, B10011001, B11100111,
  B00111100, B00011000, B10000110,
  B01111100, B00011100, B10000110
};
static const unsigned char BAT_CHG[] PROGMEM = {
  B00000000, B00000010, B00000000,
  B00000000, B00000110, B00000000,
  B00000000, B00011110, B00000000,
  B00000111, B01111110, B00000000,
  B00111110, B11111110, B00000001,
  B11111000, B11111111, B00000111,
  B11100000, B11111111, B00011111,
  B10000000, B01111111, B00111100,
  B00000000, B01111110, B11100000,
  B00000000, B01111000, B00000000,
  B00000000, B01100000, B00000000,
  B00000000, B01000000, B00000000
};
static const unsigned char PER[] PROGMEM = {
  B00100111,
  B00110101,
  B00010111,
  B00001000,
  B00000100,
  B00111010,
  B00101011,
  B00111001,
};
static const unsigned char BAT_0[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111011,
  B00110111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_1[] PROGMEM = {
  B00001100,
  B00001110,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00011110
};
static const unsigned char BAT_2[] PROGMEM = {
  B00011110,
  B00111111,
  B00110001,
  B00111100,
  B00001110,
  B00000011,
  B00111111,
  B00111111
};
static const unsigned char BAT_3[] PROGMEM = {
  B00011110,
  B00111111,
  B00110001,
  B00111100,
  B00111100,
  B00110001,
  B00111111,
  B00011110
};

static const unsigned char BAT_4[] PROGMEM = {
  B00110000,
  B00111000,
  B00111100,
  B00110110,
  B00111111,
  B00111111,
  B00110000,
  B00110000
};
static const unsigned char BAT_5[] PROGMEM = {
  B00111111,
  B00111111,
  B00000011,
  B00011111,
  B00111111,
  B00110000,
  B00111111,
  B00011111
};
static const unsigned char BAT_6[] PROGMEM = {
  B00011110,
  B00111111,
  B00000011,
  B00011111,
  B00111111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_7[] PROGMEM = {
  B00111111,
  B00111111,
  B00110000,
  B00011000,
  B00001100,
  B00001100,
  B00001100,
  B00001100
};
static const unsigned char BAT_8[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111111,
  B00111111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_9[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111111,
  B00111110,
  B00110000,
  B00111111,
  B00011110
};

static const unsigned char TERMO[] PROGMEM = {
  B11001000,
  B11010100,
  B00010100,
  B00110100,
  B00010100,
  B00110100,
  B00010100,
  B00110100,
  B00010100,
  B00010100,
  B00100010,
  B01011101,
  B01011101,
  B01011101,
  B00100010,
  B00011100
};

static const unsigned char MINIBAT[] PROGMEM = {
  // 8X12
  B00000000,
  B00000000,
  B00111000,
  B11111110,
  B11111110,
  B11111110,
  B11111110,
  B11111110,
  B11111110,
  B11111110,
  B11111110,
  B00000000
};
static const unsigned char PLUG[] PROGMEM = {
  // 8X12
  B00100100,
  B00100100,
  B00100100,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00011000,
  B00011000
};
static const unsigned char MINIBATPLUSMINUS[] PROGMEM = {
  //16X12
  B00000010, B00000000,
  B00000111, B11100000,
  B00000010, B00000000,
  B00000000, B00000000,
  B00110000, B00001100,
  B11111100, B00111111,
  B11111100, B00111111,
  B11111100, B00111111,
  B11111100, B00111111,
  B11111100, B00111111,
  B11111100, B00111111,
  B11111100, B00111111
};
