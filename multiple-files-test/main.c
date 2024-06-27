#include <stdio.h>
#include "add.c"

int main() {
    int res = add(12, 4);

    printf("12 + 4 = %d", res);

    return 0;
}
