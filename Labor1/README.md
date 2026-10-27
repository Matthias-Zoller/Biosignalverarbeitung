# Labor 1 – Biosignalverarbeitung (Stand: Aufgabe 4 & 5)

## Hardware
- **Sensor:** SparkFun BMA400 (3-Achsen-Beschleunigung), I2C, Adresse `0x14`
- **Arduino Uno:** SDA → A4, SCL → A5, Serial 57600 Baud
- **Ausgabe pro Zeile:** `X  Y  Z  Time` (Time = `millis()` in ms, auf dem Mikrocontroller erzeugt)

## Umrechnung Rohwert → g → m/s²
- Pro Achse 2 Register (LSB, MSB), zusammen **12 Bit im Zweierkomplement** (−2048 … +2047)
- Zusammensetzen: `raw = ((msb & 0x0F) << 8) | lsb`, danach `if (raw > 2047) raw -= 4096`
- **Skalierung:** `LSB/g = 2048 / Messbereich` → bei ±2 g: **1024 LSB/g**
- `a [g] = raw / 1024.0` und `a [m/s²] = a [g] · 9.81`
- Kontrolle: Sensor liegt flach → Betrag √(x² + y² + z²) ≈ **1 g**

## Gefundene Fehler im Arduino-Code
| Fehler | Korrektur |
|---|---|
| `2**11` (gibt es in C++ nicht) | `2048.0`, `pow(2, 11)` oder `1 << 11` |
| Umrechnung auf einzelne Bytes angewendet | Erst LSB + MSB zusammensetzen, dann skalieren |
| `uint8_t` / Ganzzahldivision | Ergebnis als `float`, mit `2.0` statt `2` rechnen |
| Faktor 2 fehlte → Ruhe-z = 0.49 statt ~1 g | `raw * 2.0 / 2048.0` (= `/ 1024.0`) |
| Durch 2047 statt 2048 geteilt | 2048 = 2¹¹ |
| `Serial.print(a)` → nur 2 Nachkommastellen | `Serial.print(a, 4)` (Auflösung ≈ 0.001 g) |

## Erkenntnisse aus der ersten Messung (Aufgabe 4)
- **Treppenform / ~21 gleiche Zeilen pro Wert:** Der Sensor liefert neue Werte nur mit der ODR von 12.5 Hz (alle 80 ms), die `loop()` gibt aber ohne `delay` alle ~3.7 ms aus (~270 Hz).
- **Erste ~140 ms bei 0.25 statt 0.49:** Bevor `setRange(2G)` greift, ist der Standardbereich ±4 g aktiv → diese Werte verwerfen.
- **Bewegungsphase (ca. 2–4.7 s):** Y wechselt fast bei jedem Sample das Vorzeichen → die Bewegung liegt nahe/über der Nyquist-Frequenz (6.25 Hz) → **Aliasing**, die Kurve gibt die Bewegung nicht korrekt wieder.
- **Lösung (Aufgabe 5):** ODR erhöhen (z. B. `BMA400_ODR_100HZ`) und `delay(10)` passend dazu setzen.
  - Datenblatt (Rev. 2.3) **S. 64**, Register `ACC_CONFIG1` (0x1A), Bits 3:0 `acc_odr`
  - Mögliche Werte: 0x05 = 12.5 Hz, 0x06 = 25, 0x07 = 50, 0x08 = **100**, 0x09 = 200, 0x0A = 400, 0x0B = 800 Hz (0x00–0x04 und 0x0C–0x0F reserved)
  - Gewählt: 100 Hz → Sketch `Lab1Code2_BMA_100Hz`

## Abtastrate bestimmen (Python)
```python
# Ausgaberate (Zeilen pro Sekunde)
fs = (len(df) - 1) / (df['Time'].iloc[-1] - df['Time'].iloc[0])

# Mittelwert und Abweichung
dt = df['Time'].diff().dropna()
fs_mean, dt_std = 1 / dt.mean(), dt.std()
```
- Bei wiederholten Werten ist die **effektive Sensorrate** entscheidend: nur Zeilen mit Wertänderung zählen und den Median von Δt verwenden (hier ≈ 12.5 Hz).
- Wenn ODR und `delay` zusammenpassen, sind Ausgaberate und Sensorrate gleich.

## Python-Hinweise
- Pfade als Raw-String: `r'data\IMU.csv'`, weil `\` sonst eine Escape-Sequenz einleitet (`SyntaxWarning`)
- Einlesen: `pd.read_csv(path, sep=r'\s+')` (Header mit Leerzeichen, Daten mit Tabs)
- Zeit: `df['Time'] = df['Time'].div(1000)` (ms → s)
- Alte Messung retten: Startwerte verwerfen (`Time > 0.2`) und X/Y/Z × 2. Aliasing und fehlende Auflösung lassen sich nachträglich **nicht** korrigieren → Messung wiederholen.

## Filter (Vorbereitung Aufgabe 8)
- `filtfilt` filtert vorwärts und rückwärts → **Nullphase**, effektive Ordnung wird verdoppelt
- `filtfilt` hat **keinen** Parameter `order`, die Ordnung steckt in `b, a`
- Ein Bandpass braucht `lowcut` **und** `highcut`, beide < `fs / 2`
