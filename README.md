#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// 2-2 피라미터
#define LEN_MIN 15 
#define LEN_MAX 50
#define STM_MIN 0 
#define STM_MAX 5
#define PROB_MIN 10 
#define PROB_MAX 90
#define AGGRO_MIN 0 
#define AGGRO_MAX 5

// 2-2 마동석 움직임 여부
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 2-2 좀비 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 2-2 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int MDSm;
int length, MDSs, p;
int C = 0; int Z = 0; int M = 0; int T = 1; int Ca = 0; int Ma = 0;


int trainAndp(int *length, int *MDSs, int *p) { // 2-1, 2-2 기차, 마동석 체력, 확률 입력
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


int main(void) { // 2-1 메인
    int length, MDSs, p;
    srand((unsigned int)time(NULL));

    trainAndp(&length, &MDSs, &p);
    train1st(length);
    gogo(length, p);
}

int train1st(int length) { // 2-1 첫 기차 출력
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

int trainT(length, C, Z, M) { // 2-1 반복 기차 출력
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

int move(int Rc, int p, int Md) { // 2-1 확률 이동
    if (rand() % 100 < p) {
        return Rc + Md;
    }
    return Rc;
}

int moveT(T, C, Z, Cz, Zz, Ca, Caz, Ma, Maz) { // 2-1, 2-2, 2-3 시민,좀비 상태
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

int Mmove(M, Z) { // 2-3 마동석 움직임 
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

int gogo(length, p) { // 2-1, 2-3 시민, 좀비 움직임 여부, 게임 승패 출력
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
            printf("탈출!\n");
            break;
        }
        if (C == Z - 1) {
            printf("실패\n");
            break;
        }
        T++;
    }
    return 0;
}
