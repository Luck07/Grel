#ifndef _MEDICOES_H
#define _MEDICOES_H

#define COMPRIMENTO 21 //cm
#define LARGURA     15.5 //cm
#define FITA_LARGURA 2 //cm
#define LADRILHO 30 //cm

/*
  funcao de trajetoria = f(t) = sqrt(l*l - t*t) + t
  -> d/dt = -t/sqrt(l*l - t*t) + 1
    -> d/dt = 0 -> max
    -> max = l/sqrt(2)
  -> f(l/sqrt(2)) - l = distancia minima
*/
#define DISTANCIA_MINIMA_OBSTACULO 8.69 //cm

#define V_FRENTE     3.96 //cm/s (120,60) 
#define V_FRENTE_MAX 5.26 //cm/s (180, 0)

#define V_FRENTE_CALC     4.26 //cm/s, calculado ocm v_ang
#define V_FRENTE_CALC_MAX 5.53 //cm/s, calculado ocm v_ang

#define V_TRAS     4.64 //cm/s (60,120)
#define V_TRAS_MAX 6.00 //cm/s ( 0,180)

#define V_ANG_ESQ     11.76 //ang/s (120, 90) -> 2.05cm/s no raio comprimento/2
#define V_ANG_ESQ_MAX 15.76 //ang/s (180, 90) -> 2.75cm/s no raio comprimento/2

#define V_ANG_DIR     12.67 //ang/s (90, 60) -> 2.21cm/s no raio comprimento/2
#define V_ANG_DIR_MAX 15.92 //ang/s (90,  0) -> 2.77cm/s no raio comprimento/2

#define V_GIRO_ESQ     30    //ang/s (60,60)
#define V_GIRO_ESQ_MAX 35.57 //ang/s ( 0, 0)

#define V_GIRO_DIR     29.5  //ang/s (120,120)
#define V_GIRO_DIR_MAX 37.06 //ang/s (180,180)

namespace medicoes {
 inline unsigned long frente_ms    (int cm) { return (unsigned long)1000*cm/V_FRENTE    ; }
 inline unsigned long frente_ms_max(int cm) { return (unsigned long)1000*cm/V_FRENTE_MAX; }
 inline unsigned long tras_ms    (int cm) { return (unsigned long)1000*cm/V_TRAS    ; }
 inline unsigned long tras_ms_max(int cm) { return (unsigned long)1000*cm/V_TRAS_MAX; }
 inline unsigned long esq_r_ms    (int angulo) { return (unsigned long)1000*angulo/V_ANG_ESQ    ; }
 inline unsigned long esq_r_ms_max(int angulo) { return (unsigned long)1000*angulo/V_ANG_ESQ_MAX; }
 inline unsigned long dir_r_ms    (int angulo) { return (unsigned long)1000*angulo/V_ANG_DIR    ; }
 inline unsigned long dir_r_ms_max(int angulo) { return (unsigned long)1000*angulo/V_ANG_DIR_MAX; }
 inline unsigned long esq_giro_ms    (int angulo) { return (unsigned long)1000*angulo/V_GIRO_ESQ    ; }
 inline unsigned long esq_giro_ms_max(int angulo) { return (unsigned long)1000*angulo/V_GIRO_ESQ_MAX; }
 inline unsigned long dir_giro_ms    (int angulo) { return (unsigned long)1000*angulo/V_GIRO_DIR    ; }
 inline unsigned long dir_giro_ms_max(int angulo) { return (unsigned long)1000*angulo/V_GIRO_DIR_MAX; }

 // inline unsigned long giro180_ms() {
 // #if (V_GIRO_DIR_MAX >= V_GIRO_ESQ_MAX)
 //  return dir_giro_ms_max(180);
 // #else
 //  return esq_giro_ms_max(180);
 // #endif
 // }
}
#endif