#ifndef TRIPS_H_INCLUDED
#define TRIPS_H_INCLUDED
#include <string.h>
#include <math.h>
#define MAX_LINE 300
#define MAX 11
#define pi 3.14159265358979323846
#define MAX_ID 100
#include "stations.h"
typedef struct
{
	long int hora;
	long int minuto;
}ttime;

typedef struct
{
	long int dia;
	long int mes;
	long int ano;
}date;

typedef struct
{
	char* tipo;		//criar uma contanste, caso seja 0 é um casual, 1 é membro
	long int nascimento;
	char* genero;			//mesmo raciocinio que no tipo; por -1 caso não seja membro;
}Person;

typedef struct dadosViagem
{
	long int id;
	long int duracao;
	char* BikeID;
	ttime tinicio;
	ttime tfinal;
	date dinicio;
	date dfinal;
	Person usuario;
	long int inicio;
	long int fim;
}dadosViagem;


typedef struct nViagem
{
	struct dadosViagem viagem;
	struct nViagem* next;
	struct nViagem* prev;

}nViagem;

nViagem* getNewNode(long int num[15], char* str1, char* str2, char* str3);
float distance(nViagem *curr, estacao* headstation);
void PrintTrips(nViagem *head);
void getNewTrip(nViagem **head, char* filename1);
void sortedInsert(nViagem** head, nViagem** new_viagem);
void removeDuracao(nViagem** head );
void removeWday(nViagem **head);
void PrintTrips(nViagem *head);
int weekday( nViagem* curr );
void removeDuration(nViagem *head);
void remove_criterio_duracao(nViagem **head);
void removenode(nViagem* curr);


#endif // TRIPS_H_INCLUDED
