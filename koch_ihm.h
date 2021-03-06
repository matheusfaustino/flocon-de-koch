/*
 * Fichier : koch_ihm.h
 * Description : Trace de fractales geometriques
                 Fonctions d'ihm du calcul du flocon de koch
 */

#ifndef _KOCH_IHM_H_
#define _KOCH_IHM_H_

#include <stdio.h>
#include <stdlib.h>

/* Initialisation des differents parametres de la fractale a partir
   des arguments du programme ou a defaut en mode interactif */
extern void init_parameters(struct parameters *parameters, int argc, char *argv[]);

/* Affichage de controle sous forme texte de la liste des coordonnees
   des points du flocon de Koch */
extern void show_koch_list(struct list *koch);

/* Affichage de controle des differents parametres de la fractale */
extern void show_parameters(const struct parameters *parameters);

#endif
