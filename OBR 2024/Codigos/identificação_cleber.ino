// Identificação
#include "definir.h"

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir};

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);
}

void loop()
{
  byte aleitura = 0;
  for (int i = 0; i < 5; i++)
    aleitura |= digitalRead(pinos[i]) << i;
  aleitura = (~aleitura) & 0b00011111;

  bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;

  calibra();

  Serial.print("Leitura: ");
  Serial.print(leitura, BIN);
  Serial.print("Bits / Antiga leitura: ");
  Serial.print(aleitura, BIN);
  Serial.print("Bits \nAnalogRead: ");
  Serial.print(analogRead(s_esq));
  Serial.print(" / ");
  Serial.print(analogRead(s_mesq));
  Serial.print(" / ");
  Serial.print(analogRead(s_m));
  Serial.print(" / ");
  Serial.print(analogRead(s_mdir));
  Serial.print(" / ");
  Serial.println(analogRead(s_dir));


  Serial.print("\nBool: ");
  Serial.print(besq);
  Serial.print(" / ");
  Serial.print(bmesq);
  Serial.print(" / ");
  Serial.print(bm);
  Serial.print(" / ");
  Serial.print(bmdir);
  Serial.print(" / ");
  Serial.println(bdir);
  
  Serial.print("\nMap: ");
  Serial.print(map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023));
  Serial.print(" / ");
  Serial.print(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023));
  Serial.print(" / ");
  Serial.print(map(analogRead(s_m), preto_m, branco_m, 0, 1023));
  Serial.print(" / ");
  Serial.print(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023));
  Serial.print(" / ");
  Serial.println(map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023));
}
