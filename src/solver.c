#include <string.h>
#include "solver.h"

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN]; 
    int  word_count;                     
    char letters[UNIQ_LET];                    
    int  letter_count;
    int  digit_of[LET_IN_ALF];                   
} Puzzle;

static int parse_puzzle(const char *input, Puzzle *p){
    char cur[MAX_WORD_LEN];
    int  len = 0;
    int  seen[LET_IN_ALF] = {0};
    int  eq_index = -1;

    p->word_count = 0;
    p->letter_count = 0;

    for (const char *s = input;; s++) {
        char c = *s;

        if (c >= 'A' && c <= 'Z') {
            if (len >= MAX_WORD_LEN - 1) return -1;
            cur[len++] = c;
            if (!seen[c - 'A']) {
                if (p->letter_count >= UNIQ_LET) return -1;
                seen[c - 'A'] = 1;
                p->letters[p->letter_count++] = c;
            }
            continue;
        }

        if (c != '\0' && c != ' ' && c != '\t' && c != '+' && c != '=')
            return -1; 

        if (len > 0) {
            if (p->word_count >= MAX_WORDS) return -1;
            cur[len] = '\0';
            strcpy(p->words[p->word_count++], cur);
            len = 0;
        }

        if (c == '=') {
            if (eq_index != -1) return -1;       
            eq_index = p->word_count;            
        }
        if (c == '\0') break;
    }

    if (p->word_count < 3) return -1;
    if (eq_index != p->word_count - 1) return -1;
    return 0;
}


static long long word_value(const char *w, const int digit_of[26]){
    long long value = 0;
    for (char *c = w; *c; c++){
        value = value * 10 + digit_of[*c - 'A'];
    }
    return value;
}

static int check(const Puzzle *p){
    for (int i = 0; i < p->word_count; i++){
        if (strlen(p->words[i]) > 1 && p->digit_of[p->words[i][0] - 'A'] == 0)
            return 0;
    }
    long long sum = 0;
    for (int i = 0; i < p->word_count - 1; p++){
        sum += word_value(p->words[i], p->digit_of);
    }
    return sum == word_value(p->words[p->word_count - 1], p->digit_of);
}

static int search(Puzzle *p, int idx, int used[10]){
    if (idx == p->letter_count)
        return check(*p);

    int li = p->letters[idx] - 'A';
    for (int d = 0; d < 10; d++) {
        if (used[d]) continue;
        used[d] = 1;
        p->digit_of[li] = d;
        if (search(p, idx + 1, used)) return 1;
        used[d] = 0;
    }
    p->digit_of[li] = -1;
    return 0;
    
}
static int build_output(const char *input, const Puzzle *p, char *out, size_t out_size){
    size_t n = 0;
    for (const char *s = input; *s; s++) {
        if (n + 1 >= out_size) return -1;
        if (*s >= 'A' && *s <= 'Z')
            out[n++] = (char)('0' + p->digit_of[*s - 'A']);
        else
            out[n++] = *s;
    }
    if (n >= out_size) return -1;
    out[n] = '\0';
    return 0;
}

int solve_puzzle(const char *input, char *out, size_t out_size){
    Puzzle p;
    int used[10] = {};

    for (int i = 0; i < LET_IN_ALF; i++) p.digit_of[i] = -1;
    if (parse_puzzle(input, &p) != 0) return -1;
    if (!search(&p, 0, used)) return 0;
    if (build_output(input, &p, out, out_size) != 0) return -1;
    return 1;
}