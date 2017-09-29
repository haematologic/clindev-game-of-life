/**
 * generation.c
 *
 * Duncan Brian
 * @haematologic
 *
 * Prints generations of game of life for clinical dev challenge.
 */

#include <math.h>
#include <stdio.h>


const int size = 8;

int gen0[size*size] = {
    0, 0, 1, 1, 0, 0, 0, 1,
    0, 1, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 0, 1,
    0, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 1, 1, 0
};

int gen1[size*size];

void print_header(int cur)
{
    printf("Generation %d\n\n  ", cur);
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

struct RC lookup_rc(int pos, int s, int global_offset)
{
    int row; int col;
    row = floor(pos/s);
    col = (pos-row*s);
    struct RC rc = { row+global_offset, col+global_offset };
    return rc;
}

int lookup_pos(struct RC rc)
{
    return rc.row*size+rc.col;
}

int is_valid_rc(struct RC lookup)
{
    return 0<=lookup.row && lookup.row<size && 0<=lookup.col && lookup.col<size;
}

int count_neighbours(int pos, int *gen)
{
    struct RC rc = lookup_rc(pos, size, 0);
    int total;
    int ind;
    total = 0 - gen[pos];
    // printf("Pos %d = row %d, col %d\n", pos, rc.row, rc.col);
    for (int i = 0; i < 9; i++) {
        struct RC offsets = lookup_rc(i, 3, -1);
        struct RC lookup = { rc.row+offsets.row, rc.col+offsets.col };
        if (is_valid_rc(lookup))
        {
            ind = lookup_pos(lookup);
            total += gen[ind];
            // printf("%d, %d = %d\n", lookup.row, lookup.col, gen[ind]);
        }
    }
    // printf("Total: %d\n", total);
    return total;
}

int print_array(int *arr, int cur)
{
    print_header(cur);
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
    int res; int count;
    for (int i = 0; i < 64; i++)
    {
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
        // printf("(%d) %d [%d] -> %d , ", i, gen[i], count, res);
        gen1[i] = res;
    }
    // print_array(gen1);
    return 1;
}

int get_int(void)
{
    printf("Please give me a non-negative integer to find survival state: ");
    int n;
    scanf("%d", &n);

    if (n >= 0)
    {
        return n;
    }
    else
    {
        printf("You are not the Great Spirit so you lack the \
ability to reverse time in this universe.\n");
        return -1;
    }
}

int main(void)
{

    int *gen; int ok; int n;
    n = get_int()+1;
    if ( !n ) { return -1; }
    gen = gen0;

    for(int j = 0; j < n; j++ )
    {
        print_array(gen, j);
        ok = make_next_gen(gen);
        if (ok)
        {
            for (int i = 0; i < size*size; i++ )
            {
                gen[i] = gen1[i];
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
