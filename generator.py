#!/usr/bin/env python

import sys
import random
import string


def main(output_file, lines_count, max_line_length):
    with open(output_file, 'w') as f:
        for _ in xrange(lines_count):
            line_length = random.randint(1, max_line_length)
            str = ''.join(random.choice(string.ascii_letters)
                          for _ in xrange(line_length))
            f.write(str)
            f.write('\n')


if __name__ == '__main__':
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))
