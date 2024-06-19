// Switch
#include "definir.h" // Dando include nas variaveis e funções

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_oeste, s_noroeste, s_norte, s_nordeste, s_leste};

void setup()
{
  Serial.begin(9600);
    // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
    for (int i = 0; i < 5; i++) // Usando o array para fazer os pinmode como input
        pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);
}
void loop()
{
  //calibra();
  //Serial.print(leitura, BIN);
  Serial.print(analogRead(s_noroeste));
  Serial.print(" / ");
  Serial.println(analogRead(s_nordeste));

  if ((analogRead(s_noroeste) <= max_noroeste) && (analogRead(s_nordeste) >= max_nordeste )) //! Fazer micro ajuste para esquerda
  {
    if (ver == false)
      {
          vel_esquerda();
          Serial.println("Mini esquerda");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
  }
  else if ((analogRead(s_noroeste) >= max_noroeste) && (analogRead(s_nordeste) <= max_nordeste)) //! Fazer micro ajuste para direita
  {
    if (ver == false)
    {
      vel_direita();
      Serial.println("Mini direita");
    }
    else
    {
      vel_re();
      delay(delay_pas);
      ver = false;
    }
  }
  else
  {
    vel_frente();
    Serial.println("Frente");
  }
  delay(100);
  vel_parar(1000);
  
  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Alguns nao tem break; porque faz a mesma coisa
  /* switch (leitura)
  {
  case 0b1111:
  case 0b0000:
  case 0b0110: //! Caso de ele ir so pra frente
      if (ver == false)
      {
          vel_frente();
          Serial.println(" / Frente");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
      break;
  case 0b0010: //! Caso dele fazer micro ajuste para direita
      if (ver == false)
      {
          vel_direita();
          Serial.println(" / Mini direita");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
      break;
  case 0b0100: //! Caso dele fazer micro ajuste para esquerda
      if (ver == false)
      {
          vel_esquerda();
          Serial.println(" / Mini esquerda");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
      break;
  case 0b1000:
  //case 0b1100:
  case 0b1110:
  //case 0b1010: //! Casos de fazer o esquerda 90  
      if (ver == false)
      {
          vel_esquerda();
          Serial.println(" / Mini esquerda");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
      break;
  case 0b0001:
  //case 0b0011:
  case 0b0111:
  //case 0b0101: //! Casos de fazer o direita 90
      if (ver == false)
      {
          vel_direita();
          Serial.println(" / Mini direita");
      }
      else
      {
          vel_re();
          delay(delay_pas);
          ver = false;
      }
      break;
  default:
      break;
  } */
  Serial.println();
}