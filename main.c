#include <stdio.h>
#include <stdlib.h>

// Importando as structs e definições globais
#include "include/tipos.h"

// Importando os módulos do sistema (caminho relativo a partir da raiz)
#include "src/utils.h"
#include "src/cliente.h"
#include "src/veiculo.h"
#include "src/venda.h"

int main() {
    // Exemplo de inicialização ou menu do sistema
    printf("--- SISTEMA DE CONCESSIONÁRIA / LOCADORA ---\n\n");

    // 1. Aqui você pode chamar funções utilitárias ou carregar dados
    // Exemplo: inicializarBancoDados();

    int opcao = 0;
    do {
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Veículos\n");
        printf("3. Realizar Venda\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // Função que deve estar declarada em cliente.h e implementada em cliente.c
                // menuClientes(); 
                break;
            case 2:
                // Função que deve estar declarada em veiculo.h e implementada em veiculo.c
                // menuVeiculos();
                break;
            case 3:
                // Função que deve estar declarada em venda.h e implementada em venda.c
                // menuVendas();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        printf("\n");
    } while(opcao != 0);

    return 0;
}
