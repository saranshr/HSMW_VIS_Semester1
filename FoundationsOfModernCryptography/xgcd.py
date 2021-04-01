def sgn(x):
    if x>0: return 1
    if x<0: return -1
    return 0

def xgcd(a,b):
    if b==0:
        return abs(a), sgn(a), 0
    q = a // b
    r = a % b
    d, bb, rr = xgcd(b,r)
    return d, rr, bb-q*rr


print(xgcd(13,2436))
