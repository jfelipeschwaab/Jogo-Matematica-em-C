#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para armazenar os dados da operação matemática
typedef struct {
    int dificuldade; // Nível de dificuldade
    int valor1;      // Primeiro número da operação
    int valor2;      // Segundo número da operação
    int operacao;    // Tipo de operação: 0 = soma, 1 = subtração, 2 = multiplicação
    int resultado;   // Resultado correto da operação
} Calcular;

// Função para exibir informações sobre uma operação
void mostrarInfo(Calcular calc) {
    printf("Dificuldade: Nivel %d\n", calc.dificuldade);
    printf("Operacao: ");
    switch(calc.operacao) {
        case 0:
            printf("Soma\n");
            break;
        case 1:
            printf("Subtracao\n");
            break;
        case 2:
            printf("Multiplicacao\n");
            break;
        default:
            printf("Desconhecida\n");
    }
    printf("Valores: %d e %d\n", calc.valor1, calc.valor2);
    printf("Resultado correto: %d\n", calc.resultado);
}

// Função para gerar uma operação aleatória com base no nível de dificuldade
Calcular gerarOperacao(int dificuldade) {
    Calcular calc;
    calc.dificuldade = dificuldade;

    int max;
    // Define o intervalo dos valores com base no nível de dificuldade
    switch(dificuldade) {
        case 1:
            max = 10;
            break;
        case 2:
            max = 100;
            break;
        case 3:
            max = 1000;
            break;
        case 4:
            max = 10000;
            break;
        default:
            max = 10;
    }

    // Gera valores aleatórios para a operação
    calc.valor1 = rand() % (max + 1);
    calc.valor2 = rand() % (max + 1);
    calc.operacao = rand() % 3; // Define a operação: 0 = soma, 1 = subtração, 2 = multiplicação

    // Calcula o resultado correto da operação
    switch(calc.operacao) {
        case 0:
            calc.resultado = calc.valor1 + calc.valor2;
            break;
        case 1:
            calc.resultado = calc.valor1 - calc.valor2;
            break;
        case 2:
            calc.resultado = calc.valor1 * calc.valor2;
            break;
        default:
            calc.resultado = 0;
    }

    return calc;
}

// Funções auxiliares para operações matemáticas
int somar(int a, int b) {
    return a + b;
}

int diminuir(int a, int b) {
    return a - b;
}

int multiplicar(int a, int b) {
    return a * b;
}

// Função principal do jogo
void jogar(int dificuldade) {
    int pontos = 0;                // Pontuação do jogador
    char continuar;                // Controle para continuar jogando
    int current_level = dificuldade; // Nível atual do jogo
    int next_level_up = 10;        // Pontuação necessária para subir de nível

    do {
        // Gera uma nova operação
        Calcular calc = gerarOperacao(current_level);
        int resposta;

        printf("\nNivel Atual: %d\n", current_level);
        printf("Resolva a seguinte operacao:\n");
        // Exibe a operação com base no tipo
        switch(calc.operacao) {
            case 0:
                printf("%d + %d = ", calc.valor1, calc.valor2);
                break;
            case 1:
                printf("%d - %d = ", calc.valor1, calc.valor2);
                break;
            case 2:
                printf("%d * %d = ", calc.valor1, calc.valor2);
                break;
            default:
                printf("Operacao desconhecida.\n");
        }

        // Lê a resposta do jogador e trata entrada inválida
        if (scanf("%d", &resposta) != 1) {
            while(getchar() != '\n'); // Limpa o buffer
            printf("Entrada invalida. Considerada como resposta errada.\n");
            resposta = calc.resultado + 1; // Define como incorreta
        }

        // Verifica se a resposta está correta
        int correta = 0;
        switch(calc.operacao) {
            case 0:
                correta = (resposta == somar(calc.valor1, calc.valor2));
                break;
            case 1:
                correta = (resposta == diminuir(calc.valor1, calc.valor2));
                break;
            case 2:
                correta = (resposta == multiplicar(calc.valor1, calc.valor2));
                break;
        }

        // Atualiza a pontuação com base na resposta
        if(correta) {
            printf("Resposta correta! +1 ponto.\n");
            pontos++;
        } else {
            printf("Resposta incorreta. O correto era %d.\n", calc.resultado);
        }

        // Aumenta o nível de dificuldade se necessário
        if (pontos >= next_level_up && current_level < 4) {
            current_level++;
            printf("Parabens! Você alcançou %d pontos.\n", next_level_up);
            printf("Nivel de dificuldade aumentado para %d.\n", current_level);
            next_level_up += 10; // Atualiza o próximo marco de nível
        }

        // Pergunta se o jogador quer continuar
        printf("Deseja continuar jogando? (s/n): ");
        scanf(" %c", &continuar);
        while(getchar() != '\n'); // Limpa o buffer

    } while(continuar == 's' || continuar == 'S');

    // Exibe a pontuação final ao encerrar o jogo
    printf("\nJogo encerrado! Sua pontuacao final: %d pontos.\n", pontos);
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int dificuldade;
    printf("=== Jogo de Calculos Matematicos ===\n");
    printf("Selecione o nivel de dificuldade:\n");
    printf("1 - Facil (0 a 10)\n");
    printf("2 - Medio (0 a 100)\n");
    printf("3 - Dificil (0 a 1000)\n");
    printf("4 - Insano (0 a 10000)\n");
    printf("Digite o numero correspondente ao nivel desejado: ");

    // Lê a dificuldade selecionada e trata entradas inválidas
    while(1) {
        if (scanf("%d", &dificuldade) != 1 || dificuldade < 1 || dificuldade > 4) {
            printf("Entrada invalida! Por favor, selecione um nivel entre 1 e 4: ");
            while(getchar() != '\n'); // Limpa o buffer
        } else {
            break;
        }
    }

    // Inicia o jogo
    jogar(dificuldade);

    return 0;
}
