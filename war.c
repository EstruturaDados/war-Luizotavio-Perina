#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio* territorios, int qtd) {
    for (int i = 0; i < qtd; i++) { 
        printf("\nCadastro do Territorio %d\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

void exibirTerritorios(struct Territorio* territorios, int qtd) {
    printf("\nLISTA DE TERRITORIOS\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] Territorio: %s\n", i + 1, territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\nINICIANDO BATALHA\n");
    printf("%s (%s, %d tropas) ataca %s (%s, %d tropas)\n", 
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nVitoria do atacante!\n");
        printf("Territorio %s foi conquistado por %s\n", defensor->nome, atacante->cor);
        
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
    } else if (dadoAtacante < dadoDefensor) {
        printf("\nVitoria do defensor!\n");
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    } else {
        printf("\nEmpate!\n");
    }
}

void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main(void) {
    srand(time(NULL));
    int qtdTerritorios;
    
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtdTerritorios);

    struct Territorio* territorios = (struct Territorio*)calloc(qtdTerritorios, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    cadastrarTerritorios(territorios, qtdTerritorios);
    exibirTerritorios(territorios, qtdTerritorios);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int indiceAtacante, indiceDefensor;
        
        printf("\nDigite o numero do territorio atacante (1-%d): ", qtdTerritorios);
        scanf("%d", &indiceAtacante);
        indiceAtacante--;

        printf("Digite o numero do territorio defensor (1-%d): ", qtdTerritorios);
        scanf("%d", &indiceDefensor);
        indiceDefensor--;

        if (indiceAtacante < 0 || indiceAtacante >= qtdTerritorios || 
            indiceDefensor < 0 || indiceDefensor >= qtdTerritorios) {
            printf("\nIndices invalidos\n");
            continue;
        }

        if (indiceAtacante == indiceDefensor) {
            printf("\nUm territorio nao pode atacar a si mesmo\n");
            continue;
        }

        if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
            printf("\nNao e possivel atacar um territorio da mesma cor\n");
            continue;
        }

        if (territorios[indiceAtacante].tropas < 2) {
            printf("\nO atacante precisa de pelo menos 2 tropas\n");
            continue;
        }

        atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);

        printf("\nSituacao pos-batalha:\n");
        printf("[%d] %s | Cor: %s | Tropas: %d\n", 
               indiceAtacante + 1, 
               territorios[indiceAtacante].nome,
               territorios[indiceAtacante].cor,
               territorios[indiceAtacante].tropas);
        printf("[%d] %s | Cor: %s | Tropas: %d\n", 
               indiceDefensor + 1,
               territorios[indiceDefensor].nome,
               territorios[indiceDefensor].cor,
               territorios[indiceDefensor].tropas);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    printf("\nESTADO FINAL\n");
    exibirTerritorios(territorios, qtdTerritorios);

    liberarMemoria(territorios);

    return 0;
}