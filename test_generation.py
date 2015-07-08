import random
import math
from operator import itemgetter, attrgetter
import fileinput
import numpy as np

testfile = "Test/test10.txt"

def read_data(fn):
    with open(fn) as f:
        raw_data = np.loadtxt(f, delimiter=' ', dtype="float",skiprows=0, usecols=None)

    data = []

    for row in raw_data:
        data.append(row)

    return np.array(data).tolist()

def random_index(number, volumn):
    return random.sample(xrange(number), volumn)

def test_generation(fn):
    points = read_data("cali-id.txt")
    indexes = random_index(104770, 2000)

    test = open(fn, 'w')

    for index in indexes:
        for i in range(0,2):
            test.write(str(points[index][i]) + " ")
        test.write(str(points[index][2])  + "\n")

    test.close()

def khonglienquan(fn):
    points = read_data(testfile)
    test = open(fn, 'w')
    for point in points:
        test.write(str(point[0]) + " ")
        test.write(str(point[1]) + '\n')
    test.close()

#test_generation(testfile)
khonglienquan("test1.txt")