/*PROJETO 1 IAED
Manuel Albino
tp99102*/

#include<stdio.h>
#include<string.h>

#define MAX_DESC 101
#define MAX_USER_ATI 101
#define MAX_TAREFA 10000
#define MAX_UTILIZADORES 50
#define MAX_ATIVIDADE 10
#define key(A) (A)
#define less(A,B) (key(A) < key(B))


/*INICIALIZACAO DE VARIAVEIS GLOBAIS*/

int tempo=0,identificador=0,num_user=0,num_atividades=3;
char VET_atividades[MAX_ATIVIDADE][MAX_USER_ATI];
char inicio_atividade[MAX_USER_ATI]="TO DO";
char meio_atividade[MAX_USER_ATI]="IN PROGRESS";
char fim_atividade[MAX_USER_ATI]="DONE";

/*Vetor de strings que guarda os utilizadores*/
char users[MAX_UTILIZADORES][MAX_USER_ATI];

/*Vetor de strings que guarda as descricoes*/
char guarda_descricao[MAX_TAREFA][MAX_DESC];

/*Definicao da estrutura principal*/
typedef struct {
	int iden;
	char descricao[MAX_DESC];
	char utilizador[MAX_USER_ATI];
	char atividade[MAX_USER_ATI];
	int duracao;
	int comeco;
	int PASSOU_INPROGRESS;
} Tarefa;

/*Estrutura ordena em ambos os algoritmos*/
Tarefa ordena_struct[MAX_TAREFA];


/*Estrutura principal do projeto*/
Tarefa VET_tarefa[MAX_TAREFA];


/*Funcao auxiliar que ajuda a ordenar as descricoes por ordem alfabetica*/
void merge_desc(Tarefa a[], int l, int m, int r){
	/*Estrutura que auxilia no ordenamento por ordem alfabetica*/
	Tarefa aux[MAX_TAREFA];
 	int i, j, k;
 	for (i = m+1; i > l; i--)
 		aux[i-1]= a[i-1];
 	for (j = m; j < r; j++)
 		aux[r+m-j]= a[j+1];
 	for (k = l; k <= r; k++){
 		if (strcmp(aux[j].descricao, aux[i].descricao)<0)
 			a[k] = aux[j--];
 		else
 			a[k]= aux[i++];
 	}
}


/*Funcao recursiva que ordena as descricoes por ordem alfabetica*/
void mergesort_desc(Tarefa a[], int l, int r) {
 	int m = (r+l)/2;
 	if (r <= l)
 		return;
 	mergesort_desc(a, l, m);
 	mergesort_desc(a, m+1, r);
 	merge_desc(a, l, m, r);
}


/*Algoritmo de ordenacao que ordena o comando d por ordem crescente de comeco*/
void insertion_ord_comeco(Tarefa a[MAX_TAREFA], int l, int r){
	int i,j;
 	for (i = l+1; i <= r; i++) {
		Tarefa v = a[i];
		j = i-1;
		while ( j>=l && less(v.comeco, a[j].comeco)) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = v;
	}
}


/*Funcao auxiliar que retorna 1 se tiver letras minusculas na string e 0 se nao*/
int minusculas(char atividade[MAX_USER_ATI]){
	int i,tamanho=strlen(atividade);
	for (i=0;i<tamanho;i++){
		if (atividade[i]>='a' && atividade[i]<='z'){
			return 1;
		}
	}
	return 0;
}

/*Funcao auxiliar de erros para atividades e utilizadores\
 que retorna 1 se o argumento b for igual a algum indice do vetor a e 0 se nao*/
int erros_user_ati(char a[][MAX_USER_ATI],int contador,char b[MAX_USER_ATI]){
	int i;
	for (i=0;i<contador;i++){
		if (strcmp(a[i],b)==0){  
			return 1;
		}
	}
	return 0;
}

/*Funcao auxiliar de erros para descricoes\
 que retorna 1 se o argumento b for igual a algum indice do vetor a e 0 se nao*/
int erros_desc(char a[][MAX_DESC],int contador,char b[MAX_DESC]){
	int i;
	for (i=0;i<contador;i++){
		if (strcmp(a[i],b)==0){  
			return 1;
		}
	}
	return 0;
}

/*Funcao do comando t que recebe um inteiro correspondente a duracao prevista\
e uma string correspondente a descricao da tarefa e devolve o numero da tarefa criada*/
void t() {
	int d;
	char task[MAX_DESC];

	scanf(" %d %50[^\n]",&d,task);

	if(identificador+1>MAX_TAREFA) 
		printf("too many tasks\n"); 

	else if(erros_desc(guarda_descricao,identificador,task)) /*Se houver uma descricao igual já guardada no Vetor \*/
		printf("duplicate description\n");						/*de descricoes imprime um erro*/

	else if (d<=0)                        
		printf("invalid duration\n");

	else{
		VET_tarefa[identificador].iden=identificador+1;   /*Guarda o identificador+1 de forma a facilitar acessar aos indices*/
		strcpy(VET_tarefa[identificador].atividade,inicio_atividade);  
		strcpy(guarda_descricao[identificador],task);     /*Guarda a descricao no Vetor de descricoes*/
		strcpy(VET_tarefa[identificador].descricao,task);  /*Guarda a descricao na estrutura*/
		VET_tarefa[identificador].duracao=d;               
		VET_tarefa[identificador].comeco=0;
		printf("task %d\n",VET_tarefa[identificador].iden);
		identificador++;                                
	}
}


/*Funcao do comando l que recebe, ou os ids das tarefa ou nada, e devolve a informacao de cada tarefa ou a informacao de todas/
por ordem alfabetica */
void l() {
	int j,i,k;
	char c;
	c=getchar();
	if (c==' '){                       /*Se tiver um espaco depois do l, entra no while e le o numero de inteiros que tiver imprimindo-os*/
		while (scanf(" %d",&j))
			if (j>=identificador+1 || j<=0) 
				printf("%d: no such task\n",j);
			else 
				printf("%d %s #%d %s\n",VET_tarefa[j-1].iden,VET_tarefa[j-1].atividade\
					,VET_tarefa[j-1].duracao,VET_tarefa[j-1].descricao);
	}
	else{ 						/*Caso nao tenha corre o algoritmo e imprime por ordem alfabetica*/
		for (i=0;i<identificador;i++)			 
			ordena_struct[i]=VET_tarefa[i];         
		mergesort_desc(ordena_struct,0,identificador-1);
		for (k=0;k<identificador;k++){
			printf("%d %s #%d %s\n",ordena_struct[k].iden,ordena_struct[k].atividade,\
				ordena_struct[k].duracao,ordena_struct[k].descricao);
    	}
	}
}


/*Funcao do comando n que recebe um inteiro decimal nao negativo e devolve\
o tempo que tinhamos mais o tempo que inserimos*/
void n() {
	int valor;
	char termo;
	if(scanf("%d%c", &valor, &termo) != 2 || termo != '\n' || valor<0){ /*Se tiver um caracter a seguir ao numero*/
		printf("invalid time\n");										/*que nao seja um "\n" da erro para verificar se so e inteiro*/
	}
	else {
		tempo=tempo+valor;
		printf("%d\n",tempo);
	}
}


/*Funcao do comando u que recebe uma string ou nada e guarda a string no\
vetor de utilizadores ou caso nao seja dado nenhum argumento imprime todos os utilizadores*/
void u(){
	int i;
	char c,username[MAX_USER_ATI];
	c=getchar();
	if (c==' '){    /*Se tiver um espaco le o utilizador, verifica os erros e adiciona ao vetor*/
		scanf("%20s",username);
		if (erros_user_ati(users,num_user,username)) /*Verifica o erro de utilizador ja existente a partir*/
			printf("user already exists\n");			/*da funcao auxiliar*/

		else if (num_user+1>MAX_UTILIZADORES) 
			printf("too many users\n");

		else{
			strcpy(users[num_user],username);
			num_user++;
		}
	}
	else{    /*Se nao imprime todos os utilizadores do vetor*/
		for(i=0;i<num_user;i++) printf("%s\n",users[i]);
	}
}


/*Funcao do comando m que recebe o identificador da tarefa, o utilizador e a \
atividade para a qual a queremos mudar*/
void m(){
	int id,duration,slack;
	char username[MAX_USER_ATI],atividade[MAX_USER_ATI];
	scanf("%d %20s %20[^\n]",&id,username,atividade);
	if (id>identificador || id<=0) 
		printf("no such task\n");
														/*Se quisermos passar uma atividade que ja nao esta no TO DO*/
	else if (strcmp(atividade,inicio_atividade)==0 && \
	VET_tarefa[id-1].PASSOU_INPROGRESS==1)				/*para TO DO imprime um erro*/
		printf("task already started\n");	

	else if (erros_user_ati(users,num_user,username)==0)
		printf("no such user\n");

	else if(erros_user_ati(VET_atividades,num_atividades,atividade)==0)
		printf("no such activity\n");

	else{  						/*Se nenhum erro for verificado copia a atividade para a tarefa*/
		strcpy(VET_tarefa[id-1].atividade,atividade);
		if (VET_tarefa[id-1].PASSOU_INPROGRESS==0){ /*Verifica se ja passou do TO DO para outra atividade,*/
			VET_tarefa[id-1].comeco=tempo;			/*se ja nao atualiza o comeco do tempo e se nao atualiza para o tempo atual*/
			VET_tarefa[id-1].PASSOU_INPROGRESS=1;
		}

		if (strcmp(atividade,fim_atividade)==0){
			duration=tempo-VET_tarefa[id-1].comeco;
			slack=duration-VET_tarefa[id-1].duracao;
			printf("duration=%d slack=%d\n",duration,slack);
		}
	}
}

/*Funcao do comando d que recebe uma atividade e devolve a informacao das tarefas\
que estao nessa atividade por ordem crescente de comeco e em caso de igualdade por ordem crescente*/
void d(){
	int i,j;
	char atividade[MAX_USER_ATI];

	scanf(" %20[^\n]",atividade);
	
	if (erros_user_ati(VET_atividades,num_atividades,atividade)==0) 
		printf("no such activity\n");

	else{
		for (i=0;i<identificador;i++)                /*Coloca as tarefas na estrutura auxiliar para depois*/
			ordena_struct[i]=VET_tarefa[i]; 		/*ordenar a estrutura auxiliar e imprimir a partir dessa*/
		mergesort_desc(ordena_struct,0,identificador-1);
		insertion_ord_comeco(ordena_struct,0,identificador-1);
		for (j=0;j<identificador;j++){
			if (strcmp(ordena_struct[j].atividade,atividade)==0){  /*So imprime as que tiverem a atividade recebida*/
				printf("%d %d %s\n",ordena_struct[j].iden,ordena_struct[j].comeco,\
					ordena_struct[j].descricao);
			}
		}
	}
}

/*Funcao do comando a que recebe ou uma atividade e coloca-a no vetor das atividades\
ou nao recebe nada e imprime todas as atividades existentes*/
void a(){
	int j;
	char c,atividade[MAX_USER_ATI]={0};
	c=getchar();
	if (c==' '){    /*Se tiver espaco le a atividade e se for esse o caso adiciona-a ao vetor*/
		scanf(" %20[^\n]",atividade);

		if (erros_user_ati(VET_atividades,num_atividades,atividade)) 
			printf("duplicate activity\n");

		else if (minusculas(atividade))
			printf("invalid description\n");

		else if (num_atividades+1>MAX_ATIVIDADE)
			printf("too many activities\n");

		else{
			strcpy(VET_atividades[num_atividades],atividade); /*Copia a atividade para o vetor depois de verificar*/
			num_atividades++;									/*todos os erros*/
		}
	}
	else{ /*Caso nao tenha espaco imprime todas as atividades do vetor*/
		for (j=0;j<num_atividades;j++) 
			printf("%s\n",VET_atividades[j]);
	}
}




void g(){
	char nome_grupo[MAX_USER_ATI];
	char username[MAX_USER_ATI];
	char grupo[10][MAX_USER_ATI];
	int cont_grupos=0;
	scanf(" %100s",nome_grupo);
	if (erros_user_ati(users,num_user,nome_grupo))
		printf("user already exists\n");
	else if (num_user+1>MAX_UTILIZADORES) 
		printf("too many users\n");
	else{
		while(scanf(" %100s",username)){
			if (!erros_user_ati(users,num_user,username))
				printf("no such user\n");
			else if(erros_user_ati(grupo,cont_grupos,username))
				printf("repeated user\n");
			else{
				strcpy(grupo[cont_grupos],username);
				cont_grupos++;

			}
		}
		if (cont_grupos>0){
			strcpy(users[num_user+1],nome_grupo);
			num_user++;
		}
	}
}


int main(){
	char command=getchar(); 
	/*Inicializa o vetor das atividades ja com as 3 atividades iniciais*/
	strcpy(VET_atividades[0],inicio_atividade);
	strcpy(VET_atividades[1],meio_atividade);
	strcpy(VET_atividades[2],fim_atividade);
	
	while (command!='q'){
		switch (command){
			case 't': 
				t();
				break;
			case 'l':
				l();
				break;
			case 'n':
				n();
				break;
			case 'u':
				u();
				break;
			case 'm':
				m();
				break;
			case 'd':
				d();
				break;
			case 'a':
				a();
				break;
			case 'g':
				g();
			default :
				break;
		}
		command=getchar();
	}
	return 0;
}