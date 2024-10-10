#include <MicroLCD.h>

#define OLED_W 128
#define OLED_H 64
#define lw 6
#define lh 8
#define W OLED_W/lw
#define H OLED_H/lh

// SELE 3
// CIMA  4
// BAIX  5
// testar ^

#define BTN_SELE 2
#define BTN_CIMA 3
#define BTN_BAIX 4
#define BTN_COOLDOWN 200 // ms

LCD_SSD1306 display;

enum telas {
  inicio=0, segue, calibra, resultados, dansa,
  cal_infra, cal_verde, cal_vel,
  res_infra, res_verde, res_vel,
};

int pos = 1;
int scr = inicio;

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setFontSize(FONT_SIZE_SMALL);
  display.clear();

  pinMode(BTN_SELE, INPUT_PULLUP);
  pinMode(BTN_CIMA, INPUT_PULLUP);
  pinMode(BTN_BAIX, INPUT_PULLUP);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

unsigned long mil = millis();

int center(int strlen) { return (W - strlen) * (lw/2); }

void loop() {
  bool cim = !digitalRead(BTN_CIMA);
  bool bai = !digitalRead(BTN_BAIX);
  bool sel = !digitalRead(BTN_SELE);
  digitalWrite(5, digitalRead(BTN_SELE));
  digitalWrite(6, digitalRead(BTN_CIMA));
  digitalWrite(7, digitalRead(BTN_BAIX));

  Serial.print(pos);Serial.print(" ");

  
  unsigned long btn_mil = millis() - mil;
  // inicio=0, segue, calibra, resultados, dansa,
  // cal_infra, cal_verde, cal_vel,
  // res_infra, res_verde, res_vel,
  int lims[] = {4, 1, 4, 4, 1,
                1, 1, 1,
                1, 1, 1};

  Serial.print(scr); Serial.print(" ");
  Serial.println(btn_mil);
  if((cim || bai || sel) && btn_mil>BTN_COOLDOWN) {
    mil = millis();

    // sem loop de cima/baixo
    // if((pos>1 && cim) || (pos<lims[scr] && bai)) {
    //   display.clearLine(pos);
    //   pos += (bai - cim);
    //   display.clearLine(pos);
    // }

    // com loop
    if(cim) {
      display.clearLine(pos);
      pos = (pos>1) ? pos-1 : lims[scr];
      display.clearLine(pos);
    }
    if(bai) {
      display.clearLine(pos);
      pos = (pos<lims[scr]) ? pos+1 : 1;
      display.clearLine(pos);
    }
  }

  switch(scr){
    case inicio: //inicio
      display.setCursor(center(6), 0);
      display.print("inicio");

      display.setCursor(0, pos); display.print(">");
      display.setCursor(7, 1); display.print("sege faxa");
      display.setCursor(7, 2); display.print("calibrar");
      display.setCursor(7, 3); display.print("resulktados");
      display.setCursor(7, 4); display.print("dansa");
      
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        switch(pos) {
          case 1: scr = segue; break;
          case 2: scr = calibra; break;
          case 3: scr = resultados; break;
          case 4: scr = dansa; break;
        }
        pos = 1;
      }
      break;
    case segue: //sege
      display.setCursor(center(5), 0);
      display.print("segue");
      display.setCursor(0, 1); display.print("sigo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = inicio;
        pos = 1;
      }
      break;
    case calibra: //calibra
      display.setCursor(center(7), 0);
      display.print("calibra");

      display.setCursor(0, pos); display.print(">");
      display.setCursor(7, 1); display.print("infra");
      display.setCursor(7, 2); display.print("verde");
      display.setCursor(7, 3); display.print("velocidade");
      display.setCursor(7, 4); display.print("voltar");
      
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        switch(pos) {
          case 1: scr = cal_infra; break;
          case 2: scr = cal_verde; break;
          case 3: scr = cal_vel; break;
          case 4: scr = inicio; break;
        }
        pos = 1;
      }
      break;
    case resultados:
      display.setCursor(center(10), 0);
      display.print("resultados");

      display.setCursor(0, pos); display.print(">");
      display.setCursor(7, 1); display.print("infra");
      display.setCursor(7, 2); display.print("verde");
      display.setCursor(7, 3); display.print("velocidade");
      display.setCursor(7, 4); display.print("voltar");

      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        switch(pos) {
          case 1: scr = res_infra; break;
          case 2: scr = res_verde; break;
          case 3: scr = res_vel; break;
          case 4: scr = inicio; break;
        }
        pos = 1;
      }
      break;
    case dansa:
      display.setCursor(center(11), 4);
      display.print("EM BREVE...");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = inicio;
        pos = 1;
      }
      break;
    case cal_infra:
      display.setCursor(center(5), 0);
      display.print("infra");

      display.setCursor(0, 1);
      display.print("calibra mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = calibra;
        pos = 1;
      }
      break;
    case cal_verde:
      display.setCursor(center(5), 0);
      display.print("verdre");

      display.setCursor(0, 1);
      display.print("calibra mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = calibra;
        pos = 1;
      }
      break;
    case cal_vel:
      display.setCursor(center(10), 0);
      display.print("velocidade");

      display.setCursor(0, 1);
      display.print("calibra mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = calibra;
        pos = 1;
      }
      break;
    case res_infra:
      display.setCursor(center(5), 0);
      display.print("infra");

      display.setCursor(0, 1);
      display.print("ve mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = resultados;
        pos = 1;
      }
      break;
    case res_verde:
      display.setCursor(center(5), 0);
      display.print("verde");

      display.setCursor(0, 1);
      display.print("ve mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = resultados;
        pos = 1;
      }
      break;
    case res_vel:
      display.setCursor(center(11), 0);
      display.print("velocidades");

      display.setCursor(0, 1);
      display.print("ve mesmo");
      if(sel && btn_mil>BTN_COOLDOWN) {
        display.clear();
        scr = resultados;
        pos = 1;
      }
      break;
    default:
      display.setCursor(0, 0);
      display.print("erro 404 page not found");
      break;
  }
}
