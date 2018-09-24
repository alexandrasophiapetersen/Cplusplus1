#include <fstream>
using namespace std;
class ClattToken
   {
private:
   int anzahlAtt;
   char *attName[10];
   char *attValue[10];
public:
   int getAttList(char *eingabe);
   char *zeigeAttName(int id) {return attName[id];}
   char *zeigeAttWert(int id) {return attValue[id];}
   int zahlAtt() {return anzahlAtt;}
   };

class ClToken
   {
public:
   void konvertierung(int ebene, char ausgabe[50]);
   ClToken();
   char *name() { return tokenName; }
   ClToken *child() { return tokenChild; }
   char *inhalt() { return tokenInhalt; }
   void druckeToken(int ebene);
   int getToken(ifstream &datei);
   ClattToken att;
private:
   void cleanToken();
   void druckeneueEbene(int ebene, char ausgabe[50]);
   int fillToken(int mode);
   char tokenName[100];
   ClToken *tokenChild;
   ClToken *tokenSibling;
   char *tokenInhalt;
   } ;

enum zustand { istStartTag, istEndTag } ;
