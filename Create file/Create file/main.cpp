#include <stdio.h>
#include <Windows.h>

#define MAX_BUFFER 50

typedef struct fileLang {
	int num;
	const char name[MAX_BUFFER];
}FileLang;

enum  numLang {
	PAS_D_ERREUR				= 0000,
	ERREUR_OUVERTURE_FICHIER	= 0010,
	ERREUR_ECRITURE_FICHIER		= 0011,
	ERREUR_MEMOIRE				= 0020,
	ERREUR_CHOIX				= 0030,
	ERREUR_JOUEUR_NOT_FOUND		= 0040,
	ERREUR_PERSO_NOT_FOUND		= 0050,
	ERREUR_MSG_NOT_FOUND		= 0060,
	JOUEUR_DEJA_PRESENT			= 0070,
	PERSO_DEJA_PRESENT			= 0075,
	ERROR_NUM_INVALIDE			= 0100,

	DIS_JOUEURS = 1000,
	DIS_PSEUDO = 1010,
	DIS_TOTAL = 1020,

	OBT_PSEUDO = 2000,
	OBT_PERSO_NOM = 2010,
	OBT_PERSO_POINTS = 2011,
	OBT_NB_PSEUDO = 2020,
	OBT_NB_PSEUDO_ADD = 2030,

	MENU_MSG = 3000,
	MENU_PRINC = 3010,
	MENU_INIT = 3010,
	MENU_ADD_JOUEUR = 3020,
	MENU_DEL_PERSO = 3030,
	MENU_ADD_PERS = 3040,
	MENU_DEL_JOUEUR = 3050,
	MENU_PRINT = 3060,
	MENU_SAVE = 3070,
	MENU_QUITTE = 3080
};

FileLang pLexiqueEN[] = {
	PAS_D_ERREUR,					"No error",
	ERREUR_OUVERTURE_FICHIER ,		"Fail to open the file !",
	ERREUR_ECRITURE_FICHIER ,		"Fail to write in the file !",
	ERREUR_MEMOIRE ,				"Insufficient memory !",
	ERREUR_CHOIX ,					"Invalid choice !",
	ERREUR_JOUEUR_NOT_FOUND	,		"The player was not found !",
	ERREUR_PERSO_NOT_FOUND,			"The personne was not found !",
	ERREUR_MSG_NOT_FOUND,			"The message was not found !",
	JOUEUR_DEJA_PRESENT	,			"The player already  exist !",
	PERSO_DEJA_PRESENT,				"The personne already  exist !",
	ERROR_NUM_INVALIDE,				"Error invalide numbure !",

	DIS_JOUEURS,		"Name: ",
	DIS_PSEUDO,			"Pseudo:\t\tPoints:",
	DIS_TOTAL,			"The total score of the player :",

	OBT_PSEUDO,			"Pseudo: ",
	OBT_PERSO_NOM,		"Name: ",
	OBT_PERSO_POINTS,	"Points: ",
	OBT_NB_PSEUDO,		"Number of persons: ",
	OBT_NB_PSEUDO_ADD,  "Name of person to add: ",

	MENU_MSG,			"[-] Main menu\n",
	MENU_INIT,			"Initialize list ",
	MENU_ADD_JOUEUR,	"Add a player and its characters",
	MENU_ADD_PERS,		"Add characters to a player",
	MENU_DEL_JOUEUR,	"Remove a player and its characters",
	MENU_DEL_PERSO,		"Remove a character",
	MENU_PRINT,			"Print detailes of players",
	MENU_SAVE,			"Save the list of players",
	MENU_QUITTE,		"Exit"
};

// à => \x85
// é => \x82 
FileLang pLexiqueFR[] = {
	PAS_D_ERREUR,					"pas d'\x82rreur",
	ERREUR_OUVERTURE_FICHIER ,		"Echec de l'ouvertur du fichier !",
	ERREUR_ECRITURE_FICHIER ,		"Echec de l'\202critue du fichier !",
	ERREUR_MEMOIRE ,				"M\x82moire insuffisant !",
	ERREUR_CHOIX ,					"Choix invalid !",
	ERREUR_JOUEUR_NOT_FOUND	,		"Le joueur n'a pas \x82t\x82 trouv\x82 !",
	ERREUR_PERSO_NOT_FOUND,			"la personne n'a pas \x82t\x82 trouv\x82 !",
	ERREUR_MSG_NOT_FOUND,			"Le message n'a pas \x82t\x82 trouv\x82 !",
	JOUEUR_DEJA_PRESENT	,			"Le joueur exist d\x82ja !",
	PERSO_DEJA_PRESENT,				"la personne exist d\x82ja !",
	ERROR_NUM_INVALIDE,				"Erreur num\x82ro invalide ",


	DIS_JOUEURS,		"Nom: ",
	DIS_PSEUDO,			"Pseudo:\t\tPoints:",
	DIS_TOTAL,			"Le total de point des personnages :",

	OBT_PSEUDO,			"Pseudo: ",
	OBT_PERSO_NOM,		"Nom: ",
	OBT_PERSO_POINTS,	"Points: ",
	OBT_NB_PSEUDO,		"Nombre de personne(s): ",
	OBT_NB_PSEUDO_ADD,  "Nom de la personne \x85 ajout\x82: ",

	MENU_MSG,			"[-] Menu principal\n",
	MENU_INIT,			"Initialiser list ",
	MENU_ADD_JOUEUR,	"Ajouter un joueur et ses personnages",
	MENU_ADD_PERS,		"Ajouter des personnages \x85 un joueur", // \x85 => à
	MENU_DEL_JOUEUR,	"Supprimer un joueur et ses personnages",
	MENU_DEL_PERSO,		"Supprimer une personnage",
	MENU_PRINT,			"Imprimer la liste d\x82taill\202e des joueurs", // \x82\x65 => ée
	MENU_SAVE,			"Sauver la liste des joueurs",
	MENU_QUITTE,		"Quitter"
};

int main() {
	const char* lang[] = {
		"Messages.txt",
		"EnglishMessages.txt"
	};
	const FileLang*  langLexique[] = {
		pLexiqueFR,
		pLexiqueEN
	};
	for (int i = sizeof(lang) / sizeof(const char*); i--;) {
		FILE* fiLexique;
		fopen_s(&fiLexique, lang[i], "wb");
		if (fiLexique == NULL)
			return -1;
		else {
			for (int j = sizeof(pLexiqueFR) / sizeof(FileLang); j--;)
				fwrite(&(langLexique[i][j]), sizeof(FileLang), 1, fiLexique);
		}
		fclose(fiLexique);
		SetFileAttributes(lang[i], FILE_ATTRIBUTE_READONLY);	// 'protect' the file 
	}
	return 0;
}