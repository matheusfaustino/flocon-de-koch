/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include "koch_fonctions.h"

/*
 * Traiter les arguments initiaux
 */
void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
    // améliorer cette fonction
    parameters->segment_length = (uint32_t) atoi(argv[1]);
    parameters->nb_iterations = (uint32_t)  atoi(argv[2]);
    parameters->fg_color = (uint32_t) strtol(argv[3], NULL, 0); // 0 parce que commence avec 0x
    parameters->bg_color = (uint32_t) strtol(argv[4], NULL, 0);
    parameters->outfile = argv[5];
    parameters->all_images = argc == 7 && strcmp("all", argv[6]) == 0 ? true : false;
}

/**
 * Afficher la liste
 */
void show_koch_list(struct list *koch)
{
    printf("\nListe Koch\n");
    while(koch != NULL) {
        printf("(%u, %u) -> ", koch->x, koch->y);
        koch = koch->next;
    }
}

/**
 * Afficher les arguments
 */
void show_parameters(const struct parameters *parameters)
{
    printf("Segment Length: %u \nNB Iterations: %u \nFG Color: 0x%x  \nBG Color: 0x%x \nOutfile: %s \nAll Images: %s\n"
        , parameters->segment_length, parameters->nb_iterations, parameters->fg_color, parameters->bg_color, parameters->outfile, parameters->all_images ? "true" : "false");
}
