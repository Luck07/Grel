#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H

#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(52, 53);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);

#include "EEPROMLogger.h"
#include <Ultrasonic.h>
#include <Servo.h>
// mpu6050 i2c = 0x68

#define serial_on 1
#if serial_on
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#define T90 0 // Se tiver 90 com T colocar 1, caso nao deixar 0

//* Definindo as portas dos sensores
#define s_oeste A3     //
#define s_noroeste A1 //
#define s_norte A4     //
#define s_nordeste A0 //
#define s_leste A2     //
#define analog_esq 501 // Valor que serve o quanto ele ver o cinza no micro ajuste
#define analog_dir 501 //
bool ver = false;      // O Verifica para os switchs

/*
 * 
 * 
*/
#define servo_esquerda 8
#define servo_direita 7
Servo serv_esq;
Servo serv_dir;
#define delay_fre 300
#define delay_re 3000
#define delay_peq 300 
//#define delay_peq 99999
#define delay_pas 999999

//* Definindo velocidades
#define velocidade_fre 180
#define velocidade_tras 0
#define velocidade_par 40  // Delay para o tempo dele ficar parado

//* Valores com Millis
long int millis_ant = 0;
#define time_log 2000
#define time_branco 1500 // tempo suficiente para achar o gap, mas nao se perder tanto na linha
#define time_branco_while 2000 // tempo para ele voltar para linha

//* Valores para desviar obstaculo
#define desv_lado 1
#define delay_peq_desv 99999
#define frente_1 900  // Valor que ele se distancia do obstaculo
#define frente_2 1450 // Valor que faz ele ultrapassar o obstaculo
#define frente_3 550  // Valor que faz ele nao se perder em qualquer linha
#define enc_90 580
#define enc_90_2 enc_90 + 40 // Seguunda vez que ele executa o 90 / 70
#define enc_90_3 enc_90 + 27 // E a terceira / 140

//* Valores para sala de resgate
Servo serv_vertical;
#define serv_vertical_pin 7
#define serv_vertical_min 12
#define serv_vertical_max 90
Servo serv_porta;
#define serv_porta_pin 6
#define serv_porta_min 0
#define serv_porta_max 180
#define serv_delay 500

/*
 * trig == prim (marrom)
 * echo == segun (amarelo)
 */
Ultrasonic ult_meio(30, 31);

//* Definicao variadas
#define bot A10

void calibra()
{


  
}


//* Inicio das funções, para cada caso
void vel_frente(int velo_esq = velocidade_fre, int velo_dir = velocidade_fre)
{
  serv_esq.write(velo_esq);
  serv_dir.write(velo_dir);
}
void vel_direita(int velo_esq = velocidade_fre)
{
  serv_esq.write(velo_esq);
  serv_dir.write(0);
}
void vel_esquerda(int velo_dir = velocidade_fre)
{
  serv_esq.write(0);
  serv_dir.write(velo_dir);
}
void vel_re(int velo_esq = velocidade_tras, int velo_dir = velocidade_tras)
{
  serv_esq.write(velo_esq);
  serv_dir.write(velo_dir);
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
void desv(int velo_esq = velocidade_fre, int velo_dir = velocidade_fre)
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
  vel_frente(velo_esq, velo_dir);            //* Terminando com while para ele encontrar a linah correta
  debug("andando para frente (encontrar linha)");
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1)); 
  delay(delay_peq_desv); //* Se afastando um pouco da linha
  vel_esquerda(velo_esq);             //* Virando para esquerda para se ajeiar na faixa
  debug("Virando esquerda (se ajustar na linha): ");
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1));
#else                                         //! Direita
  delay(enc_90);    //* Girando para direita
  delay(frente_1);   //* Se distanciando do obstaculo
  delay(enc_90_2); //* Virando para esquerda, com valor variado para nao girar demais
  delay(frente_2);   //* Passando do obstaculo
  delay(enc_90_3); //* Virando para esquerda, mesmo moitvo anterior
  delay(frente_3);   //* Andando em frente, para ele nao se confundir linhas aleatorias
  vel_frente(velo_esq, velo_dir);             //* Terminando com while para ele encontrar a linah correta
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("andando para frente (encontrar linha): ");
    debugln(enc.read());
  }
  delay(enc_peq_desv); //* Se afastando um pouco da linha
  vel_dir(velo_esq, velo_dir);                  //* Virando para direita para se ajeiar na faixa
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("Virando direita (se ajustar na linha): ");
    debugln(enc.read());
  }
#endif
}

void esq_90(int velo_esq = velocidade_fre, int velo_dir = velocidade_fre) //* 90 esquerda
{
  //if(sensi() == verde_branco)
  
  vel_frente(velo_esq, velo_dir);
  delay(delay_fre);

  if (digitalRead(s_norte) == 1)
  {
    vel_esquerda(velo_esq);
    delay(delay_peq);
    while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_oeste) == 1);
    // while ((digitalRead(s_norte) == 1) && (digitalRead(s_oeste) == 1));
    vel_re(velo_esq, velo_dir);
    delay(delay_re);
  }
}

void dir_90(int velo_esq = velocidade_fre, int velo_dir = velocidade_fre) //* 90 direita
{
  vel_frente(velo_esq, velo_dir);
  delay(delay_fre);

  if (digitalRead(s_norte) == 1)
  {
    vel_direita(velo_dir);
    delay(delay_peq);
    while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_leste) == 1);
    // while ((digitalRead(s_norte) == 1) && (digitalRead(s_leste) == 1));
    vel_re(velo_esq, velo_dir);
    delay(delay_re);
  }
}

void micro_ajuste_inv()
{
  if ((analogRead(s_noroeste) <= analog_esq) && (analogRead(s_nordeste) >= analog_dir)) //! Fazer micro ajuste para esquerda
  {
    vel_esquerda();
    debugln("leitura == 0010 / ajustando para esquerda");
  }
  else if ((analogRead(s_noroeste) >= analog_esq) && (analogRead(s_nordeste) <= analog_dir)) //! Fazer micro ajuste para direita
  {
    vel_direita();
    debugln("leitura == 0100 / ajustando para direita");
  }
  else
  {
    vel_re();
  }
}
#endif