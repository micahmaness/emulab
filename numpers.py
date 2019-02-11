# Micah Maness
# I typed all of my own code

import sys
import random

def generateNumber():
    return random.randint(0,3);

if __name__ == "__main__":
    size = int(sys.argv[1])
    p = open("nums.txt", "w+")
    for x in range(0, size):
        num = generateNumber()
        p.write(str(num))
    p.close();