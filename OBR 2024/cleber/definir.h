#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H

#include <SoftwareWire.h>
#include <Adafruit_TCS34725_SWwire.h>

#include "medicoes.h"
#include "oled.h"

SoftwareWire sWire(6, 7);
 
Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X); //direita
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X); //esquerda

//#include <Ultrasonic.h>
#include <Servo.h>
// mpu6050 i2c = 0x68

//* Definindo as portas dos sensores
#define s_esq  A15 // A15
#define s_mesq A2  // A2
#define s_m    A0  // A0
#define s_mdir A3  // A3
#define s_dir  A4  // A4

#define branco_esq  972 // 949 
#define branco_mesq 974 // 974
#define branco_m    976 // 976
#define branco_mdir 976 // 959
#define branco_dir  973 // 863

#define preto_esq  830 // 822
#define preto_mesq 746 // 687
#define preto_m    563 // 477
#define preto_mdir 626 // 580
#define preto_dir  686 // 540

//Esquerda sendo branco e direita sendo preto
#define media_esq (branco_esq + preto_esq) / 2
#define media_mesq (branco_mesq + preto_mesq) / 2
#define media_m (branco_m + preto_m) / 2
#define media_mdir (branco_mdir + preto_mdir) / 2
#define media_dir (branco_dir + preto_dir) / 2

bool s_bit = false;
byte leitura = 0;
bool ver = false;     // O Verifica para os switchs

#define servo_esquerda 11
#define servo_direita 12
Servo serv_esq;
Servo serv_dir;

#define delay_fre 300 // 350
#define velocidade_par 300  // 300
#define delay_re 300 // 300
#define delay_peq 100 //100


//* Valores para desviar obstaculo
#define desv_lado 1
#define delay_peq_desv 99999
#define frente_1 900  // Valor que ele se distancia do obstaculo
#define frente_2 1450 // Valor que faz ele ultrapassar o obstaculo
#define frente_3 550  // Valor que faz ele nao se perder em qualquer linha
#define enc_90 580
#define enc_90_2 enc_90 + 40 // Seguunda vez que ele executa o 90 / 70
#define enc_90_3 enc_90 + 27 // E a terceira / 140

void ler_sensores(bool* besq, bool* bmesq, bool* bm, bool* bmdir, bool* bdir) {
  uint8_t esq  = constrain(map(analogRead(s_esq) , preto_esq , branco_esq , 0, 100), 0, 100);
  uint8_t mesq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 100), 0, 100);
  uint8_t m    = constrain(map(analogRead(s_m)   , preto_m   , branco_m   , 0, 100), 0, 100);
  uint8_t mdir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 100), 0, 100);
  uint8_t dir  = constrain(map(analogRead(s_dir) , preto_dir , branco_dir , 0, 100), 0, 100);

  const uint8_t max = 50;
  *besq  = esq  <= (max - 30);
  *bmesq = mesq <= (max);
  *bm    = m    <= (max + 15);
  *bmdir = mdir <= (max);
  *bdir  = dir  <= (max);
}

/*
 * trig == prim
 * echo == segun
 */

//Ultrasonic ult_meio(30, 31);

//* Inicio das funções, para cada caso
void vel_frente()
{
  serv_esq.write(120);
  serv_dir.write(60);
}

void vel_frente_max() {
  serv_esq.write(180);
  serv_dir.write(0);
}

/*bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;*/

void vel_direita()
{
  serv_esq.write(0);
  serv_dir.write(0);
  
  // uint8_t ddv_dir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023), 0, 1023);
  // uint8_t ddv_esq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023), 0, 1023);
  // ddv_dir = (1023 - ddv_dir) /100;
  // ddv_esq = (1023 - ddv_esq) /100;

  // serv_esq.write(90 - (ddv_esq*0.75));
  // serv_dir.write(90 - ddv_dir); //80 
  
//   serv_esq.write(serv_esq.read() - ddv_esq);
//   serv_dir.write(serv_dir.read() - ddv_dir); //80 


  // int v = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 70);
  // int v2 = map(analogRead(s_mdir), preto_mdir, branco_mdir, 80, 180);
  // serv_esq.write(v);
  // serv_dir.write(v2);
}
void vel_esquerda()
{
  serv_esq.write(180);
  serv_dir.write(180);

  // uint8_t ddv_dir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023), 0, 1023);
  // uint8_t ddv_esq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023), 0, 1023);
  // ddv_dir = (1023 - ddv_dir) /100;
  // ddv_esq = (1023 - ddv_esq) /100;

  // serv_esq.write(90 + ddv_esq);
  // serv_dir.write(90 + (ddv_dir*0.75));

//   serv_esq.write(serv_esq.read() + ddv_esq);
//   serv_dir.write(serv_dir.read() + ddv_dir);


  // int v = map(analogRead(s_mesq), preto_mesq, branco_mesq, 80, 180);
  // int v2 = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 70);
  // serv_esq.write(v2);
  // serv_dir.write(v);
}
void vel_re()
{
  serv_esq.write(60);
  serv_dir.write(120);
}

void vel_re_max() {
  serv_esq.write(0);
  serv_dir.write(180);
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

    serv_esq.write(0);
    serv_dir.write(0);
    delay(delay_peq);
    Serial.println("passo");
    
    // for(;;) {

    //   if(constrain(map(analogRead(s_m), preto_m, branco_m, 0, 100), 0, 100) <= 50) {
    //     break;
    //   }

    //   if(constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100) <= 50) {
        // serv_esq.write(80);
        // serv_dir.write(100);
        // delay(820);

        // serv_dir.write(90);
        // serv_esq.write(180);
        // delay(1800/2);

        // serv_esq.write(100);
        // serv_dir.write(80);
        // delay(820/2);

        //* velocidade (medida):  ~16cm/s, largura (medida): 13cm
        //* velocidade angular (direita): 450º/9s = 360º/7.2s = 50º/s = 1.7453 rad/s
        //* 16cm--1s / 13/2cm--0.41s
        //* 450º--9s / 90º--1.8s

    //     break;
    //   }
    // }
    while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=50  &&
          constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=50) {}

    //while(map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500) { }

  //vel_re();
  //delay(delay_re);
}

void dir_90() //* 90 direita
{
    vel_frente();
    delay(delay_fre);
  //vel_direita();
    serv_esq.write(180);
    serv_dir.write(180);
    delay(delay_peq);
    Serial.println("passo");

    // for(;;) {
      
    //   if(constrain(map(analogRead(s_m), preto_m, branco_m, 0, 100), 0, 100) <= 50) {
    //     break;
    //   }

    //   if(constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)<=50) {
        // serv_esq.write(80);
        // serv_dir.write(100);
        // delay(820);

        // serv_dir.write(0);
        // serv_esq.write(90);
        // delay(1800/2);

        // serv_esq.write(100);
        // serv_dir.write(80);
        // delay(820/2);

        //* velocidade (medida):  ~16cm/s, largura (medida): 13cm
        //* velocidade angular (direita): 450º/9s = 360º/7.2s = 50º/s = 1.7453 rad/s
        //* 16cm--1s / 13/2cm--0.41s
        //* 450º--9s / 90º--1.8s

    //     break;
    //   }
    // }

    while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=65  &&
          constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=20) {}

  //vel_re();
  //delay(delay_re);
}
#endif
