#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trips.h"
#include "stations.h"


void ReadStation(FILE **fp, estacao **headstation, char* filename2)// função que lê todas as estações a partir da lista de estaçõse
{
    char line[MAX_LINE];
    *fp=fopen(filename2, "r");
    if(*fp==NULL)
    {
        printf("Error opening file!");
        return;
    }

    int station_id;
    float station_lat=0.0, station_long=0.0;
    char station_status[MAX_STATUS];
    char station_name1[MAX_NAME1];
    char station_name2[MAX_NAME2];
    char  municipio[MAX_MUNICIPIO];
    char*token;
    estacao *new_station;


    fgets(line, MAX_LINE, *fp);//remove first line
    while(fgets(line, MAX_LINE, *fp)!=NULL)
    {

    token=strtok(line,"," );
    station_id=atoi(token);

    token=strtok(NULL, ",");  //string
    strcpy(station_name1, token);


    token=strtok(NULL, ",");//string
    strcpy(station_name2, token);


    token=strtok(NULL, ",");//string
    strcpy(municipio, token);


    token=strtok(NULL, ",");
    station_lat=atof(token);

    token=strtok(NULL, ",");
    station_long=atof(token);

    token=strtok(NULL, ",");
    strcpy(station_status, token);//string

    new_station= getStation(station_id,station_name1,station_name2,municipio, station_lat, station_long, station_status);// obter uma nova estação com os dados corretos

    SortedInsertStation(headstation, &new_station);
    }

    return;
}

estacao* getStation(int station_id, char *name1, char *name2, char *municipio, float _lat, float _long, char *status)//obter os dados de uma nova estação
{

   estacao* new_station;
   new_station=(estacao*)calloc(1, sizeof(estacao));
   new_station->descricao=(char* )calloc(strlen(name2)+1, sizeof(char));
   new_station->municipio=(char*)calloc(strlen(municipio)+1, sizeof(char));
   new_station->nome_curto=(char*)calloc(strlen(name1)+1, sizeof(char));
   new_station->estado=(char*)calloc((strlen(status)+1), sizeof(char));
   new_station->stats=(InfoEstacao*)calloc(1, sizeof(InfoEstacao));
   new_station->stats->numb_in=(long long int*)calloc(14, sizeof(long long int));
   new_station->stats->numb_out=(long long int*)calloc(14, sizeof(long long int));
   new_station->id=station_id;
   strcpy(new_station->nome_curto,name1);
   strcpy(new_station->descricao,name2);
   strcpy(new_station->municipio,municipio);
   new_station->latitude=_lat;
   new_station->longitude=_long;
   strcpy(new_station->estado, status);
   return new_station;
}

void SortedInsertStation(estacao **head, estacao** new_station)// inserir um novo nó de forma ordenada, pelo id da estação, na lista de estações
{

    estacao *curr;

    if(*head==NULL)
    {
        *head=*new_station;
        (*new_station)->next=NULL;
        return;
    }

    else if((*head)->id>(*new_station)->id)
    {
        (*new_station)->next=*head;
        (*head)->prev=*new_station;
        *head=*new_station;
    }

    else
    {
    curr=*head;
    while(curr->next!=NULL&&curr->id<curr->next->id)
    {
    curr=curr->next;
    }

     (*new_station)->next=curr->next;
     (*new_station)->prev=curr;
     (curr)->next=*new_station;
    }
}

void GetInfoInOut(nViagem *head, estacao *headstation)//esta função obtém as estatísticas do máximo de bicicletas a sair e a entrar par uma cada hora e estaḉão, lendo a lista de viagens e usando a função writeInfoInOut
{
    nViagem *curr=NULL;
    curr=head;
    while(curr!=NULL)//percorrer a lista de viagens
    {
    writeInfoInOut(headstation,curr->viagem.inicio, curr->viagem.fim, curr->viagem.tinicio.hora,curr->viagem.tfinal.hora);//para cada viagem escrever na lista de estações a informação de chegada de uma bicicleta
    curr=curr->next;
    }
}


void writeInfoInOut(estacao *headstation, int idinicio, int idfinal, int horainicio, int horafim)//ver qual é o número de bicicletas a entrar para cada hora
{
    estacao *curr=NULL;
    curr=headstation;
    while(curr!=NULL)//ver qual é a estação correspondente
    {   if(curr!=NULL)
    {
        if(idinicio==curr->id)
        break;
    }
        curr=curr->next;
    }
        if(curr!=NULL&&horainicio>=8&&horainicio<22)//aumentar as viagens a sair da estacao apenas se estiver entre as 8:00 e as 22:00
        *((curr->stats->numb_out)+(horainicio-8))=*((curr->stats->numb_out)+(horainicio-8))+1;

    curr=headstation;
    while(curr!=NULL)
    {   if(curr!=NULL)
    {
        if(idfinal==curr->id)
        break;//quando chegar à estação correspondente sair do loop
        curr=curr->next;
    }
    }

    if(curr!=NULL&&horafim>=8&&horafim<22)//aumentar as viagens a entrar da estacao apenas se estiver entre as 8:00 e as 22:00
    *((curr->stats->numb_in)+(horafim-8))=*((curr->stats->numb_in)+(horafim-8))+1;


}

void getStats(estacao *headstation)//obter o máximo, mínimo e médio a sair e entrar para cada hora a partir do vetor das viagens a entrar e a sair em cada hora
{
    int total_in=0, total_out=0;
    estacao *curr;
    curr=headstation;
    int i=0;
    while(curr!=NULL)
    {   while(i<=13)
        {
            if(i==0)//
            {
                curr->max_in=*(curr->stats->numb_in);
                curr->min_in=*(curr->stats->numb_in);
                curr->max_out=*(curr->stats->numb_out);
                curr->min_out=*(curr->stats->numb_out);
                total_in=total_in+*(curr->stats->numb_in);
                total_out=total_out+*(curr->stats->numb_out);
            }

            else
            {
            if(curr->max_in<*((curr->stats->numb_in)+i))
            curr->max_in=*((curr->stats->numb_in)+i);
            if(curr->min_in>*((curr->stats->numb_in)+i))
            curr->min_in=*((curr->stats->numb_in)+i);

            if(curr->max_out<*((curr->stats->numb_out)+i))
            curr->max_out=*((curr->stats->numb_out)+i);
            if(curr->min_out>*((curr->stats->numb_out)+i))
            curr->min_out=*((curr->stats->numb_out)+i);

            total_in=total_in+*((curr->stats->numb_in)+i);
            total_out=total_out+*((curr->stats->numb_out)+i);
            }
        i++;
        }
        curr->in_average=(float)(total_in/14.00);
        curr->out_average=(float)(total_out/14.00);
        total_in=0;
        total_out=0;
        i=0;
        curr=curr->next;
    }

}

void PrintStation(estacao* head)// função que imprime todas as estações
{
estacao *curr=NULL;
curr=head;
while(curr!=NULL)
{
    printf("ID da Estação:%d\n", curr->id);
    printf("Nome:%s\n", curr->nome_curto);
    printf("Localização:%s\n", curr->descricao);
    printf("Municipio:%s\n", curr->municipio);
    printf("Estado:%s", curr->estado);
    printf("latitude:%lf\n", curr->latitude);
    printf("longitude:%lf\n", curr->longitude);
    printf("Maximo_in:%lld\n", curr->max_in);
    printf("Minimo_in:%lld\n", curr->min_in);
    printf("Maximo_out:%lld\n", curr->max_out);
    printf("Mininmo_out:%lld\n", curr->min_out);
    printf("Medio_in:%.2f\n",curr->in_average);
    printf("Medio_out:%.2f\n\n",curr->out_average);
    curr=curr->next;
}


}

void remove_lista_station(estacao** headstation)
{
    estacao *curr, *tmp;
    curr=*headstation;
    while(curr!=NULL)
    {
        tmp=curr->next;
        free(curr);
        curr=tmp;
    }
    *headstation=NULL;
}


