#ifndef STATIONS_H_INCLUDED
#define STATIONS_H_INCLUDED
#define MAX_MUNICIPIO 50
#define MAX_NAME1 20
#define MAX_NAME2 100
#define MAX_STATUS 15
#include "trips.h"//?


typedef struct{
long long  int *numb_in; //soma total das bicicletas a entrar para cada uma das 24 horas
long long int *numb_out;//soma total das bicicletas a sair para cada uma das 24 horas
}InfoEstacao;


typedef struct estacao{
int id;
char *nome_curto;//[CURTO];
char *descricao;//[DESCRICAO];
char *municipio;//[MUNICIPIO];
float latitude, longitude;
char* estado;
InfoEstacao *stats;
struct estacao *next;
struct estacao *prev;
float in_average;  // media das bicicletas a entrar na estação
float out_average;  //media das bicicletas a sair da estação
long long int max_in; //máximo das bicicletas a sair da estação numa hora
long long int min_in;  //minimo das bicicletas e entrar na estação numa hora
long long int max_out;
long long int min_out;


}estacao;


void writeInfoInOut(estacao *headstation, int idinicio, int idfinal, int horainicio, int horafim);
void ReadStation(FILE **fp, estacao **headstation, char* filename2);
estacao* getStation(int station_id, char *name1, char *name2, char *municipio, float _lat, float _long, char *status);
void SortedInsertStation(estacao **head, estacao** new_station);
void PrintStation(estacao* head);
void remove_lista_station(estacao** headstation);

#endif // STRUCTS_H_INCLUDED


