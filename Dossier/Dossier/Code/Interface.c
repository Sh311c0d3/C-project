#include <Windows.h>
#include <stdio.h>

#include "Fichiers.h"
#include "Gestion.h"
#include "constantes.h" 
#include "Lexique.h"

#define TAILLE_MENU 71 // 7 

int menu(Message* pLexique, Menu debMenu) {
	int nbChoix;
	int numMessage = debMenu;
	Message* pMessage = messageTrouve(pLexique, numMessage);
	system("cls");
	afficherMessage(pLexique, MENU_MSG);
	for (nbChoix = 0; pMessage != NULL && pMessage->num < (debMenu + TAILLE_MENU); nbChoix++) {
		printf("%i. %s\n", nbChoix + 1, pMessage->texte);
		pMessage = pMessage->pSuiv;
	}
	return nbChoix;
}

Choix choixObtenu(Message* pLexique) {
	Choix choix;
	int maxChoix;
	do {
		maxChoix = menu(pLexique, MENU_PRINC);
		printf("> ");
		scanf_s("%i", &choix);
		if (choix > maxChoix && choix > QUITTER && choix < 0)
			afficherMessage(pLexique, ERREUR_CHOIX);
	} while (choix > maxChoix && choix > QUITTER  && choix < 0);
	return choix;
}

void interface1(Message* pLexique) {
	Error codeErreur = PAS_D_ERREUR;
	FileJoueur ficheJoueur;
	char* pseudo = NULL;
	char* personnage = NULL;
	Joueur* pDebJoueur = NULL;
	Choix choix = choixObtenu(pLexique);
	while (choix !=  QUITTER) {
		switch (choix){
			case INITIALISER:
				 codeErreur = initListeJoueursPersonnages(pLexique, &pDebJoueur);
				break;
			case AJOUTERJOUEUR:
				codeErreur = obtentionJoueurPersonnages(pLexique, &ficheJoueur);
				if(codeErreur == PAS_D_ERREUR)
					codeErreur = ajouterJoueurPersonnages(pLexique, &pDebJoueur, ficheJoueur);	
				break;
			case AJOUTERPERSONNAGE:
				codeErreur = obtentionJoueurUnPersonnage(pLexique, &pseudo, &personnage);
				if(codeErreur == PAS_D_ERREUR)
					codeErreur = ajouterJoueurUnPersonnage(pLexique, &pDebJoueur, pseudo, personnage);
				free_s(personnage);
				free_s(pseudo);
				break;
			case SUPPRIMER_PERSO: 
				codeErreur = obtentionJoueurUnPersonnage(pLexique, &pseudo, &personnage);
				if (codeErreur == PAS_D_ERREUR)
					codeErreur = supprimerPersonnages(pLexique, &pDebJoueur, pseudo, personnage);
				free_s(personnage);
				free_s(pseudo);
				break;
			case SUPPRIMER_JOUEUR:
				codeErreur = obtentionJoueur(pLexique, &pseudo);
				if (codeErreur == PAS_D_ERREUR)
					codeErreur = supprimerJoueurPersonnages(pLexique, &pDebJoueur, pseudo);
				free_s(pseudo);
				break;
			case IMPRIMER:
				codeErreur = imprimerJoueursPersonnages(pLexique, pDebJoueur);
				if(codeErreur == PAS_D_ERREUR)
					system("pause>nul");
				break;
			case SAUVER:
				codeErreur = sauverJoueursPersonnages(pLexique, pDebJoueur);
				break;
		default:
			//printf("Error\n");
			break;
		}
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, codeErreur);
			system("pause>nul");
		}
		choix = choixObtenu(pLexique);
	}
	libererMemoire(pDebJoueur);
}


//principal
int main() {
	Error codeErreur = PAS_D_ERREUR;
	Message *pLexique = NULL;
	char* langue = langueLue(&codeErreur);
	if (codeErreur == PAS_D_ERREUR) {
		codeErreur = chargerLexique(langue, &pLexique);
		if (codeErreur == PAS_D_ERREUR) {
			interface1(pLexique);
			libererLexique(pLexique);
		}else
			imprimerMessageErreur(codeErreur);
		free_s(langue);
	}else{
		imprimerMessageErreur(codeErreur);
		system("pause");
	}
	return codeErreur;
}