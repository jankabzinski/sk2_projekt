import os
from PIL import Image
import linecache as lc
board = Image.open('chessboard.jpg')
pieces = os.listdir(path='img')
pieces = ['img\\' + p for p in pieces]

B = Image.open(pieces[0])
b = Image.open(pieces[1])
K = Image.open(pieces[2])
k = Image.open(pieces[3])
N = Image.open(pieces[4])
n = Image.open(pieces[5])
P = Image.open(pieces[6])
p = Image.open(pieces[7])
Q = Image.open(pieces[8])
q = Image.open(pieces[9])
R = Image.open(pieces[10])
r = Image.open(pieces[11])
s={'B': B, 'b': b, 'K' : K, 'k':k, 'N': N, 'n': n, 'P' : P, 'p' : p, 'Q' : Q, 'q' : q,
'R' : R, 'r' : r }

for i in range(0,69*8,69):
    gfg = lc.getline('out.txt', i//69 + 1)
    gfg = gfg[1:]
    for j in range(0,69*8,69):
        if gfg[j//69] != ' ':
            board.paste(s[gfg[j//69]], (2+j,5+i), mask=s[gfg[j//69]]) #2 i 5, co 69
board.show()