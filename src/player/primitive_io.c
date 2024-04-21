#include <board.h>
#include <io.h>
#include <player.h>
#include <player/primitive_io.h>
#include <sector.h>
#include <stdio.h>

FILE *playerin, *playerout;

static char buf[BUFSIZ];
static void display_state(BoardPtr board) {
    char *bp = buf;
    display_board(&bp, board);
    puts(buf);
}
static int parse_cell_ind(char **src, int *cell) {
    char this_char = **src;
    if (this_char < '1' || this_char > '9')
        return -1;
    *src += 1;
    *cell = this_char - '0';
    return 0;
}

static int fixed_sector(BoardPtr board, SectorInd sector, int *cell,
                        void *state) {
    char *bp = buf;
    display_state(board);
    if (feof(playerin)) {
        putchar('\n');
        printf("You've surrendered.\n");
        return 0;
    }
    dstcat(bp, "Please, input your move: ");
    display_sector_ind(&bp, sector);
    fputs(buf, playerout);
    fgets(buf, BUFSIZ, playerin);

    bp = buf;
    *cell = -1;
    parse_cell_ind(&bp, cell);
    return 1;
}

FixedSectorBrain primitive_io_fixed_sector() { return &fixed_sector; }

static int any_sector(BoardPtr board, SectorInd *sector, int *cell,
                      void *state) {
    char *bp = buf;
    display_state(board);
    if (feof(playerin)) {
        putchar('\n');
        printf("You've surrendered.\n");
        return 0;
    }
    dstcat(bp, "Please, input your move: ");
    fputs(buf, playerout);
    fgets(buf, BUFSIZ, playerin);
    bp = buf;
    *sector = InvalidSector;
    parse_sector_ind(&bp, sector);
    *cell = -1;
    parse_cell_ind(&bp, cell);
    return 1;
}

AnySectorBrain primitive_io_any_sector() { return &any_sector; }

PlayerBrain primitive_io_brain() {
    PlayerBrain brain;
    brain.fixed = primitive_io_fixed_sector();
    brain.any = primitive_io_any_sector();
    brain.state = NULL;
    brain.distructor = NULL;
    return brain;
}
