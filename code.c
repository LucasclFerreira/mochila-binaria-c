#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    unsigned int peso;
    int beneficio;
} type_item;

int encontra_max(int a, int b) {
    if ( a > b) return a;
    return b;
}

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

type_item *forca_bruta(type_item *items, int n_items, int capacidad) {
    int i, j, beneficio_max = 0, peso_max = 0;
    int escolhas = 0;
    int num_items_escolhidos = 0;
    type_item *items_escolhidos = malloc(n_items * sizeof(type_item));

    for (i = 0; i < (1 << n_items); i++) {
        int peso_atual = 0, beneficio_atual = 0;

        for (j = 0; j < n_items; j++) {
            if (i & (1 << j)) {
                peso_atual += items[j].peso;
                beneficio_atual += items[j].beneficio;
            }
        }

        if (peso_atual <= capacidad && beneficio_atual > beneficio_max) {
            beneficio_max = beneficio_atual;
            peso_max = peso_atual;
            escolhas = i;
            num_items_escolhidos = 0;

            for (j = 0; j < n_items; j++) {
                if (i & (1 << j)) {
                    items_escolhidos[num_items_escolhidos++] = items[j];
                }
            }
        }
    }

    printf("Items escolhidos por forca bruta: ");
    for (i = 0; i < n_items; i++) {
        if (escolhas & (1 << i)) {
            printf("Item %d; ", i + 1);
        }
    }
    printf("\nPeso total: %d\nBeneficio total: %d\n", peso_max, beneficio_max);

    printf("Total de items escolhidos =  %d\n", num_items_escolhidos);
    //items_escolhidos = realloc(items_escolhidos, num_items_escolhidos * sizeof(type_item));

    return items_escolhidos;
}

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

    clock_t inicio_t, fim_t;
    double total_t_prog_dinam, total_t_forca_bruta;

    if (argc != 2) {
        printf("Uso: %s <nome do arquivo de entrada>\n", argv[0]);
        return 1;
    }

    type_item *items = ler_items(argv[1], &n_items, &capacidad);
    imprimir_items(items, n_items);

    int tam_arr;
    //int beneficio_max_alg1 = algoritmo_1(n_items, capacidad, items);
    int beneficio_max_prog_dinam = 0, beneficio_max_forca_bruta = 0;
    int peso_max_prog_dinam = 0, peso_max_forca_bruta = 0;
    printf("\t\tExecutando o algoritmo...\n");

    // algoritmo de programação dinâmica
    inicio_t = clock();
    type_item *items_escolhidos = programacao_dinamica(n_items, capacidad, items, &tam_arr);
    fim_t = clock();
    total_t_prog_dinam = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    for (int i = 0; i < tam_arr; i++) {
        beneficio_max_prog_dinam += items_escolhidos[i].beneficio;
        peso_max_prog_dinam += items_escolhidos[i].peso;
    }

    // algoritmo de força bruta
    inicio_t = clock();
    type_item *escolhas = forca_bruta(items, n_items, capacidad);
    fim_t = clock();
    total_t_forca_bruta = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;  // tempo em milisegundos
    int aux = sizeof(escolhas) /sizeof(escolhas[0]);
    for (int i = 0; i < aux; i++) {
        beneficio_max_forca_bruta += escolhas[i].beneficio;
        peso_max_forca_bruta += escolhas[i].peso;
    }

    //printf("\t\t\tPRONTO!\n\nBENEFICIO E PESO MAXIMO PROGRAMACAO DINAMICA: %d | %d\n", beneficio_max_prog_dinam, peso_max_prog_dinam);
    //printf("BENEFICIO E PESO MAXIMO FORCA BRUTA: %d | %d\n", beneficio_max_forca_bruta, peso_max_forca_bruta);
    printf("Tempo total programacao dinamica: %lf segundos", total_t_prog_dinam);
    printf("Tempo total forca bruta: %lf segundos", total_t_forca_bruta);

    free(items_escolhidos);
    free(escolhas);
    free(items);
    return 0;
}