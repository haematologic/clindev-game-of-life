/**
 * generation.c
 *
 * Duncan Brian
 * @haematologic 
 *
 * Prints generations of game of life for clinical dev challenge.
 */

#include <stdio.h>
#include <math.h>

#define SIZE 8

int gen0[SIZE*SIZE] = {
    0, 0, 1, 1, 0, 0, 0, 1,
    0, 1, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 0, 1,
    0, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 1, 1, 0
};
int gen1[SIZE*SIZE];

void print_header(void)
{
    printf("  ");
    fflush( stdout );
    for(int i = 0; i < 8; i++) {
        printf("  %d", i+1);
        fflush( stdout );
    }
    printf("\n\n");
}

struct RC {
    int row;
    int col;
};

struct RC lookup_rc(int pos, int size, int global_offset)
{
    int row; int col;
    row = floor(pos/size);
    col = (pos-row*size);
    struct RC rc = { row+global_offset, col+global_offset };
    return rc;
}

int lookup_pos(struct RC rc)
{
    return rc.row*SIZE+rc.col;
}

int is_valid_rc(struct RC lookup)
{
    int s;
    s = SIZE;
    return 0<=lookup.row && lookup.row<s && 0<=lookup.col && lookup.col<s;
}

int count_neighbours(int pos, int *gen)
{
    struct RC rc = lookup_rc(pos, SIZE, 0);
    int total;
    total = 0 - gen[pos];
    // printf("Pos %d = row %d, col %d\n", pos, rc.row, rc.col);
    for (int i = 0; i < 9; i++) {
        struct RC offsets = lookup_rc(i, 3, -1);
        struct RC lookup = { rc.row+offsets.row, rc.col+offsets.col };
        if (is_valid_rc(lookup))
        {
            int ind;
            ind = lookup_pos(lookup);
            total += gen[ind];
            // printf("%d, %d = %d\n", lookup.row, lookup.col, gen[ind]);
        }
    }
    // printf("Total: %d\n", total);
    return total;
}

int print_array(int *arr)
{
    print_header();
    for(int i = 0; i < 8; i++) {
        printf("%d ", i+1);
        fflush( stdout );
        char c;
        for(int j = 0; j < 8; j++) {
            c = ' ';
            if (arr[i*8+j] == 1)
                c = '*';
            printf("  %c", c);
            fflush( stdout );
            }
        printf("\n");
    printf("\n");
    }
    return 0;
}

int make_next_gen(int *gen)
{
    for (int i = 0; i < 64; i++)
    {
        int res; int count;
        res = 0;
        count = count_neighbours(i, gen);
        // printf("%d", gen[i]);
        if (gen[i])
        {
            if (2<=count && count<4) { res = 1; }
        }
        else
        {
            if (count == 3) { res = 1; }
        }
        gen1[i] = res;
    }
    // print_array(gen1);
    return 1;
}

int main(void)
{
    int *gen; int gens; int ok;
    gens = 3;
    gen = gen0;

    for(int j = 0; j < gens; j++ )
    {
        print_array(gen);
        ok = make_next_gen(gen);
        if (ok)
        {
            gen = gen1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
