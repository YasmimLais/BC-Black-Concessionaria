#ifndef UTILS_H
#define UTILS_H

/* ============================================================
 *  Utilitarios — I/O, formatacao e datas
 * ============================================================ */
void limpar_buffer(void);
void ler_string(const char *prompt, char *destino, int tamanho);
int  ler_inteiro(const char *prompt);
double ler_double(const char *prompt);
void data_hora_atual(char *destino, int tamanho);
int  ano_atual(void);
void para_minusculo(char *s);
void separador(void);
void pausar(void);

/* ============================================================
 *  Validacoes
 * ============================================================ */
int validar_email(const char *email);
int validar_cpf(const char *cpf);
int validar_telefone(const char *tel);
int email_unico(const char *email, int ignorar_id);
int cpf_unico(const char *cpf, int ignorar_id);

/* ============================================================
 *  Buscas
 * ============================================================ */
int buscar_cliente_por_id(int id);
int buscar_veiculo_por_id(int id);

#endif /* UTILS_H */
