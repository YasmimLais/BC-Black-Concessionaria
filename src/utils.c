#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/tipos.h"
#include "utils.h"

/* ============================================================
 *  Utilitarios — I/O
 * ============================================================ */

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_string(const char *prompt, char *destino, int tamanho) {
    printf("%s", prompt);
    fgets(destino, tamanho, stdin);
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n')
        destino[len - 1] = '\0';
}

int ler_inteiro(const char *prompt) {
    int valor;
    char buf[32];
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin))
            if (sscanf(buf, "%d", &valor) == 1)
                return valor;
        printf("  [!] Entrada invalida. Digite um numero inteiro.\n");
    }
}

double ler_double(const char *prompt) {
    double valor;
    char buf[64];
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin))
            if (sscanf(buf, "%lf", &valor) == 1)
                return valor;
        printf("  [!] Entrada invalida. Digite um numero decimal.\n");
    }
}

/* ============================================================
 *  Utilitarios — data e texto
 * ============================================================ */

void data_hora_atual(char *destino, int tamanho) {
    time_t agora = time(NULL);
    struct tm *t  = localtime(&agora);
    snprintf(destino, tamanho, "%02d/%02d/%04d %02d:%02d",
             t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
             t->tm_hour, t->tm_min);
}

int ano_atual(void) {
    time_t agora = time(NULL);
    struct tm *t  = localtime(&agora);
    return t->tm_year + 1900;
}

void para_minusculo(char *s) {
    for (; *s; s++) *s = (char)tolower((unsigned char)*s);
}

void separador(void) {
    printf("\n============================================================\n");
}

void pausar(void) {
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

/* ============================================================
 *  Validacoes
 * ============================================================ */

int validar_email(const char *email) {
    const char *arroba = strchr(email, '@');
    if (!arroba) return 0;
    const char *ponto = strchr(arroba, '.');
    if (!ponto || ponto == arroba + 1) return 0;
    return 1;
}

int validar_cpf(const char *cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++)
        if (!isdigit((unsigned char)cpf[i])) return 0;
    return 1;
}

int validar_telefone(const char *tel) {
    if (strlen(tel) == 0) return 0;
    for (size_t i = 0; i < strlen(tel); i++)
        if (!isdigit((unsigned char)tel[i])) return 0;
    return 1;
}

int email_unico(const char *email, int ignorar_id) {
    for (int i = 0; i < total_clientes; i++) {
        if (!clientes[i].ativo) continue;
        if (clientes[i].id_cliente == ignorar_id) continue;
        if (strcmp(clientes[i].email, email) == 0) return 0;
    }
    return 1;
}

int cpf_unico(const char *cpf, int ignorar_id) {
    for (int i = 0; i < total_clientes; i++) {
        if (!clientes[i].ativo) continue;
        if (clientes[i].id_cliente == ignorar_id) continue;
        if (strcmp(clientes[i].cpf, cpf) == 0) return 0;
    }
    return 1;
}

/* ============================================================
 *  Buscas
 * ============================================================ */

int buscar_cliente_por_id(int id) {
    for (int i = 0; i < total_clientes; i++)
        if (clientes[i].id_cliente == id && clientes[i].ativo)
            return i;
    return -1;
}

int buscar_veiculo_por_id(int id) {
    for (int i = 0; i < total_veiculos; i++)
        if (veiculos[i].id_veiculo == id)
            return i;
    return -1;
}
