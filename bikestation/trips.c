#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trips.h"
#include "stations.h"


void getNewTrip(nViagem **head, char* filename1)// função utilizada para obter a lista a partir do ficheiro
{


    FILE*fp=fopen(filename1, "r");
    if (fp==NULL)
    {
        printf("error opening file");
    }
    char *token;
    long int num[15];
    char linha[MAX_LINE];
    char str1[MAX];
    char str2[MAX];
    char str3[MAX];
    nViagem *new_node;
    token=calloc(55, sizeof(long int));

    fgets(linha, MAX_LINE, fp);
    while(fgets(linha, MAX_LINE, fp)!=NULL)
    {
        token=strtok(linha, ", /:");
        num[0]=atoi(token);


        token=strtok(NULL, ", /:");
        num[1]=atoi(token);


        token=strtok(NULL, ", /:");
        num[2]=atoi(token);


        token=strtok(NULL, ", /:");
        num[3]=atoi(token);


        token=strtok(NULL, ", /:");
        num[4]=atoi(token);


        token=strtok(NULL, ", /:");
        num[5]=atoi(token);


        token=strtok(NULL, ", /:");
        num[6]=atoi(token);


        token=strtok(NULL, ", /:");

        token=strtok(NULL, ", /:");
        num[7]=atoi(token);


        token=strtok(NULL, ", /:");
        num[8]=atoi(token);


        token=strtok(NULL, ", /:");
        num[9]=atoi(token);


        token=strtok(NULL, ", /:");
        num[10]=atoi(token);


        token=strtok(NULL, ", /:");
         num[11]=atoi(token);


        token=strtok(NULL, ", /:");
        num[12]=atoi(token);


        token=strtok(NULL, ", /:");


        token=strtok(NULL, ", /:");
        num[13]=atoi(token);


        token=strtok(NULL, ", /:");
        strcpy(str1, token);

        if(strcmp(str1,"Casual")!=0&&strcmp(str1, "Registered")!=0)//ver se tem bike id
        {

        token=strtok(NULL, ", /:");
        strcpy(str2, token);

        if (strcmp(token, "Registered")==0)// ver se é registado ou casual
        {
            token=strtok(NULL, ", ");
            num[14]=atoi(token);


            token=strtok(NULL, ", ");
            strcpy(str3, token);
        }
        }
        if(num[1]>=0&&((strncmp(str1,"Casual",6)!=0&&strncmp(str1, "Registered",10 )!=0&&num[14]>=1910)))// se tiver duração negativa ou não tiver bike id ou se tiver uma idade muito elevada e supostamente inválida não se introduz na lista
        {
        new_node=getNewNode(num, str1, str2, str3);//obter um novo nó e associar-lhe os dados
        sortedInsert(head,&new_node);//inserir o nó criado na lista de forma ordenada, por hora
        }


    }
    return;


}



nViagem* getNewNode(long int num[15], char* str1, char* str2, char* str3)// função utilizada para obter um novo nó e associar-lhe os dados lidos do ficheiro
{
    nViagem *new_viagem;
    new_viagem=(nViagem*)calloc(1,sizeof(nViagem));
    new_viagem->viagem.BikeID=(char*)calloc(strlen(str1)+1, sizeof(char));
    new_viagem->viagem.usuario.tipo=(char*)calloc(strlen(str2)+1, sizeof(char));
    new_viagem->viagem.usuario.genero=(char*)calloc(strlen(str3)+1,sizeof(char));

    if (new_viagem==NULL)
        printf("Error allocating memory!");

    //associar os dados da estrutura do novo nó de acordo com os dados lidos do ficheiro
    new_viagem->viagem.id= num[0];
    new_viagem->viagem.duracao=num[1];
    new_viagem->viagem.tinicio.hora=num[5];
    new_viagem->viagem.tinicio.minuto=num[6];
    new_viagem->viagem.tfinal.hora=num[11];
    new_viagem->viagem.tfinal.minuto=num[12];
    new_viagem->viagem.dinicio.ano=num[4];
    new_viagem->viagem.dinicio.mes=num[2];
    new_viagem->viagem.dinicio.dia=num[3];
    new_viagem->viagem.dfinal.ano=num[10];
    new_viagem->viagem.dfinal.mes=num[8];
    new_viagem->viagem.dfinal.dia=num[9];
    new_viagem->viagem.inicio=num[7];
    new_viagem->viagem.fim=num[13];
    strcpy(new_viagem->viagem.BikeID, str1);
    strcpy(new_viagem->viagem.usuario.tipo, str2);
    if(strcmp(str2, "Registered")==0)
    {
        new_viagem->viagem.usuario.nascimento=num[14];
        strcpy(new_viagem->viagem.usuario.genero, str3);
    }

    return new_viagem;

}


void sortedInsert(nViagem** head, nViagem** new_viagem)// inserir na lista de forma ordenada
{
    nViagem* current;
    if(*head==NULL)// se não houver nenhum elemento da lista, a cabeça é o novo nó
    {
        (*new_viagem)->next = NULL;
        (*new_viagem)->prev=NULL;
        *head= *new_viagem;
    }

    else if ((*head)->viagem.tinicio.hora>= (*new_viagem)->viagem.tinicio.hora)//se o valor da hora da head for maior ou igual do que o do novo nó, inserir na cabeça
    {
        (*new_viagem)->next =*head;
        (*new_viagem)->prev=NULL;
        (*head)->prev=*new_viagem;
        (*head)=*new_viagem;
    }

    else
    {
        current=*head;
        while(current!=NULL&&(current->viagem.tinicio.hora < (*new_viagem)->viagem.tinicio.hora))// percorrer a lisra enquanto o next do nó atual tiver uma hora menor, de forma a inserir de forma ordenada
        {
            current=current->next;
        }
        (*new_viagem)->next=current;
        if(current!=NULL)
        {
        (*new_viagem)->prev=current->prev;
        current->prev->next=(*new_viagem);
        current->prev=(*new_viagem);
        }
    }
}

void removenode(nViagem* curr)  //função utilizada para remover um nó
{

    if(curr==NULL)
    return;
    if(curr->prev!=NULL)
    curr->prev->next=curr->next;
    if(curr->next!=NULL)
    curr->next->prev=curr->prev;
    free(curr);
}

void remove_criterio_duracao(nViagem **head)//remover de acordo com a duração
{
    nViagem *curr, *bloco_a_remover;
    curr=*head;
    int duracao1=0;
    printf("Insira uma duração máxima para as viagens:");
    scanf("%d", &duracao1);

    while(curr!=NULL)// percorrer a lista
    {
        if(curr->viagem.duracao>duracao1)// se a duração for maio do que a desejada o nó é removido
        {bloco_a_remover=curr;
            if(bloco_a_remover==*head)
            {
            *head=bloco_a_remover->next; // se o nó for a cabeça é necessário alterar o valor da mesma
            }
        curr=bloco_a_remover->next;
        removenode(bloco_a_remover);
        }

        else
        {
        curr=curr->next;

        }
    }
}

void remove_criterio_hora(nViagem **head)// remover nós da lista de acordo com a hora inicial e hora final definidas pelo utilizador
{
    nViagem *curr, *bloco_a_remover;
    curr=*head;
    int hora1=0, hora2=0;
    printf("Introduza uma hora de início para a viagem:");
    scanf("%d", &hora1);
    printf("Introduza uma hora de fim para a viagem:");
    scanf("%d", &hora2);
    while(curr!=NULL)
    {

     if(curr->viagem.tinicio.hora!=hora1||curr->viagem.tfinal.hora!=hora2)// se a hora final ou a hora inicial forem diferentes das pretendidas o nó é removido
     {
         bloco_a_remover=curr;
         if(bloco_a_remover==*head)
         {
             *head=bloco_a_remover->next;
         }
         curr=bloco_a_remover->next;
         removenode(bloco_a_remover);

     }
     else
     {
         curr=curr->next;
     }
    }

}


int weekday( nViagem* curr )//função que usa a função de zeller para determinar o dia da semana a partir  do dia ,mes e ano
{

    int ano= curr->viagem.dinicio.ano;
    int mes= curr->viagem.dinicio.mes;
    int dia= curr->viagem.dinicio.dia;
    int zmes=0;
    int zano=0;
    int wday=0;
    int f=0;//saves the result of zeller's function
    int last_two=0, first_two=0;

    if(mes==1||mes==2)
    {
        zmes=mes+10;  //zeller's month
        zano=ano-1;
    }
    else
    {
        zmes=mes-2;
        zano=ano;
    }

    last_two= zano%100;  // para anos com 4 digitos pode-se usar esta fórmula pois o resto da divisão dá os últimos 2 dígitos
    first_two= zano/100; // para anos com 4 digitos pode-se usar esta fórmula pois a divisão inteira dá os primeiros 2 dígitos

    f=(dia+((13*zmes-1)/5)+last_two+(last_two/4)+(first_two/4)-(2*first_two))%7;
    if(f>0)
    {
        wday=(7-f)%7;
        return wday;
    }
    else
    {
        f=(f%(-7))+7; //adjust f when it is negative
        wday=(7-wday)%7;
        return wday; //  para obter ajustado fazer (7-wday)%7
    }

}


void removeWday(nViagem **head)//remover o nó da lista de acordo com o dia da semana
{
    int wday=0;
    printf("Enter a weekday to remove:");
    scanf("%d",&wday);
    nViagem *curr=NULL;
    nViagem *bloco_a_remover;
    curr=*head;

    while(curr!=NULL)
    {

     if(weekday(curr)!=wday)// se
     {
         bloco_a_remover=curr;
         if(bloco_a_remover==*head)
         {
             *head=bloco_a_remover->next;
         }
         curr=bloco_a_remover->next;
         removenode(bloco_a_remover);

     }
     else
     {
         curr=curr->next;
     }
    }
}


void PrintTrip(nViagem *curr)// imprimir os dados de um nó lista
{
        printf("\nDuração:%ld",curr->viagem.duracao);
        printf("\nHora Inicial-%ld:%ld",curr->viagem.tinicio.hora, curr->viagem.tinicio.minuto);
        printf("\nHora Final-%ld:%ld", curr->viagem.tfinal.hora, curr->viagem.tfinal.minuto);
        printf("\nData Inicial-%ld/%ld/%ld",curr->viagem.dinicio.dia, curr->viagem.dinicio.mes, curr->viagem.dinicio.ano);
        printf("\nData Final-%ld/%ld/%ld", curr->viagem.dfinal.dia, curr->viagem.dfinal.mes, curr->viagem.dfinal.ano);
        printf("\nEstação Início:%ld", curr->viagem.inicio);
        printf("\nEstação Fim:%ld", curr->viagem.fim);
        printf("\nID Bicicleta:%s", curr->viagem.BikeID);
        printf("\nTipo Usuário:%s\n", curr->viagem.usuario.tipo);

        if(strcmp(curr->viagem.usuario.tipo, "Registered")==0)
        {
            printf("Ano de Nascimento Usuário:%ld\n ",curr->viagem.usuario.nascimento);
            printf("Género:%s\n ", curr->viagem.usuario.genero);
        }
}


void PrintTrips(nViagem *head)//imprimir toda a lista
{


    nViagem* curr;
    curr=NULL;
    curr=head;
    int count=0, user=0;

    printf("\n\nQuantas viagens pretende imprimir?\n\n");
    scanf("%d", &user);

    while(curr!=NULL)
    {
        if(count==user)
        break;  // se já se tiver chegado ao total de viagens que o utilizador pediu pára-se de imprimir
        PrintTrip(curr);
        curr=curr->next;
        count++;
        //if(curr->viagem.duracao>100000000)
        //break;
    }

    printf("Total trips:\n%d", count);
}


void ListagemRotas(nViagem *head)//Encontrar todas as rotas que saiam de uma dada estação e analisar a estações de chegada
{
    nViagem *curr;
    int i=0;
    int* rota=(int*)calloc(100, sizeof(int));//um vetor com todas as rotas, uma para cada estação final
    int count=0;
    int id1=0;//id da estação final

    printf("Choose the station id you want:\n");// escolher uma estação para analisar
    scanf("%d", &id1);

    if(head==NULL)
    {
        printf("No elements in list!");
        return;
    }

    curr=head;
    while(curr!=NULL)
    {   if(curr->viagem.inicio==id1)//guardar as viagens apenas se tiverem o id inicial  igual ao da estação indicada
        {PrintTrip(curr);
        rota[curr->viagem.fim]=rota[curr->viagem.fim]+1;}//incrementar o número de rotas para a estação destino
        curr=curr->next;
        count++;
    }


    for(i=0;i<=99;i++)
    {
        if(*(rota+i)!=0)//imprimir as viagens a partir do vetor das estações para a estação escolhida, mas apenas se não for 0,
        {
            printf("\n\nViagens entre a estação %d e a estação %d= %d",id1,i, rota[i]);
        }

    }

}



void StatsGenero(nViagem* head)//Imprimir as estatísticas de acordo com o género do utilizador
{
    nViagem* curr;
    curr=head;
    float total=0.0, male=0.0, female=0.0;
    float pmale=0.0, pfemale=0.0;
    while(curr!=NULL)
    {   if(strncmp(curr->viagem.usuario.tipo, "Registered",10)==0)
        {
        if(strncmp(curr->viagem.usuario.genero,"Female",6)==0)//se for mulher
        {
            female++;
            total++;
        }
        else//se for homem
        {
        male++;
        total++;
        }
        }
        curr=curr->next;

    }
    pmale=(float)((male/total)*100.0);// obter a percentagem de homens a partir do total e das viagens efetuadas pelos mesmos
    pfemale=(float)((female/total)*100.0);

    printf("percentage of women: %.1f\n", pfemale);
    printf("percentage of men:%.1f\n\n ", pmale);


}

void StatsIdade(nViagem *head)//obter os stats em função da idade
{

    nViagem* curr=NULL;
    int i=0;
    int idadeperson=0;
    int *idade;
    float *percentage;
    float total=0.0;
    float totalperc=0.00;
    idade=(int*)calloc(55, sizeof(int));//Idade máxima par o vetor 110 anos(55 intervalos de 2)
    percentage=(float*)calloc(55, sizeof(float));

    curr=head;

    while(curr!=NULL)
    {
        if(strncmp(curr->viagem.usuario.tipo, "Registered", 10)==0)// se o usuário estiver registado analisam-se os dados da sua idade
        {
        idadeperson=2017-(curr->viagem.usuario.nascimento);// obter a idaded do usuário
        *(idade+idadeperson/2)=*(idade+idadeperson/2)+1;//guardar a idade do usuário na posição do vetor correspondente à idade
        total++;
        }
        curr=curr->next;
    }

    for(i=0;i<=54;i++)
    {


        *(percentage+i)=(float)*(idade+i)/total*100;;//guardar no vetor das percentagens em função do total e da contagem no vetor correspondente da idade
    }


    i=0;
    do//imprimir
    {   i++;
        printf("Intervalo de idade %d-%d = %.2f %% \n", (i-1)*2,i*2,*(percentage+i-1)) ;
        totalperc=(float)totalperc+*(percentage+i-1);

    }while(i<=55);

    printf("%2.f",totalperc);

    free(idade);
    free(percentage);
}

void StatsDuracao(nViagem *head)//obter a duração
{
nViagem *curr=NULL;
curr=head;
int i;
int *total_dur;
float *percent_dur;
int total=0;
total_dur=(int*)calloc(24, sizeof(int));
percent_dur=(float*)calloc(24, sizeof(float));

while(curr!=NULL)
{
    if(curr->viagem.duracao<=21600)//se a viagem tiver 6 horas ou menos (21600 segundos) será analisada
    {
        *(total_dur+((curr->viagem.duracao)/900))=*(total_dur+((curr->viagem.duracao)/900))+1;//incrementar o total de viagens nesses 15 minutos(900 segundos)
        total++;
    }
curr=curr->next;

}

for(i=0;i<=23;i++)
{
   *(percent_dur+i)=(float)*(total_dur+i)/total*100;
}

for(i=1;i<=24;i++)
{
    printf("Intervalo %d m - %d m = %.2f %% \n", (i-1)*15,i*15,*(percent_dur+i-1));
}

free(total_dur);
free(percent_dur);


}

int checkGender(nViagem* curr)//função que devolve 1 se o género for masculino e 0 se for feminino
{
    if (strncmp(curr->viagem.usuario.genero, "Male", 4)==0)
    return 1;

    else return 0;
}

int intervaloAge(nViagem* curr)//função que devolve o intervalo de anos em que a idade do utilizador está contida(intervalos de 2 em 2 anos)
{
    int intervalo=0; //devolve o intervalo de idade em que a idade está contida
    intervalo=(2017-curr->viagem.usuario.nascimento)/2;

    return intervalo;
}




float velocidade(nViagem *curr, float distancia)
{
    float velocity=0.0;
    velocity=(float)distancia/(curr->viagem.duracao)*3600/1000;
    return velocity;
}

float deg2rad(float deg)  //função que converte de graus para radianos
 {
  return (float)(deg * pi / 180);
}

float distance(nViagem *curr, estacao* headstation)// esta função obtém a distância entre duas estações sabendo a latitude e longitude de cada uma
{
    float lat_init=0.0, lat_fim=0.0, long_init=0.0, long_fim=0.0;
    float variacao_lat=0.0, variacao_long=0.0;
    float distancia=0.0;
    estacao* station=headstation;
    float a=0.0, c=0.0;

    while(station!=NULL)// iterar pela lista de estações até encontrar a estação correspondente à viagem;
    {
        if(curr->viagem.inicio==station->id)
        {
            lat_init=deg2rad(station->latitude);
            long_init=deg2rad(station->longitude);//guardar a longitude de início correspondente à viagem
        }
        if(curr->viagem.fim==station->id)
        {
            long_fim=deg2rad(station->longitude);
            lat_fim=deg2rad(station->latitude);//guardar a latitude de fim correpondente à viagem

        }
    station=station->next;
    }

    //usar a fórmula definida pelo prof: joão ascenso para determinar a distância sabendo a latitude e a longitude
    variacao_lat=(float)lat_fim-lat_init;
    variacao_long=(float)long_fim-long_init;
    a=(float)sinf(variacao_lat/2)*sinf(variacao_lat/2)+cosf(lat_init)*cosf(lat_fim)*sinf(variacao_long/2)*sinf(variacao_long/2);
    c=2*atan2f(sqrtf(a), sqrtf(1.0-a));
    distancia=c*6371000;
    return distancia;

}



void StatsVelocidade(nViagem *head, estacao* headstation)// obter a velocidade média, para homens e mulheres, em intervalos de 2 anos
{
    nViagem *curr=NULL;
    float* homem=NULL;
    float* mulher=NULL;
    int* count_homem=NULL;
    int* count_mulher=NULL;
    int i=0;

    homem=(float*)calloc(55, sizeof(float));
    mulher=(float*)calloc(55, sizeof(float));
    count_homem=(int*)calloc(55, sizeof(int));
    count_mulher=(int*)calloc(55, sizeof(int));
    curr=head;


    while(curr!=NULL)
    {


        if(strncmp (curr->viagem.usuario.tipo,"Registered", 10)==0&&curr->viagem.duracao>0)// apenas se contabilizam nas estatísticas da velocidade os usuários registados
        {
            if(checkGender(curr)==1) //se for homem
            {
                    *(homem+intervaloAge(curr))=*(homem+intervaloAge(curr))+velocidade(curr, distance(curr, headstation));//guardar a velocidade no vetor de velocidades com intervalo de idade (dos homens) correspondente
                    *(count_homem+intervaloAge(curr))=*(count_homem+intervaloAge(curr))+1;
            }
            else // se for mulher
            {
                *(mulher+intervaloAge(curr))=*(mulher+intervaloAge(curr))+velocidade(curr, distance(curr, headstation));//guardar a velocidade  no vetor de velocidades com  intervalo de idade (das mulheres) correspondente
                *(count_mulher+intervaloAge(curr))=*(count_mulher+intervaloAge(curr))+1;
            }

        }

    curr=curr->next;
    }

    for(i=0; i<=54;i++)//obter a média das velocidades para o vetor dos homens e das mulheres(dividindo a soma das velocidades pelo total das velocidades)
    {
        *(homem+i)=(float)*(homem+i)/(*(count_homem+i));
        *(mulher+i)=(float)*(mulher+i)/(*(count_mulher+i));
    }

    printf("Média velocidades(km/h)\nIdade   Homem    Mulher\n");

    for(i=0; i<=54;i++)
    {
    if(*(count_mulher+i)>0&&*(count_homem+i)>0)//imprimir apenas se o total não for 0, para não incorrer em erros de +-infinito quando se faz adivisão pelo total para obter a média
    printf("%d-%d   %.1f      %.1f\n", (i-1)*2, i*2, *(homem+i), *(mulher+i));
    }

    printf("\n\n");

}

void DeleteList(nViagem **head)
{
    nViagem *curr, *temp;
    curr=*head;
    while(curr!=NULL)
    {
        temp=curr->next;
        free(curr);
        curr=temp;
    }
    *head=NULL;
}
