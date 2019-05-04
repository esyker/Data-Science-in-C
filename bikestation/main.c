#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "trips.h"
#include "menu.h"
#include "parte_grafica.h"

int main(int argc, char *argv[])
{
    nViagem* head=NULL;       // inicializar a cabeça para a lista das viagens
    estacao* headstation=NULL;// inicializar a cabeça para a lista das estações
    char filename1[MAX_ID];
    char filename2[MAX_ID];
    FILE*fp=NULL;

    if(argc != 4)           // se não forem encontrados 4 argumentos não executa o resto do programa
    {
        printf("ERROR\n");
        return -1;
    }

    strcpy(filename1,argv[2]);  // ler dos argumentos da main para nomes que serão usados para abrir ficheiros
    strcpy(filename2, argv[3]);


     if((strcmp("-t", argv[1]))== 0) // abrir parte textual
    {
        MenuMain(&head, &headstation, &fp, filename1, filename2);
        DeleteList(&head);
        remove_lista_station(&headstation);

    }


    else if((strcmp("-g", argv[1])==0))// abrir parte gráfica
    {
        menuGrafic();
    }

    else
    {
      printf("\n\nModo de abertura do programa inexistente!\n");
      return -1;
    }

}

