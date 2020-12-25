#include <stdio.h>
#include "tokenize.h"
#include "parse.h"
#include "exec.h"

#define MAX_TEXT_LEN 10000

int get_text(char *buf, int max, FILE *f) {
    char c; int i;
    for (i = 0; (i < max - 1) && ((c = getc(f)) != EOF); i++) {
        buf[i] = c;
    }
    buf[i] = '\0';
    return i - 1;
}

void print_result(Root *root) {
    Node *child;
    for (int i = 0; i < root->node.children->length; i++) {
        child = list_get(root->node.children, i);
        if (child->type == NODE_INT) {
            printf("%d\n", ((Int*)child)->val);
        }
        else if (child->type == NODE_STR) {
            printf("%s\n", ((Str*)child)->val);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *f;
    char text[MAX_TEXT_LEN];

    if (argc > 1) {
        f = fopen(argv[1], "r");
        if (!f) {
            printf("could not open file %s\n", argv[1]);
            return 0;
        }
    } else {
        f = stdin;
    }


    get_text(text, MAX_TEXT_LEN, f);
    List *tokens = tokenize(text);
    Root *root = parse(tokens);
    exec(root);
    print_result(root);

    return 0;
}