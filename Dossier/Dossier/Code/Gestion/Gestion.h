#pragma once
#include "constantes.h"
#include "Fichiers.h"

void libererMemoire(Joueur* pDebJoueur);
void free_s(void* buffer);

// INITIALISER (1)
Error initListeJoueursPersonnages(Message* pLexique, Joueur** pDebJoueur);

// AJOUTERJOUEUR (2)
Error ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueur, FileJoueur ficheJoueur);		// also in (3)
Error obtentionJoueurPersonnages(Message* pLexique, FileJoueur *joueur);								// also in (4)

// AJOUTERPERSONNAGE (3)
Error obtentionJoueurUnPersonnage(Message* pLexique, char** pseudo, char** personnage);
Error ajouterJoueurUnPersonnage(Message* pLexique, Joueur** pDebJoueur, char* pseudo, char* personnage);

// SUPPRIMER Joueur (4)
Error supprimerJoueurPersonnages(Message* pLexique, Joueur**pDebJoueur, char* pseudo);
Error obtentionJoueur(Message* pLexique, char** pseudo);

// SUPPRIMER Personnage (5)
Error supprimerPersonnages(Message* pLexique, Joueur**pDebJoueur, char* joueur, char* pseudo);


// IMPRIMER (6)
Error imprimerJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur);

// SAUVER (7) 
Error sauverJoueursPersonnages(Message* pLexique, Joueur* pDebJoueur);