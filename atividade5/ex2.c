
void correlacaobinaria(int n) {
    if (n > 0) {
        correlacaobinaria(n/2);
        printf("%d", n % 2);
    } else {
        if (n == 0) {
            printf("%d", n);
        }
    }
}
int main() {
    int n;

    printf("Digite um número inteiro positivo: ");
    scanf("%d", &n);

    printf("A representação binária de %d é: ", n);
    correlacaobinaria(n);
    printf("\n");

    return 0;
}
