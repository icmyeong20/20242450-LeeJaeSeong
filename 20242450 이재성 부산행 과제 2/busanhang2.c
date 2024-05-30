#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// �Ƕ����
#define LEN_MIN 15 
#define LEN_MAX 50
#define STM_MIN 0 
#define STM_MAX 5
#define PROB_MIN 10 
#define PROB_MAX 90
#define AGGRO_MIN 0 
#define AGGRO_MAX 5

// ������ ������ ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ���� ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int MDSm;
int length, MDSs, p;
int C = 0; int Z = 0; int M = 0; int T = 1; int Ca = 0; int Ma = 0;


int trainAndp(int *length, int *MDSs, int *p) { // ����, ������ ü��, Ȯ�� �Է�
    int lengthToF = 0, MDSsToF = 0, PToF = 0;
    while (!(lengthToF && MDSsToF && PToF)) {
        if (!lengthToF) {
            printf("train length(15~50)>> ");
            scanf_s("%d", length);
            if (*length < LEN_MIN || *length > LEN_MAX) {
                continue;
            }
            lengthToF = 1;
        }
        if (!MDSsToF) {
            printf("madongseok stamina(0~5)>> ");
            scanf_s("%d", MDSs);
            if (*MDSs < STM_MIN || *MDSs > STM_MAX) {
                continue;
            }
            MDSsToF = 1;
        }
        if (!PToF) {
            printf("percentile probability 'p' (10~90)>> ");
            scanf_s("%d", p);
            if (*p < PROB_MIN || *p > PROB_MAX) {
                continue;
            }
            PToF = 1;
        }
    }
    return 0;
}


int main(void) { // ����
    int length, MDSs, p;
    srand((unsigned int)time(NULL));

    trainAndp(&length, &MDSs, &p);
    train1st(length);
    gogo(length, p);
}

int train1st(int length) { // ù��° ���� ���
    for (int i = 0; i < 3; i++) {
        if (i == 0 || i == 2) {
            for (int i = 0; i < length; i++) {
                printf("#");
            }
        }
        else {
            printf("#");
            for (int i = 0; i < length - 7; i++) {
                printf(" ");
            }
            printf("C  ZM#");
        }
        printf("\n");
    }
    printf("\n");
}

int trainT(length, C, Z, M) { // �ݺ� ���� ���
    for (int i = 0; i < 3; i++) {
        if (i == 0 || i == 2) {
            for (int i = 0; i < length; i++) printf("#");
        }
        else {
            printf("#");
            for (int i = 1; i < C; i++) printf(" ");
            printf("C");
            for (int i = C + 1; i < Z; i++) printf(" ");
            printf("Z");
            for (int i = Z + 1; i < M; i++) printf(" ");
            printf("M");
            for (int i = 1; i <= length - M - 2; i++) printf(" ");
            printf("#");
        }
       printf("\n");
    }
    printf("\n");
}

int move(int Rc, int p, int Md) { // Ȯ�� �̵�
    if (rand() % 100 < p) {
        return Rc + Md;
    }
    return Rc;
}

int moveT(T, C, Z, Cz, Zz, Ca, Caz, Ma, Maz) { // �ù�,���� ����
    if (Cz == C) {
        if (AGGRO_MIN < Ca) {
            Ca--;
        }
        printf("C : stay %d (arrow: %d)\n", C, Ca);
    }
    else {
        if (AGGRO_MAX > Ca) {
            Ca++;
        }
        printf("C : move %d -> %d (arrow: %d -> %d)\n", Cz, C, Caz, Ca);
    }

    if (T % 2 == 0) {
        printf("Z : stay %d (cannot move)\n\n", Z);
    }
    else {
        if (Zz == Z) {
            printf("Z : stay %d\n\n", Z);
        }
        else {
            printf("Z : move %d -> %d\n\n", Zz, Z);
        }
    }
    return Ca;
}

int Mmove(M, Z) {
    int MDSmToF = 0;
    while (!(MDSmToF)) {
        if (!MDSmToF) {
            if (M == Z+1) {
                printf("madongseok move(0:stay)>> ");
                scanf_s("%d", &MDSm);
                if (MDSm != MOVE_STAY) {
                    continue;
                }
            }
            else {
                printf("madongseok move(0:stay, 1:left)>> ");
                scanf_s("%d", &MDSm);
                if (MDSm < MOVE_STAY || MDSm > MOVE_LEFT) {
                    continue;
                }
                if (MDSm == MOVE_LEFT) {
                    M--;
                }
            }
            MDSmToF = 1;
        }
    }
    return MDSm, M;
}

int gogo(length, p) { // �ù�, ����, ������ ������ ����, ���� ���� ���
    int C = length - 6; int Z = length - 3; int M = length - 2; int T = 1; int Ca = 0; int Ma = 0;

    while (1) {
        int Cz = C, Zz = Z, Caz = Ca, Maz = Ma;
        C = move(C, 100 - p, -1);
        if (T % 2 != 0) Z = move(Z, p, -1);
        trainT(length, C, Z, M);
        Ca = moveT(T, C, Z, Cz, Zz, Ca, Caz, Ma, Maz);

        MDSm, M = Mmove(M,Z);
        trainT(length, C, Z, M);


        if (C == 1) {
            printf("Ż��!\n");
            break;
        }
        if (C == Z - 1) {
            printf("����\n");
            break;
        }
        T++;
    }
    return 0;
}

