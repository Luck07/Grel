// Switch
#include "definir.h"  // Dando include nas variaveis e funções
#include "imu.h"
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };
euler_t ypr;

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setFontSize(FONT_SIZE_SMALL);
  display.clear();
  // display.print("oi");

  if (!tcs_real.begin(&sWire)) {
    Serial.println("tcs real n");
    display.println("tcs real n");
  } else {
    Serial.println("tcs real passou");
    display.println("tcs real");
  }

  if (!tcs_soft.begin(&Wire)) {
    Serial.println("tcs soft n");
    display.println("tcs soft n");
  } else {
    Serial.println("tcs soft passou");
    display.println("tcs soft");
  }

  if (!imu.begin_I2C()) {
    //if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte UART buffer!
    //if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");
  setReports(reportType, reportIntervalUs);

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

 mpu.begin();
 display.println("calibrando mpu");
  mpu.calibrar_offsets();

 mpu.set_gyro_offsets(0.97f, -1.68f, 0.55f);
  mpu.set_accl_offsets(-0.04f, -0.03f, 1.00f);

  // display.print(mpu.get_gyro_Xoffset());
  // display.print("/");
  // display.print(mpu.get_gyro_Yoffset());
  // display.print("/");
  // display.println(mpu.get_gyro_Zoffset());
  // display.print(mpu.get_accl_Xoffset());
  // display.print("/");
  // display.print(mpu.get_accl_Yoffset());
  // display.print("/");
  // display.println(mpu.get_accl_Zoffset());
  // // for(;;)delay(1000);
  // display.clear();
  // //   serv_esq.write(0);
  // //   serv_dir.write(0);//45ang/s
  // //   delay(4100);vel_parar();

  // // update_imu(&ypr);
  // // float yaw = ypr.yaw;
  // // serv_dir.write(0);
  // // serv_esq.write(0);
  // // unsigned long m = millis();
  // // Serial.println(yaw);
  // // delay(100);

  // // if(yaw == 0.0) yaw = 179.0;

  // // while(ypr.yaw >= -yaw) {
  // //   update_imu(&ypr);
  // //   Serial.println(ypr.yaw);
  // // }
  // // vel_parar();
  // // unsigned long _m = millis();
  // // display.clear();
  // // display.setCursor(1, 1);
  // // display.println(_m);
  // // display.println(m);
  // // display.println(_m - m);

  // serv_esq.write(180);
  // serv_dir.write(0);
  // delay(10000);
  // vel_parar();  
}


unsigned long mil = 0;


void loop() {
  bool besq, bmesq, bm, bmdir, bdir;
  ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);

  byte b_sens = 0b00000;
  b_sens |= besq << 4;
  b_sens |= bmesq << 3;
  b_sens |= bm << 2;
  b_sens |= bmdir << 1;
  b_sens |= bdir;

  uint16_t r1, g1, b1, c1;  //esq, real
  uint16_t r2, g2, b2, c2;  //dir, soft
  bool verde_esq = false;
  bool verde_dir = false;
  int ult = ultra_sonico.read();

  Serial.print(besq);
  Serial.print(bmesq);
  Serial.print(bm);
  Serial.print(bmdir);
  Serial.print(bdir);
  Serial.print("\t");


#ifdef calpb
  Serial.print(analogRead(s_esq));
  Serial.print(" / ");
  Serial.print(analogRead(s_mesq));
  Serial.print(" / ");
  Serial.print(analogRead(s_m));
  Serial.print(" / ");
  Serial.print(analogRead(s_mdir));
  Serial.print(" / ");
  Serial.print(analogRead(s_dir));
  Serial.println(" / ");

  display.clear();
  display.setCursor(0, 2);
  display.print(analogRead(s_esq));
  display.println(" / s_esq ");
  display.print(analogRead(s_mesq));
  display.println(" / s_mseq");
  display.print(analogRead(s_m));
  display.println(" / s_m   ");
  display.print(analogRead(s_mdir));
  display.println(" / s_mdir");
  display.print(analogRead(s_dir));
  display.println(" / s_dir ");
  delay(100);
  return;
#endif

#ifdef caltcs
  display.setCursor(0, 0);
  tcs_soft.getRawData(&r1, &g1, &b1, &c1);
  tcs_real.getRawData(&r2, &g2, &b2, &c2);
  display.clear();
  Serial.print(r1);
  Serial.print("/");
  Serial.print(g1);
  Serial.print("/");
  Serial.print(b1);
  Serial.print("\t");
  Serial.print(r2);
  Serial.print("/");
  Serial.print(g2);
  Serial.print("/");
  Serial.print(b2);
  Serial.print("\t");
  Serial.print(ESQ_VERDE_TOL * (r1 + g1 + b1) / 3);
  Serial.print("/");
  Serial.print(DIR_VERDE_TOL * (r2 + g2 + b2) / 3);
  Serial.print("\t");
  Serial.print(verde(r1, g1, b1, ESQ_VERDE_TOL) ? "esq_s" : "esq_n");
  Serial.print(" / ");
  Serial.println(verde(r2, g2, b2, DIR_VERDE_TOL) ? "dir_s" : "dir_n");

  display.print(r1);
  display.print("/");
  display.print(g1);
  display.print("/");
  display.println(b1);
  
  display.print(r2);
  display.print("/");
  display.print(g2);
  display.print("/");
  display.println(b2);
  delay(200);
  
  return;
#endif

  // tcs_soft.getRawData(&r1, &g1,&b1,&c1);
  // verde_esq = verde(r1,g1,b1,1.00);
  // tcs_real.getRawData(&r2, &g2, &b2, &c2);
  // verde_dir = verde(r2, g2, b2, 1.05);
  // Serial.println("");
  // return;

  OLED::print_sens(besq, bmesq, bm, bmdir, bdir);
  OLED::print_verdes(verde_esq, verde_dir);
  OLED::print_ult(ult);
  display.clearLine(5);
  // display.print(analogRead(s_esq));
  // display.print(" / ");
  // display.print(analogRead(s_dir));
  Serial.print("(ultrasonico=");
  Serial.print(ult);
  Serial.print(") ");

  update_imu(&ypr);
  Serial.print("\t");
  Serial.print(ypr.yaw);
  Serial.print(" , ");
  Serial.print(ypr.pitch);
  Serial.print(" , ");
  Serial.println(ypr.roll);

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
        verde_esq = verde(r1, g1, b1, ESQ_VERDE_TOL);
        OLED::print_verdes(verde_esq, verde_dir);
        if (verde_esq) {
          Serial.println("90 esq verde");
          // giro_esq_ang_mpu(45);
          giro_esq_ang_imu(45, &ypr);
          esq_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if (!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            // esq_90();
            // serv_esq.write(0);
            // serv_dir.write(0);
            // delay(medicoes::esq_giro_ms_max(60));
            // giro_esq_ang(60);
            // while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  &&
            //       constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=60) {}

            giro_esq_ang(60);
            while (constrain(map(analogRead(s_m), preto_m, branco_m, 0, 100), 0, 100) >= 60) {
              if (constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100) >= 60) {
                giro_dir_ang(30);
                break;
              }
            }
            // if(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  ||
            //    constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=60) {
            //   esq_90();
            // } else {
            //   while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  &&
            //         constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100)>=60) {}
            // }

            vel_re_max();
            delay(delay_re / 2);
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
        verde_dir = verde(r2, g2, b2, DIR_VERDE_TOL);
        OLED::print_verdes(verde_esq, verde_dir);
        if (verde_dir) {
          Serial.println("90 dir verde");
          // giro_dir_ang_mpu(45);
          giro_dir_ang_imu(45, &ypr);
          dir_90();
        } else {
          vel_frente_max();
          delay(medicoes::frente_ms_max(FITA_LARGURA * 1.5));

          ler_sensores(&besq, &bmesq, &bm, &bmdir, &bdir);
          if (!(besq || bmesq || bm || bmdir || bdir)) {
            vel_re_max();
            delay(medicoes::tras_ms_max(FITA_LARGURA * 1.5));
            // dir_90();
            // serv_esq.write(180);
            // serv_dir.write(180);
            // giro_dir_ang(60);
            // while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  &&
            //       constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=60) {}

            giro_dir_ang(60);
            while (constrain(map(analogRead(s_m), preto_m, branco_m, 0, 100), 0, 100) >= 60) {
              if (constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100) >= 60) {
                giro_esq_ang(30);
                break;
              }
            }

            // if(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  ||
            //    constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=60) {
            //   esq_90();
            // } else {
            //   while(constrain(map(analogRead(s_m)  , preto_m  , branco_m  , 0, 100), 0, 100)>=20  &&
            //         constrain(map(analogRead(s_esq), preto_esq, branco_esq, 0, 100), 0, 100)>=60) {}
            // }

            vel_re_max();
            delay(delay_re / 2);
          }
        }
      }
      break;

    // case 0b01000:
    // case 0b00010:
    case 0b00100:
    case 0b01100:
    case 0b00110:
    case 0b01110:
    case 0b01010:  //-----------------------frente-------------------------
      OLED::print_frente(ver);
      if (!ver) {
        Serial.println("Frente");

        if (ult <= 9 && ult > 0) {
          obstaculo(false);
        }

        vel_frente();

        if (millis() - mil >= 2000) {

        }

      } else {
        Serial.println("Frente Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re / 2);
      }
      break;

    case 0b01000:  //--------------------micro esquerda-------------------
                   //case 0b01100:
      OLED::print_micro(false, ver);
      if (!ver) {
        Serial.println("micro esq");
        vel_direita();
      } else {
        Serial.println("micro esq Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re / 2);
      }
      break;

    case 0b00010:  //--------------------micro direita-------------------
                   //case 0b00110:
      OLED::print_micro(true, ver);
      if (!ver) {
        Serial.println("micro dir");
        vel_esquerda();
      } else {
        Serial.println("micro dir Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re / 2);
      }
      break;

    case 0b00000:  //-------------------------gap------------------------
      OLED::print_gap(ver);
      if (ver) {
        Serial.println("gap Verdadeiro");
        ver = false;
        vel_re();
        delay(delay_re);
      } else {
        Serial.println("frente (gap)");

        // if (yaw > 10) {
        //   serv_esq.write(90);
        //   serv_dir.write(120);
        //   delay(400);
        // } else if (yaw < -15) {
        //   serv_esq.write(60);
        //   serv_dir.write(90);
        //   delay(400);
        // }

        //vel_frente_max();

        // tcs_soft.getRawData(&r1, &g1, &b1, &c1);
        // if (verde(g1, r1, b1, 1.1)) {
        //   tcs_real.getRawData(&r2, &g2, &b2, &c2);
        //   if (verde(g2, r2, b2, 1.1)) {
        //     vel_parar();

        //     display.clear();
        //     display.print("ola");
        //     for (;;) {
        //       display.invertDisplay(true);
        //       delay(500);
        //       display.invertDisplay(false);
        //       delay(500);
        //     }
        //   }
        // }

        vel_frente();
      }

      break;
    case 0b11111:
    case 0b10001:
    case 0b10011:
    case 0b10101:
    case 0b10111:
    case 0b11001:
    case 0b11011:
    case 0b11101:  //encru
      OLED::print_encru();
      ver = false;
      Serial.println("Enc");
      vel_parar(180);

      tcs_soft.getRawData(&r1, &g1, &b1, &c1);
      tcs_real.getRawData(&r2, &g2, &b2, &c2);
      verde_esq = verde(r1, g1, b1, ESQ_VERDE_TOL);
      verde_dir = verde(r2, g2, b2, DIR_VERDE_TOL);
      OLED::print_verdes(verde_esq, verde_dir);

      // display.clearLine(3);
      // display.setCursor(OLED::center(12), 3);
      // display.print("encru -> ");
      if (verde_esq && verde_dir) {
        // display.print("180");
        Serial.print("tudo verd");
        giro_esq_ang(135);
        while (constrain(map(analogRead(s_m), preto_m, branco_m, 0, 100), 0, 100) >= 50 && constrain(map(analogRead(s_dir), preto_dir, branco_dir, 0, 100), 0, 100) >= 50) {}
      } else if (verde_esq && !verde_dir) {
        // display.print("esq");
        Serial.print("esq verde");
        // giro_esq_ang(30);
        giro_esq_ang_imu(60, &ypr);
        esq_90();
      } else if (!verde_esq && verde_dir) {
        // display.print("dir");
        Serial.print("dir verde");
        // giro_dir_ang(30);
        giro_dir_ang_imu(60, &ypr);
        dir_90();
      } else {
        // display.print("nad");
        Serial.print("NADa verde");
        vel_frente_max();
        delay(medicoes::frente_ms_max(2));
        vel_frente();
      }
      display.clearLine(3);
      Serial.println("");
      break;
    default: Serial.print("."); break;
  }

  if (bm == 1 || (bmesq == 1 && bmdir == 1)) mil = millis();
}
