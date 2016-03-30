
from __future__ import print_function

import random

notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

for _ in range(1000):
    M = random.randint(1, 80)
    T = random.randint(1, M)

    print(M, T)

    for _ in range(M):
        i = random.randint(0, len(notes) - 1)
        print(notes[i], end=' ')

    print('')

    for _ in range(T):
        i = random.randint(0, len(notes) - 1)
        print(notes[i], end=' ')

    print('')

print('0 0')