// Q4. Design and Simulate the Behaviour of XOR Gate Using Back-Propagation Network in c for Bipolar Inputs and Targets.

#include <stdio.h>
#include <math.h>
#define NUM_PATTERNS 4
#define NUM_INPUTS 2
#define MAX_ITERATIONS 3000

int main() {
    signed int x[NUM_PATTERNS][NUM_INPUTS], tar[NUM_PATTERNS], y_actual, i, j, itr = 1, k;
    float v[NUM_INPUTS][NUM_INPUTS], vc[NUM_INPUTS][NUM_INPUTS], v_b[NUM_INPUTS], zin[NUM_INPUTS], zout[NUM_INPUTS], yin, yout, w1, w2, w0, alpha = 0.25, delta_out, delta_internal[NUM_INPUTS] = {0}, delta_in[NUM_INPUTS] = {0};

    printf("Enter input patterns and targets for Bipolar XOR Gate (-1 or 1):\n");
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("Enter input pattern %d (x1 x2): ", i + 1);
        scanf("%d %d", &x[i][0], &x[i][1]);
        printf("Enter target for pattern %d: ", i + 1);
        scanf("%d", &tar[i]);
    }

    printf("Enter Weights and Bias Between Input and Hidden Layer:\n");
    for (i = 0; i < NUM_INPUTS; i++) {
        for (j = 0; j < NUM_INPUTS; j++) {
            printf("Enter Weight: v[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &v[i][j]);
            vc[i][j] = 0;
        }
        printf("Enter bias v_b[%d]: ", i + 1);
        scanf("%f", &v_b[i]);
    }

    printf("\nEnter Weights and Bias Between Hidden and Output Layer:\n");
    printf("Enter Weight: w1: ");
    scanf("%f", &w1);
    printf("Enter Weight: w2: ");
    scanf("%f", &w2);
    printf("Enter bias: w0: ");
    scanf("%f", &w0);

    do {
        printf("\n-------------------\n| Iteration: %d |\n-------------------\n", itr);
        printf("| x₁ | x₂ | Target | Zin₁ | Zin₂ | Zout₁ | Zout₂ | yin | yout | y_actual | New v₁₁ | New v₂₁ | New v_b₁ | New v₁₂ | New v₂₂ | New v_b₂ | New w1 | New w2 | New w0 |\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        k = 0;
        for (i = 0; i < NUM_PATTERNS; i++) {
            zin[0] = zin[1] = zout[0] = zout[1] = yin = yout = delta_out = delta_in[0] = delta_in[1] = delta_internal[0] = delta_internal[1] = 0;
            for (j = 0; j < NUM_INPUTS; j++) {
                zin[j] = x[i][0] * v[0][j] + x[i][1] * v[1][j] + v_b[j];
                zout[j] = (1 - expf(-zin[j])) / (1 + expf(-zin[j]));
            }
            yin = zout[0] * w1 + zout[1] * w2 + w0;
            yout = (1 - expf(-yin)) / (1 + expf(-yin));
            y_actual = yout >= 0 ? 1 : -1;

            if (y_actual != tar[i]) {
                delta_out = (tar[i] - yout) * (0.5 * (1 + yout) * (1 - yout));
                w1 += alpha * delta_out * zout[0];
                w2 += alpha * delta_out * zout[1];
                w0 += alpha * delta_out;
                delta_in[0] = delta_out * w1;
                delta_in[1] = delta_out * w2;
                delta_internal[0] = delta_in[0] * (0.5 * (1 + zout[0]) * (1 - zout[0]));
                delta_internal[1] = delta_in[1] * (0.5 * (1 + zout[1]) * (1 - zout[1]));
                v[0][0] += alpha * delta_internal[0] * x[i][0];
                v[0][1] += alpha * delta_internal[1] * x[i][0];
                v_b[0] += alpha * delta_internal[0];
                v[1][0] += alpha * delta_internal[0] * x[i][1];
                v[1][1] += alpha * delta_internal[1] * x[i][1];
                v_b[1] += alpha * delta_internal[1];
            } else {
                k++;
            }
            printf("| %d | %d | %d | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %d | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f | %.3f |\n",
                   x[i][0], x[i][1], tar[i], zin[0], zin[1], zout[0], zout[1], yin, yout, y_actual, v[0][0], v[1][0], v_b[0], v[0][1], v[1][1], v_b[1], w1, w2, w0);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        if (k == 4) {
            printf("Converged in %d iterations\nFinal Weights: v11=%.5f, v21=%.5f, v12=%.5f, v22=%.5f, w1=%.5f, w2=%.5f, Bias1=%.5f, Bias2=%.5f, Bias0=%.5f\n",
                   itr, v[0][0], v[1][0], v[0][1], v[1][1], w1, w2, v_b[0], v_b[1], w0);
            break;
        }
        itr++;
    } while (itr <= MAX_ITERATIONS);

    if (itr > MAX_ITERATIONS)
        printf("Not converged within %d iterations.\n", MAX_ITERATIONS);
    return 0;
}