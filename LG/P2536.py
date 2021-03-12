# ! ! ! ! ! ! WARNING ! ! ! ! ! ! #
# ! ! TimeLimitExceeded Code ! ! #
import re

m = re.compile(input().replace("*", ".*").replace("?", "."))
n = int(input().replace(" ", ''))
Ss = 0
for i in range(0, n):
    s = input()
    if m.match(s):
        Ss += 1
print(n - Ss)
