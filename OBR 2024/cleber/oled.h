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
 void print_sens(bool besq, bool bmesq, bool bm, bool bmdir, bool bdir) {
  display.clearLine(0);
  display.setCursor((W*lw/2) - (5*lw/2),0);
  display.print(besq);
  display.print(bmesq);
  display.print(bm);
  display.print(bmdir);
  display.print(bdir);
 }

  void print_90(bool direita, bool ver) {
    display.clearLine(1);
    if(ver)
    display.setCursor((W*lw/2) - (17*lw/2), 1);
    else
    display.setCursor((W*lw/2) - (12*lw/2), 1);
    
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
   display.setCursor((W*lw/2) - (17*lw/2), 1);
   display.print("frente verdadeiro");
  } else {
   display.setCursor((W*lw/2) - (6*lw/2), 1);
   display.print("frente");
  }
 }

  void print_micro(bool direita, bool ver) {
   //micro esq verdadeiro
   display.clearLine(1);
   if(ver)
    display.setCursor((W*lw/2) - (20*lw/2), 1);
   else
    display.setCursor((W*lw/2) - (9*lw/2), 1);
   
   if(direita)
    display.print("micro dir ");
   else
    display.print("micro esq ");
   
   if(ver)
    display.print("verdadeiro");
 }

 void print_gap() {
  display.clearLine(1);
  display.setCursor((W*lw/2) - (3*lw/2), 1);
  display.print("gap");
 }

 void print_encru() {
  display.clearLine(1);
  display.setCursor((W*lw/2) - (5*lw/2), 1);
  display.print("encru");
 }

 void print_verdes(bool esq, bool dir) {
  display.clearLine(2);

  //verde / verde
  display.setCursor((W*lw/2) - (13*lw/2), 2);
  if(esq)
   display.print("verde");
  else
   display.print(".....");

  display.setCursor((W*lw/2) - (13*lw/2) + (6*lw), 2);
  display.print("/");

  display.setCursor((W*lw/2) - (13*lw/2) + (8*lw), 2);
  if(dir)
   display.print("verde");
  else
   display.print(".....");
 }
}

#endif