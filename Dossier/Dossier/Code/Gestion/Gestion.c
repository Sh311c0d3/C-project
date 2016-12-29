#include <Windows.h>
#include <stdio.h>

#include "Fichiers.h"
#include "constantes.h"
#include "Lexique.h"


void vide() {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}
void getSecur(char* buffer, int sizeBuffer) {
	vide();
	gets_s(buffer, sizeBuffer);
	buffer[0] = toupper(buffer[0]);
	for (int i = 1; i < (int)strlen(buffer) -1; i++)
		buffer[i] = tolower(buffer[i]);
}

int nombrePersonnages(Joueur* pJoueur) {
	Personnage* ptr = pJoueur->pDebPersonnage;
	int i;
	for (i = 0; ptr != NULL; i++)
		ptr = ptr->pSuiv;
	return i;
}

///////////// LIBERER /////////////////
//
void free_s(void* buffer) {
	if (buffer != NULL)
		free(buffer);
}

void libererMemoire(Joueur* pDebJoueur) {
	Joueur* ptr = pDebJoueur;
	while (ptr != NULL) {
		Joueur* ptrFree = ptr;
		ptr = ptr->pSuiv;
		free(ptrFree);
	}
}

void libererPerso(Personnage *pPerso) {
	while (pPerso != NULL) {
		free(pPerso->personnage);
		pPerso->pSuiv;
	}
}
//
///////////// LIBERER //////////////////


///////////// OBTENTION ////////////////
//
Error obtentionJoueurUnPersonnage(Message* pLexique, char** pseudo, char** personnage) {
	Error codeErreur = PAS_D_ERREUR;
	afficherMessage(pLexique, OBT_PSEUDO);
	*pseudo = (char*)calloc(MAX_BUFFER, 1);
	if (*pseudo == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		getSecur(*pseudo, MAX_BUFFER);//scanf_s("%s", (*pseudo), MAX_BUFFER);
		*pseudo = (char*)realloc((*pseudo), strlen((*pseudo)) + 1);
		if (*pseudo == NULL)
			codeErreur = ERREUR_MEMOIRE;
		else {
			afficherMessage(pLexique, OBT_PERSO_NOM);//OBT_NB_PSEUDO_ADD
			*personnage = (char*)calloc(MAX_BUFFER, 1);
			if (*personnage == NULL)
				codeErreur = ERREUR_MEMOIRE;
			else {
				scanf_s("%s", (*personnage), MAX_BUFFER);
				*personnage = (char*)realloc(*personnage, strlen(*personnage) + 1);
				if (*personnage == NULL)
					codeErreur = ERREUR_MEMOIRE;
			}
		}
	}
	return codeErreur;
}

Error obtentionJoueur(Message* pLexique, char** pseudo) {
	Error codeErreur = PAS_D_ERREUR;
	afficherMessage(pLexique, OBT_PSEUDO);
	*pseudo = (char*)calloc(MAX_BUFFER, 1);
	if (*pseudo == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		getSecur(*pseudo, MAX_BUFFER);//scanf_s("%s", *pseudo, MAX_BUFFER);
		*pseudo = (char*)realloc(*pseudo, strlen(*pseudo) + 1);
		if (*pseudo == NULL)
			codeErreur = ERREUR_MEMOIRE;
	}
	return codeErreur;
}

Error obtentionJoueurPersonnages(Message* pLexique, FileJoueur *joueur) {
	Error codeErreur = PAS_D_ERREUR;
	joueur->pseudo = NULL;
	obtentionJoueur(pLexique, &joueur->pseudo);
	afficherMessage(pLexique, OBT_NB_PSEUDO);
	scanf_s("%i", &(joueur->nbPerso));
	while (joueur->nbPerso > MAX_PERSO || joueur->nbPerso < 0) {
		afficherMessage(pLexique, ERROR_NUM_INVALIDE);
		afficherMessage(pLexique, OBT_NB_PSEUDO);
		scanf_s("%i", &(joueur->nbPerso));
	}
	for (int i = joueur->nbPerso; i--;){
		afficherMessage(pLexique, OBT_PERSO_NOM);
		joueur->tabPersonnages[i].nom = (char*)calloc(MAX_BUFFER, 1);
		if (joueur->tabPersonnages[i].nom == NULL)
			codeErreur = ERREUR_MEMOIRE;
		else {
			getSecur(joueur->tabPersonnages[i].nom, MAX_BUFFER);
			joueur->tabPersonnages[i].nom = (char*)realloc(joueur->tabPersonnages[i].nom, strlen(joueur->tabPersonnages[i].nom) + 1);
			if (joueur->tabPersonnages[i].nom == NULL)
				codeErreur = ERREUR_MEMOIRE;
			else {
				afficherMessage(pLexique, OBT_PERSO_POINTS);
				scanf_s("%i", &(joueur->tabPersonnages[i].points));
				while (joueur->tabPersonnages[i].points < 0) {
					afficherMessage(pLexique, ERROR_NUM_INVALIDE);
					afficherMessage(pLexique, OBT_PERSO_POINTS);
					scanf_s("%i", &(joueur->tabPersonnages[i].points));
				}
			}
		}
	}
	return codeErreur;
}

//
///////////// OBTENTION /////////////////


/////////////// Recherche ///////////////
//
Personnage* joueurTrouvePers(Personnage* pDebJoueur, char* personnage, Personnage** pSauvJoueur) {
	Personnage* pJoueur = pDebJoueur;
	while (pJoueur != NULL && strcmp(pJoueur->personnage, personnage) < 0) {
		*(pSauvJoueur) = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	return pJoueur;
}// ret pJoueur, pSauvJoueur

Joueur* joueurTrouve(Joueur* pDebJoueur, char* pseudo, Joueur** pSauvJoueur) {
	Joueur* pJoueur = pDebJoueur;
	while (pJoueur != NULL && strcmp(pJoueur->pseudo, pseudo) < 0) {
		*(pSauvJoueur) = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	return pJoueur;
}
//
/////////////// Recherche ///////////////


/////////////// AJOUTE //////////////////
//
Error ajouterJoueur(Joueur** pDebJoueur, Joueur* pJoueur, Joueur* pSauvJoueur, Joueur* pNouvJoueur) {
	Error codeErreur = PAS_D_ERREUR;
	pNouvJoueur->pSuiv = NULL;
	if (*pDebJoueur == NULL) { // init
		*pDebJoueur = pNouvJoueur;
		(*pDebJoueur)->pSuiv = NULL;
	}else {
		Joueur *ptr = joueurTrouve(*pDebJoueur, pNouvJoueur->pseudo, &pSauvJoueur);
		if (ptr == NULL || pNouvJoueur == NULL || strcmp(ptr->pseudo, pNouvJoueur->pseudo) != 0) {
			if (*pDebJoueur == ptr) {	// Test if first 
				pNouvJoueur->pSuiv = *pDebJoueur;
				*pDebJoueur = pNouvJoueur;
			}else {
				pNouvJoueur->pSuiv = ptr;
				pSauvJoueur->pSuiv = pNouvJoueur;
			}
		}else {
			codeErreur = PERSO_DEJA_PRESENT;
		}
	}
	return codeErreur;
}// ret pDebJoueur

Error ajouterPersonnage(Personnage** pDebPerso, Personnage* pNouvPerso, FilePersonnages pNouvFPerso) {
	Error codeErreur = PAS_D_ERREUR;
	pNouvPerso->personnage = (char*)calloc(strlen(pNouvFPerso.nom) + 1, 1);
	if (pNouvPerso->personnage == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		strcpy_s(pNouvPerso->personnage, strlen(pNouvFPerso.nom) + 1, pNouvFPerso.nom);
		pNouvPerso->points = pNouvFPerso.points;
		pNouvPerso->pSuiv = NULL;

		if (*pDebPerso == NULL) 
			*pDebPerso = pNouvPerso;
		else {
			Personnage* pPerso = *pDebPerso;
			Personnage* pSauvPerso = NULL;
			while (pPerso != NULL && pPerso->points > pNouvFPerso.points) {
				pSauvPerso = pPerso;
				pPerso = pPerso->pSuiv;
			}
			if (pPerso == NULL || pPerso->points <= pNouvFPerso.points) {
				if (pPerso == *(pDebPerso)) {
					pNouvPerso->pSuiv = *pDebPerso;
					*pDebPerso = pNouvPerso;
				}
				else {
					pSauvPerso->pSuiv = pNouvPerso;
					pNouvPerso->pSuiv = pPerso;
				}
			}
			else
				codeErreur = PERSO_DEJA_PRESENT;
		}
	}
	return codeErreur;
}

Error ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueur, FileJoueur ficheJoueur) {
	Error codeErreur = PAS_D_ERREUR;
	Joueur* pNouvJoueur = (Joueur*)calloc(sizeof(Joueur), 1);
	if (pNouvJoueur == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		Joueur *pSauvJoueur = NULL;
		Joueur *pJoueur = joueurTrouve(*(pDebJoueur), ficheJoueur.pseudo, &pSauvJoueur);// ret pJoueur, pSauvJoueur
		if (pJoueur != NULL && strcmp(ficheJoueur.pseudo, pJoueur->pseudo) == 0) {
			codeErreur = JOUEUR_DEJA_PRESENT;
			free(pNouvJoueur);
		}
		else {
			pNouvJoueur->pseudo = (char*)calloc(strlen(ficheJoueur.pseudo) + 1, 1);
			if (pNouvJoueur->pseudo == NULL)
				codeErreur = ERREUR_MEMOIRE;
			else {
				strcpy_s(pNouvJoueur->pseudo, strlen(ficheJoueur.pseudo) + 1, ficheJoueur.pseudo);
				pNouvJoueur->pDebPersonnage = NULL;
				ajouterJoueur(pDebJoueur, pJoueur, pSauvJoueur, pNouvJoueur);// return pDebJoueur
				pJoueur = pNouvJoueur;
				for (int iPersonnage = 0; (iPersonnage < ficheJoueur.nbPerso) && (codeErreur == PAS_D_ERREUR); iPersonnage++) {
					Personnage *pNouvPerso = (Personnage*)calloc(sizeof(Personnage), 1);
					if (pNouvPerso == NULL)
						codeErreur = ERREUR_MEMOIRE;
					else
						codeErreur = ajouterPersonnage(&(pJoueur->pDebPersonnage), pNouvPerso, ficheJoueur.tabPersonnages[iPersonnage]);
				}
			}
		}
	}
	return codeErreur;
}

Error ajouterJoueurUnPersonnage(Message* pLexique, Joueur** pDebJoueur, char* pseudo, char* personnage) {
	Error codeErreur = PAS_D_ERREUR;
	Joueur *pSauvJoueur = NULL;
	Joueur *pJoueur = joueurTrouve(*(pDebJoueur), pseudo, &pSauvJoueur);// ret pJoueur, pSauvJoueur
	if (pJoueur == NULL || strcmp(pseudo, pJoueur->pseudo) != 0) {
		codeErreur = ERREUR_JOUEUR_NOT_FOUND;
	}else {
		Personnage* pNouvPerso = (Personnage*)calloc(sizeof(Personnage), 1);
		if (pNouvPerso == NULL)
			codeErreur = ERREUR_MEMOIRE;
		else {
			FilePersonnages pNouvFPerso;
			pNouvFPerso.nom = (char*)calloc(strlen(personnage) + 1, 1);
			if (pNouvFPerso.nom == NULL)
				codeErreur = ERREUR_MEMOIRE;
			else {
				strcpy_s(pNouvFPerso.nom, strlen(personnage) + 1, personnage);
				afficherMessage(pLexique, OBT_PERSO_POINTS);
				scanf_s("%i", &(pNouvFPerso.points));
				while (pNouvFPerso.points < 0) {
					afficherMessage(pLexique, ERROR_NUM_INVALIDE);
					afficherMessage(pLexique, OBT_PERSO_POINTS);
					scanf_s("%i", &(pNouvFPerso.points));
				}
				ajouterPersonnage(&(pJoueur->pDebPersonnage), pNouvPerso, pNouvFPerso);
				free(pNouvFPerso.nom);
			}
		}
	}
	return codeErreur;
}
//
/////////////// AJOUTE //////////////////


/////////////// FWRITE //////////////////
//
void ecrirePersonnage(FilePersonnages personnage, FILE* fJoueur) {
	fwrite(&personnage.sizePseudo, sizeof(int), 1, fJoueur);
	fwrite(personnage.nom, personnage.sizePseudo, 1, fJoueur);
	fwrite(&personnage.points, sizeof(int), 1, fJoueur);
}

void ecrireJoueur(FileJoueur joueur, FILE* fJoueur) {
	fwrite(&joueur.sizeJoueur, sizeof(int), 1, fJoueur);
	fwrite(joueur.pseudo, joueur.sizeJoueur, 1, fJoueur);
	fwrite(&joueur.nbPerso, sizeof(int), 1, fJoueur);
}
//
/////////////// FWRITE //////////////////


/////////////// SUPPRIMER ///////////////
//
Error supprimerJoueurPersonnages(Message* pLexique, Joueur** pDebJoueur, char* pseudo) {
	Error codeErreur = PAS_D_ERREUR;
	Joueur* ptrSauve = NULL;
	Joueur* ptr = joueurTrouve(*pDebJoueur, pseudo, &ptrSauve);

	if (ptr == NULL)
		codeErreur = ERREUR_JOUEUR_NOT_FOUND;
	else {
		if (ptr == *pDebJoueur) {
			*pDebJoueur = ptr->pSuiv;
			libererPerso(ptr->pDebPersonnage);
			free(ptr->pseudo);
			free(ptr);
		}
		else {
			ptrSauve->pSuiv = ptr->pSuiv;
			libererPerso(ptr->pDebPersonnage);
			free(ptr->pseudo);
			free(ptr);
		}
	}
	return codeErreur;
}//ret pDebJoueur, error

Error supprimerPersonnages(Message* pLexique, Joueur** pDebJoueur, char* joueur, char* pseudo) {
	Error codeErreur = PAS_D_ERREUR;
	Joueur* ptrSauve = NULL;
	Joueur* ptr = joueurTrouve(*pDebJoueur, joueur, &ptrSauve);

	if (ptr == NULL || strcmp(ptr->pseudo, joueur) != 0)
		codeErreur = ERREUR_JOUEUR_NOT_FOUND;
	else {
		Personnage* pPersSauve = NULL;
		Personnage* pPers = joueurTrouvePers(ptr->pDebPersonnage, pseudo, &pPersSauve);
		if (pPers == NULL || strcmp(pPers->personnage, pseudo) != 0)
			codeErreur = ERREUR_PERSO_NOT_FOUND;
		else {
			if (pPers == ptr->pDebPersonnage) {
				ptr->pDebPersonnage = pPers->pSuiv;
				free(pPers->personnage);
				free(pPers);
			}else {
				pPersSauve->pSuiv = pPers->pSuiv;
				free(pPers->personnage);
				free(pPers);
			}
		}
	}
	return codeErreur;
}//ret pDebJoueur, error
//
/////////////// SUPPRIMER ///////////////


/////////////// LECTURE /////////////////
//
Error lectureJoueur(FileJoueur* joueur, FILE* fJoueur) {
	Error codeErreur = PAS_D_ERREUR;
	fread_s(&joueur->sizeJoueur, sizeof(int), sizeof(int), 1, fJoueur);
	joueur->pseudo = (char*)calloc(joueur->sizeJoueur, 1);
	if (joueur->pseudo == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		fread_s(joueur->pseudo, joueur->sizeJoueur, joueur->sizeJoueur, 1, fJoueur);
		fread_s(&joueur->nbPerso, sizeof(int), sizeof(int), 1, fJoueur);
	}
	return codeErreur;
}

Error lecturePersonnage(FilePersonnages* personnage, FILE* fJoueur) {
	Error codeErreur = PAS_D_ERREUR;
	fread_s(&(personnage->sizePseudo), sizeof(int), sizeof(int), 1, fJoueur);
	personnage->nom = (char*)calloc(personnage->sizePseudo, 1);
	if (personnage->nom == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		fread_s(personnage->nom, personnage->sizePseudo, personnage->sizePseudo, 1, fJoueur);
		fread_s(&personnage->points, sizeof(int), sizeof(int), 1, fJoueur);
	}
	return codeErreur;
}
//
/////////////// LECTURE /////////////////


Error sauverJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur) {
	FILE* fJoueur;
	Error codeErreur = PAS_D_ERREUR;
	fopen_s(&fJoueur, "joueur.dat", "wb");
	if (fJoueur == NULL)
		codeErreur = ERREUR_ECRITURE_FICHIER;
	else {
		Joueur* pJoueur = pDebJoueur;
		while (pJoueur != NULL) {
			Personnage* pPerso;
			FileJoueur joueur;
			joueur.sizeJoueur = (int)strlen(pJoueur->pseudo) + 1;
			joueur.pseudo = (char*)calloc(joueur.sizeJoueur, 1);
			if (joueur.pseudo == NULL)
				codeErreur = ERREUR_MEMOIRE;
			else {
				strcpy_s(joueur.pseudo, joueur.sizeJoueur, pJoueur->pseudo);
				joueur.nbPerso = nombrePersonnages(pJoueur);
				ecrireJoueur(joueur, fJoueur);
				pPerso = pJoueur->pDebPersonnage;
				while (pPerso != NULL) {
					FilePersonnages personnage;
					personnage.sizePseudo = (int)strlen(pPerso->personnage) + 1;
					personnage.nom = (char*)calloc(personnage.sizePseudo, 1);
					if (joueur.pseudo == NULL)
						codeErreur = ERREUR_MEMOIRE;
					else {
						strcpy_s(personnage.nom, personnage.sizePseudo, pPerso->personnage);
						personnage.points = pPerso->points;
						ecrirePersonnage(personnage, fJoueur);
						free(personnage.nom);
					}
					pPerso = pPerso->pSuiv;
				}
				free(joueur.pseudo);
			}
			pJoueur = pJoueur->pSuiv;
		}
		fclose(fJoueur);
	}
	return codeErreur;
}

Error imprimerJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur) { 
	Error codeErreur = PAS_D_ERREUR; 
	Joueur* ptr = pDebJoueur;
	if (ptr == NULL)
		codeErreur = ERREUR_JOUEUR_NOT_FOUND;
	else {
		do {
			Personnage* ptrPers = ptr->pDebPersonnage;
			printf("-----------------------------------------------------------------------------------------\n");
			afficherMessage(pLexique, DIS_JOUEURS);
			printf("%s\n\n", ptr->pseudo);
			

			if(ptrPers != NULL){
				int totalPoints = 0;
				afficherMessage(pLexique, DIS_PSEUDO);
				do{
					printf("%s\t\t%i\n", ptrPers->personnage, ptrPers->points);
					totalPoints += ptrPers->points;
					ptrPers = ptrPers->pSuiv;
				}while (ptrPers != NULL) ;
				afficherMessage(pLexique, DIS_TOTAL);
				printf("%i\n", totalPoints);
			}
			ptr = ptr->pSuiv;
			printf("-----------------------------------------------------------------------------------------\n\n");
		} while (ptr != NULL);
	
	}
	return codeErreur; 
}

Error initListeJoueursPersonnages(Message* pLexique, Joueur** pDebJoueur) {
	FILE* fJoueur;
	Error codeErreur = PAS_D_ERREUR;
	fopen_s(&fJoueur, "joueur.dat", "rb");
	if (fJoueur == NULL)
		codeErreur = ERREUR_ECRITURE_FICHIER;
	else {
		FileJoueur joueur;
		Joueur* pJoueur = NULL;
		Joueur* pSauvJoueur = NULL;

		codeErreur = lectureJoueur(&joueur, fJoueur);
		while (!feof(fJoueur)) {
			Joueur* pNouvJoueur = (Joueur*)calloc(sizeof(Joueur), 1);
			if (pNouvJoueur == NULL) 
				codeErreur = ERREUR_MEMOIRE;
			else{
				pNouvJoueur->pseudo = (char*)calloc(strlen(joueur.pseudo) + 1, 1);
				if (pNouvJoueur->pseudo == NULL)
					codeErreur = ERREUR_MEMOIRE;
				else {
					strcpy_s(pNouvJoueur->pseudo, strlen(joueur.pseudo) + 1, joueur.pseudo);
					ajouterJoueur(pDebJoueur, pJoueur, pSauvJoueur, pNouvJoueur);// return pDebJoueur
					pSauvJoueur = pNouvJoueur;
					for (int cptPersonnages = 0; cptPersonnages < joueur.nbPerso; cptPersonnages++) {
						FilePersonnages personnage;
						Personnage* pNouvPerso = (Personnage*)calloc(sizeof(Personnage), 1);
						if (pNouvPerso == NULL) {
							codeErreur = ERREUR_MEMOIRE;
						}
						else {
							codeErreur = lecturePersonnage(&personnage, fJoueur);
							if (codeErreur == PAS_D_ERREUR)
								ajouterPersonnage(&(pNouvJoueur->pDebPersonnage), pNouvPerso, personnage);
						}
						free(personnage.nom);
					}
				}				
			}
			free(joueur.pseudo);
			codeErreur = lectureJoueur(&joueur, fJoueur);
		}
		if(joueur.pseudo != NULL)
			free(joueur.pseudo);
		fclose(fJoueur);
	}
	return codeErreur;
}