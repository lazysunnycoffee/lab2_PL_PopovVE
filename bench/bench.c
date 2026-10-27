#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/solver.h"

static const char *puzzles[] = {
    "SO + MANY = MORE",
    "I + DID = TOO",
    "AM + PM = DAY",
    "BE + BE = MOO",
    "SEND + MORE = MONEY",
    "BIG + CAT = LION",
    "ELEVEN + NINE + FIVE + FIVE = THIRTY",
    "BASE + BALL = GAMES",
    "FOUR + FIVE = NINE",
};

static int count_letters(const char *s) {
    int seen[26] = {0}, n = 0;
    for (; *s; s++)
        if (*s >= 'A' && *s <= 'Z' && !seen[*s - 'A']) { seen[*s - 'A'] = 1; n++; }
    return n;
}

static double now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

int main(int argc, char **argv) {
    int runs = (argc >= 2) ? atoi(argv[1]) : 5;
    if (runs < 1) runs = 1;

    printf("puzzle,letters,runs,min_ms,avg_ms\n");

    for (size_t i = 0; i < sizeof(puzzles) / sizeof(puzzles[0]); i++) {
        double min = 1e18, total = 0;
        char out[256];

        for (int r = 0; r < runs; r++) {
            double t0 = now_ms();
            int res = solve_puzzle(puzzles[i], out, sizeof(out));
            double dt = now_ms() - t0;
            if (res != 1) { fprintf(stderr, "не решён: %s\n", puzzles[i]); return 1; }
            if (dt < min) min = dt;
            total += dt;
        }
        printf("\"%s\",%d,%d,%.3f,%.3f\n",
               puzzles[i], count_letters(puzzles[i]), runs, min, total / runs);
    }
    return 0;
}