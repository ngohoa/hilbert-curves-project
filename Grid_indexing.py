import numpy as np
import scipy.spatial.distance as ssd
import time
import math
import fileinput

order = 1024

def read_data(fn):
    ""
    with open(fn) as f:
        raw_data = np.loadtxt(f, delimiter=' ', dtype="float",skiprows=0, usecols=None)

    data = []

    for row in raw_data:
        data.append(row[:-1])

    return np.array(data).tolist()

def extract_data():
	return read_data("cali-id.txt")

def bounding_coor(points_list):
	min_x = max_y = 0
	max_x = -150.0
	min_y = 100.0

	for point in points_list:
		x_coor = point[0]
		y_coor = point[1]
		if x_coor <= min_x:
			min_x = x_coor
		if x_coor >= max_x:
			max_x = x_coor
		if y_coor <= min_y:
			min_y = y_coor
		if y_coor >= max_y:
			max_y = y_coor
	return min_x, min_y, max_x, max_y

def grid_unit(points_list):
	bounding = bounding_coor(points_list)
	x_unit = (bounding[2] - bounding[0]) / order
	y_unit = (bounding[3] - bounding[1]) / order
	return x_unit, y_unit

def grid_index():
	index_file = open('cali-index.txt', 'w')

	points_list = extract_data()
	bounding = bounding_coor(points_list)
	units = grid_unit(points_list)
	for point in points_list:
		index_column = math.floor((point[0] - bounding[0]) / units[0])
		index_row = math.floor((point[1] - bounding[1]) / units[1])
		index_file.write(str(point[0]) + " " + str(point[1]) + " " + str(index_column) + " " + str(index_row) + "\n")

	print str(bounding[0])+" "+str(bounding[1])+" "+str(bounding[2])+" "+str(bounding[3])
	index_file.close()

grid_index()