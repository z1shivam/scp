// Q3. Design and simulate the behaviour XOR Gate using Madaline network in C language for bipolar inputs and targets.

#include <stdio.h>
#include <math.h>
#define NUM_PATTERNS 4
#define NUM_INPUTS 2
#define MAX_ITERATIONS 10

int main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS], i, j, itr = 1;
    float w[NUM_INPUTS][NUM_INPUTS], wc[NUM_INPUTS][NUM_INPUTS], b[NUM_INPUTS], zin[NUM_INPUTS], zout[NUM_INPUTS], yin, yout, b3 = 0.5, v1 = 0.5, v2 = 0.5, alpha = 0.5, e, es = 0, prev_es = 0;

    printf("Enter input patterns and targets for Bipolar XOR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    printf("Enter Weights:\n");
    for (i = 0; i < NUM_INPUTS; i++) {
        for (j = 0; j < NUM_INPUTS; j++) {
            printf("Enter Weight: w[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &w[i][j]);
            wc[i][j] = 0;
        }
        printf("Enter bias b[%d]: ", i + 1);
        scanf("%f", &b[i]);
    }

    do {
        printf("\n-------------------\n| Iteration: %d |\n-------------------\n", itr);
        printf("| x₁ | x₂ | Target | Zin₁ | Zin₂ | Zout₁ | Zout₂ | yin | yout | New w₁₁ | New w₂₁ | New b₁ | New w₁₂ | New w₂₂ | New b₂ |\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");

        prev_es = es;
        es = 0.0;

        for (i = 0; i < NUM_PATTERNS; i++) {
            zin[0] = zin[1] = zout[0] = zout[1] = yin = yout = 0.0;
            for (j = 0; j < NUM_INPUTS; j++) {
                zin[j] += x[i][0] * w[0][j] + x[i][1] * w[1][j] + b[j];
                zout[j] = zin[j] >= 0 ? 1 : -1;
            }
            yin += zout[0] * v1 + zout[1] * v2 + b3;
            yout = yin >= 0 ? 1 : -1;

            if (yout != tar[i]) {
                if (tar[i] == 1) {
                    float abs_zin1 = fabsf(zin[0]), abs_zin2 = fabsf(zin[1]);
                    if (abs_zin1 < abs_zin2) {
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);
                    } else {
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    }
                } else {
                    if (zin[0] > 0 && zin[1] < 0) {
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);
                    } else if (zin[1] > 0 && zin[0] < 0) {
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    } else {
                        w[0][0] += alpha * (tar[i] - zin[0]) * x[i][0];
                        w[1][0] += alpha * (tar[i] - zin[0]) * x[i][1];
                        b[0] += alpha * (tar[i] - zin[0]);
                        w[0][1] += alpha * (tar[i] - zin[1]) * x[i][0];
                        w[1][1] += alpha * (tar[i] - zin[1]) * x[i][1];
                        b[1] += alpha * (tar[i] - zin[1]);
                    }
                }
            }
            printf("| %d | %d | %d | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f |\n",
                   x[i][0], x[i][1], tar[i], zin[0], zin[1], zout[0], zout[1], yin, yout, w[0][0], w[1][0], b[0], w[0][1], w[1][1], b[1]);

            e = (float)tar[i] - yin;
            es += e * e;
        }
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");

        if (itr != 1 && prev_es == es) {
            printf("Converged in %d iterations, error=%.5f\nFinal Weights: w11=%.5f, w21=%.5f, w12=%.5f, w22=%.5f, Bias1=%.5f, Bias2=%.5f\n", itr, es, w[0][0], w[1][0], w[0][1], w[1][1], b[0], b[1]);
            break;
        }
        itr++;
    } while (itr <= MAX_ITERATIONS);

    if (itr > MAX_ITERATIONS)
        printf("Not converged within %d iterations.\n", MAX_ITERATIONS);
    return 0;
}