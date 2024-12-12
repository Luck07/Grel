#ifndef _OLED_H
#define _OLED_H

#include <MicroLCD.h>

#define OLED_W 128
#define OLED_H 64
#define lw 6
#define lh 8
#define W OLED_W/lw
#define H OLED_H/lh

LCD_SSD1306 display; 

namespace OLED {

  inline int center(int strlen) { return (W - strlen) * (lw/2); }

 void print_sens(bool besq, bool bmesq, bool bm, bool bmdir, bool bdir) {
  display.clearLine(0);
  display.setCursor(center(5), 0);
  display.print(besq);
  display.print(bmesq);
  display.print(bm);
  display.print(bmdir);
  display.print(bdir);
 }

 void print_obs() {
  display.clearLine(1);
  display.setCursor(center(9), 1);
  display.print("OBSTACULO");
 }

  void print_90(bool direita, bool ver) {
    display.clearLine(1);
    if(ver)
      display.setCursor(center(17), 1);
    else
      display.setCursor(center(12), 1);
    
    if(direita)
      display.print("90 dir ");
    else
      display.print("90 esq ");

    if(ver)
      display.print("verdadeiro");
    else
      display.print("falso");
 }

 void print_frente(bool ver) {
  display.clearLine(1);
  //frente Verdadeiro
  if(ver) {
   display.setCursor(center(17), 1);
   display.print("frente verdadeiro");
  } else {
   display.setCursor(center(6), 1);
   display.print("frente");
  }
 }

  void print_micro(bool direita, bool ver) {
   //micro esq verdadeiro
   display.clearLine(1);
   if(ver)
    display.setCursor(center(20), 1);
   else
    display.setCursor(center(9), 1);
   
   if(direita)
    display.print("micro dir ");
   else
    display.print("micro esq ");
   
   if(ver)
    display.print("verdadeiro");
 }

 void print_gap(bool ver) {
  display.clearLine(1);
  if(!ver) {
    display.setCursor(center(3), 1);
    display.print("gap");
  } else {
    display.setCursor(center(14), 1);
    display.print("gap verdadeiro");
  }
 }

 void print_encru() {
  display.clearLine(1);
  display.setCursor(center(5), 1);
  display.print("encru");
 }

 void print_verdes(bool esq, bool dir) {
  display.clearLine(2);

  //verde / verde
  display.setCursor(center(13), 2);
  if(esq)
   display.print("verde");
  else
   display.print(".....");

  display.setCursor(center(13) + (6*lw), 2);
  display.print("/");

  display.setCursor(center(13) + (8*lw), 2);
  if(dir)
   display.print("verde");
  else
   display.print(".....");
 }

 void print_ult(int ult) {
  display.clearLine(6);
  display.setCursor(center((ult<9)?1:2), 6);
  display.print(ult);
 }

  void print_refyaw(float yaw) {
  display.clearLine(5);
  display.setCursor(center(18), 5);//11+7
  display.print("yaw (ref): ");
  display.print(yaw);
  }

 void print_yaw(float yaw) {
  display.clearLine(4);
  display.setCursor(center(18), 4);
  display.print("yaw      : ");
  display.print(yaw);
 }
}

#endif