#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H
#include "EEPROMLogger.h"
#include <Ultrasonic.h>
#include <Encoder.h>
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
#define s_oeste 22     //
#define s_noroeste A15 //
#define s_norte 32     //
#define s_nordeste A14 //
#define s_leste 26     //
#define analog_esq 501 // Valor que serve o quanto ele ver o cinza no micro ajuste
#define analog_dir 501 //
bool ver = false;      // O Verifica para os switchs

/*
 * Motor 1 = Esquerda (enc)
 * Motor 2 = Direita
 */
#define mot_in1 9  // laranja, direita, tras
#define mot_in2 10 // preto, direita, frente
#define mot_in3 11 // vermelho, esquerda, frente
#define mot_in4 12 // verde, esquerda, tras

//* Definindo velocidades
#define vel_esq 180 // PWM usado para a velocidade, min == 0 e max == 255
#define vel_dir 170 //
#define mot_par 40  // Delay para o tempo dele ficar parado

//* Valores com Millis
long int millis_ant = 0;
#define time_log 2000
#define time_branco 1500 // tempo suficiente para achar o gap, mas nao se perder tanto na linha
#define time_branco_while 2000 // tempo para ele voltar para linha

//* Valores para encoders
Encoder enc(3, 2);       // Encoder do motor da esquerda
long int enc_ant = 0;    // Valor do encoder anterior
#define enc_fre 170      // Frente apos ver 90 / 140
#define enc_peq 130      // Valor que vira para completar com while /
#define enc_pas 40       // Valor que vai para atras /
#define enc_pas_outro 30 // Valor que vai para atras na passagem ver /
#define enc_passo 10

//* Valores para desviar obstaculo
#define desv_lado 1
#define enc_peq_desv 180
#define frente_1 900  // Valor que ele se distancia do obstaculo
#define frente_2 1450 // Valor que faz ele ultrapassar o obstaculo
#define frente_3 550  // Valor que faz ele nao se perder em qualquer linha
#define enc_90 580
#define enc_90_2 enc_90 + 40 // Seguunda vez que ele executa o 90 / 70
#define enc_90_3 enc_90 + 27 // E a terceira / 140

//* Valores para servo
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

//* Inicio das funções, para cada caso
void mot1_anti(int velo = vel_esq)
{
  analogWrite(mot_in4, velo);
  analogWrite(mot_in3, 0);
}
void mot1_hor(int velo = vel_esq)
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo);
}
void mot1_par()
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, 0);
}

void mot2_anti(int velo = vel_dir)
{
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo);
}
void mot2_hor(int velo = vel_dir)
{
  analogWrite(mot_in2, velo);
  analogWrite(mot_in1, 0);
}
void mot2_par()
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void vel_frente(int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo_esq);
  analogWrite(mot_in2, velo_dir);
  analogWrite(mot_in1, 0);
}
void vel_direita(int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo_esq);
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo_dir);
}
void vel_esquerda(int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  analogWrite(mot_in4, velo_esq);
  analogWrite(mot_in3, 0);
  analogWrite(mot_in2, velo_dir);
  analogWrite(mot_in1, 0);
}
void vel_re(int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  analogWrite(mot_in4, velo_esq);
  analogWrite(mot_in3, 0);
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo_dir);
}
void vel_parar(int velo_esq = mot_par)
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, 0);
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, 0);
  delay(velo_esq);
}

void enc_frente(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  vel_frente(velo_esq, velo_dir);
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_valor)
  {
    debug("Indo frente: ");
    debugln(enc.read());
  }
}

void enc_direita(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  vel_direita(velo_esq, velo_dir);
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_valor)
  {
    debug("Virando direita: ");
    debugln(enc.read());
  }
}

void enc_esquerda(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  vel_esquerda(velo_esq, velo_dir);
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_valor)
  {
    debug("Virando esquerda: ");
    debugln(enc.read());
  }
}

void enc_re(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  vel_re(velo_esq, vel_dir);
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_valor)
  {
    debug("Indo atras: ");
    debugln(enc.read());
  }
}

/**
 *! false = direita
 *! true = esquerda
 */
void desv(int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_re(enc_pas_outro, velo_esq, velo_dir); //* Dando um passo para atras, isso e bom caso a traseira do robo e maior do que na frente
/*mot1_par();                                //* Colocando pra parar bem rapido pq sim
mot2_par();
delay(mot_par);*/
#if desv_lado                                //! Esquerda
  enc_esquerda(enc_90, velo_esq, velo_dir);  //* Girando para esquerda
  enc_frente(frente_1, velo_esq, velo_dir);  //* Se distanciando do obstaculo
  enc_direita(enc_90_2, velo_esq, velo_dir); //* Virando para direita, com valor variado para nao girar demais
  enc_frente(frente_2, velo_esq, velo_dir);  //* Passando do obstaculo
  enc_direita(enc_90_3, velo_esq, velo_dir); //* Virando para direita, mesmo moitvo anterior
  enc_frente(frente_3, velo_esq, velo_dir);  //* Andando em frente, para ele nao se confundir linhas aleatorias
  vel_frente(velo_esq, velo_dir);            //* Terminando com while para ele encontrar a linah correta
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("andando para frente (encontrar linha): ");
    debugln(enc.read());
  }
  enc_frente(enc_peq_desv, velo_esq, velo_dir); //* Se afastando um pouco da linha
  vel_esquerda(velo_esq, velo_dir);             //* Virando para esquerda para se ajeiar na faixa
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("Virando esquerda (se ajustar na linha): ");
    debugln(enc.read());
  }
#else                                         //! Direita
  enc_direita(enc_90, velo_esq, velo_dir);    //* Girando para direita
  enc_frente(frente_1, velo_esq, velo_dir);   //* Se distanciando do obstaculo
  enc_esquerda(enc_90_2, velo_esq, velo_dir); //* Virando para esquerda, com valor variado para nao girar demais
  enc_frente(frente_2, velo_esq, velo_dir);   //* Passando do obstaculo
  enc_esquerda(enc_90_3, velo_esq, velo_dir); //* Virando para esquerda, mesmo moitvo anterior
  enc_frente(frente_3, velo_esq, velo_dir);   //* Andando em frente, para ele nao se confundir linhas aleatorias
  vel_frente(velo_esq, velo_dir);             //* Terminando com while para ele encontrar a linah correta
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("andando para frente (encontrar linha): ");
    debugln(enc.read());
  }
  enc_frente(enc_peq_desv, velo_esq, velo_dir); //* Se afastando um pouco da linha
  vel_dir(velo_esq, velo_dir);                  //* Virando para direita para se ajeiar na faixa
  while ((digitalRead(s_noroeste) == 1) && (digitalRead(s_nordeste) == 1))
  {
    debug("Virando direita (se ajustar na linha): ");
    debugln(enc.read());
  }
#endif
}

void esq_90(int velo_esq = vel_esq, int velo_dir = vel_dir) //* 90 esquerda
{
  enc_frente(enc_fre, velo_esq, velo_dir);
#if T90
  if (digitalRead(s_norte) == 1)
  {
    enc_esquerda(enc_peq, velo_esq, velo_dir);
    vel_esquerda(velo_esq, velo_dir);
    while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_oeste) == 1)
    // while ((digitalRead(s_norte) == 1) && (digitalRead(s_oeste) == 1))
    {
    }
    enc_re(enc_pas);
  }
#else
  enc_esquerda(enc_peq, velo_esq, velo_dir);
  vel_esquerda(velo_esq, velo_dir);
  while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_oeste) == 1)
  // while ((digitalRead(s_norte) == 1) && (digitalRead(s_oeste) == 1))
  {
  }
  enc_re(enc_pas);
#endif
}

void dir_90(int velo_esq = vel_esq, int velo_dir = vel_dir) //* 90 direita
{
  enc_frente(enc_fre, velo_esq, velo_dir);
#if T90
  if (digitalRead(s_norte) == 1)
  {
    enc_direita(enc_peq, velo_esq, velo_dir);
    vel_direita(velo_esq, velo_dir);
    while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_leste) == 1)
    // while ((digitalRead(s_norte) == 1) && (digitalRead(s_leste) == 1))
    {
    }
    enc_re(enc_pas);
  }
#else
  enc_direita(enc_peq, velo_esq, velo_dir);
  vel_direita(velo_esq, velo_dir);
  while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_leste) == 1)
  // while ((digitalRead(s_norte) == 1) && (digitalRead(s_leste) == 1))
  {
  }
  enc_re(enc_pas);
#endif
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