#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H

#include <SoftwareWire.h>
#include <Adafruit_TCS34725_SWwire.h>
#include <Ultrasonic.h>

#include "medicoes.h"
#include "oled.h"
#include "MPU6050_BKP.h"

SoftwareWire sWire(A6, A5);
 
Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X); //direita
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X); //esquerda
MPU6050 mpu(Wire);


#include <Servo.h>
// mpu6050 i2c = 0x68

/* Definindo as portas dos sensores
                      Antes*/                     
#define s_esq  A2 //  A15
#define s_mesq A1  //  A2
#define s_m    A4  //  A0
#define s_mdir A0  //  A3
#define s_dir  A3  //  A4

// #define calpb
// #define caltcs

// #define branco_esq  971 // 967
// #define branco_mesq 975 // 969
// #define branco_m    980 // 972
// #define branco_mdir 977 // 971
// #define branco_dir  978 // 969

// #define preto_esq  816 // 853
// #define preto_mesq 736 // 792
// #define preto_m    507 // 485
// #define preto_mdir 634 // 664
// #define preto_dir  616 // 617

#define branco_esq  975 // 967
#define branco_mesq 976 // 969
#define branco_m    979 // 972
#define branco_mdir 978 // 971
#define branco_dir  976 // 969

#define preto_esq  835 // 853
#define preto_mesq 741 // 792
#define preto_m    504 // 485
#define preto_mdir 629 // 664
#define preto_dir  615 // 617

//Esquerda sendo branco e direita sendo preto
#define media_esq  (branco_esq  + preto_esq ) / 2
#define media_mesq (branco_mesq + preto_mesq) / 2
#define media_m    (branco_m    + preto_m   ) / 2
#define media_mdir (branco_mdir + preto_mdir) / 2
#define media_dir  (branco_dir  + preto_dir ) / 2

bool s_bit = false;
byte leitura = 0;
bool ver = false;     // O Verifica para os switchs

#define servo_esquerda 10
#define servo_direita 11
Servo serv_esq;
Servo serv_dir;

#define delay_fre 400 // 350
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
  uint8_t mesq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 200), 0, 200);
  uint8_t m    = constrain(map(analogRead(s_m)   , preto_m   , branco_m   , 0, 100), 0, 100);
  uint8_t mdir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 200), 0, 200);
  uint8_t dir  = constrain(map(analogRead(s_dir) , preto_dir , branco_dir , 0, 100), 0, 100);

  const uint8_t max = 50;
  *besq  = esq  <= (max+30);
  *bmesq = mesq <= (max*2);
  *bm    = m    <= (max+15);
  *bmdir = mdir <= (max*2);
  *bdir  = dir  <= (max+10);
}

/*
  esq:  1.00
  dir:  1.05
  verm: 1.10
*/

#define ESQ_VERDE_TOL 1.00 //07
#define DIR_VERDE_TOL 1.05 
bool verde(int r, int g, int b, float tol) { 
  // Serial.print(g);
  // Serial.print("/");
  // Serial.print((r + b + g) / 3);
  // Serial.print("-");
  // Serial.print(tol * (r + b + g) / 3);
  // Serial.print("\t");
  if ((r + b + g) / 3 >= 2900) return false;
  return (g >= tol * (r + b + g) / 3);
}

/**
  739 607 529 625
  581 564 497 547

  2791 2497 2215 2501
  2267 2229 2019 2171

  3924 3443 2977 3448
  3175 3049 2680 2968
*/

bool cinza1(int r, int g, int b) {
  float t = (r+g+b)/3;
  // if(t<1000 || t>2900)return false;
  return (t>=2000 && t<=2800);
}

bool cinza(int r1, int g1, int b1,
           int r2, int g2, int b2){
  float t1 = (r1+g1+b1)/3;
  float t2 = (r2+g2+b2)/3;
  float t = (t1+t2)/2;
  //if(t1<1000 || t2<1000 || t1>2900 ||t2>2900)return false;
  return ((t>=2000) && (t<=2800));
}

/*
 * trig == prim
 * echo == segun
 */

Ultrasonic ultra_sonico(6, 12);


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

void vel_direita()
{
  serv_esq.write(90);
  serv_dir.write(0);
  // serv_esq.write(60);
  // serv_dir.write(90);

  // uint8_t ddv = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 90), 0, 90);
  // Serial.print(ddv);Serial.print("&");
  // serv_esq.write(constrain(90 - ddv, 0, 90));
  // serv_dir.write(constrain(90 - (90 - ddv/2), 0, 90));
  
  // uint8_t ddv_dir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 90), 0, 90);
  // uint8_t ddv_esq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 90), 0, 90);
  // ddv_dir = (90 - ddv_dir) /9;
  // ddv_esq = (90 - ddv_esq) /9;
  // serv_esq.write(90 + (ddv_esq*10));
  // serv_dir.write(90 + (ddv_dir*10)); //80 
}
void vel_esquerda()
{
  serv_esq.write(180);
  serv_dir.write(90);

  // serv_esq.write(90);
  // serv_dir.write(120);

  // uint8_t ddv_dir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 90), 0, 90);
  // uint8_t ddv_esq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 90), 0, 90);
  // ddv_dir = (90 - ddv_dir) /9;
  // ddv_esq = (90 - ddv_esq) /9;
  // serv_esq.write(90 - (ddv_esq*10));
  // serv_dir.write(90 - (ddv_dir*10));

  // uint8_t ddv = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 90), 0, 90);
  // Serial.print(ddv);Serial.print("&");
  // serv_esq.write(constrain(90 + ddv, 90, 180));
  // serv_dir.write(constrain(90 + (90 - ddv/2), 90, 180));
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

void giro_dir_ang(int angulo) {
  serv_esq.write(180);
  serv_dir.write(180);
  delay(medicoes::dir_giro_ms_max(angulo));
}

void giro_esq_ang(int angulo) {
  serv_esq.write(0);
  serv_dir.write(0);
  delay(medicoes::esq_giro_ms_max(angulo));
}

void giro_dir_ang_mpu(int angulo) {
  int yaw = 0;
  mpu.reset_yaw();
  serv_esq.write(180);
  serv_dir.write(180);
  while(abs(yaw) < angulo) {
    mpu.update();
    yaw = mpu.yaw();
  }
}

void giro_esq_ang_mpu(int angulo) {
  int yaw = 0;
  mpu.reset_yaw();
  serv_esq.write(0);
  serv_dir.write(0);
  while(abs(yaw) < angulo) {
    mpu.update();
    yaw = mpu.yaw();
  }
}

void obstaculo(bool dir = true) {
  OLED::print_obs();
  unsigned dl90 = (dir) ? 2000: 2050;

  serv_esq.write(180*dir);
  serv_dir.write(180*dir);//45ang/s
  delay(dl90); // 90graus dir

  //8cm/s
  vel_frente_max();
  delay(2400);//LARGURA*0.8/8
  // delay(medicoes::frente_ms_max(LARGURA*0.8));

  serv_esq.write(180 - (180*dir));
  serv_dir.write(180 - (180*dir));//43.9ang/s
  delay(1800); //90graus esq

  //8cm/s
  vel_frente_max(); // 8cm/s
  delay(4850); //35cm

  serv_esq.write(180 - (180*dir));
  serv_dir.write(180 - (180*dir));//43.9ang/s
  delay(1600); //90graus esq

  vel_frente_max(); //8cm/s
  delay(700); //LARGURA*0.8/8 - 300ms
  while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=50) {}
  vel_frente();
  delay(225);


  serv_esq.write(180*dir);
  serv_dir.write(180*dir);//45ang/s
  delay(1333); //60graus dir

  while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=30) {
      if(constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=50) {
        giro_esq_ang(30);
        break;
      }
  }

  vel_re_max();
  delay(125);
}

void esq_90() //* 90 esquerda
{

  vel_frente();
  delay(delay_fre);
  serv_esq.write(0);
  serv_dir.write(0);
  delay(delay_peq);
  Serial.println("passo");
  while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=50  &&
        constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=50) {}
}

void dir_90() //* 90 direita
{
  vel_frente();
  delay(delay_fre);
  serv_esq.write(180);
  serv_dir.write(180);
  delay(delay_peq);
  Serial.println("passo");

    while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=65  &&
          constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=20) {}
}
#endif
