// Q5. Write a program in C to Implement the various primitive operations of classical sets.

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int elements[MAX_SIZE];
    int size;
} Set;

void initSet(Set *s);
bool isEmpty(Set *s);
bool isMember(Set *s, int element);
void addElement(Set *s, int element);
void removeElement(Set *s, int element);
int cardinality(Set *s);
void printSet(Set *s);
void unionSet(Set *set1, Set *set2, Set *result);
void intersectionSet(Set *set1, Set *set2, Set *result);
void differenceSet(Set *set1, Set *set2, Set *result);
bool isSubset(Set *set1, Set *set2);
bool isEqual(Set *set1, Set *set2);
void complementSet(Set *universal, Set *s, Set *result);

int main() {
    Set A, B, C, universal;
    int i;

    initSet(&A);
    initSet(&B);
    initSet(&C);
    initSet(&universal);

    printf("Creating universal set {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n");
    for (i = 1; i <= 10; i++)
        addElement(&universal, i);

    printf("\nEnter elements for Set A (e.g., 1 2 3 5 7):\n");
    for (i = 0; i < 5; i++) {
        int elem;
        scanf("%d", &elem);
        addElement(&A, elem);
    }

    printf("\nEnter elements for Set B (e.g., 2 4 6 8):\n");
    for (i = 0; i < 4; i++) {
        int elem;
        scanf("%d", &elem);
        addElement(&B, elem);
    }

    printf("\nUniversal set: ");
    printSet(&universal);
    printf("Set A: ");
    printSet(&A);
    printf("Set B: ");
    printSet(&B);

    printf("\nIs set A empty? %s\n", isEmpty(&A) ? "Yes" : "No");
    printf("Is 3 a member of set A? %s\n", isMember(&A, 3) ? "Yes" : "No");
    printf("Is 4 a member of set A? %s\n", isMember(&A, 4) ? "Yes" : "No");

    printf("\nCardinality of Sets:\n");
    printf("Cardinality of set A: %d\n", cardinality(&A));
    printf("Cardinality of set B: %d\n", cardinality(&B));

    printf("\nEnter element to remove from set A (e.g., 3): ");
    int remove_elem;
    scanf("%d", &remove_elem);
    removeElement(&A, remove_elem);
    printf("Set A after removal: ");
    printSet(&A);

    printf("\nFinal Set A: ");
    printSet(&A);
    printf("Final Set B: ");
    printSet(&B);

    unionSet(&A, &B, &C);
    printf("\nUnion of Sets:\nA ∪ B: ");
    printSet(&C);

    intersectionSet(&A, &B, &C);
    printf("\nIntersection of Sets:\nA ∩ B: ");
    printSet(&C);

    differenceSet(&A, &B, &C);
    printf("\nDifference of Sets:\nA - B: ");
    printSet(&C);

    differenceSet(&B, &A, &C);
    printf("B - A: ");
    printSet(&C);

    printf("\nIs A a subset of universal? %s\n", isSubset(&A, &universal) ? "Yes" : "No");
    printf("Is universal a subset of A? %s\n", isSubset(&universal, &A) ? "Yes" : "No");

    printf("\nIs A equal to B? %s\n", isEqual(&A, &B) ? "Yes" : "No");

    complementSet(&universal, &A, &C);
    printf("\nComplement of Set A': ");
    printSet(&C);
    complementSet(&universal, &B, &C);
    printf("Complement of Set B': ");
    printSet(&C);

    return 0;
}

void initSet(Set *s) {
    s->size = 0;
}

bool isEmpty(Set *s) {
    return s->size == 0;
}

bool isMember(Set *s, int element) {
    for (int i = 0; i < s->size; i++)
        if (s->elements[i] == element)
            return true;
    return false;
}

void addElement(Set *s, int element) {
    if (!isMember(s, element) && s->size < MAX_SIZE)
        s->elements[s->size++] = element;
}

void removeElement(Set *s, int element) {
    for (int i = 0; i < s->size; i++)
        if (s->elements[i] == element) {
            s->elements[i] = s->elements[s->size - 1];
            s->size--;
            return;
        }
}

int cardinality(Set *s) {
    return s->size;
}

void printSet(Set *s) {
    printf("{ ");
    for (int i = 0; i < s->size; i++) {
        printf("%d", s->elements[i]);
        if (i < s->size - 1)
            printf(", ");
    }
    printf(" }\n");
}

void unionSet(Set *set1, Set *set2, Set *result) {
    initSet(result);
    for (int i = 0; i < set1->size; i++)
        addElement(result, set1->elements[i]);
    for (int i = 0; i < set2->size; i++)
        addElement(result, set2->elements[i]);
}

void intersectionSet(Set *set1, Set *set2, Set *result) {
    initSet(result);
    for (int i = 0; i < set1->size; i++)
        if (isMember(set2, set1->elements[i]))
            addElement(result, set1->elements[i]);
}

void differenceSet(Set *set1, Set *set2, Set *result) {
    initSet(result);
    for (int i = 0; i < set1->size; i++)
        if (!isMember(set2, set1->elements[i]))
            addElement(result, set1->elements[i]);
}

bool isSubset(Set *set1, Set *set2) {
    for (int i = 0; i < set1->size; i++)
        if (!isMember(set2, set1->elements[i]))
            return false;
    return true;
}

bool isEqual(Set *set1, Set *set2) {
    return isSubset(set1, set2) && isSubset(set2, set1);
}

void complementSet(Set *universal, Set *s, Set *result) {
    differenceSet(universal, s, result);
}