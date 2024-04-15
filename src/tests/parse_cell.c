#include <board.h>

#include <stdio.h>

#define TEST_PARSE(str, cell)                                                  \
    {                                                                          \
        Cell c = parse_cell(str);                                              \
        if (c != cell) {                                                       \
            fprintf(stderr, "Failed test for %s\n", str);                      \
            errf++;                                                            \
        }                                                                      \
    }

int main() {
    int errf = 0;

    init_boards();
    TEST_PARSE("A0", NullCell);

    TEST_PARSE("A1", A_1);
    TEST_PARSE("A2", A_2);
    TEST_PARSE("A3", A_3);
    TEST_PARSE("A4", A_4);
    TEST_PARSE("A5", A_5);
    TEST_PARSE("A6", A_6);
    TEST_PARSE("A7", A_7);
    TEST_PARSE("A8", A_8);
    TEST_PARSE("A9", A_9);

    TEST_PARSE("T1", T_1);
    TEST_PARSE("T5", T_5);
    TEST_PARSE("T9", T_9);

    return errf;
}
