#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H


#include <Servo.h>
#include "Wire.h"

#include "./MPU6050_BKP.h"

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

#define analog_esq 501
#define analog_dir 501 

// diminuir 20 do max
#define max_oeste 490
#define max_noroeste 40 // menos esse, foi 10
#define max_norte 640
#define max_nordeste 835
#define max_leste 638

bool s_bit = false;
byte leitura = 0;
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
#define delay_re 30
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

//* Definicao variadas
#define bot A10

void calibra()
{
  leitura = 0;

  if (analogRead(s_oeste) >= max_oeste)
    s_bit = true;
  else
    s_bit = false;

  leitura |= s_bit << 0;
  if (analogRead(s_noroeste) >= max_noroeste)
    s_bit = true;
  else
    s_bit = false;

  leitura |= s_bit << 1;
  if (analogRead(s_nordeste) >= max_norte)
    s_bit = true;
  else
    s_bit = false;

  leitura |= s_bit << 2;
  if (analogRead(s_nordeste) >= max_nordeste)
    s_bit = true;
  else
    s_bit = false;

  leitura |= s_bit << 3;
  if (analogRead(s_leste) >= max_leste)
    s_bit = true;
  else
    s_bit = false;

  leitura |= s_bit << 4;
  leitura = (~leitura) & 0b00011111;  
}


//* Inicio das funções, para cada caso
void vel_frente(int velo_esq = velocidade_fre, int velo_dir = velocidade_fre)
{
  serv_esq.write(180);
  serv_dir.write(0);
}
void vel_direita(int velo_esq = velocidade_fre)
{
  serv_esq.write(180);
  serv_dir.write(180);
}
void vel_esquerda(int velo_dir = velocidade_fre)
{
  serv_esq.write(0);
  serv_dir.write(0);
}
void vel_re(int velo_esq = velocidade_tras, int velo_dir = velocidade_tras)
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

#endif