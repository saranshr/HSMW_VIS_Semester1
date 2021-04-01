# we want to calculate x = log_g(a) (mod p) where a is a random number less than p, p is a prime and g is a primitive root of p
# x would be between 0 and p-2
# implementation will be done via the baby step giant step algorithm --> Exponoential running time

import math


def sgn(x):
    if x > 0:
        return 1
    if x < 0:
        return -1
    return 0


def xgcd(a, b):                              # Extendend Euclidean algorithm
    if b == 0:
        return abs(a), sgn(a), 0
    q = a // b
    r = a % b
    d, bb, rr = xgcd(b, r)
    return d, rr, bb-q*rr


def pot(a, n):                               # fast exponentiation
    if n == 0:
        return 1
    n = bin(n)[2:]
    result = 1
    for i in range(len(n)):
        result *= result
        if n[i] == '1':
            result *= a
    return result


def discrete_log(a, p, g):
    w = math.ceil(math.sqrt(p-1))
    # gtow = g**w % p                         # should actually use fast exponentiation
    gtow = pot(g, w) % p
    # print('gtow is ' + str(gtow))
    # to calculate g^-1 mod p --> we can use the xgcd since g^-1 mod p = 1 --> since p is prime, gcd(a number, p) != 1
    gtoMinus1 = xgcd(g, p)
    gtoMinus1 = list(gtoMinus1)[1]          # take the 'rr' value, as this is the inverse of g and the xgcd returns 3 arguments
    while gtoMinus1 < 0:
        gtoMinus1 += p                      # inverse mod needs to be between 0 and p
    # print('gtoMinus1 is ' + str(gtoMinus1))
    B = [None]*(w)                          # initialize Baby step list
    G = [None]*(w)                          # initialize Giant step list
    #print('w is ' + str(w))
    for r in range(w):
        # B[r] = a*(gtoMinus1**r) % p         # should actually use fast exponentiation
        B[r] = a*(pot(gtoMinus1, r)) % p
        # G[q] = gtow**q % p                  # should actually use fast exponentiation
        G[r] = pot(gtow, r) % p
    return w, B, G


x = [None]*10
for a in range(1, 11):
    # Example solve x=log_2(a) mod 101 for a values from 1 to 10
    w, B, G = discrete_log(a, 101, 2)
    both = set(B).intersection(G)
    rem = [B.index(x) for x in both]
    quot = [G.index(x) for x in both]
    x[a-1] = quot[0]*w + rem[0]

print('Answer is ', x)