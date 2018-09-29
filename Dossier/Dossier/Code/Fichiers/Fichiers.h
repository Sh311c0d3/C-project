#pragma once
#define MAX_PERSO 3

typedef struct filePersonnages {
	int sizePseudo;
	char* nom;
	int points;
}FilePersonnages;


typedef struct fileJoueur {
	int sizeJoueur;
	char* pseudo;
	int nbPerso;
	FilePersonnages tabPersonnages[MAX_PERSO];
}FileJoueur;
