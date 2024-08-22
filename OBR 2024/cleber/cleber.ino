// Switch
#include "definir.h"  // Dando include nas variaveis e funções
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };

bool verde(int r, int g, int b, float tol = 1.03) {  //soft 1 real 1.05
  Serial.print(g);
  Serial.print("/");
  Serial.print((r + b + g) / 3);
  Serial.print("-");
  Serial.print(tol * (r + b + g) / 3);
  Serial.print("\t");
  if ((r + b + g) / 3 >= 2900) return false;
  return (g >= tol * (r + b + g) / 3);
}

void setup() {
  Serial.begin(9600);

  // display.begin();
  // display.setFontSize(FONT_SIZE_SMALL);
  // display.clear();
  // display.print("oi");

  if (!tcs_real.begin(&Wire)) {
    Serial.println("tcs real n");
  } else {
    Serial.println("Tcs Soft passou");
  }
  
  if (!tcs_soft.begin(&sWire)) {
    Serial.println("tcs soft n");
  } else {
    Serial.println("Tcs Soft passou");
  }

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

  // mpu.begin();
  // mpu.calibrar_offsets(1000);
  
  serv_esq.write(180);
  serv_dir.write(180);
  unsigned long _n = 0;

  // mpu.reset_yaw();

  for(_n=millis(); _n <= 4200; _n=millis()) {
    // mpu.update();
    // display.clear();
    // display.setCursor(0,0);
    // yaw = mpu.yaw();
    // pit = mpu.pitch();
    // rol = mpu.roll();
    Serial.println(_n);
    // display.print(_n);
    // display.setCursor(0,1);
    // display.print(yaw); display.print("/");
    // display.print(pit); display.print("/");
    // display.print(rol);
  }
  // mpu.update();
  // display.setCursor(0,3);
  // display.print(_n);
  // display.setCursor(0,4);
  // display.print(yaw); display.print("/");
  // display.print(pit); display.print("/");
  // display.print(rol);
  // vel_parar();
  // delay(2000);

  // serv_esq.write(60);
  // serv_dir.write(60);
  // _n = 0;
  // for(_n = millis(); _n <=5000 +6000; _n=millis()) {
  //   Serial.println(_n-6000);
  // }
  // display.println(_n-6000);
  vel_parar();
}

byte prv = 0;

void loop() {return;

  /* display.clearDisplay();
  display.setCursor(0, 0);
  display.print("PRIMEIRO\nSEGUE\nFAIXA!!!");
  display.drawBitmap(W - 32, H - 32 + sin(n * PI / 180) * 3, aeia, 32, 32, WHITE);
  display.display();
  n = (n < 360) ? n + 36 : 0;

  display.display(); */
  //Serial.print(leitura, BIN);

  //   bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  //   bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  //   bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  //   bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  //   bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;

  // uint8_t esq  = constrain(map(analogRead(s_esq) , preto_esq , branco_esq , 0, 100), 0, 100);
  // uint8_t mesq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 100), 0, 100);
  // uint8_t m    = constrain(map(analogRead(s_m)   , preto_m   , branco_m   , 0, 100), 0, 100);
  // uint8_t mdir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 100), 0, 100);
  // uint8_t dir  = constrain(map(analogRead(s_dir) , preto_dir , branco_dir , 0, 100), 0, 100);

  // const uint8_t max = 50;
  // bool besq  = esq  <= (max - 30);
  // bool bmesq = mesq <= (max);
  // bool bm    = m    <= (max + 15);
  // bool bmdir = mdir <= (max);
  // bool bdir  = dir  <= (max);
  bool besq, bmesq, bm, bmdir, bdir;
  ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);

  byte b_sens = 0b00000;
  b_sens |= besq  << 4;
  b_sens |= bmesq << 3;
  b_sens |= bm    << 2;
  b_sens |= bmdir << 1;
  b_sens |= bdir;

  uint16_t r1, g1, b1, c1; //esq, soft
  uint16_t r2, g2, b2, c2; //dir, real
  uint16_t tg1, tg2;
  bool verde_esq = false;
  bool verde_dir = false;

  int ult = ultra_sonico.read();

  Serial.print(besq);
  Serial.print(bmesq);
  Serial.print(bm);
  Serial.print(bmdir);
  Serial.print(bdir);
  Serial.print("\t");

  //display.clear();

  // display.setCursor(W/2 - (2*lw), 0);
  // display.print(besq);
  // display.print(bmesq);
  // display.print(bm);
  // display.print(bmdir);
  // display.print(bdir);

  // Serial.print(" / ");
  // Serial.print(esq);  Serial.print("-"); Serial.print(besq);  Serial.print(" / ");
  // Serial.print(mesq); Serial.print("-"); Serial.print(bmesq); Serial.print(" / ");
  // Serial.print(m);    Serial.print("-"); Serial.print(bm);    Serial.print(" / ");
  // Serial.print(mdir); Serial.print("-"); Serial.print(bmdir); Serial.print(" / ");
  // Serial.print(dir);  Serial.print("-"); Serial.print(bdir);  Serial.println(" / ");

  // Serial.print(analogRead(s_esq)); Serial.print(" / ");
  // Serial.print(analogRead(s_mesq)); Serial.print(" / ");
  // Serial.print(analogRead(s_m)); Serial.print(" / ");
  // Serial.print(analogRead(s_mdir)); Serial.print(" / ");
  // Serial.print(analogRead(s_dir)); Serial.println(" / ");

  // tcs_soft.getRawData(&r1, &g1,&b1,&c1);
  // verde_esq = verde(r1,g1,b1,1.00);
  // tcs_real.getRawData(&r2, &g2, &b2, &c2);
  // verde_dir = verde(r2, g2, b2, 1.05);
  // Serial.println("");
  // return;

  OLED::print_sens(besq, bmesq, bm, bmdir, bdir);
  OLED::print_verdes(verde_esq, verde_dir);
  display.clearLine(3);
  Serial.print("(ultrasonico=");
  Serial.print(ult);
  Serial.println(") ");
  // delay(200);
  //return;

  unsigned long m = 0;

  
  display.clearLine(5);
  display.setCursor(0, 5);
  display.print(ult);
  display.print(" / ");
  display.print(m);
  display.print(" / ");
  display.print(prv, BIN);

  return;


  switch (b_sens) {
    case 0b10000:
    case 0b10010:
    case 0b10110:
    case 0b11010:
    case 0b11110:
    case 0b10100:
    case 0b11000:
    case 0b11100:  //casos de 90 esquerda
      OLED::print_90(false, ver);
      if (!ver) {
        Serial.println("90 esq Falso");
        ver = true;
        vel_parar();
      } else {
        Serial.println("90 esq Verdadeiro");
        ver = false;

        tcs_soft.getRawData(&r1, &g1, &b1, &c1);
        verde_esq = verde(r1, g1, b1, 1.00);
        OLED::print_verdes(verde_esq, verde_dir);
        if(verde_esq) {
          Serial.println("90 esq verde");
          serv_esq.write(0);
          serv_dir.write(0);
          delay(medicoes::esq_giro_ms_max(45));
          esq_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));
          vel_parar(0);

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if(!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            esq_90();
          }
        }
      }
      break;
    case 0b00001:
    case 0b00011:
    case 0b00101:
    case 0b00111:
    case 0b01001:
    case 0b01011:
    case 0b01101:
    case 0b01111:  // casos de 90 graus direita
      OLED::print_90(true, ver);
      if (!ver) {
        Serial.println("90 dir Falso");
        vel_parar();
        ver = true;
      } else {
        Serial.println("90 dir Verdadeiro");
        ver = false;
        
        tcs_real.getRawData(&r2, &g2, &b2, &c2);
        verde_dir = verde(r2, g2, b2, 1.05);
        OLED::print_verdes(verde_esq, verde_dir);
        if(verde_dir) {
          Serial.println("90 dir verde");
          serv_esq.write(180);
          serv_dir.write(180);
          delay(medicoes::dir_giro_ms_max(45));
          dir_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));
          vel_parar(0);

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if(!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            dir_90();
          }
        }
      }
      break;
    case 0b01100:
    case 0b00110:
    case 0b00100:
    case 0b01110:
    case 0b01010:
    // case 0b01000:
    // case 0b00010:
      OLED::print_frente(ver);
      if (!ver) {
        Serial.println("Frente");

        if(ult <= 5 && ult > 0) {
          OLED::print_obs();
          serv_dir.write(0);
          serv_esq.write(0);
          int _aj = 0;
          if(bmesq || bmdir) {
            _aj = (bmesq - bmdir)*10;
          }
          delay(medicoes::esq_giro_ms_max(90+_aj));
          vel_frente_max();
          delay(medicoes::frente_ms_max(12));
          serv_dir.write(180);
          serv_esq.write(180);
          delay(medicoes::dir_giro_ms_max(80+_aj));
          vel_frente_max();
          delay(medicoes::frente_ms_max(15 + ult*2));
          serv_dir.write(180);
          serv_esq.write(180);
          delay(medicoes::dir_giro_ms_max(80+_aj));
          vel_frente_max();
          delay(medicoes::frente_ms_max(8));
          serv_dir.write(0);
          serv_esq.write(0);
          delay(medicoes::esq_giro_ms_max(60+_aj));
        }

        vel_frente();
      } else {
        Serial.println("Frente Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re/2);
      }
      break;
    case 0b01000:
    //case 0b01100:
      OLED::print_micro(false, ver);
      if (!ver) {
        Serial.println("micro esq");
        vel_direita();
      } else {
        Serial.println("micro esq Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re/2);
      }
      //serv_dir.write(90 - (100-m)/5);
      //serv_esq.write(90 - (100-m)/2);
      break;
    case 0b00010:
    //case 0b00110:
      OLED::print_micro(true, ver);
      if (!ver) {
        Serial.println("micro dir");
        vel_esquerda();
      } else {
        Serial.println("micro dir Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re/2);
      }
      //delay(100);
      //serv_dir.write(90 + (100-m)/2);
      //serv_esq.write(90 + (100-m)/5);
      break;
    case 0b00000:
      OLED::print_gap();
      Serial.println("frente (gap)");

      display.clearLine(4);
      display.setCursor(OLED::center(14), 3);
      display.print("gap -> prv ");
      if(prv == 0b01000) {
        display.print("esq");
        serv_esq.write(0);
        serv_dir.write(0);
        delay(medicoes::dir_giro_ms_max(30));
      } else if(prv == 0b00010) {
        display.print("dir");
        serv_esq.write(180);
        serv_dir.write(180);
        delay(medicoes::esq_giro_ms_max(30));
      } else {
        display.print("fre");
      }
      vel_frente();
      delay(200);

      // m = millis();
      // if(m <= 1000)
      //   break;



      // //m = 0;
      // // if(besq||bmesq||bm||bdir)
      // //   break;

      // //while(!(besq||bmesq||bm||bdir)  || m <= 2525) {
      // for(m=0; m<=2500; m=millis()) {
      //   ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
      //   if(besq||bmesq||bm||bdir)
      //     break;
      //   display.clearLine(5);
      //   display.setCursor(0, 5);
      //   display.print(ult);
      //   display.print(" / ");
      //   display.print(m);
      //   display.print(" / ");
      //   display.print(prv, BIN);
      //   OLED::print_sens(besq, bmesq, bm, bmdir, bdir);
      // }

      // if(!(besq||bmesq||bm||bdir)) {
      //     vel_re();
      //     delay(2500/2);

      //     display.setCursor(0, 3);
      //   if(prv | 0b11000) {
      //     display.print("gap -> prv esq");
      //     serv_esq.write(0);
      //     serv_dir.write(0);
      //     delay(medicoes::dir_giro_ms_max(30));
      //   } else if(prv | 0b00011) {
      //     display.print("gap -> prv dir");
      //     serv_esq.write(180);
      //     serv_dir.write(180);
      //     delay(medicoes::esq_giro_ms_max(30));
      //   } else {
      //     display.print("gap -> prv fre");
      //   }
      //   vel_frente();
      // }

      // vel_frente();
      // delay(200);
      break;
    case 0b11111:
    case 0b10001:
    case 0b10011:
    case 0b10101:
    case 0b10111:
    case 0b11001:
    case 0b11011:
    case 0b11101: //encru
      OLED::print_encru();
      vel_parar();

      COISO:
      tcs_soft.getRawData(&r1, &g1, &b1, &c1);
      tcs_real.getRawData(&r2, &g2, &b2, &c2);
      verde_esq = verde(r1, g1, b1, 1.00);
      verde_dir = verde(r2, g2, b2, 1.05);
      OLED::print_verdes(verde_esq, verde_dir);
      
      display.clearLine(3);
      display.setCursor(OLED::center(12), 3);
      display.print("encru -> ");
      if (verde_esq && verde_dir) {
        display.print("180");
        Serial.print("tudo verd");
        serv_esq.write(0);
        serv_dir.write(0);
        delay(medicoes::esq_giro_ms_max(180));
      } else if (verde_esq && !verde_dir) {
        display.print("esq");
        Serial.print("esq verde");
        esq_90();
      } else if (!verde_esq && verde_dir) {
        display.print("dir");
        Serial.print("dir verde");
        dir_90();
      } else {
        display.print("nad");
        Serial.print("NADa verde");
        vel_frente_max();
        delay(medicoes::frente_ms_max(2));
        vel_frente();
        //goto COISO;
      }
      Serial.println("");
      break;
    default: Serial.print("."); break;
  }

  if(b_sens != 0b00000) {
    prv = b_sens;
    m = 0;
  }

}
