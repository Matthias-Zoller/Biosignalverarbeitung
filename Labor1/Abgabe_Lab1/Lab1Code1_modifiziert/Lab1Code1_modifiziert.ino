/* Lab1Code1, modifiziert (Aufgabe 5): ODR 100 Hz, Ausgabe in g mit Zeitstempel millis().
   Install the SparkFun BMA400 Arduino Library through the Arduino Library Manager.

   The BMA400 uses I2C address 0x14 by default. On an Arduino Uno, connect
   SDA to A4 and SCL to A5. Use the breakout's supported supply voltage.
*/

#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"

#define BMA400_ACCEL_DATA_REG 0x04

BMA400 accel;

int16_t readRawAxis(uint8_t lsb, uint8_t msb) {
  int16_t value = ((uint16_t)msb << 8) | lsb;
  if (value > 2047) {
    value -= 4096;
  }
  return value;
}


void setup() {
  Serial.begin(57600);
  Wire.begin();

  if (accel.beginI2C() != BMA400_OK) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

  accel.setRange(BMA400_RANGE_2G);
  // ACC_CONFIG1 (0x1A), acc_odr, Datenblatt S. 64: 0x08 = 100 Hz
  accel.setODR(BMA400_ODR_100HZ);
}

void loop() {
  Wire.beginTransmission(BMA400_I2C_ADDRESS_DEFAULT);
  Wire.write(BMA400_ACCEL_DATA_REG);
  if (Wire.endTransmission(false) != 0) {
    return;
  }

  if (Wire.requestFrom((uint8_t)BMA400_I2C_ADDRESS_DEFAULT, (uint8_t)6) == 6) {
    uint8_t xLsb = Wire.read(); 
    uint8_t xMsb = Wire.read();
    uint8_t yLsb = Wire.read();
    uint8_t yMsb = Wire.read();
    uint8_t zLsb = Wire.read();
    uint8_t zMsb = Wire.read();

    float ax = readRawAxis(xLsb, xMsb) * 2.0 / pow(2, 11);
    float ay = readRawAxis(yLsb, yMsb) * 2.0 / pow(2, 11);
    float az = readRawAxis(zLsb, zMsb) * 2.0 / pow(2, 11);

    Serial.print(ax, 4);
    Serial.print("\t");
    Serial.print(ay, 4);
    Serial.print("\t");
    Serial.print(az, 4);
    Serial.print("\t");
    Serial.println(millis());
  }

  // Ausgaberate an ODR anpassen: 1 / 100 Hz = 10 ms
  delay(10);
}
