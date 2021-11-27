#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1_Speed.h>
#include <Adafruit_Sensor.h>

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);

float accelMultiplier;
float gyroMultiplier;

void setupSensor()
{
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}


void setup() 
{
  Serial.begin(115200);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
  
  accelMultiplier = lsm._accel_mg_lsb/1000*lsm.SENSORS_GRAVITY_STANDARD;
  gyroMultiplier = _gyro_dps_digit;
}

void loop() 
{
  lsm.readAccel();
  lsm.readGyro();
  
  Serial.println(lsm.accelData.x*accelMultiplier);
  Serial.println(lsm.gyroData.x*gyroMultiplier);
}
