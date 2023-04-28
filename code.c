#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int peso;
    int beneficio;
} type_item;

int encontra_max(int a, int b) {
    if ( a > b) return a;
    return b;
}

int algoritmo_1(int n_items, int capacidad, type_item *items) {
    // força BRUTAL
    if (n_items == 0 || capacidad == 0)
        return 0;

    if (items[n_items - 1].peso > capacidad)
        return algoritmo_1(n_items - 1, capacidad, items);
    else
        return encontra_max(items[n_items - 1].beneficio + algoritmo_1(n_items - 1, capacidad - items[n_items - 1].peso, items), algoritmo_1(n_items - 1, capacidad, items));

}

type_item *algoritmo_2(int n_items, int capacidad, type_item *items, int *tam_arr) {
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
			//printf("\tItem %d com PESO = %d e BENEFICIO %d\n", n_items, items[n_items - 1].peso, items[n_items - 1].beneficio);
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

void algoritmo_3(int n_items, int capacidad, type_item *items) {}

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
    //int beneficio_max_alg1 = algoritmo_1(n_items, capacidad, items);
    int beneficio_max_alg2 = 0;
    printf("\t\tExecutando o algoritmo...\n");
    type_item *items_escolhidos = algoritmo_2(n_items, capacidad, items, &tam_arr);

    for (int i = 0; i < tam_arr; i++) {
        printf("\tItem %d -- PESO = %d e BENEFICIO %d\n", i, items_escolhidos[i].peso, items_escolhidos[i].beneficio);
        beneficio_max_alg2 += items_escolhidos[i].beneficio;
    }

    //printf("\nBENEFICIO MAXIMO ALG1: %d\n", beneficio_max_alg1);
    printf("\t\t\tPRONTO!\n\nBENEFICIO MAXIMO ALG2: %d\n", beneficio_max_alg2);

    free(items_escolhidos);
    free(items);
    return 0;
}