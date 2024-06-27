// Switch
#include "definir.h"  // Dando include nas variaveis e funções
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define W 128
#define H 64
#define lw 6
#define lh 8

const unsigned char aeia[] PROGMEM = {
    // 'bfcaab3c7ed1666ef086e690ec778ad0, 32x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xb0,
    0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x01, 0xbc, 0x08, 0x20, 0x44, 0x34, 0x00, 0x40, 0x08, 0x28,
    0x00, 0x03, 0x10, 0x20, 0x05, 0xff, 0x80, 0x30, 0x07, 0xfe, 0x20, 0xa0, 0x0f, 0xdf, 0xee, 0x80,
    0x0f, 0xb9, 0x3d, 0x70, 0x1f, 0xe3, 0x73, 0xc0, 0x1d, 0xe0, 0xe3, 0xc0, 0x1f, 0xe0, 0x00, 0xc0,
    0x1f, 0x63, 0xa0, 0x40, 0x1f, 0x67, 0xc1, 0xc0, 0x1f, 0x47, 0x21, 0x40, 0x1b, 0x47, 0xe3, 0xc0,
    0x1f, 0x47, 0xc3, 0xc0, 0x1f, 0x47, 0xc3, 0xc0, 0x0e, 0x5f, 0xdb, 0x80, 0x1b, 0xdf, 0x83, 0xe0,
    0x03, 0x78, 0x00, 0x80, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x6b, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };

int n;
bool a = false;

void setup() {
  Serial.begin(9600);

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
void loop() {
  /* display.clearDisplay();
  display.setCursor(0, 0);
  display.print("PRIMEIRO\nSEGUE\nFAIXA!!!");
  display.drawBitmap(W - 32, H - 32 + sin(n * PI / 180) * 3, aeia, 32, 32, WHITE);
  display.display();
  n = (n < 360) ? n + 36 : 0;

  display.display(); */
  //Serial.print(leitura, BIN);
  bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;

  Serial.print(besq);
  Serial.print(" / ");
  Serial.print(bmesq);
  Serial.print(" / ");
  Serial.print(bm);
  Serial.print(" / ");
  Serial.print(bmdir);
  Serial.print(" / ");
  Serial.print(bdir);
  Serial.println(" / ");

  
  if(besq && bdir) {
    if(!bm && (bmesq && bmdir))
      vel_frente();
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
    } else {
      Serial.println("esquerda 90");
      esq_90();
    }
  }

  
  if(a) {
    if (!bm)
      vel_frente();
    else if ((bmesq && !bmdir))
      vel_esquerda();
    else
      vel_direita();
    a = false;
  }
  

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
