// Q2. Design and simulate the behaviour of OR Gate using Adaline Network in C for bipolar inputs and targets.
#include <stdio.h>
#define NUM_INPUTS 2
#define NUM_PATTERNS 4
#define MAX_ITERATIONS 100

int main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS], i, j, k, q = 1;
    float w[NUM_INPUTS] = {0.1}, wc[NUM_INPUTS] = {0}, e, es = 0, et = 1.4, yin, alpha = 0.1, b = 0.1, bc = 0;

    printf("Enter input patterns and targets for Bipolar OR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    do {
        printf("\n-------------------\n| Iteration: %d |\n-------------------\n", q);
        printf("| x1 | x2 | Target | Net | Error: (t-yin) | Δw₁ | Δw₂ | Δb | New w₁ | New w₂ | New b | Error^2: (t-yin)^2 |\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");

        es = 0;
        for (i = 0; i < NUM_PATTERNS; i++) {
            yin = b;
            for (j = 0; j < NUM_INPUTS; j++)
                yin += x[i][j] * w[j];
            e = tar[i] - yin;
            es += e * e;
            for (k = 0; k < NUM_INPUTS; k++)
                wc[k] = alpha * e * x[i][k], w[k] += wc[k];
            bc = alpha * e;
            b += bc;
            printf("| %d | %d | %d | %.5f | %.5f | %.5f| %.5f| %.5f | %.5f | %.5f | %.5f | %.5f |\n",
                   x[i][0], x[i][1], tar[i], yin, e, wc[0], wc[1], bc, w[0], w[1], b, e * e);
        }
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("Final Weights and bias after Iteration %d: Weights: w[1]=%.5f, w[2]=%.5f, Bias=%.5f   |   Total Error^2 = %.5f\n", q, w[0], w[1], b, es);

        if (es <= et) {
            printf("\nConverged in %d iterations, error=%.5f\nFinal Weights: w1=%.5f, w2=%.5f, Bias=%.5f\n", q, es, w[0], w[1], b);
            break;
        }
        q++;
    } while (q <= MAX_ITERATIONS);

    if (q > MAX_ITERATIONS)
        printf("Not converged within %d iterations.\n", MAX_ITERATIONS);
    return 0;
}