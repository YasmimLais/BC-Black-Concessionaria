#include <stdio.h>
#include <string.h>
#include "../include/tipos.h"
#include "utils.h"
#include "cliente.h"
#include "venda.h"

/* ============================================================
 *  MODULO 3 - Realizar Venda
 * ============================================================ */

void realizar_venda(void) {
    separador();
    printf("\n");
    printf("  REALIZAR VENDA\n");
    separador();

    if (total_vendas >= MAX_VENDAS) {
        printf("  [!] Limite de vendas atingido.\n");
        pausar();
        return;
    }

    /* Selecionar cliente */
    listar_clientes();
    int id_cli  = ler_inteiro("  ID do cliente: ");
    int idx_cli = buscar_cliente_por_id(id_cli);
    if (idx_cli < 0) {
        printf("  [!] Cliente nao encontrado.\n");
        pausar();
        return;
    }

    /* Listar veiculos disponiveis */
    separador();
    printf("\n");
    printf("  VEICULOS DISPONIVEIS\n");
    separador();
    printf("  %-4s  %-6s  %-15s  %-15s  %-4s  %12s\n",
           "ID", "Tipo", "Marca", "Modelo", "Ano", "Preco(R$)");
    printf("  %-4s  %-6s  %-15s  %-15s  %-4s  %12s\n",
           "----", "------", "---------------", "---------------", "----", "------------");

    int tem_disponivel = 0;
    for (int i = 0; i < total_veiculos; i++) {
        if (strcmp(veiculos[i].status, "disponivel") == 0) {
            printf("  %-4d  %-6s  %-15s  %-15s  %-4d  %12.2f\n",
                   veiculos[i].id_veiculo, veiculos[i].tipo,
                   veiculos[i].marca,      veiculos[i].modelo,
                   veiculos[i].ano,        veiculos[i].preco);
            tem_disponivel = 1;
        }
    }
    if (!tem_disponivel) {
        printf("  Nenhum veiculo disponivel no momento.\n");
        pausar();
        return;
    }

    /* Selecionar veiculo */
    int id_vei  = ler_inteiro("  ID do veiculo: ");
    int idx_vei = buscar_veiculo_por_id(id_vei);
    if (idx_vei < 0) {
        printf("  [!] Veiculo nao encontrado.\n");
        pausar();
        return;
    }
    if (strcmp(veiculos[idx_vei].status, "disponivel") != 0) {
        printf("  [!] Veiculo nao esta disponivel para venda.\n");
        pausar();
        return;
    }

    /* Forma de pagamento */
    char forma[20];
    do {
        ler_string("  Forma de pagamento (a vista/financiamento/consorcio): ",
                   forma, sizeof(forma));
        para_minusculo(forma);
        if (strcmp(forma, "a vista")       != 0 &&
            strcmp(forma, "financiamento") != 0 &&
            strcmp(forma, "consorcio")     != 0)
            printf("  [!] Forma invalida. Use: a vista, financiamento ou consorcio.\n");
        else break;
    } while (1);

    /* Registrar venda */
    double valor = veiculos[idx_vei].preco;
    if (valor <= 0) {
        printf("  [!] Valor invalido.\n");
        pausar();
        return;
    }

    Venda venda;
    memset(&venda, 0, sizeof(venda));
    venda.id_venda    = proximo_id_venda;
    venda.id_cliente  = id_cli;
    venda.id_veiculo  = id_vei;
    venda.valor_total = valor;
    data_hora_atual(venda.data_venda, sizeof(venda.data_venda));
    strncpy(venda.forma_pagamento, forma, sizeof(venda.forma_pagamento) - 1);

    vendas[total_vendas++] = venda;

    /* Registrar item */
    ItemVenda item;
    item.id_item    = proximo_id_item;
    item.id_venda   = proximo_id_venda;
    item.id_veiculo = id_vei;
    itens[total_itens++] = item;
    proximo_id_item++;

    /* Marcar veiculo como vendido */
    strcpy(veiculos[idx_vei].status, "vendido");
    proximo_id_venda++;

    separador();
    printf("\n");
    printf("  [OK] VENDA REGISTRADA COM SUCESSO!\n");
    printf("  Venda ID  : #%d\n",     venda.id_venda);
    printf("  Cliente   : %s\n",      clientes[idx_cli].nome);
    printf("  Veiculo   : %s %s\n",   veiculos[idx_vei].marca, veiculos[idx_vei].modelo);
    printf("  Data      : %s\n",      venda.data_venda);
    printf("  Valor     : R$ %.2f\n", venda.valor_total);
    printf("  Pagamento : %s\n",      venda.forma_pagamento);
    separador();
    pausar();
}
