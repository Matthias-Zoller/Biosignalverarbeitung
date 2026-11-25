/*
  Lab1Code2 – Aufgabe 5 (Biosignalverarbeitung, Labor 1)
  Basierend auf Lab1Code1 (SparkFun_MMA8452Q Beispiel)

  Änderungen gegenüber Lab1Code1:
  1) Messbereich (Full Scale): SCALE_2G  -> SCALE_8G
     Register XYZ_DATA_CFG (0x0E), Bits FS[1:0]
     Mögliche Werte: 00 = ±2 g, 01 = ±4 g, 10 = ±8 g (11 = reserviert)
     -> Bei ±2 g sättigt der Sensor bei schnellen Bewegungen (>2 g),
        daher die abgeschnittenen Plateaus. ±8 g deckt die Handbewegung ab.

  2) Datenrate (Output Data Rate): ODR_1 -> ODR_100
     Register CTRL_REG1 (0x2A), Bits DR[2:0]
     Mögliche Werte: 800, 400, 200, 100, 50, 12.5, 6.25, 1.56 Hz
     -> Mit 1.56 Hz werden die Bewegungen stark unterabgetastet.
        100 Hz liegt weit über der doppelten Frequenz der Handbewegung
        (Nyquist) und schafft die serielle Übertragung bei 57600 Baud sicher.

  Umrechnung Rohwert -> g (12 Bit, Zweierkomplement):
     ±2 g: 1024 counts/g   ±4 g: 512 counts/g   ±8 g: 256 counts/g
     a[m/s^2] = raw / 256 * 9.81   (bei SCALE_8G)

  Hardware: SparkFun RedBoard Qwiic + MMA8452Q über Qwiic-Kabel
*/

#include <Wire.h>                 // I2C
#include "SparkFun_MMA8452Q.h"    // http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel;

void setup() {
  Serial.begin(57600);            // Serieller Monitor: 57600 Baud
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

  accel.setScale(SCALE_8G);       // vorher: SCALE_2G  -> Clipping bei >2 g
  accel.setDataRate(ODR_100);     // vorher: ODR_1     -> nur 1.56 Hz Abtastrate
}

void loop() {
  if (accel.available()) {        // neue Daten vom Sensor?
    // Rohwerte (counts) x, y, z + Zeitstempel in ms
    Serial.print(accel.getX());
    Serial.print("\t");
    Serial.print(accel.getY());
    Serial.print("\t");
    Serial.print(accel.getZ());
    Serial.print("\t");
    Serial.print(millis());
    Serial.println();
  }
}
