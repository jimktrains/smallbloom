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

There are some collisions, but they're not for contigigous values and under
1% even upwards of 11 entries in the table

    Adding 0c3d54d712 YES
    Adding 0c3d54f754 YES
    Adding 0c3d54ee14 YES
    Adding 0c3d54d713 YES
    Adding 0c3d54d714 YES
    Adding 0c3d54fe14 YES
    Adding d7b95ebbe7 YES
    Adding 3f39e6ebd3 YES
    Adding 3f39e6ebde YES
    Adding 3f39e6ebff YES
    Adding 3f34e6ebdf YES
    774f35e666 YES
    91e14ae313 YES
    All Tested: 215
    False Positives: 2

