#include <stdio.h>
#include <string.h>
#include "../include/tipos.h"
#include "utils.h"
#include "cliente.h"

/* ============================================================
 *  MODULO 1 - Cadastro de Clientes
 * ============================================================ */

void cadastrar_cliente(void) {
    separador();
    printf("  CADASTRO DE CLIENTE\n");
    separador();

    if (total_clientes >= MAX_CLIENTES) {
        printf("  [!] Limite de clientes atingido.\n");
        pausar();
        return;
    }

    Cliente c;
    memset(&c, 0, sizeof(c));
    c.id_cliente = proximo_id_cliente;
    c.ativo = 1;

    do {
        ler_string("  Nome        : ", c.nome, sizeof(c.nome));
        if (strlen(c.nome) == 0)
            printf("  [!] Nome e obrigatorio.\n");
    } while (strlen(c.nome) == 0);

    do {
        ler_string("  Email       : ", c.email, sizeof(c.email));
        if (!validar_email(c.email))
            printf("  [!] Email invalido. Deve conter '@' e dominio valido.\n");
        else if (!email_unico(c.email, -1))
            printf("  [!] Email ja cadastrado.\n");
        else break;
    } while (1);

    do {
        ler_string("  Telefone    : ", c.telefone, sizeof(c.telefone));
        if (!validar_telefone(c.telefone))
            printf("  [!] Telefone deve conter apenas numeros.\n");
        else break;
    } while (1);

    do {
        ler_string("  CPF (11 dig): ", c.cpf, sizeof(c.cpf));
        if (!validar_cpf(c.cpf))
            printf("  [!] CPF invalido. Deve ter exatamente 11 digitos numericos.\n");
        else if (!cpf_unico(c.cpf, -1))
            printf("  [!] CPF ja cadastrado.\n");
        else break;
    } while (1);

    ler_string("  Endereco    : ", c.endereco, sizeof(c.endereco));

    clientes[total_clientes++] = c;
    proximo_id_cliente++;

    printf("\n  [OK] Cliente '%s' cadastrado com ID #%d.\n", c.nome, c.id_cliente);
    pausar();
}

void listar_clientes(void) {
    separador();
    printf("\n");
    printf("  LISTA DE CLIENTES\n");
    separador();
    printf("\n");
    printf("  %-4s  %-30s  %-20s  %-15s\n", "ID", "Nome", "Email", "Telefone");
    printf("  %-4s  %-30s  %-20s  %-15s\n", "----", "------------------------------",
           "--------------------", "---------------");

    int encontrou = 0;
    for (int i = 0; i < total_clientes; i++) {
        if (!clientes[i].ativo) continue;
        printf("  %-4d  %-30s  %-20s  %-15s\n",
               clientes[i].id_cliente,
               clientes[i].nome,
               clientes[i].email,
               clientes[i].telefone);
        encontrou = 1;
    }
    if (!encontrou) printf("  Nenhum cliente cadastrado.\n");
    pausar();
}

void editar_cliente(void) {
    separador();
    printf("  EDITAR CLIENTE\n");
    separador();

    int id  = ler_inteiro("  ID do cliente: ");
    int idx = buscar_cliente_por_id(id);
    if (idx < 0) {
        printf("  [!] Cliente nao encontrado.\n");
        pausar();
        return;
    }

    Cliente *c = &clientes[idx];
    printf("  Editando: %s\n", c->nome);
    printf("  (Deixe em branco para manter o valor atual)\n\n");

    char buf[200];

    printf("  Nome atual [%s]: ", c->nome);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strncpy(c->nome, buf, sizeof(c->nome) - 1);

    do {
        printf("  Email atual [%s]: ", c->email);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) break;
        if (!validar_email(buf))              { printf("  [!] Email invalido.\n");   continue; }
        if (!email_unico(buf, c->id_cliente)) { printf("  [!] Email ja em uso.\n"); continue; }
        strncpy(c->email, buf, sizeof(c->email) - 1);
        break;
    } while (1);

    do {
        printf("  Telefone atual [%s]: ", c->telefone);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) break;
        if (!validar_telefone(buf)) { printf("  [!] Telefone invalido.\n"); continue; }
        strncpy(c->telefone, buf, sizeof(c->telefone) - 1);
        break;
    } while (1);

    printf("  Endereco atual [%s]: ", c->endereco);
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strncpy(c->endereco, buf, sizeof(c->endereco) - 1);

    printf("\n  [OK] Cliente atualizado com sucesso.\n");
    pausar();
}

void excluir_cliente(void) {
    separador();
    printf("  EXCLUIR CLIENTE\n");
    separador();

    int id  = ler_inteiro("  ID do cliente: ");
    int idx = buscar_cliente_por_id(id);
    if (idx < 0) {
        printf("  [!] Cliente nao encontrado.\n");
        pausar();
        return;
    }
    clientes[idx].ativo = 0;
    printf("  [OK] Cliente #%d removido.\n", id);
    pausar();
}

void menu_clientes(void) {
    int op;
    do {
        separador();
        printf("\n");
        printf("  MENU - Clientes\n");
        separador();
        printf("\n");
        printf("  1. Cadastrar cliente\n");
        printf("  2. Listar clientes\n");
        printf("  3. Editar cliente\n");
        printf("  4. Excluir cliente\n");
        printf("  0. Voltar\n");
        separador();
        op = ler_inteiro("  Opcao: ");
        switch (op) {
            case 1: cadastrar_cliente(); break;
            case 2: listar_clientes();   break;
            case 3: editar_cliente();    break;
            case 4: excluir_cliente();   break;
            case 0: break;
            default: printf("  [!] Opcao invalida.\n");
        }
    } while (op != 0);
}
