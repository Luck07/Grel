#include "aa.h"
#include "Oled.h"

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_oeste, s_noroeste, s_norte, s_nordeste, s_leste};

MPU6050 mpu(Wire);

#define esq_fre 180
#define esq_rev 0
#define dir_fre 0
#define dir_rev 180
#define parar 90


void setup()
{
  Serial.begin(9600); // Iniciando o serial monitor (talvez colocar 115200)
  serv_esq.attach(servo_esquerda);
  serv_dir.attach(servo_direita);

  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Protocolo para iniciar o display
  // display.setTextColor(WHITE);               // Colocando cor para o texto
  // display.setCursor(0, 0);
  // display.clearDisplay();

  mpu.begin();
  mpu.calibrar_offsets();
  Serial.println("calibrado");
  delay(1000);

  // serv_dir.write(dir_fre);
  // serv_esq.write(esq_fre);
  // unsigned m = millis();
  // for(int _i=0; _i<8; _i++) {
  // while(mpu.yaw() >= -45) {
  //   mpu.update();
  //   //display.clearDisplay();
  //   //display.setCursor(0, 0);
  //   //display.print(mpu.yaw());
  //   //display.display();
  // }
  // mpu.reset_yaw();
  // }


  // m = millis() - m;
  // display.clearDisplay();
  // display.print(m);
  // display.display();

  serv_dir.write(dir_fre);
  serv_esq.write(esq_fre);
  delay(1637);
  serv_dir.write(parar);
  serv_esq.write(parar);
  
  // comprimento: ~21cm
  // velocidade angular (direita): 450º/9s = 360º/7.2s = 50º/s = 1.7453 rad/s
  // velocidade (medida):  ~16cm/s
  // velocidade (calculada): 18.3259cm/s
}

void loop()
{
    //mpu.update();

    /*
    Serial.print(mpu.yaw())   ; Serial.print("\t");
    Serial.print(mpu.pitch()) ; Serial.print("\t");
    Serial.print(mpu.roll())  ; Serial.print("\t");
    Serial.println(mpu.temp());
    */
                   
    //delay(100);
}