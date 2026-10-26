#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/solver.h"

static int verify(const char *in, const char *out) {
    int map[26], rev[10];
    memset(map, -1, sizeof(map));
    memset(rev, -1, sizeof(rev));

    if (strlen(in) != strlen(out)) return 0;

    for (size_t i = 0; in[i]; i++) {
        if (in[i] >= 'A' && in[i] <= 'Z') {
            int l = in[i] - 'A', d = out[i] - '0';
            if (d < 0 || d > 9) return 0;
            if (map[l] != -1 && map[l] != d) return 0;
            if (rev[d] != -1 && rev[d] != l) return 0;
            map[l] = d;
            rev[d] = l;
        } else if (in[i] != out[i]) {
            return 0;
        }
    }

    long long nums[MAX_WORDS];
    int n = 0;
    const char *s = out;
    while (*s) {
        if (*s >= '0' && *s <= '9') {
            const char *start = s;
            long long v = 0;
            while (*s >= '0' && *s <= '9') v = v * 10 + (*s++ - '0');
            if (s - start > 1 && *start == '0') return 0; 
            if (n >= MAX_WORDS) return 0;
            nums[n++] = v;
        } else {
            s++;
        }
    }
    if (n < 3) return 0;

    long long sum = 0;
    for (int i = 0; i < n - 1; i++) sum += nums[i];
    return sum == nums[n - 1];
}

static const char *cases[] = {
    "SO + MANY = MORE",
    "I + DID = TOO",
    "AM + PM = DAY",
    "SANTA + CLAUS = GIFTS",
    "WINTER + WINDS = SNOWS",
    "BE + BE = MOO",
    "SEND + MORE = MONEY",
    "BIG + CAT = LION",
    "ELEVEN + NINE + FIVE + FIVE = THIRTY",
    "BASE + BALL = GAMES",
    "FOUR + FIVE = NINE",

};

int main(void) {
    int failed = 0;
    int total = (int)(sizeof(cases) / sizeof(cases[0]));

    for (int i = 0; i < total; i++) {
        char out[256];
        int r = solve_puzzle(cases[i], out, sizeof(out));
        if (r == 1 && verify(cases[i], out)) {
            printf("[ OK ] %s -> %s\n", cases[i], out);
        } else {
            printf("[FAIL] %s (r=%d, out=%s)\n", cases[i], r, r == 1 ? out : "-");
            failed++;
        }
    }

    char out[64];
    if (solve_puzzle("A + B", out, sizeof(out)) != -1) { puts("Ошибка, нет '='"); failed++; }
    if (solve_puzzle("a + b = c", out, sizeof(out)) != -1) { puts("Ошибка, нижний регистр"); failed++; }

    printf("\n%s: %d/%d\n", failed ? "FAILED" : "PASSED", total - failed, total);
    return failed ? 1 : 0;
}