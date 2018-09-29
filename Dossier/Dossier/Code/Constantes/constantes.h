#pragma once

#define MAX_BUFFER 30
#define FILE_NAME_SIZE 30
#define MSG_SIZE 50

typedef enum  error {
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
	ERROR_NUM_INVALIDE			= 0100
} Error;


typedef enum  choix {
	INITIALISER				= 1,
	AJOUTERJOUEUR,
	AJOUTERPERSONNAGE,
	SUPPRIMER_JOUEUR,
	SUPPRIMER_PERSO,
	IMPRIMER,
	SAUVER,
	QUITTER
} Choix;
typedef enum  menu {
	DIS_JOUEURS			= 1000,
	DIS_PSEUDO			= 1010,
	DIS_TOTAL			= 1020,

	OBT_PSEUDO			= 2000,
	OBT_PERSO_NOM		= 2010,
	OBT_PERSO_POINTS	= 2011,
	OBT_NB_PSEUDO		= 2020,
	OBT_NB_PSEUDO_ADD	= 2030,

	MENU_MSG			= 3000,
	MENU_PRINC			= 3010,
	MENU_INIT			= 3010,
	MENU_ADD_JOUEUR		= 3020,
	MENU_DEL_PERSO		= 3030,
	MENU_DEL_JOUEUR		= 3040,
	MENU_ADD_PERS		= 3050,
	MENU_PRINT			= 3060,
	MENU_SAVE			= 3070,
	MENU_QUITTE			= 3080
} Menu;

typedef struct message Message;
struct message {
	int num;
	char *texte;
	Message *pSuiv;
};

typedef struct personnage Personnage;
struct personnage {
	char *personnage;
	int points;
	Personnage *pSuiv;
};
typedef struct joueur Joueur;
struct joueur {
	char *pseudo;
	Personnage *pDebPersonnage;
	Joueur *pSuiv;
};