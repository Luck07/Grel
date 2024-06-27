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
#define s_esq A15     // A15
#define s_mesq A2    // A2
#define s_m A0     // A0
#define s_mdir A3 // A3
#define s_dir A4    // A4

#define branco_esq 965 // ressistor 36k
#define branco_mesq 960 // ressistor 36k
#define branco_m 861
#define branco_mdir 960
#define branco_dir 848

#define preto_esq 904
#define preto_mesq 780
#define preto_m 469
#define preto_mdir 700
#define preto_dir 541

//Esquerda sendo branco e direita sendo preto
#define media_esq (branco_esq + preto_esq) / 2
#define media_mesq (branco_mesq + preto_mesq) / 2
#define media_m (branco_m + preto_m) / 2
#define media_mdir (branco_mdir + preto_mdir) / 2
#define media_dir (branco_dir + preto_dir) / 2

bool s_bit = false;
byte leitura = 0;
bool ver = false;      // O Verifica para os switchs

#define servo_esquerda 11
#define servo_direita 12
Servo serv_esq;
Servo serv_dir;
#define delay_fre 300
#define delay_re 30
#define delay_peq 2500 
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

/* void calibra()
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
  leitura |= s_bit << 2;

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
} */

void calibra()
{
  leitura = 0;
  s_bit = analogRead(s_esq) >= media_esq ? 1 : 0;
  leitura |= s_bit << 0;

  s_bit = analogRead(s_mesq) >= media_mesq ? 1 : 0;
  leitura |= s_bit << 1; 

  /* s_bit = analogRead(s_m) <= media_m ? 1 : 0;
  leitura |= s_bit << 1; */

  s_bit = analogRead(s_mdir) >= media_mdir ? 1 : 0;
  leitura |= s_bit << 2;

  s_bit = analogRead(s_dir) >= media_dir ? 1 : 0;
  leitura |= s_bit << 3;

  leitura = (~leitura) & 0b00001111;
}

/* 
void calibra()
{
  leitura = 0;

  s_bit = analogRead(s_esq) >= media_esq ? 1 : 0;
  leitura |= s_bit << 0;

  s_bit = analogRead(s_mesq) >= media_mesq ? 1 : 0;
  leitura |= s_bit << 1; 

  s_bit = analogRead(s_m) <= media_m ? 1 : 0;
  leitura |= s_bit << 1; 

  s_bit = analogRead(s_mdir) >= media_mdir ? 1 : 0;
  leitura |= s_bit << 2;

  s_bit = analogRead(s_dir) >= media_dir ? 1 : 0;
  leitura |= s_bit << 3;

  leitura = (~leitura) & 0b00001111;
} */

//* Inicio das funções, para cada caso
void vel_frente()
{
  serv_esq.write(100);
  serv_dir.write(80);
}

/*bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;*/

void vel_direita()
{
  int v = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023);
  v = (1023 - v) /102;
  int v2 = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023);
  v2 = (1023 - v2) /102;
  serv_esq.write(serv_esq.read() - v2); // talvez usar 90
  serv_dir.write(serv_dir.read() - v); //80
}
void vel_esquerda()
{
  int v = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023);
  v = (1023 - v) /102;
  int v2 = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023);
  v2 = (1023 - v2) /102;
  serv_esq.write(serv_esq.read() + v);
  serv_dir.write(serv_dir.read() + v2); // talvez usar 90
}
void vel_re()
{
  serv_esq.write(80);
  serv_dir.write(100);
}
void vel_parar(int velo_esq = velocidade_par)
{
  serv_esq.write(90);
  serv_dir.write(90);
  delay(velo_esq);
}

void esq_90() //* 90 esquerda
{
  vel_frente();
  delay(delay_fre);
  //vel_esquerda();
  serv_esq.write(80);
  serv_dir.write(80);
  delay(delay_peq);
  //while (((analogRead(s_mesq) <= media_mesq) || (analogRead(s_mdir) <= media_mdir)) && analogRead(s_esq) <= media_esq);
  //while ((analogRead(s_m) <= media_m) && (analogRead(s_dir) <= media_dir));
    //while ((map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500) && (map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500));

  //vel_re();
  //delay(delay_re);
}

void dir_90() //* 90 direita
{
  vel_frente();
  delay(delay_fre);
  //vel_direita();
  serv_esq.write(100);
  serv_dir.write(100);
  delay(delay_peq);
  //while ((analogRead(s_mesq) >= media_mesq) && (analogRead(s_mdir) >= media_mdir) /* && (analogRead(s_dir) <= media_dir) */);
  //while ((analogRead(s_m) <= media_m) && (analogRead(s_esq) <= media_esq));
  //while ((map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500) && (map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500));

  //vel_re();
  //delay(delay_re);
}
#endif
