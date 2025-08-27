#include <stdio.h>
//h significa header (cabeçalho)
//temos stdio.c que possui a implementação de funções, como as de biblioteca/dicionário

int potencia(int base, int expoente) { 
    //tipo f; nome f; (tipo p; nome p;, tipo p; nome p.)
    int resultado = 1; //não fazer por 0, por ser multiplicação
    for (int cont = 1; cont <= expoente; cont++) {
        resultado *= base;  // resultado = resultado * base;
    }
    return resultado;
}
int main() { 
    int base, expoente;
    printf("Base: ");
    scanf("%d", &base);
    printf("Expoente: ");
    scanf("%d", &expoente);

    int pot = potencia(base, expoente);
    printf("Potência: %d\n", pot);
    return 0;
}
