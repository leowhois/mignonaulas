#include <stdio.h>
#include <stdlib.h>

int somatoria(int n) {
    if (n == 0) {
        return 0;
    }
    else {
        return(n % 10) + somatoria(n / 10);
    }
}

int main() {
    int n, resultado;

    printf("Digite um número inteiro positivo: ");
    scanf("%d", &n);

    resultado = somatoria(n);
    printf("A somatória dos dígitos de %d é: %d\n", n, resultado);

    return 0;
}