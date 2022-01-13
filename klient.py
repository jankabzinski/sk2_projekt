import os
from PIL import Image
import socket

board = Image.open('chessboard.jpg')
pieces = os.listdir(path='img')
pieces = ['img//' + p for p in pieces]


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
s = {'B': B, 'b': b, 'K': K, 'k': k, 'N': N, 'n': n, 'P': P, 'p': p, 'Q': Q, 'q': q,
     'R': R, 'r': r}

adres = input("Podaj adres serwera\n")
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((adres, 1234))

while True:
    board = Image.open('chessboard.jpg')
    data = []
    while not data:
        data = sock.recv(200)

    komunikat = []
    for item in data.decode().split("\n"):
        komunikat = item
        break

    data = str(data)
    data = data[2:]
    if komunikat == "Nieprawidlowy ruch. Sprobuj ponownie":
        print(komunikat)
    elif (komunikat == "Zawodnik grajacy bialymi rozlaczyl sie, wygrales. Gratulacje, ale nie do konca" or
          komunikat == "Zawodnik grajacy czarnymi rozlaczyl sie, wygrales. Gratulacje, ale nie do konca" or
          komunikat == "STALEMATE!!!" or komunikat == "CHECKMATE!!!"):
        print(komunikat)
        break
    else:
        last_position = data

    print(last_position)

    for i in range(0, 69 * 8, 69):
        line = last_position[i // 69 * 11:i // 69 * 11 + 11]
        line = line[1:9]
        for j in range(0, 69 * 8, 69):
            if line[j // 69] != ' ':
                board.paste(s[line[j // 69]], (2 + j, 5 + i), mask=s[line[j // 69]])  # 2 i 5, co 69

    board.show()
    move = input("Wprowadź ruch: format pole-pole lub O-O/O-O-O\n")
    move += '!'
    sock.send(move.encode())
