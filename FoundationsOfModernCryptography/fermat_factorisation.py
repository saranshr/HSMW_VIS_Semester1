import math

def isSquare(a):
    if a//math.sqrt(a) == math.sqrt(a):
        return True

def fermat_factor(n):
    rootn = math.floor(math.sqrt(n))
    i=1
    while True:
        t = rootn + i
        i+=1
        if isSquare(t**2 - n):
            return int(math.sqrt(t**2 - n))


print('factor by Fermat\'s method is ' + str(fermat_factor(200819)))



