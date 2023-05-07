#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    unsigned int peso;
    int beneficio;
} type_item;

// funções e variáveis globais auxiliares
int maior_peso=0,maior_beneficio=0,tam_solucao_otima=0;
type_item * solucao_otima;

int encontra_max(int a, int b) {
    if ( a > b) return a;
    return b;
}

int compare(const void *a, const void *b) {
    type_item *itemA = (type_item *)a;
    type_item *itemB = (type_item *)b;
    double ratioA = (double)itemA->beneficio / (double)itemA->peso;
    double ratioB = (double)itemB->beneficio / (double)itemB->peso;
    if (ratioA > ratioB)
        return -1;
    else if (ratioA < ratioB)
        return 1;
    else
        return 0;
}

// algoritmos de resolução
type_item *programacao_dinamica(int n_items, int capacidad, type_item *items, int *tam_arr) {
    int i, j;
    
    int **tabela = malloc(sizeof(int*) * (n_items + 1));
    for (i = 0; i <= n_items; i++) {
        tabela[i] = malloc(sizeof(int) * (capacidad + 1));
    }

    for (i = 0; i <= n_items; i++) {
        for (j = 0; j <= capacidad; j++) {
            if (i == 0 || j == 0)
                tabela[i][j] = 0;
            else if (items[i - 1].peso <= j)
                tabela[i][j] = encontra_max(items[i - 1].beneficio + tabela[i - 1][j - items[i - 1].peso], tabela[i - 1][j]);
            else
                tabela[i][j] = tabela[i - 1][j];
        }
    }

    int beneficio_max = tabela[n_items][capacidad];

    int x = 0;
    int max_items = n_items;
    type_item temp;
    type_item *items_escolhidos = malloc(sizeof(type_item) * n_items);

    while (n_items != 0) {
		if (tabela[n_items][capacidad] != tabela[n_items - 1][capacidad]) {
            temp.peso = items[n_items - 1].peso;
            temp.beneficio = items[n_items - 1].beneficio;

			items_escolhidos[x++] = temp;
            if (x == max_items) {
                max_items *= 2;
                items_escolhidos = realloc(items_escolhidos, sizeof(type_item) * max_items);
            }

			capacidad = capacidad - items[n_items - 1].peso;
		}
		
		n_items--;
	}

    *tam_arr = x;
 
    return items_escolhidos;
}

void forca_bruta(type_item *item, int num_items, int capacidad) { 
    /*percorre todos os elementos do vetor de itens e chama a função 
    permutação para cada um deles gerando todas as combinações possíveis*/
   for(int i=0;i<num_items;i++){
        type_item * elemento_unico = (type_item *)malloc(sizeof(type_item));
        elemento_unico[0] = item[i];
        permutacao(item,elemento_unico,1,num_items,capacidad); 
   }
}

type_item * add(type_item *item,int num_combinacoes, type_item number){
    //adiciona o item ao vetor de combinações
    type_item *new_item = (type_item *)malloc((num_combinacoes+1) * sizeof(type_item));
    for(int i=0;i<num_combinacoes;i++){
        new_item[i] = item[i];
    }
    new_item[num_combinacoes] = number;
    return new_item;
}

void permutacao(type_item *item, type_item *combinacoes,int tam_combinacoes, int num_items,int capacidad){
    //termina a recursão quando o tamanho das combinações for maior que o numero de itens
    if(tam_combinacoes>num_items){
        return;
    }
    //verifica a soma o peso e o beneficio da combinação atual
    float beneficio = 0, peso = 0;
    for(int i=0;i<tam_combinacoes;i++){
        beneficio+=combinacoes[i].beneficio;
        peso+=combinacoes[i].peso;
    }
    printf("Peso: %f, Beneficio: %f\n",peso,beneficio);
    //verifica se a combinação atual é melhor que a solução ótima
    if(peso<=capacidad && beneficio>=maior_beneficio){
        maior_peso = peso;
        maior_beneficio = beneficio;
        tam_solucao_otima = tam_combinacoes;
        solucao_otima = combinacoes;
    }
    //percorre todos os itens
    for(int i=0;i<num_items;i++){
        bool contem = false;
        //verifica se o item atual já está na combinação atual
        for(int j=0;j<tam_combinacoes;j++){
            if(item[i].peso == combinacoes[j].peso && item[i].beneficio == combinacoes[j].beneficio){
                contem = true;
            }
        }
        if(!contem){
            //chama a função permutação para cada item que não está na combinação atual
            permutacao(item,add(combinacoes,tam_combinacoes,item[i]),tam_combinacoes+1,num_items,capacidad);
        }
        contem = false;
    }
}

void guloso(type_item *item, int num_items, int capacidad) { 
    qsort(item, num_items, sizeof(type_item), compare); // ordena os itens
    type_item *solucao = malloc(num_items * sizeof(type_item));
    type_item *melhor_solu = malloc(num_items * sizeof(type_item));
    int armz_peso = 0;
    int soma_bene = 0;
    int aux_bene = -1;
    int b = 0; // guarda a quantidade de itens no vetor solucao
    int a =0;
    for(int i = 0; i < num_items; i++){
    for(int j = 0; j < num_items; j++){
        if (j != i && armz_peso + item[j].peso <= capacidad){
            armz_peso += item[j].peso;
            soma_bene += item[j].beneficio;
            solucao[b++] = item[j];
        }
    } 
    printf("%d\n" , soma_bene);
    if(soma_bene > 0){
        for(int k = 0; k < b; k++){
            printf("Solução: peso: %d, beneficio: %d \n", solucao[k].peso, solucao[k].beneficio);
            if(aux_bene <= soma_bene){
                melhor_solu[k].peso = solucao[k].peso;
                melhor_solu[k].beneficio = solucao[k].beneficio;
                aux_bene = soma_bene;
                a = b;
            }
        }  
    }
    armz_peso = 0;
    soma_bene = 0;
    b = 0;
  }
  int max= 0;
  int max2 = 0;
   for(int k = 0; k < a; k++){
            printf("Solução final: peso: %d, beneficio: %d \n", melhor_solu[k].peso, melhor_solu[k].beneficio);
            max  += melhor_solu[k].beneficio ;
            max2  += melhor_solu[k].peso ;
   }
   printf("\n%d", max);
   printf("\n%d", max2);
}

// funções originais do código base
void imprimir_items(type_item *items, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}

type_item *ler_items(char *filename, int *n_items, int *capacidad) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }

    fscanf(fp, "%d %d", n_items, capacidad);
    printf("Número de elementos: %d, Capacidade: %d\n", *n_items, *capacidad);

    type_item *items = (type_item *)malloc(*n_items * sizeof(type_item));

    for (int i = 0; i < *n_items; i++) {
        fscanf(fp, "%d %d", &items[i].peso, &items[i].beneficio);
    }

    fclose(fp);

    return items;
}


int main(int argc, char *argv[]) {
    int n_items, capacidad;

    if (argc != 2) {
        printf("Uso: %s <nome do arquivo de entrada>\n", argv[0]);
        return 1;
    }

    type_item *items = ler_items(argv[1], &n_items, &capacidad);
    imprimir_items(items, n_items);

    int tam_arr;
    int beneficio_max_prog_dinam = 0;
    int peso_max_prog_dinam = 0;
    printf("\t\tExecutando o algoritmo...\n");

    clock_t inicio_t, fim_t;
    double total_t_prog_dinam, total_t_forca_bruta, total_t_guloso;

    // programação dinâmica
    inicio_t = clock();
    type_item *items_escolhidos = programacao_dinamica(n_items, capacidad, items, &tam_arr);  // chama o algoritmo
    fim_t = clock();
    total_t_prog_dinam = (double)(fim_t - inicio_t) / (CLOCKS_PER_SEC / 1000);

    for (int i = 0; i < tam_arr; i++) {
        beneficio_max_prog_dinam += items_escolhidos[i].beneficio;
        peso_max_prog_dinam += items_escolhidos[i].peso;
    }

    // força bruta
    // inicio_t = clock();
    // forca_bruta(items, n_items, capacidad);
    // fim_t = clock();
    // total_t_forca_bruta = (double)(fim_t - inicio_t) / (CLOCKS_PER_SEC/1000);

    // guloso
    // inicio_t = clock();
    // guloso(items, n_items, capacidad);
    // fim_t = clock();
    // total_t_guloso = (double)(fim_t - inicio_t) / (CLOCKS_PER_SEC/1000);

    printf("\t\t\tPRONTO!\n\nBENEFICIO E PESO MAXIMO PROGRAMACAO DINAMICA: %d | %d\n", beneficio_max_prog_dinam, peso_max_prog_dinam);
    //printf("Tempo total forca bruta: %.0lf milisegundos\n", total_t_forca_bruta);
    printf("Tempo total programacao dinamica: %.0lf milisegundos\n", total_t_prog_dinam);
    printf("Tempo total algoritmo guloso: %.0lf milisegundos\n", total_t_guloso);

    free(items_escolhidos);
    free(items);
    return 0;
}