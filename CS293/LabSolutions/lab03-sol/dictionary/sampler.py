#!/usr/bin/python3
#

import string
import random

NUM_WORDS = 10000
MAXIMUM_WORD_LENGTH = 32
FILE_NAME = "sample.txt"

def convert(s):
    new = ""
    for x in s:
        new += x
    return new


with open(FILE_NAME, "w") as file:
    file.write('0\n')
    for i in range(NUM_WORDS):
        x = random.randint(1, MAXIMUM_WORD_LENGTH)
        word = []
        for j in range(x):
            word.append(chr(random.randint(97, 122)))
        st = convert(word)
        file.write(st)
        file.write("\n")
