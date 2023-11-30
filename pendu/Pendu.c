//
// Created by ziyad on 24/11/2023.
//

#include "Pendu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Game() {
    printf("Bienvenue sur mon jeu du pendu !\n");

    printf("Quel est le mot Rechercher ?\n");
    char word[100];
    scanf("%s", word);
    for (int i = 0; i < strlen(word); ++i) {
        word[i] = toupper(word[i]);
    }
    char letter;
    int length = strlen(word);
    if (length < 3) {
        printf("Le mot doit contenir au moins 3 lettres\n");
        exit(666);
    }
    char* hidden = malloc(length * sizeof(char));
    hidden[length] = '\0';
    for (int i = 0; i < length; ++i) {
        hidden[i] = '_';
    }
    hidden[0] = word[0];
    hidden[length - 1] = word[length - 1];
    int found = 0;    int found = 0;
    int max_incorrect_attemps = 8;
    int max_tries = length + max_incorrect_attemps;
    char letter_user[max_tries];
    int incorrect_attemps = 0;
    int tries = 0;
    char gameField[7][7] = {{'=', '=', '=', '=', '=', 'Y', '='},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {' ', '|', ' ', ' ', ' ', ' ', ' '},
                            {'=', '=', '=', '=', '=', '=', '='}};
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
        letter = toupper(letter);
        int isFound = 0;
        //Verification de la lettre deja entrer
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

        for (int i = 0; i < length; ++i) {
            if (word[i] == letter) {
                hidden[i] = letter;
                isFound = 1;
                found++;
            }
        }
        if (isFound == 0) {
            incorrect_attemps++;
        }
        if (incorrect_attemps >= 1){
            gameField[1][5] = '|';
        }
        if (incorrect_attemps >= 2){
            gameField[2][5] = 'O';
        }
        if (incorrect_attemps >= 3){
            gameField[3][5] = '|';
        }
        if (incorrect_attemps >= 4){
            gameField[3][4] = '/';
        }
        if (incorrect_attemps >= 5){
            gameField[3][6] = '\\';
        }
        if (incorrect_attemps >= 6) {
            gameField[4][5] = '|';
        }
        if (incorrect_attemps >= 7) {
            gameField[4][4] = '/';
        }
        if (incorrect_attemps >= 8) {
            gameField[4][6] = '\\';
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 7; ++j) {
                    printf("%c", gameField[i][j]);
                }
                printf("\n");
            }
            printf("Dommage !Vous avez perdu .\n");
            break;
        }
        printf("Il vous restes %d essais incorects.\n", max_incorrect_attemps - incorrect_attemps);
        tries++;
    } while (strcmp(word, hidden) != 0);
    if (strcmp(word, hidden)==0) {
        printf("Bravo vous avez gagner en %d coups !\n", tries);
    }
}