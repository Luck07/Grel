// Identificação
#include "Oled.h"
#include "Definir.h"

const unsigned char aeia[] PROGMEM = {
    // 'bfcaab3c7ed1666ef086e690ec778ad0, 32x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xb0,
    0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x01, 0xbc, 0x08, 0x20, 0x44, 0x34, 0x00, 0x40, 0x08, 0x28,
    0x00, 0x03, 0x10, 0x20, 0x05, 0xff, 0x80, 0x30, 0x07, 0xfe, 0x20, 0xa0, 0x0f, 0xdf, 0xee, 0x80,
    0x0f, 0xb9, 0x3d, 0x70, 0x1f, 0xe3, 0x73, 0xc0, 0x1d, 0xe0, 0xe3, 0xc0, 0x1f, 0xe0, 0x00, 0xc0,
    0x1f, 0x63, 0xa0, 0x40, 0x1f, 0x67, 0xc1, 0xc0, 0x1f, 0x47, 0x21, 0x40, 0x1b, 0x47, 0xe3, 0xc0,
    0x1f, 0x47, 0xc3, 0xc0, 0x1f, 0x47, 0xc3, 0xc0, 0x0e, 0x5f, 0xdb, 0x80, 0x1b, 0xdf, 0x83, 0xe0,
    0x03, 0x78, 0x00, 0x80, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x6b, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const unsigned char aeiapeqena[] PROGMEM = {
    // 'bfcaab3c7ed1666ef086e690ec778ad0, 16x16px
    0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x04, 0x2a, 0x2f, 0xc8, 0x3d, 0xc0, 0x3e, 0xec, 0x74, 0x88,
    0x79, 0x88, 0x7b, 0x90, 0x7b, 0x98, 0x3f, 0x98, 0x17, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
const int pinos[] = { s_oeste, s_noroeste, s_norte, s_nordeste, s_leste};

float tensaoA0;

int n;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  Serial.begin(9600);
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);
  //serv_robo.attach(serv_robo_pin);
  //serv_garra.attach(serv_garra_pin);


  n = 0;
}

void loop()
{
  display.clearDisplay();
  
  

  byte aleitura = 0;
  for (int i = 0; i < 5; i++)
    aleitura |= digitalRead(pinos[i]) << i;
  aleitura = (~aleitura) & 0b00011111; //6.181kbb
  //sensi();
  calibra();


  display.setCursor(0, lh * 2);
  display.print("Leitura: ");
  for (int i = 11; i <= 15; i++)
    display.print(binString(leitura)[i]);
  display.print(" Bits");

  display.setCursor(0, lh * 3);
  display.print("Esq: ");
  display.print(analogRead(s_nordeste));
  display.print(" / Dir: ");
  display.print(analogRead(s_noroeste));

  /*
  display.setCursor(0, lh * 3);
  display.print("Tensao: ");
  display.print(tensaoA0);
  display.print(" V");

  display.setCursor(0, lh * 4);
  display.print("Olho: ");
  display.print(ult_meio.read());
  display.print("cm");

  display.setCursor(0, lh * 5);
  display.print("Esq_ldr: ");
  display.print(m_esq);
  display.print("(");
  display.print(analogRead(esq));
  display.print(")");

  display.setCursor(0, lh * 6);
  display.print("Dir_ldr: ");
  display.print(m_dir);
  display.print("(");
  display.print(analogRead(dir));
  display.print(")");

  display.setCursor(0, lh * 7);
  display.print("Enc: ");
  display.print(enc.read());
  */

  display.drawBitmap(W - 32, H - 32 + sin(n * PI / 180) * 3, aeia, 32, 32, WHITE);
  display.drawBitmap(W - 16, -sin(n * PI / 180) * 1.5, aeiapeqena, 16, 16, WHITE);
  display.display();
  n = (n < 360) ? n + 36 : 0;

  display.display();

  Serial.print("Leitura: ");
  Serial.print(leitura, BIN);
  Serial.print("Bits / Antiga leitura: ");
  Serial.print(aleitura, BIN);
  Serial.print("Bits / AnalogRead: ");
  Serial.print(analogRead(s_oeste));
  Serial.print(" / ");
  Serial.print(analogRead(s_noroeste));
  Serial.print(" / ");
  Serial.print(analogRead(s_norte));
  Serial.print(" / ");
  Serial.print(analogRead(s_nordeste));
  Serial.print(" / ");
  Serial.print(analogRead(s_leste));
  Serial.print(" / Olho: ");
  Serial.print(ult_meio.read());
  Serial.println("cm /");
}

char *binString(unsigned short n)
{
  static char bin[17];
  int x;

  for (x = 0; x < 16; x++)
  {
    bin[x] = n & 0x8000 ? '1' : '0';
    n <<= 1;
  }
  bin[16] = '\0';

  return (bin);
}
