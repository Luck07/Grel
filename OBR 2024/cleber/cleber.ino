// Switch
#include "definir.h"  // Dando include nas variaveis e funções
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define lw 6
#define lh 8


// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };

int n;

void setup() {
  Serial.begin(9600);
  if(!tcs_real.begin(&Wire)) {
    Serial.println("tcs real n");
  };
 if(!tcs_soft.begin(&sWire)) {
  Serial.println("tcs soft n");
 };
  /* display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2); */

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

  
}

bool verde(int r, int g, int b, float tol=1.03) { //soft 1 real 1.05
  Serial.print(g); Serial.print("/"); Serial.print((r+b+g)/3); Serial.print("-"); Serial.print(tol*(r+b+g)/3); Serial.print("\t");
  if((r+b+g)/3 >= 2900) return false;
  return (g >= tol*(r+b+g)/3);
}

void loop() {
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

    uint8_t esq  = constrain(map(analogRead(s_esq) , preto_esq , branco_esq , 0, 100), 0, 100);
    uint8_t mesq = constrain(map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 100), 0, 100);
    uint8_t m    = constrain(map(analogRead(s_m)   , preto_m   , branco_m   , 0, 100), 0, 100);
    uint8_t mdir = constrain(map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 100), 0, 100);
    uint8_t dir  = constrain(map(analogRead(s_dir) , preto_dir , branco_dir , 0, 100), 0, 100);

    const uint8_t max = 50;
    bool besq  = esq  <= (max-30);
    bool bmesq = mesq <= (max);
    bool bm    = m    <= (max+15);
    bool bmdir = mdir <= (max);
    bool bdir  = dir  <= (max);

    byte b_sens = 0b00000;
    b_sens |= besq  << 4;
    b_sens |= bmesq << 3;
    b_sens |= bm    << 2;
    b_sens |= bmdir << 1;
    b_sens |= bdir;

    uint16_t r1, g1, b1, c1;
    uint16_t r2, g2, b2, c2;
    uint16_t tg1, tg2;

     Serial.print(besq); 
     Serial.print(bmesq); 
     Serial.print(bm); 
     Serial.print(bmdir); 
     Serial.print(bdir);  Serial.print("\t");
    //Serial.print(b_sens, BIN); Serial.print("\t");
    //return;
    
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
    
    /*
    switch(b_sens) {
        case 0b11111:
            Serial.println("encru");
            vel_parar(0);
            break;
        case 0b10000:
        case 0b10010:
        case 0b10110:
        case 0b11010:
        case 0b11110:
        case 0b10100:
        case 0b11000:
        case 0b11100:
            vel_frente();
            delay(300);
            if(besq) {
                vel_re();
                delay(450);
                Serial.println("90 esq");
                esq_90();
            }
            break;
        case 0b00001:
        case 0b00011:
        case 0b00101:
        case 0b00111:
        case 0b01001:
        case 0b01011:
        case 0b01101:
        case 0b01111:
            vel_frente();
            delay(300);
            if(bdir) {
                vel_re();
                delay(450);
                Serial.println("90 dir");
                dir_90();
            } else {
                //serv_dir.write()
            }
            break;
        case 0b01100:
        case 0b00110:
        case 0b01010:
        case 0b00100:
        case 0b01110:
            Serial.println("frente");
            vel_frente();
            //delay(200);
            break;
        case 0b01000:
        //case 0b01100:
            Serial.println("micro esq");
            vel_direita();
            //serv_dir.write(90 - (100-m)/5);
            //serv_esq.write(90 - (100-m)/2);
            break;  
        case 0b00010:
        //case 0b00110:
            Serial.println("micro dir");
            vel_esquerda();
            //delay(100);
            //serv_dir.write(90 + (100-m)/2); 
            //serv_esq.write(90 + (100-m)/5);
            break;
        case 0b00000:
            Serial.println("frente (gap)");
            vel_frente();
            delay(400);
            break;
        default: Serial.print("."); break;
    }
    */

  bool _r, _s;
  tcs_real.getRawData(&r1, &g1, &b1, &c1);
            tcs_soft.getRawData(&r2, &g2, &b2, &c2);
            _r = verde(r1, g1, b1, 1.05);
            _s = verde(r2, g2, b2, 1.00);
            if(_r && _s) {
              Serial.print("2 verde ");
            } else if(_r && !_s) {
              Serial.print("real verde ");
            } else if(!_r && _s) {
              Serial.print("soft verde ");
            } else {
              Serial.print("NADa verde ");
            }
            // Serial.print(g1); Serial.print("/"); Serial.print((r1+b1+g1)/3); Serial.print("-"); Serial.print(1.05*(r1+b1+g1)/3); Serial.print("\t");
            // Serial.print(g2); Serial.print("/"); Serial.print((r2+b2+g2)/3); Serial.print("-"); Serial.print(1.01*(r2+b2+g2)/3); Serial.print("\t");
switch(b_sens) {
        case 0b10000:
        case 0b10010:
        case 0b10110:
        case 0b11010:
        case 0b11110:
        case 0b10100:
        case 0b11000:
        case 0b11100: //casos de 90 esquerda
        
            if(!ver)
          {
            Serial.println("90 esq Falso");
            ver = true;
            vel_parar();
          }
          else
          {
            Serial.println("90 esq Verdadeiro");
            ver = false;
            esq_90();
          }
          break;
        case 0b00001:
        case 0b00011:
        case 0b00101:
        case 0b00111:
        case 0b01001:
        case 0b01011:
        case 0b01101:
        case 0b01111: // casos de 90 graus direita
        
          if(!ver)
          {
            Serial.println("90 dir Falso");
            vel_parar();
            ver = true;
          }
          else
          {
            Serial.println("90 dir Verdadeiro");
            ver = false;
            dir_90();
          }
            break;
        case 0b01100:
        case 0b00110:
        case 0b01010:
        case 0b00100:
        case 0b01110:
          if(!ver)
          {
            Serial.println("Frente");
            vel_frente();
          }
          else
          {
            Serial.println("Frente Verdadeiro");
            ver = false;
            vel_re();
            delay(delay_re);
          }
            break;
        case 0b01000:
        //case 0b01100:
            if(!ver)
            {
              Serial.println("micro esq");
            vel_direita();
            }
            else 
            {
              Serial.println("micro esq Verdadeiro");
              ver = false;
              vel_re();
            delay(delay_re);
            }
            //serv_dir.write(90 - (100-m)/5);
            //serv_esq.write(90 - (100-m)/2);
            break;  
        case 0b00010:
        //case 0b00110:
            if(!ver)
            {
              Serial.println("micro dir");
            vel_esquerda();
            }
            else 
            {
              Serial.println("micro dir Verdadeiro");
              ver = false;
              vel_re();
            delay(delay_re);
            }
            //delay(100);
            //serv_dir.write(90 + (100-m)/2); 
            //serv_esq.write(90 + (100-m)/5);
            break;
        case 0b00000:
            Serial.println("frente (gap)");
            vel_frente();
            delay(800);
            break;
        case 0b11111:
        case 0b10001:
        case 0b10011:
        case 0b10101:
        case 0b10111:
        case 0b11001:
        case 0b11011:
        case 0b11101:
            vel_parar(0);
            Serial.println("");
            // tcs_real.getRawData(&r1, &g1, &b1, &c1);
            // tcs_soft.getRawData(&r2, &g2, &b2, &c2);
            // _r = verde(r1, g1, b1);
            // _s = verde(r2, g2, b2);
            // if(_r && _s) {
            //   Serial.print("2 verde ");
            // } else if(_r && !_s) {
            //   Serial.print("real verde ");
            // } else if(!_r && _s) {
            //   Serial.print("soft verde ");
            // } else {
            //   Serial.print("NADa verde ");
            // }
            // Serial.print(g1); Serial.print("/"); Serial.print((r1+b1)/2); Serial.print("-"); Serial.print(1.03*(r1+b1)/2); Serial.print("\t");
            // Serial.print(g2); Serial.print("/"); Serial.print((r2+b2)/2); Serial.print("-"); Serial.print(1.03*(r2+b2)/2); Serial.println("\t");
            break;
        default: Serial.print("."); break;
    }
    
    /*
    if(besq && bdir) {
        if(bmesq && bmdir) {
            Serial.print("frente");
            vel_frente();
            if(bm) {
                Serial.print(" branco");
                delay(200);
            }
            Serial.println("");
        }
        else if(bmesq && !bmdir) {
        if(!a) {
            a = true;
            Serial.println("a true dir");
        } else {
            a = false;
            vel_esquerda();
        }
        } else {
        if(!a) {
            Serial.println("a true esq");
            a = true;
        } else {
            a = false;
            vel_direita();
        }
        }
    } else {
        a = true;
        if(!bdir) {
        Serial.println("direita 90");
        dir_90();
        
        /* jeito chique de fazer curva 
        serv_dir.write(180);
        serv_esq.write(0);
        delay(410); // velocidade (medida):  ~16cm/s, largura (medida): 13cm
        // 16cm--1s / 13/2cm--0.41s
        serv_dir.write(90);
        serv_esq.write(180);
        delay(1800); // velocidade angular (direita): 450º/9s = 360º/7.2s = 50º/s = 1.7453 rad/s
        // -> 450º--9s / 90º--1.8s
        /

        } else if(!besq) {
        Serial.println("esquerda 90");
        esq_90();

        /*
        serv_dir.write(180);
        serv_esq.write(0);
        delay(410);
        serv_dir.write(0);
        serv_esq.write(90);
        delay(1800);
        /
        } else {
            Serial.println("encru");
            serv_esq.write(90);
            serv_dir.write(90);
        }
    }

    
    if(a) {
        if (!bm || (!bmesq && !bmdir))
            vel_frente();
        else if ((bmesq && !bmdir))
            vel_esquerda();
        else
            vel_direita();
        a = false;
    }
    */
    
    

    /*
    //if(!bm) {
        if(!bm && (bmesq && bmdir))
        vel_frente();
        else if(bmesq && !bmdir) {
        //if(!bdir)
        //  dir_90();
        //else
            vel_esquerda();
        } else {
        //if(!besq)
        //  esq_90();
        //else
            vel_direita();
        }
    //}
    */

    /*if (!bm/* && ((bmesq && bmdir) || (!bmesq && !bmdir)))
        vel_frente();
    else if ((bmesq && !bmdir))
        vel_esquerda();
    else
        vel_direita(); */

    //delay(100);
    //vel_parar(100);

    /*if((besq && bmesq && bmdir && bdir) || (besq && !bmesq && !bmdir && bdir))
        vel_frente();
    else if ((besq && bmesq && !bmdir && bdir))
        vel_direita();
    else if ((besq && !bmesq && bmdir && bdir))
        vel_esquerda();
    else if ((besq && bmesq && bmdir && !bdir) || (besq && !bmesq && !bmdir && !bdir))
        dir_90();
    //else if ((!besq && bmesq && bmdir && bdir) || (!besq && !bmesq && !bmdir && bdir))
        //esq_90();
        
    /* if((besq && bmesq && bm && bmdir && bdir) || (besq && bmesq && !bm && bmdir && bdir) || (besq && !bmesq && !bm && !bmdir && bdir) || (!besq && !bmesq && !bm && !bmdir && !bdir))
    {
        vel_frente();
    }
    else if((besq && !bmesq && bm && bmdir && bdir))
    {
        vel_direita();
    }
    else if((besq && bmesq && bm && !bmdir && bdir))
    {
        vel_esquerda();
    }
    else if((!besq && bmesq && bm && bmdir && bdir) || (!besq && !bmesq && !bm && !bmdir && bdir) || (!besq && bmesq && !bm && bmdir && bdir) || (!besq && !bmesq && bm && !bmdir && bdir))
    {
        esq_90();
        vel_parar(3000);
    }
    else if((besq && bmesq && bm && bmdir && !bdir) || (besq && !bmesq && !bm && !bmdir && !bdir) || (besq && bmesq && !bm && bmdir && !bdir) || (besq && !bmesq && bm && !bmdir && !bdir))
    {
        dir_90();
        vel_parar(3000);
    }  */
    /* if ((analogRead(s_mesq) >= media_mesq) && (analogRead(s_mdir) <= media_mdir))  //! Fazer micro ajuste para esquerda
    {
        if (ver == false) {
        //vel_esquerda();
        Serial.println("Mini esquerda");
        } else {
        //vel_re();
        delay(delay_pas);
        ver = false;
        }
    } else if ((analogRead(s_mesq) <= media_mesq) && (analogRead(s_mdir) >= media_mdir))  //! Fazer micro ajuste para direita
    {
        if (ver == false) {
        //vel_direita();
        Serial.println("Mini direita");
        } else {
        //vel_re();
        delay(delay_pas);
        ver = false;
        }
    } else { */

        // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
        // Alguns nao tem break; porque faz a mesma coisa
        /* switch (leitura) {
        case 0b0110:
        case 0b1111:
        case 0b0000:  //! Caso de ele ir so pra frente
            vel_frente();
            Serial.println(" / Frente");
            break;
        case 0b0100:  //! Casos de fazer mini esquerda
            Serial.println(" / mini esquerda");
            vel_esquerda();
            break;
        case 0b0010:  //! Casos de fazer mini direita 
            vel_direita();
            Serial.println(" / mini direita");
            break;
        case 0b1000:
        case 0b1110:
            Serial.println(" / 90 esq");
            vel_parar(6000);
            //esq_90();
            break;
        case 0b0001:
        case 0b0111:
            Serial.println(" / 90 dir");
            //vel_parar(6000);
            dir_90();
            break;
        default:
            break;
        } */
  
}
