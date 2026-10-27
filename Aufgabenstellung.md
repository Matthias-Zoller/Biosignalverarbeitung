Pflicht: Abgabe der Python Dateien in .zip-File (Main Skript der Python Auswertung als MainCode1.ipynb)

Pflicht: Laborbericht zu übrigen Fragen. Max 10 Seiten. (Berichte, die die vorgegebene Maximallänge überschreiten, werden nicht korrigiert und mit 0 Punkten bewertet.)

Für Teil 1 des Labors werden Sie einen Laborbericht einreichen müssen, in dem Sie die nachfolgenden Fragen beantworten und ihren Code zur Signalverarbeitung von Biosignalen abgeben. Dadurch bekommen Sie vor den eigentlich bewerteten Laborberichten Feedback und können dieses direkt in die Folgenden Berichte einbauen. Der Bericht soll in LATEX geschrieben werden. Die dafür benötigte Vorlage können Sie auf Sakai finden.

Die Abgabe des Python Codes umfasst das Bearbeiten der Aufgaben:

4 (a)
5
6 (a)
7
8
9
10
Es wird empfohlen das Python Scripts als .ipynb aufzubauen und die genannten Aufgaben untereinander abzuarbeiten.

Erstellen Sie Diagramme, in denen das Messsystem dargestellt ist. Beschriften Sie jede Komponente, jeden Bus (einschließlich Bustyp und -geschwindigkeit) sowie jeden Signalpfad, und beschreiben Sie diese jeweils kurz. (1-2 Sätze pro Komponente). (1 Darstellung, 2 Punkte)

Angenommen Sie bestimmte Ihre Körpertemperatur mit einem Sensor, der Spannungen von 0 − 3.3 V messen kann und einen Messbereich von 0 − 40°C hat. Ihr Mikrocontroller kann bis zu 5 V und mit einer Auflösung von 10 Bit messen. Welche Temperatur misst der Sensor, wenn der Mikrocontroller einen Wert von 520 ausgibt? Zeigen Sie Ihre Rechnung! (1 Darstellung, 2 Punkte)

Auf dem Beschleunigungssensor ist ein Koordinatensystem gegeben, welches die x-, y- und z-Achse angibt. Welcher Wert der drei angezeigten Beschleunigungen gehört zu welcher Achse? Wie kann man dies testen und in welcher Einheit werden die Daten ausgegeben? Wie kann ich die Daten in physikalische Größen (m/s²) umrechnen? (Als Referenz für die Umrechnung verwenden Sie die Datenblatt von dem Beschleunigungssensor.) (1 Darstellung, 2 Punkte)

Führen Sie folgendes Experiment aus (Nehmen Sie dafür den gegebenen Arduino Code Lab1Code1): Nehmen Sie den Beschleunigungssensor in Ihre geschlossene Hand und bewegen Sie ihn sehr schnell pro Sekunde einmal hoch und runter (ohne Rotation). Führen Sie dies für 10 Sekunden aus und speichern Sie die Daten. Das Speichern der Daten in eine .txt Datei für die Verarbeitung wird über einfaches Copy&Paste durchgeführt. Dafür muss ein neues .txt-Dokument erstellt und geöffnet werden. Trennen Sie nun die Verbindung zwischen Mikrocontroller und Computer, dadurch stoppt die im seriellen Monitor angezeigte Datenübertragung. Wählen Sie das Feld mit den Daten aus und kopieren Sie alle Daten mit der Tastenkombination Strg + A (Alles auswählen) → Strg + C (Kopieren) & Strg + V (Einfügen) in Ihr Text-Datei.

(a) Plotten Sie 4 Sekunden der Daten. (1 Darstellung, 1 Punkte)

(b) Diskutieren Sie die Plateaus der Peaks. Warum sind diese alle beim gleichen Wert? Wie könnte man dieses Problem lösen? (1 Paragraph, 1 Punkte)

(c) Warum stellen die Daten nicht exakt die durchgeführten Bewegungen dar? (1 Paragraph, 1 Punkte)

Ändern Sie den vorherigen Arduino Code so, dass die Aufzeichnungen mit den Bewegungen übereinstimmen, indem Sie das Datenblatt des Sensors konsultieren. Dokumentieren Sie die Seite, auf der Sie die Information über das betreffende Register gefunden haben, sowie den Parameter und alle möglichen Werte, die dieser Parameter annehmen kann. Begründen Sie die Auswahl des verwendeten Wertes. Wiederholen Sie das Experiment. Plotten Sie wieder 4 Sekunden der Daten und vergleichen Sie den Plot mit dem aus der vorhergegangenen Aufgabe. Welche Gemeinsamkeiten und Unterschiede gibt es, und warum bestehen sie? (1 Darstellung, 1 Paragraph, 2 Punkte)

Die Abtastfrequenz zu bestimmen jede Messung soll mit einem eigenen Zeitstempel versehen werden, der unmittelbar auf dem Mikrocontroller erzeugt wird (z. B. mit einer Mikrosekunden- oder Millisekunden-Uhr). Verwenden Sie dafür nicht die Zeitstempel der seriellen Konsole, sondern eine Funktion in Ihre Code während der Datenerfassung. Aus den aufgezeichneten Zeitstempeln berechnen Sie die mittlere Abtastfrequenz und Abweichung Ihrer Messung. Drehen Sie den Beschleunigungssensor in alle 6 Richtungen (jede Achse nach oben und unten zeigend) und messen Sie jeweils 10 Sekunden in jedem Zustand. Prüfen Sie damit, ob jeweils eine Beschleunigung von 1 g angezeigt wird.

(a) Stellen Sie die Daten in einem Plot dar. (1 Darstellung, 1 Punkte)

(b) Sehen Sie sich die Daten an, wenn der Sensor mit einer Achse nach unten oder oben zeigt. Ergeben die Daten Sinn?

Plotten Sie die gefilterten gegen die ungefilterten Daten des vorherigen Experiments. Beschreiben Sie in ein oder zwei Sätzen, welchen Effekt der Filter erzielt hat und warum Sie diesen Filter verwendet haben. (1 Darstellung, kurze Antwort, 2 Punkte)

Nutzen Sie die gesammelten Daten, um die Absatzfrequenz (Mittelwert und Abweichung) zu bestimmen (1 Darstellung, 2 Punkte) (Code, 1 Punkt)

Verwenden Sie jetzt das mobile Messsystem und mit dem DataLogger und der Batterie. Nehmen Sie mit dem Code Lab1Code2 etwa 10 Sekunden auf (Bewegung ist egal) und vergleichen Sie die Abtastfrequenz (Mittelwert und Abweichung) mit dem früheren Wert. Warum sind diese unterschiedlich? (1 Paragraph, 2 Punkte)

Ihr abgegebener Code funktioniert und erzeugt die richtigen Plots, welche für diesen Bericht gefordert waren. (1 Punkt)

Gesamte Punkte: 20

Abgabe auf Sakai:

Die Abgabe erfolgt über das Sakai Portal. Verwenden Sie dabei diese Schreibweise (Lab1_Gruppe_Gruppennummer) für die Gruppeneinreichung und speichern Sie die folgenden Dateien in dieser .zip-Datei:

Laborbericht als PDF als Bericht_1_Gruppe_Gruppennummer (Berichte, die die vorgegebene Maximallänge überschreiten, werden nicht korrigiert und mit 0 Punkten bewertet.)

Modifiziertes Lab1Code1 Arduino Code (Abgabe 5)

Main Skript der Python Auswertung als MainCode1.ipynb

Alle Datensätze um MainCode1 ausführen zu können

Selbstgeschrieben Python Bibliotheken, welche für MainCode1 benötigt werden

Bitte alles in eine .zip -Datei speichern!!!