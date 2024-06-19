// Switch
#include "Definir.h" // Dando include nas variaveis e funções
#include "Oled.h"    // Dando include no arquivo que tem as bibliotecas e criando o objeto do display oled s

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_oeste, s_noroeste, s_norte, s_nordeste, s_leste};

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Protocolo para iniciar o display
    display.setTextColor(WHITE);               // Colocando cor para o texto

    // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
    for (int i = 0; i < 5; i++) // Usando o array para fazer os pinmode como input
        pinMode(pinos[i], INPUT);

  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

#if serial_on
    Serial.begin(9600); // Iniciando o serial monitor (talvez colocar 115200)
#endif
}
void loop()
{
    display.clearDisplay();  // Limpando o display no inicio do loop
    display.setCursor(0, 0); // Setando para todos iniciar no inicio da tela

    /*if (ult_meio.read() <= 3 && ult_meio.read() > 0) // Se o sensor dectar que esta distancia ativa a função de desviar
    {
        display.print("Desvia ");
        display.print(ult_meio.read());
        display.display();
        desv(); //! Lembrar de saber qual direcao ele esta indo
    }*/

    //  Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
    byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
    for (int i = 0; i < 5; i++)
        leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
    leitura = (~leitura) & (0b00011111);       // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero

    // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
    // Alguns nao tem break; porque faz a mesma coisa
    switch (leitura)
    {
    case 0b00000:
        if (ver == false)
        {
            vel_frente();
            display.print("0000");
            display.display();
            debugln("leitura = 0000");
        }
        else
        {
            display.print("0000 / Tras");
            display.display();
            delay(delay_pas);
            ver = false;
            millis_ant = millis();
        }
        break;
    case 0b01010: //! Caso de ele ir so pra frente
        if (ver == false)
        {
            vel_frente();
            display.print("0110");
            display.display();
            debugln("leitura = 0110");
        }
        else
        {
            display.print("0110 / Tras");
            display.display();
            delay(delay_pas);
            ver = false;
        }
        millis_ant = millis();
        break;
    case 0b00010: //! Caso dele fazer micro ajuste para direita
        if (ver == false)
        {
            vel_direita();
            display.print("0010 / Direita");
            display.display();
            debugln("leitura == 0010 / ajustando para direita");
        }
        else
        {
            display.print("0010 / Tras");
            display.display();
            vel_re();
            ver = false;
        }
        millis_ant = millis();
        break;
    case 0b01000: //! Caso dele fazer micro ajuste para esquerda
        if (ver == false)
        {
            vel_esquerda();
            display.print("0100 / Esquerda");
            display.display();
            debugln("leitura == 0100 / ajustando para esquerda");
        }
        else
        {
            display.print("0100 / Tras");
            display.display();
            vel_re();
            ver = false;
        }
        millis_ant = millis();
        break;
    case 0b10000:
    case 0b11000:
    case 0b11010:
    case 0b10010: //! Casos de fazer o esquerda 90  
        if (ver == false)
        {
            display.print("1000 / parar");
            display.display();
            vel_parar();
            ver = true;
        }
        else
        {
            ver = false;
            display.print("1000 / Esq_90");
            display.display();
            esq_90();
        }
        millis_ant = millis();
        break;
    case 0b00001:
    case 0b00011:
    case 0b01011:
    case 0b01001: //! Casos de fazer o direita 90
        if (ver == false)
        {
            display.print("0001 / parar");
            display.display();
            vel_parar();
            ver = true;
        }
        else
        {
            ver = false;
            display.print("0001 / Dir_90");
            display.display();
            dir_90();
        }
        millis_ant = millis();
        break;
    case 0b1111: //! Caso de encruzilhada
        millis_ant = millis();
        if (ver == false)
        {
            display.print("111 / frente");
            display.display();
            vel_frente();
        }
        else
        {
            display.print("111 / re");
            display.display();
            vel_re();
            ver = false;
        }
        millis_ant = millis();
        break;
    default:
        break;
    }
}