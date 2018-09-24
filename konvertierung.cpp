#include <iostream>
#include <fstream>
#include <string.h>
#include "parsercsv.h"
#include "konvertierung.h"

using namespace std;

int konvertieren(){
    ifstream eingabe;
    ClToken *token;
    char dateiname[30];

    cout << "Bitte geben Sie den Dateinamen inklusive Suffix (.xml) ein." << endl;
    cin >> dateiname;
    eingabe.open("sendungsliste.xml");
    token=new ClToken();

    if (token->getToken(eingabe) != 0){
        token->konvertierung(0, dateiname);
    }

    eingabe.close();

    cout << endl << "Die Datei wurde gespeichert. Falls Sie diese anzeigen lassen wollen, drücken Sie ('d') und geben" << '"' << dateiname << '"' << "ein." << endl;

    return 0;
}

void ClToken::konvertierung(int ebene, char ausgabe[50]){
    ifstream eingabe;
    ofstream datei;
    Parser *prs;
    eingabe.open("sendungsliste.csv");
    prs = new Parser();
    prs->parserCSV(eingabe);
    eingabe.close();
    druckeneueEbene(ebene, ausgabe);
    datei.open(ausgabe,ios::app);

    datei << "<" << name();

   if (att.zahlAtt() > 0)
    {
      for (int i=0;i<att.zahlAtt();i++)
      {
        datei << " " << att.zeigeAttName(i) << "="
             << '"' << att.zeigeAttWert(i) << '"' << '>';

        for (int j=0; j<prs->csvreader; j++){
            if (!strcmp(prs->zeigeKennzeichen(j), att.zeigeAttWert(i))){
                datei << "<episoden>" << endl;
                datei << "<staffel nummer=" << '"' << prs->zeigeStaffel(j) << '"' <<">" <<prs->zeigeEpisoden(j) <<"</staffel>"<< endl;
                datei << "</episoden>" << endl;
                }
            }
      }
    }


 else if (att.zahlAtt()==0)
 {
 datei << ">";
     if (tokenChild!=NULL)
     {
        datei << endl;
     }
 }

 datei << tokenInhalt;

 if (tokenChild!=NULL) tokenChild->konvertierung(ebene,ausgabe);

 datei << "</" << name() << ">" << endl;

 if (tokenSibling!=NULL) tokenSibling->konvertierung(ebene,ausgabe);

 datei.close();

}


void ClToken::druckeneueEbene(int ebene, char ausgabe[50]){
    while (ebene > 0){
        ofstream datei;

        datei.open(ausgabe, ios::app);

        datei << " ";
        ebene = ebene - 1;

        datei.close();
    }
}
