n = int(input ())
a = n % 10
b = n // 10 % 10
c = n // 100 % 10
d = n // 1000 % 10
m = 1000 * a + 100 * b + 10 * c + d
print (n - m + 1)