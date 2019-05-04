#include <stdio.h>
#include <stdlib.h>
#include "trips.h"
#include "menu.h"
#define MAX_ID 100

void MenuMain(nViagem**head, estacao**headstation, FILE**fp, char* filename1, char* filename2)//função que dá o menu principal
{
    int choice=0;
    do
    {
        printf("\n\nNota: os dados demoram a carregar do ficheiro após a a seleção da opção desejada!\n");
        printf("\nMenu\n\n");
        printf("1. Seleção de Dados\n");
        printf("2. Listagem de Viagens\n");
        printf("3. Listagem de Estações\n");
        printf("4. Listagem de Rotas\n");
        printf("5. Listagem de Estatísticas\n");
        printf("6. Limpar a Seleção de Dados\n");
        printf("7. Exit\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            DeleteList(head);
            getNewTrip(head, filename1);
            Menu1(head, headstation); //função que mostra o menu sa seleção de dados
            break;
        case 2:
            if(*head==NULL)
            getNewTrip(head, filename1);
            PrintTrips(*head);

            break;
        case 3:
            if(*headstation==NULL)// se não houver lista de estações, criar
            ReadStation(fp, headstation,filename2);
            if(*head==NULL)//se não houver lista de viagens criar
            getNewTrip(head, filename1);
            GetInfoInOut(*head, *headstation);//guardar as informações de bicicletas a entrar e a sair
            getStats(*headstation);// obter a media, maximo e media a partir das informações obtidaos por GetInfoInOut
            PrintStation(*headstation);
            break;
        case 4:
            if(*headstation==0)
            ReadStation(fp, headstation,filename2);
            if(*head==0)
            getNewTrip(head, filename1);
            ListagemRotas(*head);
            break;
        case 5:
            if(*headstation==0)//
            ReadStation(fp, headstation,filename2);
            if(*head==0)
            getNewTrip(head, filename1);
            Menu5(head, headstation);//função que mostra o menu das estatísticas
            break;

        case 6:
            DeleteList(head);
            break;

        case 7:
            printf("\nGoodbye!");
            break;
        default:
            printf("Wrong Choice. Enter again\n");
            break;
        }
    }
    while (choice != 7);
    return;
}


void Menu1(nViagem **head, estacao ** headstation)
{
    int choice=0;
    do
    {
        printf("Seleção por:");
        printf("\n  1.Período de Tempo\n ");
        printf(" 2.Dia da Semana\n ");
        printf(" 3.Duração\n");
        printf("  4. Voltar ao Menu Inicial\n\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:remove_criterio_hora(head);
            break;
        case 2:removeWday(head);
            break;
        case 3:remove_criterio_duracao(head);
            break;
        }
    }
    while(choice!=4);

    return;
}

void Menu5(nViagem **head, estacao **headstation)
{
    int choice=0;
    do
    {
        printf("Tipo de Estatística:\n");
        printf(" 1.Estatísticas por género\n ");
        printf("2.Estatísticas por idade\n ");
        printf("3.Estatísticas da duração\n");
        printf(" 4.Estatísticas da velocidade\n");
        printf(" 5.Voltar ao Menu Inicial\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:StatsGenero(*head);
            break;
        case 2:StatsIdade(*head);
            break;
        case 3:StatsDuracao(*head);
            break;
        case 4:StatsVelocidade(*head, *headstation);
            break;
        case 5:
            printf("\nVoltar ao Menu Inicial");
            break;

        }
    }
    while(choice!=5);

    return;
}
