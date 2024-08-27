// Switch
#include "definir.h"  // Dando include nas variaveis e funções
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setFontSize(FONT_SIZE_SMALL);
  display.clear();
  // display.print("oi");

  if (!tcs_real.begin(&Wire)) {
    Serial.println("tcs real n");
    display.println("tcs real n");
  } else {
    Serial.println("tcs real passou");
    display.println("tcs real");
  }
  
  if (!tcs_soft.begin(&sWire)) {
    Serial.println("tcs soft n");
    display.println("tcs soft n");
  } else {
    Serial.println("tcs soft passou");
    display.println("tcs soft");
  }

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

  mpu.begin();
  display.println("calibrando mpu");
  // mpu.calibrar_offsets(3000);

  mpu.set_gyro_offsets( 0.95f, -1.66f, 0.54f);
  mpu.set_accl_offsets(-0.08f, -0.01f, 1.00f);

  display.print(mpu.get_gyro_Xoffset()); display.print("/");
  display.print(mpu.get_gyro_Yoffset()); display.print("/");
  display.println(mpu.get_gyro_Zoffset());
  display.print(mpu.get_accl_Xoffset()); display.print("/");
  display.print(mpu.get_accl_Yoffset()); display.print("/");
  display.println(mpu.get_accl_Zoffset());

  delay(100);
  display.clear();

  // serv_esq.write(90);
  // serv_dir.write(0);
  // delay(9000);
  // vel_parar();

  // unsigned long mmm = 0;
  // int yaw = 0;

  // mpu.reset_yaw();
  // serv_esq.write(180);
  // serv_dir.write(180);
  // unsigned long __m = millis();
  // for(;abs(yaw) < 90;) {
  //   mmm = millis();
  //   mpu.update();
  //   yaw = mpu.yaw();
  //   // display.clear();
  //   // display.printLong(mmm - __m);
  // }
  // vel_parar();
  // unsigned long _m = millis();
  // display.println(yaw);
  // //display.print(__m - _m);display.print("/");display.println(__m - mmm);
  // display.println(_m - __m);
  // display.println(mmm - __m);
  // display.printLong(mmm); display.println("/");
  // display.printLong(_m);display.println("/");
  // display.printLong(__m);display.println("/");
}

void loop() {
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
  display.clearLine(6);
  display.setCursor(OLED::center((ult<9)?1:2), 6);
  display.print(ult);
  Serial.print("(ultrasonico=");
  Serial.print(ult);
  Serial.println(") ");

  switch (b_sens) {
    case 0b10000:
    case 0b10010:
    case 0b10110:
    case 0b11010:
    case 0b11110:
    case 0b10100:
    case 0b11000:
    case 0b11100:  //---------------------90 esquerda---------------------
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
          giro_esq_ang_mpu(45);
          esq_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if(!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            // esq_90();
            serv_esq.write(0);
            serv_dir.write(0);
            delay(delay_peq);
            Serial.println("passo");
            while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=50  &&
                  constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=50) {}
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
    case 0b01111:  //---------------------90 direita---------------------
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
          giro_dir_ang_mpu(45);
          dir_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if(!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            // dir_90();
            serv_esq.write(180);
            serv_dir.write(180);
            delay(delay_peq);
            Serial.println("passo");
              while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=65  &&
                    constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=20) {}
          }
        }
      }
      break;

    // case 0b01000:
    // case 0b00010:
    case 0b01100:
    case 0b00110:
    case 0b00100:
    case 0b01110:
    case 0b01010: //-----------------------frente-------------------------
      OLED::print_frente(ver);
      if (!ver) {
        Serial.println("Frente");

        if(ult <= 9 && ult > 0) {
          obstaculo2();
        }

        vel_frente_max();
      } else {
        Serial.println("Frente Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re/2);
      }
      break;

    case 0b01000: //--------------------micro esquerda-------------------
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
      break;

    case 0b00010: //--------------------micro direita-------------------
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
      break;

    case 0b00000: //-------------------------gap------------------------
      OLED::print_gap(ver);
      if(ver) {
        Serial.println("gap Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re);
      } else {
        Serial.println("frente (gap)");
        vel_frente_max();
        
        tcs_soft.getRawData(&r1, &g1, &b1, &c1);
        if(verde(g1, r1, b1, 1.1)) {
          tcs_real.getRawData(&r2, &g2, &b2, &c2);
          if(verde(g2, r2, b2, 1.1)) {
            vel_parar();
            
            display.clear();
            display.print("ola");
            for(;;){
              display.invertDisplay(true);
              delay(500);
              display.invertDisplay(false);
              delay(500);
            }
          }
        }
      }

      // vel_parar(180);
      // tcs_soft.getRawData(&r1, &g1, &b1, &c1);
      // ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
      // if((verde(g1, r1, b1, 1.25)) {
      //   tcs_real.getRawData(&r2, &g2, &b2, &c2);
      //   if(verde(g2, r2, b2, 1.25)) {
      //     vel_parar();
      //     delay(7000);
      //       display.clear();
      //       display.print("ebaaa");
      //     while(true) {
      //       display.invertDisplay(true);
      //       delay(1000);
      //       display.invertDisplay(false);
      //       delay(1000);
      //     }
      //   } else {
      //     vel_frente_max();
      //   }
      // }

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
      ver = false;
      Serial.println("Enc");
      vel_parar(180);

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
        giro_esq_ang(135);
        while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=50  &&
              constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=50) {}
      } else if (verde_esq && !verde_dir) {
        display.print("esq");
        Serial.print("esq verde");
        // giro_esq_ang(30);
        giro_esq_ang_mpu(30);
        esq_90();
      } else if (!verde_esq && verde_dir) {
        display.print("dir");
        Serial.print("dir verde");
        //giro_dir_ang(30);
        giro_dir_ang_mpu(30);
        dir_90();
      } else {
        display.print("nad");
        Serial.print("NADa verde");
        vel_frente_max();
        delay(medicoes::frente_ms_max(2));
        vel_frente();
      }
      Serial.println("");
      break;
    default: Serial.print("."); break;
  }

}