# smallbloom
Small Bloom Filter for eventual use on a microcontroller with small messages

Example output:

    Adding 80ec791f24 YES
    Adding 1ef8454091 YES
    Adding e14ae31389 YES
    Adding 09e3b83f31 YES
    Adding 726da7214f YES
    All Tested: 245
    False Positives: 0

Unfortunatly there are some cases where similar values collide.  This is
much more undesirable than random ones colliding.

    Adding c43c22ac92 YES
    Adding c43c22ac93 YES
    Adding c43c22ac94 YES
    Adding c43c22ac95 YES
    Adding c43c22ac96 YES
    c43c22ac97 YES
    c43c22aca7 YES
    c43c22acb7 YES
    c43c22acc7 YES
    All Tested: 245
    False Positives: 4

