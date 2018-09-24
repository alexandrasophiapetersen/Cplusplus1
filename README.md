# Semesterarbeit C++ Aufgabenteil 1 - Alexandra Petersen

Repository: https://github.com/alexandrasophiapetersen/Semesterarbeit-C-Aufgabenteil-1-Alexandra-Petersen

Es wurde die Stufe 1 erfüllt. 

Ziel: In dem Programmarchiv der Mediengruppe RTL finden sich Sendungen von VOX, RTL, RTL II. Für die Sendeplanung 2019 möchte das Unternehmen herausfinden, welcher Sender am meisten Eigenformate ausgestrahlt hat. In einer XML-Instanz sind die einzelnen Sendungen aufgelistet. Beim Scannen einer Episode, wird eine TXT Datei erzeugt, welche die Kennzeichnung der Sendung und die Staffeln mit deren Episodenanzahl beinhaltet.  Eine Software führt die  Datensätze zusammen und zeigt die Episodenanzahl der Staffeln der Sendungen an. 

main.cpp: 
Menüführung

parsercsv.cpp & parsercsv.h:

Einlesen und Ausgabe der CSV Datei sendungsliste.csv.

parserxml.cmpp & parserxml.h:
Einlesen und Ausgabe der XML Datei sendungsliste.xml. Dafür wurden Klassen und Funktionen der Vorlesungsfolien verwendet.

konvertieren.cpp & konvertieren.h & Zielformat.dtd:
Konvertierung der Dateien sendungsliste.csv und sendungsliste.xml in eine neue XML Instanz. Definiert wird die neue XML-Instanz durch die DTD Zielformat.dtd. Also Beispiel wie die XML-Datei am Ende aussehen soll siehe: Zielformat.xml. 

anzeigenkonvertierung.cpp & anzeigenkonvertierung.h :
Einlesen und Ausgabe der konvertierten Datei. Dafür wurden Klassen und Funktionen der Vorlesungsfolien verwendet. 







