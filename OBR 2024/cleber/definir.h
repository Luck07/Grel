#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H

#include <SoftwareWire.h>
#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(6, 7);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);

#include <Ultrasonic.h>
#include <Servo.h>
// mpu6050 i2c = 0x68

//* Definindo as portas dos sensores
#define s_esq A4     //
#define s_mesq A3 //
#define s_m A0     //
#define s_mdir A2 //
#define s_dir A1     //

// diminuir 20 do max
#define max_esq 125
#define max_mesq 170
#define max_m 130
#define max_mdir 230
#define max_dir 200

bool s_bit = false;
byte leitura = 0;
bool ver = false;      // O Verifica para os switchs

#define servo_esquerda 11
#define servo_direita 12
Servo serv_esq;
Servo serv_dir;
#define delay_fre 300
#define delay_re 30
#define delay_peq 30 
#define delay_pas 30

#define velocidade_par 40  // Delay para o tempo dele ficar parado

//* Valores para desviar obstaculo
#define desv_lado 1
#define delay_peq_desv 99999
#define frente_1 900  // Valor que ele se distancia do obstaculo
#define frente_2 1450 // Valor que faz ele ultrapassar o obstaculo
#define frente_3 550  // Valor que faz ele nao se perder em qualquer linha
#define enc_90 580
#define enc_90_2 enc_90 + 40 // Seguunda vez que ele executa o 90 / 70
#define enc_90_3 enc_90 + 27 // E a terceira / 140

/*
 * trig == prim
 * echo == segun
 */
Ultrasonic ult_meio(30, 31);

void calibra()
{
  leitura = 0;

  if (analogRead(s_esq) >= max_esq)
    s_bit = true;
  else
    s_bit = false;
  leitura |= s_bit << 0;

  if (analogRead(s_mesq) >= max_mesq)
    s_bit = true;
  else
    s_bit = false;
  leitura |= s_bit << 1;

  /*
  if (analogRead(s_m) >= max_m)
    s_bit = true;
  else
    s_bit = false;
  leitura |= s_bit << 2;*/

  if (analogRead(s_mdir) >= max_mdir)
    s_bit = true;
  else
    s_bit = false;
  leitura |= s_bit << 2;

  if (analogRead(s_dir) >= max_dir)
    s_bit = true;
  else
    s_bit = false;
  leitura |= s_bit << 3;

  leitura = (~leitura) & 0b00001111;  
}


//* Inicio das funções, para cada caso
void vel_frente()
{
  serv_esq.write(180);
  serv_dir.write(0);
}
void vel_direita()
{
  serv_esq.write(180); // talvez usar 90
  serv_dir.write(180);
}
void vel_esquerda()
{
  serv_esq.write(0);
  serv_dir.write(0); // talvez usar 90
}
void vel_re()
{
  serv_esq.write(0);
  serv_dir.write(180);
}
void vel_parar(int velo_esq = velocidade_par)
{
  serv_esq.write(90);
  serv_dir.write(90);
  delay(velo_esq);
}

enum cores {
  branco_branco, branco_verde,
  verde_branco , verde_verde,
  vermelho_vermelho,
  outro
};

cores sensi()
{
  int cor1, cor2;
  uint16_t r1, g1, b1, c1;
  uint16_t r2, g2, b2, c2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t t1  = (r1+g1+b1)/3;
  uint16_t tr1 = (g1+b1)/2;
  uint16_t tg1 = (r1+b1)/2;

  uint16_t t2  = (r2+g2+b2)/3;
  uint16_t tr2 = (g2+b2)/2;
  uint16_t tg2 = (r2+b2)/2;

  if(r1 > tr1*1.07)
    return vermelho_vermelho;
  else if(g1 > tg1*1.07)
    cor1 = 1; //verd
  else {
    if(t1 >= 11500) //1050
      cor1 = 2; //b
    else 
      cor1 = 3; //p
  }

  if(r2 > tr2*1.07)
    return vermelho_vermelho;
  else if(g2 > tg2*1.07)
    cor2 = 1;
  else {
    if(t2 >= 11500) //1050
      cor2 = 2;
    else 
      cor2 = 3;
  }

  if     (cor1 == 1 && cor2 == 1)
    return verde_verde;
  else if(cor1 == 1 && cor2 == 2)
    return branco_verde;
  else if(cor1 == 2 && cor2 == 1)
    return verde_branco;
  else
    return branco_branco;


}

/**
 *! false = direita
 *! true = esquerda
 */
void desv()
{
  delay(delay_re); //* Dando um passo para atras, isso e bom caso a traseira do robo e maior do que na frente
/*mot1_par();                                //* Colocando pra parar bem rapido pq sim
mot2_par();
delay(mot_par);*/
#if desv_lado                                //! Esquerda
  delay(enc_90);  //* Girando para esquerda
  delay(frente_1);  //* Se distanciando do obstaculo
  delay(enc_90_2); //* Virando para direita, com valor variado para nao girar demais
  delay(frente_2);  //* Passando do obstaculo
  delay(enc_90_3); //* Virando para direita, mesmo moitvo anterior
  delay(frente_3);  //* Andando em frente, para ele nao se confundir linhas aleatorias
  vel_frente();            //* Terminando com while para ele encontrar a linah correta
  while ((digitalRead(s_mesq) == 1) && (digitalRead(s_mdir) == 1)); 
  delay(delay_peq_desv); //* Se afastando um pouco da linha
  vel_esquerda();             //* Virando para esquerda para se ajeiar na faixa
  while ((digitalRead(s_mesq) == 1) && (digitalRead(s_mdir) == 1));
#else                                         //! Direita
  delay(enc_90);    //* Girando para direita
  delay(frente_1);   //* Se distanciando do obstaculo
  delay(enc_90_2); //* Virando para esquerda, com valor variado para nao girar demais
  delay(frente_2);   //* Passando do obstaculo
  delay(enc_90_3); //* Virando para esquerda, mesmo moitvo anterior
  delay(frente_3);   //* Andando em frente, para ele nao se confundir linhas aleatorias
  vel_frente(velo_esq, velo_dir);             //* Terminando com while para ele encontrar a linah correta
  while ((digitalRead(s_mesq) == 1) && (digitalRead(s_mdir) == 1))
  {
  }
  delay(enc_peq_desv); //* Se afastando um pouco da linha
  vel_dir(velo_esq, velo_dir);                  //* Virando para direita para se ajeiar na faixa
  while ((digitalRead(s_mesq) == 1) && (digitalRead(s_mdir) == 1))
  {
  }
#endif
}

void esq_90() //* 90 esquerda
{
  vel_frente();
  delay(delay_fre);

  if (analogRead(s_m) >= max_m)
  {
    vel_esquerda();
    delay(delay_peq);
    while (((analogRead(s_mesq) >= max_mesq) || (analogRead(s_mdir) >= max_mdir)) && analogRead(s_esq) >= max_esq);
    // while ((digitalRead(s_m) == 1) && (digitalRead(s_esq) == 1));
    vel_re();
    delay(delay_re);
  }
}

void dir_90() //* 90 direita
{
  vel_frente();
  delay(delay_fre);

  if (analogRead(s_m) >= max_m)
  {
    vel_direita();
    delay(delay_peq);
    while (((analogRead(s_mesq) >= max_mesq) || (analogRead(s_mdir) >= max_mdir)) && analogRead(s_dir) >= max_dir);
    // while ((digitalRead(s_m) == 1) && (digitalRead(s_dir) == 1));
    vel_re();
    delay(delay_re);
  }
}
#endif