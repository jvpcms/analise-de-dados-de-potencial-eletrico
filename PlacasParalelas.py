# by jvpcms

import matplotlib.pyplot as plt


# class para pontos do Grid (x, y, v)
class Point:
    def __int__(self, x, y, v):
        self.x = x
        self.y = y
        self.v = v


# class para armazenar as propriedades de cada melhor reta (x, a, b)
class Lines:
    def __int__(self, x, a, b):
        self.x = x
        self.a = a
        self.b = b


# input points
file = open("data.txt", "r")
dataRaw = file.readlines()
file.close()

n = len(dataRaw)
nx = 8
ny = 11
X = [85, 60, 30, 10, -10, -30, -60, -85]
pts = []
lns = []

for i in range(n):

    ix = int(dataRaw[i][0:3])
    iy = int(dataRaw[i][4:7])
    iv = float(dataRaw[i][8:13])

    p = Point()
    p.x = ix
    p.y = iy
    p.v = iv

    pts.append(p)

# calcular a melhor reta V(y) para cada coordenada x
for i in range(nx):

    Y = V = 0.0
    denominator = numerator = 0.0

    for j in range(ny):
        Y += pts[i*ny + j].y / ny
        V += pts[i*ny + j].v / ny
    for j in range(ny):
        denominator += (pts[i*ny + j].y - Y)*(pts[i*ny + j].v - V)
        numerator += (pts[i*ny + j].y - Y)*(pts[i*ny + j].y - Y)

    m = denominator / numerator
    b = V - m*Y

    l = Lines()
    l.x = pts[i*ny].x
    l.a = m
    l.b = b

    lns.append(l)


# localizar pontos com mesmo potencial ao longo das retas e mostar o gráfico
for v in range(9, 0, -1):
    Y = []
    for i in range(nx):
        Y.append((v - lns[i].b) / lns[i].a)
    plt.plot(X, Y, label=f"U = {v}V")

plt.plot(150, 0)

plt.title("Linhas Equipotenciais (Placas Planas)")
plt.xlabel("Coodenada X (mm)")
plt.ylabel("Coordenada Y (mm)")
plt.legend()
plt.show()
