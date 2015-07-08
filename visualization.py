import matplotlib.pyplot as plt
import numpy as np
import scipy.spatial.distance as ssd
import time
import math
import fileinput

def read_data(fn):
    with open(fn) as f:
        raw_data = np.loadtxt(f, delimiter=' ', dtype="float",skiprows=0, usecols=None)

    data = []

    for row in raw_data:
        data.append(row)

    return np.array(data).tolist()

def find_max_size_index(fn):
	points = read_data(fn)
	pois = [points]
	max_point = [0,0]
	maxx = 0
	i = 0
	for point in pois:
		point.sort()
		if point[len(point)-1] > maxx:
			maxx = point[len(point)-1]
			max_point[0] = i
			max_point[1] = maxx
		i += 1

	return max_point

def find_max_size_coor(fn, max_point):
	points = read_data(fn)
	pois = [points]
	poi = pois[max_point[0]]
	x, y = poi[0], poi[1]
	return {'x':x, 'y':y}

def draw(fn, x, y):
	plt.axis([-130.0, -110.0, 30.0, 50])
	points = read_data(fn)
	for point in points:
		if point[0] == x and point[1] == y:
			plt.plot([point[0]], [point[1]], 'o', color='#000000')
		else:
			plt.plot([point[0]], [point[1]], '^', color='#ffcccc')
	plt.show()

# def draw(fn):
# 	plt.axis([500, 1024, 100, 600])
# 	points = read_data(fn)
# 	i = 1
# 	for point in points:
# 		if i%161 == 1:
# 			plt.plot([point[0]], [point[1]], 'o', color='#000000')
# 		elif i <= 161:
# 			plt.plot([point[0]], [point[1]], 'o', color='#ffcccc') #hong nhat
# 		elif i<=161*2:
# 			plt.plot([point[0]], [point[1]], 'o', color='#a8f0b6') #xanh la nhat
# 		elif i<=161*3:
# 			plt.plot([point[0]], [point[1]], 'o', color='#a3bbe6') #xanh duong nhat
# 		elif i<=161*4:
# 			plt.plot([point[0]], [point[1]], 'o', color='#4f8f5b') #xanh la dam
# 		elif i<=161*5:
# 			plt.plot([point[0]], [point[1]], 'o', color='#dff29b') #vang nhat
# 		elif i<=161*6:
# 			plt.plot([point[0]], [point[1]], 'o', color='#f2b48d') #vang cam nhat
# 		elif i<=161*7:
# 			plt.plot([point[0]], [point[1]], 'o', color='#9c74b3') #tim
# 		elif i<=161*8:
# 			plt.plot([point[0]], [point[1]], 'o', color='#476096') #xanh duong dam
# 		i += 1
# 	plt.show()

max_point = find_max_size_index("test_result.txt")
max_coors = find_max_size_coor("test.txt", max_point)
draw("cali-id.txt", max_coors['x'], max_coors['y'])