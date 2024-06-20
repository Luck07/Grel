// Switch
#include "definir.h"  // Dando include nas variaveis e funções

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_esq, s_mesq, s_m, s_mdir, s_dir };

void setup() {
  Serial.begin(9600);
  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);
}
void loop() {
  //calibra();
  //Serial.print(leitura, BIN);
  bool besq = map(analogRead(s_esq), preto_esq, branco_esq, 0, 1023) >= 500 ? 1 : 0;
  bool bmesq = map(analogRead(s_mesq), preto_mesq, branco_mesq, 0, 1023) >= 500 ? 1 : 0;
  bool bm = map(analogRead(s_m), preto_m, branco_m, 0, 1023) >= 500 ? 1 : 0;
  bool bmdir = map(analogRead(s_mdir), preto_mdir, branco_mdir, 0, 1023) >= 500 ? 1 : 0;
  bool bdir = map(analogRead(s_dir), preto_dir, branco_dir, 0, 1023) >= 500 ? 1 : 0;

  if((besq && bmesq && bm && bmdir && bdir) || (besq && bmesq && !bm && bmdir && bdir) || (besq && !bmesq && !bm && !bmdir && bdir) || (!besq && !bmesq && !bm && !bmdir && !bdir))
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
    //esq_90();
    //vel_parar(3000);
  }
  else if((besq && bmesq && bm && bmdir && !bdir) || (besq && !bmesq && !bm && !bmdir && !bdir) || (besq && bmesq && !bm && bmdir && !bdir) || (besq && !bmesq && bm && !bmdir && !bdir))
  {
    dir_90();
    //vel_parar(3000);
  }
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
  //delay(1000);
//Serial.println();
//delay(100);
//vel_parar(1000);
}

