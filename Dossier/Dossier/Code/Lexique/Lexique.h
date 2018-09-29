#pragma once
#include "constantes.h"

Message* messageTrouve(Message* pLexique, int numMessage);
void afficherMessage(Message* pLexique, int numMessage);
void imprimerMessageErreur(Error codeErreur);


char* langueLue(Error *codeErreur);
void libererLexique(Message* pLexique);
Error chargerLexique(char* langue, Message** pLexique);

typedef struct lexique {
	int num;
	char texte[MSG_SIZE];
}Lexique;