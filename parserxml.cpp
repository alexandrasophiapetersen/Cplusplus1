#include <iostream>
#include <fstream>
#include <string>
#include "parserxml.h"

// Der XML Parser enthält die Attributklasse und lib von Beispiel 9 Rekursion und verknüpfte Listen II(http://hki.uni-koeln.de/beispiel-3/.)
//Da die ClToken Klasse nicht die Endtags mit einbezieht, eignet sich diese nicht für die Konventierung.
//Daher wurde die Tokenklasse von Beispiel 3 von Rekursion und verknüpfte Listen III verwendet (http://hki.uni-koeln.de/beispiel-3-rekursion-und-verknuepfte-listen-iii/)
//Ursprünglich wollte ich wie vorgeschlagen Beispiel 8 verwenden (http://hki.uni-koeln.de/beispiel-8-cltoken-token/).
//Diese eignete sich jedoch nicht für die Form meiner XML-Datei.

using namespace std;
int zeigexml()
{
    ifstream eingabe;
    ClToken *token;

    eingabe.open("sendungsliste.xml");
    token=new ClToken;

    if (token->getToken(eingabe)!=0) token->druckeToken(1);

eingabe.close();
return 0;
}


// von der Datei attlib.cpp
int ClattToken::getAttList(
char                      *eingabe)
{
char puffer[100];
int zaehler;
enum zustand { zwischenTags, inNamen, erwarteAttributNamen, erwarteAttributWert,
               verarbeiteAttributWert} ;
enum zustand zustand;

for (zaehler=0,zustand=inNamen,anzahlAtt=0;*eingabe!='\0';
     eingabe = eingabe + 1)
    {
   switch(*eingabe)
      {
   case ' ':
      if (zustand == inNamen)
         {
         zustand = erwarteAttributNamen;
         *eingabe='\0';
         zaehler=0;
         }
      else if (zustand == verarbeiteAttributWert)
         {
         puffer[zaehler] = *eingabe;
         zaehler++;
         }
      break;

   case '=':
      if (zustand == erwarteAttributNamen)
         {
         zustand = erwarteAttributWert;
         puffer[zaehler] = '\0';
         attName[anzahlAtt] = new char[zaehler+1];
         strcpy(attName[anzahlAtt],puffer);
         zaehler=0;
         }
      else if (zustand == verarbeiteAttributWert)
         {
         puffer[zaehler] = *eingabe;
         zaehler++;
         }
      else cout << "Fehlerhaftes Zeichen! '='" << endl;
      break;

   case '"':
      if (zustand == erwarteAttributWert)
         {
         zustand = verarbeiteAttributWert;
         zaehler = 0;
         }
      else if (zustand == verarbeiteAttributWert)
         {
         zustand = erwarteAttributNamen;
         puffer[zaehler] = '\0';
         attValue[anzahlAtt] = new char[zaehler+1];
         strcpy(attValue[anzahlAtt],puffer);
         zaehler=0;
         anzahlAtt++;
         }
      else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
      break;

   default:
         puffer[zaehler] = *eingabe;
         zaehler++;
      break;
      }
   }

return 1;
}


//von der Datei tokenlib.cpp
ClToken::ClToken()
{
*tokenName='\0';
tokenChild=NULL;
tokenSibling=NULL;
tokenInhalt=new char[1];
*tokenInhalt='\0';
}

int  ClToken::getToken(
ifstream              &datei)
{
int zaehler;
enum zustand zustand;
char zeichen;
char puffer[100];
ClToken *child;

cleanToken();

for (zaehler=0;;)
    {
    datei.get(zeichen);
    if (datei.eof())
       {
       if (*tokenName == '\0' && tokenChild == NULL && tokenInhalt == NULL)
          return fillToken(0);
       return fillToken(1);
       }
    switch(zeichen)
       {
    case '<':
       datei.get(zeichen);
       if (zeichen=='/')
          {
          zustand = istEndTag;
          if (zaehler!=0)
             {
             puffer[zaehler]='\0';
             tokenInhalt = new char[zaehler+1];
             strcpy(tokenInhalt,puffer);
             }
          }
       else
          {
          datei.putback(zeichen);
          if (*tokenName!='\0')
             {
             datei.putback('<');
	     if (tokenChild==NULL)
	        {
                tokenChild=new ClToken;
                if (tokenChild->getToken(datei)==0) return fillToken(0);
		}
	     else
	        {
		for (child=tokenChild;;child=child->tokenSibling)
		    {
		    if (child->tokenSibling==NULL)
		       {
		       child->tokenSibling=new ClToken;
                       if (child->tokenSibling->getToken(datei)==0)
		          return fillToken(0);
		       break;
		       }
		    }
		}
             }
          else zustand=istStartTag;
          }
       zaehler=0;
       break;
    case '>':
       puffer[zaehler]='\0';
       if (zustand==istEndTag)
          {
	  if (strcmp(tokenName,puffer))
	     {
	     cout << "Fehlerhaftes End Tag" << endl;
	     cout << "Erhalten: '" << puffer << "'; erwartet: '"
	          << tokenName << "'" << endl;
             return fillToken(0);   
	     }
	  return fillToken(1);
	  }
       if (zustand==istStartTag)
          {
          att.getAttList(puffer);
          strcpy(tokenName,puffer);
          }
       zaehler=0;
       break;
    case '\n':
       break;
    default:
       puffer[zaehler]=zeichen;
       zaehler++;
       break;
       }
    }
}

int ClToken::fillToken(
int                    mode)
{
if (*tokenName=='\0')
   strcpy(tokenName,"Unbekanntes Element");
if (tokenInhalt==NULL)
   {
   tokenInhalt=new char[1];
   *tokenInhalt='\0';
   }

return mode;
}

void ClToken::cleanToken(void)
{
*tokenName='\0';
if (tokenChild!=NULL)
   {
   delete tokenChild;
   tokenChild=NULL;
   }
if (tokenInhalt!=NULL)
   {
   delete tokenInhalt;
   tokenInhalt=NULL;
   }
}


void ClToken::druckeToken(
int                       ebene)
{
ClToken *child;

druckeTokenEbene(ebene);
cout << name() << ": " << inhalt() << endl;
if (att.zahlAtt() > 0)
   {
   for (int i=0;i<att.zahlAtt();i++)
       {
       druckeTokenEbene(ebene);
       cout << "Attribut " << att.zeigeAttName(i) << " hat den Wert "
            << att.zeigeAttWert(i) << endl;
       }
   }
if (tokenChild!=NULL) tokenChild->druckeToken(ebene+1);
if (tokenSibling!=NULL) tokenSibling->druckeToken(ebene);
}

void ClToken::druckeTokenEbene(
int                            ebene)
{
while (ebene > 0)
      {
      ebene = ebene - 1;
      }
}

