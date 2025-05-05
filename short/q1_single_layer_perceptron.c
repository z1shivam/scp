//Q1. Design and simulate the behaviour of AND Gate using Perceptron Network in C for bipolar inputs and targets.

#include <stdio.h>

#define NUM_INPUTS 2
#define NUM_PATTERNS 4

int main() {
    int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS], i, j, k = 0, h = 1;
    float w[NUM_INPUTS] = {0}, wc[NUM_INPUTS] = {0}, s, b = 0, bc = 0, alpha, theta, out;

    printf("Enter theta & alpha: ");
    scanf("%f %f", &theta, &alpha);
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input row %d & target: ", i + 1);
        for (j = 0; j < NUM_INPUTS; j++)
            scanf("%d", &x[i][j]);
        scanf("%d", &tar[i]);
    }

    do {
        k = 0;
        for (i = 0; i < NUM_PATTERNS; i++) {
            s = b;
            for (j = 0; j < NUM_INPUTS; j++)
                s += x[i][j] * w[j];
            printf("%.2f\t", s);
            out = s > theta ? 1 : s < -theta ? -1 : 0;
            printf("%d\t", tar[i]);
            if (out == tar[i]) {
                for (j = 0; j < NUM_INPUTS; j++)
                    wc[j] = 0, printf("%.2f\t", wc[j]);
                for (j = 0; j < NUM_INPUTS; j++)
                    printf("%.2f\t", w[j]);
                k++;
                bc = 0;
                printf("%.2f\t\t%.2f\t", bc, b);
            } else {
                for (j = 0; j < NUM_INPUTS; j++)
                    wc[j] = x[i][j] * tar[i] * alpha, w[j] += wc[j], printf("%.2f\t", wc[j]);
                for (j = 0; j < NUM_INPUTS; j++)
                    printf("%.2f\t", w[j]);
                bc = tar[i] * alpha, b += bc;
                printf("%.2f\t\t%.2f\t", bc, b);
            }
            printf("\n");
        }
        h++;
    } while (k < NUM_PATTERNS);

    for (j = 0; j < NUM_INPUTS; j++)
        printf("w[%d]=%.2f\t", j, w[j]);
    printf("Bias b=%.2f\n", b);
    return 0;
}