//
// Created by ziyad on 24/11/2023.
//

#include "Pendu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define wordsPath "DEFINE ABSOLUTE PATH TO FILE THERE, BUT IN PLACE YOU WRITE BACK SLASH WRITE 2, LIKE THIS : \\, OR IT WILL NOT WORK"
void Game() {
    srand(time(NULL));
    FILE *file = fopen(wordsPath, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        printf("Les mots sont a placer dans le fichier words.txt, il faut aussi remplacer le wordspath(ligne 12 )\n");
        exit(666);
    }
    rewind(file);
    int wordsAmount = 0;

    char curent = 0;

    int totalChars = 0;

    while (curent != EOF) {
        curent = fgetc(file);
        totalChars++;

        if (curent == '\n') {
            wordsAmount++;
        }
    }
    if (totalChars == 0) {
        printf("Le fichier est vide\n");
        exit(666);
    }
    curent = 0;
    rewind(file);

    char word[100];
    int random = rand() % wordsAmount;
    for (int i = 0; i < random; ++i) {
        fgets(word, 100, file);
    }

    for (int i = 0; i < strlen(word); ++i) {
        word[i] = toupper(word[i]);
    }
    char letter;
    int length = strlen(word);
    char* hidden = malloc(length * sizeof(char));
    hidden[length] = '\0';
    if (length < 3) {
        printf("Le mot doit contenir au moins 3 lettres\n");
        exit(666);
    }
    for (int i = 0; i < length; ++i) {
        hidden[i] = '_';
    }
    hidden[0] = word[0];
    hidden[length - 1] = word[length - 1];
    int found = 0;
    int max_incorrect_attemps = 8;
    int max_tries = length + max_incorrect_attemps;
    char letter_user[max_tries];
    int incorrect_attemps = 0;
    int tries = 0;
    //Pendu
    char gameField[7][7] = {{'=', '=', '=', '=', '=', 'Y', '='},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {'=', '=', '=', '=', '=', '=', '='}};
    printf("Bienvenue sur mon jeu du pendu !\n");
    printf("Les mots sont a placer dans le fichier words.txt\n");
    //Boucle du jeu tant que le mot n'est pas trouver ou que le pendu n'est pas fini
    do {
        //print gamefield
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                printf("%c", gameField[i][j]);
            }
            printf("\n");
        }
        //Demande de lettre
        printf("%s\n", hidden);
        printf("Entrez une lettre!\n");
        scanf(" %c", &letter);
        //Lettre majuscule
        letter = toupper(letter);
        int isFound = 0;
        //Nombre de coups restants
        int left_tries = max_incorrect_attemps - incorrect_attemps;
        if (letter > 'Z' || letter < 'A') {
            printf("Entrez une lettre valide\n");
            continue;
        }
        //Verification de la lettre deja entrer
        //letter_user[0] = '_';
        if (letter_user[0] != ' ' ) {
            for (int i = 0; i < max_tries; ++i) {
                letter_user[i] = ' ';
            }
        }

        for (int i = 1; i < max_tries; ++i) {
            if (letter_user[i] == letter) {
                printf("Vous avez deja entrer cette lettre\n");
                tries--;
                isFound = 1;
                continue;
            }else if (letter_user[tries] != letter){
                letter_user[tries] = letter;
                continue;
            }
        }

        //Verification de la lettre
        for (int i = 0; i < length; ++i) {
            if (word[i] == letter) {
                hidden[i] = letter;
                isFound = 1;
                found++;
            }
        }
        //Verification correct ou incorrect
        if (isFound == 0) {
            incorrect_attemps++;
        }
        //Affichage du pendu
        if (incorrect_attemps >= 1){
            gameField[1][5] = '|';
        }
        if (incorrect_attemps >= 2){
            gameField[2][5] = 'O';
        }
        if (incorrect_attemps >= 3){
            gameField[2][4] = '|';
        }
        if (incorrect_attemps >= 4){
            gameField[2][6] = '/';
        }
        if (incorrect_attemps >= 5){
            gameField[3][5] = '\\';
        }
        if (incorrect_attemps >= 6) {
            gameField[4][4] = '|';
        }
        if (incorrect_attemps >= 7) {
            gameField[4][6] = '/';
        }
        if (incorrect_attemps >= 8) {
            gameField[5][4] = '\\';
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    printf("%c", gameField[i][j]);
                }
                printf("\n");
            }
            printf("Dommage !Vous avez perdu. Le mot etait %s\n", word);
            exit(666);
        }
        //Affichage du nombre de coups restants
        printf("Il vous restes %d essais incorects.\n", max_incorrect_attemps - incorrect_attemps);
        tries++;
    } while (strcmp(word, hidden) != 0);

    if (strcmp(word, hidden)==0) {
        printf("Bravo, vous avez gagne !\n");
        printf("Le mot etait %s , vous l'avez trouver en %d coups\n" ,word ,tries);
    }

}