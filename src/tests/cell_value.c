#include <board.h>

#include <stdio.h>

#define TEST_CELL_FROM(sect, digi, cell)                                       \
    {                                                                          \
        Cell c = from_sector_num(sect, digi);                                  \
        if (c != cell) {                                                       \
            fprintf(stderr,                                                    \
                    "Error for sector %d, digi %d. Expected %d, got %d\n",     \
                    sect, digi, cell, c);                                      \
            ++errors;                                                          \
        }                                                                      \
    }

int main() {
    int errors = 0;

    TEST_CELL_FROM(A, 'e', NullCell);

    TEST_CELL_FROM(A, '1', A_1);
    TEST_CELL_FROM(A, '2', A_2);

    if (errors) {
        fprintf(stderr, "Test had failed, %d errors\n", errors);
        return errors;
    }
}
