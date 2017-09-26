
# coding: utf-8

# In[324]:

from math import floor

g0 = [[0,0,1,1,0,0,0,1],
      [0,1,1,1,0,0,1,1],
      [1,0,0,0,1,1,0,1],
      [0,1,1,0,1,1,1,1],
      [1,1,0,1,0,1,0,0],
      [1,0,1,0,1,1,1,0],
      [0,1,1,1,1,1,1,1],
      [1,0,1,0,0,1,1,0],
     ]

g1 = [[0,1,0,1,0,0,1,1],
      [0,1,0,0,0,1,0,1],
      [1,0,0,0,0,0,0,0],
      [0,0,1,0,0,0,0,1],
      [1,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,1],
      [0,0,1,0,0,0,0,1],
     ]

c = []
c.append([y for x in g0 for y in x])
c.append([y for x in g1 for y in x])

size = len(c[0])**0.5
square_size = int(size) if size % 1 == 0 else False
square_size

pos = 63

def lookup_rc(pos, size=square_size, offset=0):
    row = pos//size
    col = pos-row*size
    return row+offset, col+offset

def lookup_pos(r, c, size=square_size):
    return r*size+c

def is_valid_rc(r, c, size=square_size):
    return all(0<=x<size for x in (r,c))

def count_neighbours(pos, gen):
    r, c = lookup_rc(pos)
#     print('Position {} = Row {}, Col {}\n'.format(pos, r, c))
    total = 0 - gen[pos]
    for x in range(9):
        r_offset, c_offset = lookup_rc(x, 3, -1)
        r_lookup, c_lookup = r + r_offset, c + c_offset
        if is_valid_rc(r_lookup, c_lookup):
            ind = lookup_pos(r_lookup, c_lookup)
            total += gen[ind]
    return total

def make_next_generation(gen):
    next_gen = []
    for i, cell in enumerate(gen):
        res = 0
        count = count_neighbours(i, gen)
        if cell:
            if 2<=count<4:
                res = 1
        else:
            if count == 3:
                res =1
        next_gen.append(res)
    return next_gen

def print_gen(gen, size=square_size):
    for a in range(size):
        row = ' '.join(list(map(lambda x: {0:' ', 1:'*'}.get(x), gen[8*a: 8*(a+1)])))
        print('{} {}'.format(a+1, row))
    print('\n')
        

pos = lookup_pos(6,4)
# print(pos)
count_neighbours(pos, c[0])

gen = c[0]

def main(gens):
    gen = c[0]
    for j in range(gens):
        print('Gen {}\n'.format(j))
        print('  {}'.format(' '.join([str(x+1) for x in range(8)])))
        print_gen(gen)
        gen = make_next_generation(gen)
    
main(10)


