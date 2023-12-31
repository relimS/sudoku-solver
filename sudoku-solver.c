#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

uint8_t table[81] = { 0, 1, 2, 9, 10, 11, 18, 19, 20, 3, 4, 5, 12, 13, 14, 21, 22, 23, 6, 7, 8, 15, 16, 17, 24, 25, 26, 27, 28, 29, 36, 37, 38, 45, 46, 47, 30, 31, 32, 39, 40, 41, 48, 49, 50, 33, 34, 35, 42, 43, 44, 51, 52, 53, 54, 55, 56, 63, 64, 65, 72, 73, 74, 57, 58, 59, 66, 67, 68, 75, 76, 77, 60, 61, 62, 69, 70, 71, 78, 79, 80 };
uint8_t board[81];

bool solve(const uint8_t lk_i) {
    uint8_t i, j, stack[9], row, col, n, n2;
    bool ret;
    if (lk_i == 81) return true;
    n2 = lk_i % 9;
    if (board[table[lk_i]] != 0) {
        for (i = 0; i != n2; ++i) {
            if (board[table[lk_i]] == board[table[lk_i-i-1]]) break;
        }
        if (i == n2) return solve(lk_i+1);
        return false;
    }
    row = table[lk_i] / 9;
    col = table[lk_i] % 9;
    n = 0;
    for (i = 0; i != 9; ++i) {
        if (i == col || board[row*9+i] == 0) continue;
        for (j = 0; j != n; ++j) {
            if (board[row*9+i] == stack[j]) break; 
        }
        if (j == n) stack[n++] = board[row*9+i];
    }
    for (i = 0; i != 9; ++i) {
        if (i == row || board[i*9+col] == 0) continue;
        for (j = 0; j != n; ++j) {
            if (board[i*9+col] == stack[j]) break;
        }
        if (j == n) stack[n++] = board[i*9+col];
    }
    if (n == 9) return false;
    for (i = 1; i != 10; ++i) {
        for (j = 0; j != n; ++j) {
            if (i == stack[j]) break;
        }
        if (j != n) continue;
        for (j = 0; j != n2; ++j) {
            if (i == board[table[lk_i-j-1]]) break;
        }
        if (j != n2) continue;
        board[table[lk_i]] = i;
        ret = solve(lk_i+1);
        if (ret == true) return true;
    }
    board[table[lk_i]] = 0;
    return false;
}

int main(/*int argc, char *argv[]*/) {
    uint8_t i;
    int ret;
    clock_t start, end;
    
    // if (argc == 2 && (!strcmp("--help", argv[1]) || !strcmp("-help", argv[1]) || !strcmp("help", argv[1]) || !strcmp("-h", argv[1]) || !strcmp("h", argv[1]))) {
    //     puts("Currently does not exist (and probably never will).");
    //     return 0;
    // }
    puts("Input:");
    // scanf("%81s", board);
    for (i = 0; i != 81; ++i) {
        // board[i] -= 48;
        scanf("%hhu", board+i);
        if (board[i] > 10) {
            for (++i; i != 81; ++i) {
                scanf("%hhu", board);
                return 1;
            }
        }
    }
    puts("Solving");
    start = clock();
    ret = solve(0);
    end = clock();
    if (!ret) {
        puts("cannot find");
        goto r;
    }
    for (i = 0; i != 81; ++i) {
        printf("%hhu%c", board[i], (i % 9 == 8) ? '\n' : ' ');
    }
    r:
    printf("took %f\n", (float)(end-start)/CLOCKS_PER_SEC);
    return 0;
}