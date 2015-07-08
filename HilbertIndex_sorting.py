import numpy as np
import scipy.spatial.distance as ssd
import time
import math
from operator import itemgetter, attrgetter
import fileinput

def read_data(fn):
    with open(fn) as f:
        raw_data = np.loadtxt(f, delimiter=' ', dtype="float",skiprows=0, usecols=None)

    data = []

    for row in raw_data:
        data.append(row)

    return np.array(data).tolist()

def extract_data(fn):
	return read_data(fn)

def sorting(fn, pos):
	points = extract_data(fn)
	points = sorted(points, key=itemgetter(pos))
	return points

# sort the Hilbert curve index values
def printing():
	j = 0;
	points = sorting("HIndexO/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexO/cali-HIndex-sorted.txt", 'w')
	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingN90():
	j = 0
	points = sorting("HIndexN90/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexN90/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingP90():
	j = 0
	points = sorting("HIndexP90/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexP90/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printing180():
	j = 0
	points = sorting("HIndex180/cali-HilbertIndex.txt", 4)
	outfile = open("HIndex180/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingTR():
	j = 0
	points = sorting("HIndexTR/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexTR/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingTL():
	j = 0
	points = sorting("HIndexTL/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexTL/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingBR():
	j = 0
	points = sorting("HIndexBR/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexBR/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

def printingBL():
	j = 0
	points = sorting("HIndexBL/cali-HilbertIndex.txt", 4)
	outfile = open("HIndexBL/cali-HIndex-sorted.txt", 'w')

	for point in points:
		j += 1
		point.append(j)

	#points = sorted(points, key=itemgetter(0))

	for point in points:
		for i in range(0,4):
			outfile.write(str(point[i]) + " ")
		outfile.write(str(point[4]) + "\n")	

	outfile.close()

printing()
printingN90()
printingP90()
printing180()
printingBL()
printingTL()
printingBR()
printingTR()