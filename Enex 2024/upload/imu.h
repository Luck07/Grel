#ifndef _IMU_H
#define _IMU_H

#include <Adafruit_BNO08x.h>
#include "definir.h"

struct euler_t {
  float yaw;
  float pitch;
  float roll;
};

Adafruit_BNO08x  imu(-1);
sh2_SensorValue_t sensorValue;

#ifdef FAST_MODE
  // Top frequency is reported to be 1000Hz (but freq is somewhat variable)
  sh2_SensorId_t reportType = SH2_GYRO_INTEGRATED_RV;
  long reportIntervalUs = 2000;
#else
  // Top frequency is about 250Hz but this report is more accurate
  sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
  long reportIntervalUs = 5000;
#endif

void setReports(sh2_SensorId_t reportType, long report_interval) {
  Serial.println("Setting desired reports");
  if (! imu.enableReport(reportType, report_interval)) {
    Serial.println("Could not enable stabilized remote vector");
  }
}

void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false) {

    float sqr = sq(qr);
    float sqi = sq(qi);
    float sqj = sq(qj);
    float sqk = sq(qk);

    ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
    ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
    ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));

    if (degrees) {
      ypr->yaw *= RAD_TO_DEG;
      ypr->pitch *= RAD_TO_DEG;
      ypr->roll *= RAD_TO_DEG;
    }
}

void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false) {
 quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, euler_t* ypr, bool degrees = false) {
 quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void update_imu(euler_t* ypr) {
 if (imu.getSensorEvent(&sensorValue)) {
     // in this demo only one report type will be received depending on FAST_MODE define (above)
     switch (sensorValue.sensorId) {
       case SH2_ARVR_STABILIZED_RV:
         quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, ypr, true);
       case SH2_GYRO_INTEGRATED_RV:
         // faster (more noise?)
         quaternionToEulerGI(&sensorValue.un.gyroIntegratedRV, ypr, true);
         break;
     }
 }
}

void giro_dir_ang_imu(int angulo, euler_t* ypr) {
 update_imu(ypr);
  float yaw = ypr->yaw;
 
 serv_esq.write(180);
 serv_dir.write(180);
 while(ypr->yaw > yaw - angulo) {
  update_imu(ypr);
  if(ypr->yaw - yaw > angulo)
    break;
  // display.clearLine(5);
  // display.setCursor(0, 5);
  // display.print(ypr->yaw);
 }
}

// void giro_dir_ang_imu(int angulo, euler_t* ypr) {
//   update_imu(ypr);
//   float yaw = ypr->yaw;
//   float dest = (yaw - angulo < -180) ? 180 - abs(angulo) + 180 - abs(yaw) : yaw - angulo; 
 
//  serv_esq.write(180);
//  serv_dir.write(180);
//  //while(ypr->yaw > dest) {
//   if(dest < 0) {
//     while(ypr->yaw > dest) {
//       update_imu(ypr);
//       //if(ypr->yaw - yaw > angulo)
//         //break;
//       display.clearLine(5);
//       display.setCursor(0, 5);
//       display.print(ypr->yaw);
//     }
//   } else {
//     while(ypr->yaw > 0 && ypr->yaw < dest) {

//       update_imu(ypr);

//       //if(ypr->yaw - yaw > angulo)
//         //break;
//       display.clearLine(5);
//       display.setCursor(0, 5);
//       display.print(ypr->yaw);
//     }
//   }
//   // while(dest<0 && ypr->yaw > dest || dest>0 && ypr->yaw < dest) {
//   // update_imu(ypr);
//   // //if(ypr->yaw - yaw > angulo)
//   //   //break;
//   // display.clearLine(5);
//   // display.setCursor(0, 5);
//   // display.print(ypr->yaw);
// }

void giro_esq_ang_imu(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw = ypr->yaw;
  
 serv_esq.write(0);
 serv_dir.write(0);
 while(ypr->yaw < yaw + angulo) {
  update_imu(ypr);
  if(ypr->yaw - yaw > 110)
    break;
 }
}

// void giro_esq_ang_imu(int angulo, euler_t* ypr) {
//   update_imu(ypr);
//   float yaw = ypr->yaw;
//   float dest = yaw - angulo > 180 ? 180 - abs(angulo) + 180 - abs(yaw) : yaw - angulo; 

//  serv_esq.write(0);
//  serv_dir.write(0);
//  while(ypr->yaw < dest) {
//   update_imu(ypr);
//   if(ypr->yaw - yaw > 110)
//     break;
//  }


//
// alguuns testes q eu fiz e fui refatorando aos poucos
//******************************** VERSAO 1
/*

float clamp_yaw(float ang) {
  if(ang >  180) return ang - 360;
  if(ang < -180) return ang + 360;
  return ang;
  //return (ang>180)?ang-360:((ang<-180)?ang+360:ang);
}

void giro_dir(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = clamp_yaw(yaw - angulo);
  
  if(yaw - angulo > -180) {
    while(ypr->yaw > dest) { update_imu(ypr); }
  } else {
    while(ypr->yaw <= 0 || ypr->yaw > dest) { update_imu(ypr); }
  }
}

void giro_esq(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = clamp_yaw(yaw + angulo);
  
  if(yaw + angulo < 180) {
    while(ypr->yaw < dest) { update_imu(ypr); }
  } else {
    while(ypr->yaw >= 0 || ypr->yaw < dest) { update_imu(ypr); }
  }
}

*/
//********************************

//******************************** VERSAO 2
/*

void giro_dir(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = yaw - angulo;

  if(dest < -180) {
    dest += 360;
    while(ypr->yaw <= 0 || ypr->yaw > dest) { update_imu(ypr); }
  } else {
    while(ypr->yaw > dest) { update_imu(ypr); }
  }
}

void giro_esq(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = yaw + angulo;
  
  if(dest > 180) {
    dest -= 360;
    while(ypr->yaw >= 0 || ypr->yaw < dest) { update_imu(ypr); }
  } else {
    while(ypr->yaw < dest) { update_imu(ypr); }
  }
}

*/
//********************************

//******************************** VERSAO 3
/*

void giro_dir(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = yaw - angulo;
  
  if(dest < -180)
    dest += 360;

  while((ypr->yaw <= 0 && yaw - angulo < -180) || ypr->yaw > dest) { update_imu(ypr); }
}

void giro_esq(int angulo, euler_t* ypr) {
  update_imu(ypr);
  float yaw  = ypr->yaw;
  float dest = yaw + angulo;

  if(dest > 180)
    dest -= 360;

  while((ypr->yaw >= 0 && yaw + angulo > 180) || ypr->yaw < dest) { update_imu(ypr); }
}

*/
//********************************

#endif
