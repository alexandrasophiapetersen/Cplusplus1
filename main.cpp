#include <iostream>
#include "main.h"
#include <string>
#include <fstream>
using namespace std;


int main(){

    zurueck:
    cout << "Willkommen im Menü !" << endl;
    cout << "-------------------------------------------------" << endl;
    //Stufe 1: Menüführung
    cout << "----------------------Menü-----------------------" << endl;
    cout << "Bitte wählen Sie einen der folgenden Menüpunkte aus ('a', 'b', 'c'). Bitte achten Sie dabei darauf, dass ihre Feststell-Taste deaktiviert ist!" << endl;
    cout << "_________________________________________________" << endl;
    cout << "1. Anzeigen der Daten der XML('a') und der CSV Datei ('b')" << endl;
    cout << "2. Dateikonverter/Export der Sendungslisten ('c')" << endl;
    cout << "3. Konvertierte Datei anzeigen lassen ('d')"<<endl;
    cout << "_________________________________________________" << endl;
    cout <<  "4. Anwendung beenden ('e').Für Hilfe drücken Sie 'h'." <<endl;
    char auswahl;


    cin >>(auswahl);
    cout << endl;

    switch (auswahl) {
    case 'a':
        zeigexml();
        break;

    case 'b':
        zeigecsv();
        break;

    case 'c':
        konvertieren();
        break;

    case 'd':
        anzeigen();
        break;

    case 'e':
            cout << "Programm erfolgreich beendet." << endl;
            return 0;
            break;

    case 'h':
        cout << "Bitte wählen Sie einen der Buchstaben in den Klammern aus. Beispiel: 'a' --> tippen Sie einfach ein a ein und drücken Sie enter." << endl;
        break;

    default:
        cout << "Dies ist keine Option, bitte wählen Sie einen der Buchstaben in den Klammern aus." << endl;
        break;


    }
goto zurueck;
return 0;

}


