#include <Windows.h>
#include <stdio.h>
#include "constantes.h"
#include "Lexique.h"

Message* messageTrouve(Message* pLexique, int numMessage) {
	Message* pMessage = pLexique;
	while (pMessage != NULL && numMessage > pMessage->num)
		pMessage = pMessage->pSuiv;
	return pMessage;
}

void imprimerMessageErreur(Error codeErreur) {
	printf("[X] Error number: 0x000%i !\n", codeErreur);
	system("pause>nul");
}

void afficherMessage(Message* pLexique, int numMessage) {
	Message* pMessage = messageTrouve(pLexique, numMessage);
	if (pMessage != NULL && pMessage->num == numMessage)
		if(numMessage > ERROR_NUM_INVALIDE)
			printf("%s\n", pMessage->texte);
		else
			printf("[X] %s\n", pMessage->texte); // Show error 
	else 
		imprimerMessageErreur(numMessage);
}

void Welcome() {
	printf("-----------------------------------------------------------------------------------------\n");
	printf("------------------------------------- Welcome -------------------------------------------\n");
	printf("-----------------------------------------------------------------------------------------\n\n\n");
}

char* langueLue(Error *codeErreur) {
	char* langue = (char*)calloc(MSG_SIZE, 1);
	if (langue == NULL)
		*codeErreur = ERREUR_MEMOIRE;
	else {
		Welcome();
		printf("- If you want to continue in English entre: en\n");
		printf("- Si vous voulez continuer en Fran\x87\x61is entrez: fr\n"); // \x87\x61  == ça &&  \x82 == é
		printf("> ");
		scanf_s("%s", langue, MSG_SIZE);
		sprintf_s(langue, MSG_SIZE, "%c%c", tolower(langue[0]), tolower(langue[1]));
		system("cls");
	}
	return langue;
} 


int messageLu(char* texte, FILE* pfile) {
	Lexique data;
	if (fread_s(&data, sizeof(Lexique), sizeof(Lexique), 1, pfile)) {
		strcpy_s(texte, MSG_SIZE, data.texte);
	}else
		data.num=0;
	return data.num;
}// return  num, texte

void libererLexique(Message* pLexique) {
	Message* ptr = pLexique;
	while (ptr != NULL) {
		Message* ptrFree = ptr;
		ptr = ptr->pSuiv;
		free(ptrFree->texte);
		free(ptrFree);
	}
}

Error chargerLexique(char* langue, Message** pLexique) {
	Error codeErreur = PAS_D_ERREUR;
	char* pfileName = (char*)calloc(FILE_NAME_SIZE,1);
	if (pfileName == NULL)
		codeErreur = ERREUR_MEMOIRE;
	else {
		FILE* fiLexique;
		if (!strcmp(langue, "fr"))
			strcpy_s(pfileName, FILE_NAME_SIZE, "Messages.txt");
		else
			strcpy_s(pfileName, FILE_NAME_SIZE, "EnglishMessages.txt");
		fopen_s(&fiLexique, pfileName, "rb");
		free(pfileName);
		if (fiLexique == NULL)
			codeErreur = ERREUR_OUVERTURE_FICHIER;
		else {
			char *texte=(char*)calloc(MSG_SIZE,1);
			if (texte == NULL) 
				codeErreur = ERREUR_MEMOIRE;
			else{
				Message* pMessage;
				*(pLexique) = NULL;
				int num = messageLu(texte, fiLexique);
				while (!feof(fiLexique) && codeErreur == PAS_D_ERREUR) {
					pMessage = (Message*)calloc(sizeof(Message),1);
					if (pMessage == NULL)
						codeErreur = ERREUR_MEMOIRE;
					else {
						pMessage->num = num;
						pMessage->texte = (char*)calloc(MSG_SIZE, 1);
						if (pMessage->texte == NULL)
							codeErreur = ERREUR_MEMOIRE;
						else {
							strcpy_s(pMessage->texte, MSG_SIZE, texte);
							pMessage->texte = (char*)realloc(pMessage->texte, strlen(pMessage->texte) + 1);
							if (pMessage->texte == NULL)
								codeErreur = ERREUR_MEMOIRE;
							else {
								pMessage->pSuiv = *(pLexique);
								*(pLexique) = pMessage;
								num = messageLu(texte, fiLexique);
							}
						}
					}
				}
			}
			free(texte);
			fclose(fiLexique);
		}
	}
	return codeErreur;
}
