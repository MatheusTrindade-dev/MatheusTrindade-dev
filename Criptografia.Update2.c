/* 
Neste programa, o usuário cria uma senha que atende a uma série de requisitos para proteger um texto. 
Em seguida, o texto é cifrado duas vezes, utilizando, respectivamente, os métodos de cifra de transposição e cifra de substituição.
Para decifrar o texto, o usuário precisa digitar a senha criada anteriormente, tendo direito a duas tentativas.
1 - O usuário cria uma senha (atendendo uma série de requisitos).
2 - Escreve um texto.
3 - O texto é cifrado pelo método de transposição.
4 - O texto (já cifrado) é cifrado novamente pelo método de substituição.
5 - Para decifrar o texto, o usuário precisa digitar a senha criada anteriormente.
6 - Caso o usuário erre a senha, ele tem mais uma tentativa.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 256
#define MAXSENHA 100
#define MAXPALAVRA 20


// Função para decifrar a mensagem
void decifraMensagem(char string[], int len) {
    int i, j, k = 0, raiz;
    char matriz[MAX][MAX];
    len = strlen(string);
    if (string[len - 1] == '\n'){
        string[len - 1] = '\0';
        len--;
    }

    for (raiz = 1; raiz * raiz < len; raiz++);

    k = 0;
    for(i = 0; i < raiz; i++){
        for(j = 0; j < raiz ; j++){
            if(k < len && string[k] != '\0'){
                matriz[i][j] = (string[k] == ' ') ? '*' : string[k];
                k++;
            } else {
                matriz[i][j] = ' ';
            }
        }
    }

    k = 0;
    for(i = 0; i < raiz; i++){
        for(j = 0; j < raiz ; j++){
            if(k < len && string[k] != '\0'){
                string[k] = (matriz[j][i] == '*') ? ' ' : matriz[j][i];
                k++;
            } else {
                string[k] = ' ';
            }
        }
    }

    j = 0;
    int espaco = 0;
    for(i = 0; i < len; i++){
        if(string[i] != ' '){
            espaco = 0;
            string[j++] = string[i];
        } else if(!espaco){
            string[j++] = ' ';
            espaco = 1;
        }
    }

    if(j > 0 && string[j - 1] == ' '){
        j--;
    }

    string[j] = '\0';
}
// Função para embaralhar os valores da tabela (Fisher-Yates Shuffle)
void shuffle(char table[]) {
    for (int i = MAX - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = table[i];
        table[i] = table[j];
        table[j] = temp;
    }
}

int main()
{
    // Inicio da criação da senha
    char senha[MAXSENHA];
    int cont = 0, lenSENHA, tamanho = 1, i, n;

    printf("==========================================Verifica Senha==========================================\n");
    printf("Deve conter pelo menos 8 caracteres\n");
    printf("Deve conter pelo menos uma letra maiuscula\n");
    printf("Deve conter pelo menos uma letra minuscula\n");
    printf("Deve conter pelo menos um numero\n");
    printf("Deve conter pelo menos um dos seguintes simbolos: !, ?, #, @, $\n");
    printf("Nao pode ser um palindromo, i.e., revertendo-se os caracteres não podemos obter a mesma senha\n");
    printf("Nao pode conter nenhuma palavra reservada do dicionario\n");
    printf("==================================================================================================\n");

    printf("Digite a quantidade de palavras reservadas para o dicionario: ");
    scanf("%d", &n);
    system("cls");

    char dicionario[n][MAXPALAVRA];
    for(i = 0; i < n; i++) {
        system("cls");
        printf("=============Adicionando no Dicionario=============\n");
        printf("Digite a palavra %d: ", i+1);
        scanf("%s", dicionario[i]);
    }

    system("cls");
    printf("==========================================Verifica Senha==========================================\n");
    printf("Deve conter pelo menos 8 caracteres\n");
    printf("Deve conter pelo menos uma letra maiuscula\n");
    printf("Deve conter pelo menos uma letra minuscula\n");
    printf("Deve conter pelo menos um numero\n");
    printf("Deve conter pelo menos um dos seguintes simbolos: !, ?, #, @, $\n");
    printf("Nao pode ser um palindromo, i.e., revertendo-se os caracteres não podemos obter a mesma senha\n");
    printf("Nao pode conter nenhuma palavra reservada do dicionario\n");
    printf("==================================================================================================\n");

    printf("Crie uma senha: ");
    getchar();
    fgets(senha, MAXSENHA, stdin);

    lenSENHA = strlen(senha);

    if (senha[lenSENHA - 1] == '\n'){
        senha[lenSENHA - 1] = '\0';
        lenSENHA--;
    }

    if(lenSENHA < 8) tamanho = 0;

    int minuscula = 0, maiuscula = 0, numero = 0, simbolo = 0, palindromo = 1, verifica_dicionario = 1;

    for(i = 0; senha[i] != '\0'; i++){
        if(senha[i] >= 'A' && senha[i] <= 'Z') maiuscula = 1;
        else if(senha[i] >= 'a' && senha[i] <= 'z') minuscula = 1;
        else if(senha[i] >= '0' && senha[i] <= '9') numero = 1;
        else if(senha[i] == '!' || senha[i] == '?' || senha[i] == '#' || senha[i] == '@' || senha[i] == '$') simbolo = 1;
    }

    palindromo = 1;
    for (i = 0; i < lenSENHA / 2; i++) {
        if (senha[i] != senha[lenSENHA - i - 1]) {
            palindromo = 0; // Não é palíndromo
            break;
        }
    }

    for(i = 0; i < n; i++)
    {
        if(strstr(senha, dicionario[i]) != NULL)
        {
            verifica_dicionario = 0;
            break;
        }
    }

    if (tamanho && maiuscula && minuscula && numero && simbolo && !palindromo && verifica_dicionario) {
        printf("\nA senha atende a todos os criterios.\n");
    } else {
        printf("\nA senha nao atende a todos os criterios:\n");
        if (!tamanho) printf("-A senha nao tem pelo menos 8 caracteres.\n");
        if (!maiuscula) printf("-A senha nao contem nenhuma letra maiuscula.\n");
        if (!minuscula) printf("-A senha nao contem nenhuma letra minuscula.\n");
        if (!numero) printf("-A senha nao contem nenhum numero.\n");
        if (!simbolo) printf("-A senha nao contem nenhum simbolo especial.\n");
        if (palindromo) printf("-A senha e um palindromo.\n");
        if (!verifica_dicionario) printf("-A senha contem pelo menos uma palavra reservada do dicionario.");
        return 1;
    }
    // Fim da criação da senha

    char string[1024], matriz[MAX][MAX];
    int m, raiz;

    printf("\nDigite um texto: ");
    fgets(string, MAX, stdin);
    system("cls");

    // Cifragem do texto usando o método de cifra de transposição
    int len = strlen(string);
    if (string[len - 1] == '\n'){
        string[len - 1] = '\0';
        len--;
    }

    for (m = 1; m * m < len; m++);
    raiz = m;

    int j;
    for(i = 0; i < raiz; i++){
        for(j = 0; j < raiz; j++){
            matriz[i][j] = ' ';
        }
    }

    int k = 0;
    for(i = 0; i < raiz; i++){
        for(j = 0; j < raiz; j++){
            if(k < len && string[k] != '\0'){
                matriz[i][j] = (string[k] == ' ') ? '*' : string[k];
                k++;
            }
        }
    }

    k = 0;
    for(i = 0; i < raiz; i++){
        for(j = 0; j < raiz; j++){
            string[k++] = matriz[j][i];
        }
    }

    string[k] = '\0';

    // Segunda cifragem do texto usando o método de cifra de substituição
    char substitutionTable[MAX], inverseTable[MAX];

    srand(time(NULL));

    for (i = 0; i < MAX; i++) {
        substitutionTable[i] = (char)i; // Inicializa a tabela com valores 0-255
    }
    shuffle(substitutionTable); // Embaralha os valores da tabela

    // Cria a tabela inversa para decodificação
    for (i = 0; i < MAX; i++) {
        inverseTable[(unsigned char)substitutionTable[i]] = (char)i;
    }

    // Substitui os caracteres da string com base na tabela de substituição
    for (i = 0; i < strlen(string); i++) {
        string[i] = substitutionTable[(unsigned char)string[i]];
    }

    // Exibe a string codificada
    printf("Mensagem codificada: %s\n", string);

    // Decifragem do texto
    char senha2[MAXSENHA];
    printf("Digite a senha: ");
    fgets(senha2, MAXSENHA, stdin);

    if (senha2[strlen(senha2) - 1] == '\n') {
        senha2[strlen(senha2) - 1] = '\0';
    }

    if(strcmp(senha2, senha) == 0){
        // Decodifica a string utilizando a tabela inversa
        for (i = 0; i < strlen(string); i++) {
            string[i] = inverseTable[(unsigned char)string[i]];
        }
        // Exibe a string decodificada
        decifraMensagem(string, len);
        printf("Mensagem decifrada: %s\n", string);
    } else {
        system("cls");
        printf("Mensagem cifrada: %s\n", string);
        printf("Senha errada. Mais uma tentativa disponível \n");
        printf("\nDigite a senha: ");
        fgets(senha2, MAXSENHA, stdin);

        if (senha2[strlen(senha2) - 1] == '\n') {
            senha2[strlen(senha2) - 1] = '\0';
        }

        if(strcmp(senha2, senha) == 0){
            // Decodifica a string utilizando a tabela inversa
            for (i = 0; i < strlen(string); i++) {
                string[i] = inverseTable[(unsigned char)string[i]];
            }
            // Exibe a string decodificada
            decifraMensagem(string, len);
            printf("Mensagem decifrada: %s\n", string);
        } else {
            printf("Senha errada novamente. Bloqueado \n");
            return 1;
        }
    }

    return 0;
}
