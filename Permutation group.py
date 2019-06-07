#刘熙达 57117232
#r1=2,r2=3,r3=2
g=['A','2','3','4','5','6','7','8','9','10','J','Q','K']
r1=2
r2=3
r3=2
def g1():
    global g
    tmp=[]
    Tlist=[9,11,0,4,1,5,12,2,7,8,6,10,3]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g=tmp

def g2():
    global g
    tmp=[]
    Tlist=[2,5,6,0,9,12,3,1,10,11,8,4,7]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g=tmp

def g3():
    global g
    tmp=[]
    Tlist=[3,0,2,12,10,9,5,11,7,8,4,6,1]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g=tmp

def inverse_g1():
    global g
    tmp = []
    Tlist = [2, 4, 7, 12, 3, 5, 10, 8, 9, 0, 11, 1, 6]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g = tmp
def inverse_g2():
    global g
    tmp = []
    Tlist = [3, 7, 0, 6, 11, 1, 2, 12, 10, 4, 8, 9, 5]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g = tmp
def inverse_g3():
    global g
    tmp = []
    Tlist = [1, 12, 2, 0, 10, 6, 11, 8, 9, 5, 4, 7, 3]
    for i in range(13):
        tmp.append(g[Tlist[i]])
    g = tmp

def permutation_op(r1=0,r2=0,r3=0):
    for i in range(r1):
        g1()
    for i in range(r2):
        g2()
    for i in range(r3):
        g3()

def inverse_permutation_op(r1=0,r2=0,r3=0):
    for i in range(r3):
        inverse_g3()
    for i in range(r2):
        inverse_g2()
    for i in range(r1):
        inverse_g1()

print("初始G:",g)
permutation_op(r1,r2,r3)
print("按照r1=%u,r2=%u,r3=%u置换后："%(r1,r2,r3),g)
inverse_permutation_op(r1,r2,r3)
print("经过r3=%u,r2=%u,r1=%u的顺序逆置换后复原得到G:"%(r3,r2,r1),g)