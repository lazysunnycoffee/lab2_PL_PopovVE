#include <string.h>
#include <stdio.h>
#include "solver.h"

int solve_and_print(const char *line){
    char out[256];
    int solve = solve_puzzle(line, out, sizeof(line))
    if (solve == 1){
        printf("%s\n", out);
        return 0;
    }
    if (solve == 0) fprinf(stderr, "Решение не найдено: %s\n", line);
    else fprinf(stderr, "Прочие ошибки: %s\n", line);
    return 1;
}

int main(int argc, char **argv){
    // 1 mode
    if (argc >= 2) return solve_and_print(argv[1]);

    // 2 mode
    char buf[256];
    int flag = 0;
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (buf[0] == '\0') continue;
        if (solve_and_print(buf) != 0) flag = 1;
    }
    return flag;
}
// Запуск: ./solver "SEND + MORE = MONEY" или echo "BE + BE = MOO" | ./solver.