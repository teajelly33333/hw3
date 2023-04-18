#include "mbed.h"
#include "accelerometer.h"
#include "gyro.h"

AnalogOut Aout(PA_4);
InterruptIn btnRecord(BUTTON1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
Accelerometer acc;
static BufferedSerial pc(USBTX, USBRX);
double Accel[3]={0};
double Gyro[3]={0};
double  accAngleX=0;
double  accAngleY=0;
double elapsedTime=0;
double roll, pitch, yaw;
double gyroAngleX=0;
double gyroAngleY=0;
int counter=0;
int idR[32] = {0};
int indexR = 0;
/*
void record(void) {

  acc.GetAcceleromterSensor(Accel);
  acc.GetAcceleromterCalibratedData(Accel);

  //printf("Calibrated ACC= %f, %f, %f\n", Accel[0], Accel[1], Accel[2]);

  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(Accel[0] / sqrt(Accel[1]*Accel[1] + Accel[2]*Accel[2])) * 180 / SENSOR_PI_DOUBLE);
  accAngleY = (atan(Accel[1] / sqrt(Accel[0]*Accel[0] + Accel[2]*Accel[2])) * 180 / SENSOR_PI_DOUBLE);

  gyro.GetGyroSensor(Gyro);
  gyro.GetGyroCalibratedData(Gyro);

  //printf("Calibrated Gyro= %f, %f, %f\n", Gyro[0], Gyro[1], Gyro[2]);
  elapsedTime=0.5; //500ms by thread sleep time
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = gyroAngleX + Gyro[0] * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + Gyro[1] * elapsedTime;
  yaw =  yaw + Gyro[2] * elapsedTime;
  // Complementary filter - combine acceleromter and gyro angle values
  //roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  //pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  //Use Acc data only
  roll = accAngleX;
  pitch = accAngleY;
  printf("%f/%f/%f\n", roll, pitch, yaw);

  //ThisThread::sleep_for(10ms);

}

void startRecord(void) {
  //printf("---start---\n");
  idR[indexR++] = queue.call_every(100ms, record);
  indexR = indexR % 32;

}

void stopRecord(void) {
  //printf("---stop---\n");
  for (auto &i : idR)
    queue.cancel(i);
}

int main() {
  t.start(callback(&queue, &EventQueue::dispatch_forever));
  btnRecord.fall(queue.event(startRecord));
  btnRecord.rise(queue.event(stopRecord));
}*/

int main() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    int i = 128;
    char command;
    int n = 0;
    while(1){
        pc.read(&command, 1);
        if(command == '1'){
            i = 0;
            n = 1;
        }
        while(i < 128){
            acc.GetAcceleromterSensor(Accel);
            acc.GetAcceleromterCalibratedData(Accel);
            printf("%f\n", Accel[0]);
            ThisThread::sleep_for(5ms);
            printf("%f\n", Accel[1]);
            ThisThread::sleep_for(5ms);
            printf("%f\n", Accel[2]);
            ThisThread::sleep_for(5ms);
            i++;
        }
        command = '0';
        if(n == 1)
            printf("end\n");
    }

}