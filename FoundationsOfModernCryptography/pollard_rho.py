def gcd(a,b):
    if b==0:
        return abs(a)
    else:
        return gcd(b,a%b)


def pollard_rho(n):
    f = lambda k: (k**2+1) % n
    x=2
    y=x
    i=1
    while 1:
        x=f(x)
        print('x is ' + str(x))
        y=f(f(y))
        print('y is ' + str(y) + " iteration " + str(i))
        i+=1
        g = gcd(x-y,n)
        print('g is ' + str(g) + "\n")
        if g>1 and g<n:
            print('in if 1')
            return g
        if x==y:
            print('in if 2')
            return None


print('Non trivial factor is ' + str(pollard_rho(323)))
print('gcd is ' + str(gcd(-21,323)))