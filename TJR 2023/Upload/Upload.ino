// AnalogRead
#include "Definir.h"  // Dando include nas variaveis e funções
#include "Oled.h"     // Dando include no arquivo que tem as bibliotecas e criando o objeto do display oled

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_oeste, s_norte, s_leste, s_noroeste, s_nordeste, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4 };

byte leitura;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Protocolo para iniciar o display
  display.setTextColor(WHITE);               // Colocando cor para o texto
  //display.setRotation(3);                    // rotacionando a tela para ficar condizente com as setas

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 7; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++)  // Usando o array para fazer que o resto seja como output
    pinMode(pinos[i], OUTPUT);
  pinMode(bot, INPUT_PULLUP);

#if serial_on
  Serial.begin(9600);  // Iniciando o serial monitor (talvez colocar 115200)
#endif

  if (!digitalRead(bot)) {
    //EEPROMLogger::print_log();
    //EEPROMLogger::print_debug();
    millis_ant = millis();
    //while (!digitalRead(bot))
      //if (millis() - millis_ant >= time_log)
        //EEPROMLogger::limpar();
  }
}
void loop() {
  display.clearDisplay();  // Limpando o display no inicio do loop
  display.setCursor(0, 0);           // Setando para todos iniciar no inicio da tela
  OLED::abeia_grande(26 - 24, 85 - 24);
  OLED::abeia_pequena(55 - 8, 75 - 8, 40, -6);
  OLED::setas();

  if ((ult_meio.read() <= 3) && (ult_meio.read() > 0))  // Se o sensor dectar que esta distancia ativa a função de desviar
  {
    display.print("Desvia ");
    display.print(ult_meio.read());
    display.display();
    //EEPROMLogger::new_line(millis(), EEPROMLogger::OBJ, ult_meio.read());
    desv();  //! Lembrar de saber qual direcao ele esta indo
  }

  //  Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  leitura = 0;  // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 3; i++)
    leitura |= digitalRead(pinos[i]) << i;  // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00000111);      // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero

  //* Parte em que ele faz o micro ajuste (pensando que o valor maior fica no branco)
  if ((analogRead(s_noroeste) <= analog_esq) && (analogRead(s_nordeste) >= analog_dir))  //! Fazer micro ajuste para esquerda
  {
    millis_ant = millis();
    if (ver == false) {
      vel_direita();
      display.println("Direita ");
      display.print(analogRead(s_noroeste));
      OLED::seta_dir();
      display.display();
      debugln("leitura == 0100 / ajustando para direita");
    } else {
      display.print("D_Tras");
      display.display();
      enc_re(enc_pas_outro);
      ver = false;
    }
  } else if ((analogRead(s_noroeste) >= analog_esq) && (analogRead(s_nordeste) <= analog_dir))  //! Fazer micro ajuste para direita
  {
    millis_ant = millis();
    if (ver == false) {
      vel_esquerda();
      display.println("Esquerda ");
      display.print(analogRead(s_nordeste));
      display.display();
      OLED::seta_esq();
      display.display();
      debugln("leitura == 0010 / ajustando para esquerda");
    } else {
      display.print("E_Tras");
      display.display();
      enc_re(enc_pas_outro);
      ver = false;
    }
  } else
    // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
    // Alguns nao tem break; porque faz a mesma coisa
    switch (leitura) {
      case 0b000:
        /*
        if (ver == false) {
          if (millis() - millis_ant >= time_branco) {
            millis_ant = millis();
            while (millis() - millis_ant <= time_branco)
              micro_ajuste_inv();
          } else {
            vel_frente();
            display.print("000 / frente");
            OLED::seta_cima();
            debugln("leitura = 000");
          }
        } else {
          millis_ant = millis();
          display.print("000 / Tras");
          enc_re(enc_pas_outro);
          ver = false;
        }
        break;
        */
      case 0b010:  //! Caso de ele ir so pra frente
        millis_ant = millis();
        if (ver == false) {
          vel_frente();
          display.print("010 / frente");
          OLED::seta_cima();
          display.display();
          debugln("leitura = 010");
        } else {
          display.print("010 / Tras");
          display.display();
          enc_re(enc_pas_outro);
          ver = false;
        }
        break;
      case 0b100:
      case 0b110:  //! Casos de fazer o esquerda 90
        millis_ant = millis();
        if (ver == false) {
          display.print("100 / parar");
          display.display();
          mot1_par();
          mot2_par();
          delay(mot_par);
          ver = true;
        } else {
          ver = false;
          //EEPROMLogger::new_line(millis(), EEPROMLogger::ESQ, leitura, BIN);
          display.print("100 / Esq_90");
          OLED::seta_esq();
          display.display();
          esq_90();
        }
        break;
      case 0b001:
      case 0b011:  //! Casos de fazer o direita 90
        millis_ant = millis();
        if (ver == false) {
          display.print("001 / parar");
          display.display();
          mot1_par();
          mot2_par();
          delay(mot_par);
          ver = true;
        } else {
          //EEPROMLogger::new_line(millis(), EEPROMLogger::DIR, leitura, BIN);
          display.print("001 / Dir_90");
          OLED::seta_dir();
          display.display();
          dir_90();
          ver = false;
        }
        break;
      case 0b111:  //! Caso de encruzilhada
        millis_ant = millis();
        if (ver == false) {
          display.print("111 / frente");
          display.display();
          vel_frente();
          enc_frente(enc_fre);
        } else {
          display.print("111 / re");
          display.display();
          enc_re(enc_pas_outro);
          ver = false;
        }
        break;
      default:
        break;
    }

  OLED::frame_incr();
}
