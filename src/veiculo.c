#include <stdio.h>
#include <string.h>
#include "../include/tipos.h"
#include "utils.h"
#include "veiculo.h"

/* ============================================================
 *  MODULO 2 - Cadastro de Veiculos
 * ============================================================ */

void cadastrar_veiculo(void) {
    separador();
    printf("  CADASTRO DE VEICULO\n");
    separador();

    if (total_veiculos >= MAX_VEICULOS) {
        printf("  [!] Limite de veiculos atingido.\n");
        pausar();
        return;
    }

    Veiculo v;
    memset(&v, 0, sizeof(v));
    v.id_veiculo = proximo_id_veiculo;
    strcpy(v.status, "disponivel");

    do {
        ler_string("  Tipo (carro/moto): ", v.tipo, sizeof(v.tipo));
        para_minusculo(v.tipo);
        if (strcmp(v.tipo, "carro") != 0 && strcmp(v.tipo, "moto") != 0)
            printf("  [!] Tipo deve ser 'carro' ou 'moto'.\n");
        else break;
    } while (1);

    do {
        ler_string("  Marca        : ", v.marca, sizeof(v.marca));
        if (strlen(v.marca) == 0) printf("  [!] Marca e obrigatoria.\n");
        else break;
    } while (1);

    do {
        ler_string("  Modelo       : ", v.modelo, sizeof(v.modelo));
        if (strlen(v.modelo) == 0) printf("  [!] Modelo e obrigatorio.\n");
        else break;
    } while (1);

    int ano_max = ano_atual();
    do {
        v.ano = ler_inteiro("  Ano          : ");
        if (v.ano <= 1900 || v.ano > ano_max)
            printf("  [!] Ano deve ser entre 1901 e %d.\n", ano_max);
        else break;
    } while (1);

    do {
        v.preco = ler_double("  Preco (R$)   : ");
        if (v.preco <= 0) printf("  [!] Preco deve ser maior que zero.\n");
        else break;
    } while (1);

    do {
        v.quilometragem = ler_inteiro("  Quilometragem: ");
        if (v.quilometragem < 0) printf("  [!] Quilometragem nao pode ser negativa.\n");
        else break;
    } while (1);

    veiculos[total_veiculos++] = v;
    proximo_id_veiculo++;

    printf("\n  [OK] Veiculo '%s %s' cadastrado com ID #%d e status 'disponivel'.\n",
           v.marca, v.modelo, v.id_veiculo);
    pausar();
}

void listar_veiculos(const char *filtro_status) {
    separador();
    if (filtro_status)
        printf("  VEICULOS - Status: %s\n", filtro_status);
    else
        printf("  TODOS OS VEICULOS\n");
    separador();
    printf("  %-4s  %-6s  %-15s  %-15s  %-4s  %12s  %-8s  %-12s\n",
           "ID", "Tipo", "Marca", "Modelo", "Ano", "Preco(R$)", "KM", "Status");
    printf("  %-4s  %-6s  %-15s  %-15s  %-4s  %12s  %-8s  %-12s\n",
           "----", "------", "---------------", "---------------",
           "----", "------------", "--------", "------------");

    int encontrou = 0;
    for (int i = 0; i < total_veiculos; i++) {
        if (filtro_status && strcmp(veiculos[i].status, filtro_status) != 0) continue;
        printf("  %-4d  %-6s  %-15s  %-15s  %-4d  %12.2f  %-8d  %-12s\n",
               veiculos[i].id_veiculo,
               veiculos[i].tipo,
               veiculos[i].marca,
               veiculos[i].modelo,
               veiculos[i].ano,
               veiculos[i].preco,
               veiculos[i].quilometragem,
               veiculos[i].status);
        encontrou = 1;
    }
    if (!encontrou) printf("  Nenhum veiculo encontrado.\n");
    pausar();
}

void atualizar_status_veiculo(void) {
    separador();
    printf("  ATUALIZAR STATUS DE VEICULO\n");
    separador();

    int id  = ler_inteiro("  ID do veiculo: ");
    int idx = buscar_veiculo_por_id(id);
    if (idx < 0) {
        printf("  [!] Veiculo nao encontrado.\n");
        pausar();
        return;
    }

    Veiculo *v = &veiculos[idx];
    printf("  Status atual: %s\n", v->status);

    if (strcmp(v->status, "vendido") == 0) {
        printf("  [!] Veiculo vendido nao pode ter status alterado.\n");
        pausar();
        return;
    }

    char novo[20];
    do {
        ler_string("  Novo status (disponivel/reservado): ", novo, sizeof(novo));
        para_minusculo(novo);
        if (strcmp(novo, "disponivel") != 0 && strcmp(novo, "reservado") != 0)
            printf("  [!] Status invalido.\n");
        else break;
    } while (1);

    strncpy(v->status, novo, sizeof(v->status) - 1);
    printf("  [OK] Status atualizado para '%s'.\n", v->status);
    pausar();
}

void menu_veiculos(void) {
    int op;
    do {
        separador();
        printf("\n");
        printf("  MENU - Veiculos\n");
        separador();
        printf("\n");
        printf("  1. Cadastrar veiculo\n");
        printf("  2. Listar todos os veiculos\n");
        printf("  3. Listar disponiveis\n");
        printf("  4. Listar reservados\n");
        printf("  5. Listar vendidos\n");
        printf("  6. Atualizar status manualmente\n");
        printf("  0. Voltar\n");
        separador();
        op = ler_inteiro("  Opcao: ");
        switch (op) {
            case 1: cadastrar_veiculo();           break;
            case 2: listar_veiculos(NULL);         break;
            case 3: listar_veiculos("disponivel"); break;
            case 4: listar_veiculos("reservado");  break;
            case 5: listar_veiculos("vendido");    break;
            case 6: atualizar_status_veiculo();    break;
            case 0: break;
            default: printf("  [!] Opcao invalida.\n");
        }
    } while (op != 0);
}
