import random
import math
from operator import itemgetter, attrgetter
import fileinput
import numpy as np

#coef = (0.4, 0.2, 0.1, 0.06, 0.06, 0.06, 0.06, 0.06)
# e = 150000
#coef = (0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125)
thredhold = 1.0/60
curve_num = 160
# coef = (1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

def read_data(fn):
    with open(fn) as f:
        raw_data = np.loadtxt(f, delimiter=' ', dtype="float",skiprows=0, usecols=None)

    data = []

    for row in raw_data:
        data.append(row)

    return np.array(data).tolist()

def extract_data(fn):
	return read_data(fn)

def find_global_maxdistance(points):
	global thredhold
	max_min = 0
	max_max = 0
	min_min = 100000000
	for point in points:
		point.sort()
		if point[0] > max_min:
			max_min = point[0]
		if point[len(point)-1] > max_max:
			max_max = point[len(point)-1]
		if point[0] < min_min:
			min_min = point[0]
	return max_min - min_min, max_max - min_min

def find_e(points):
	glo_max_min = find_global_maxdistance(points)[0]
	glo_max_max = find_global_maxdistance(points)[1]
	e = (2*glo_max_min+glo_max_max)/(math.log(((curve_num-1)*thredhold)/(1-thredhold), 2.72))
	return e

def find_coefficients(values, e):
	coef = []
	max_distance = values[1] - values[0]
	#print "ee => ", 2*max_distance/e

	if max_distance == 0:
		for i in range (0,8):
			coef.append(1.0/8)
		return coef

	for value in values:
		#coef.append(math.exp((e*(values[0]-value)) / (2.0*max_distance)))
		coef.append(math.exp((values[0]-value) / e))
		#coef.append(math.exp(e*(value-values[0]) / (0-max_distance)))
		#coef.append(math.exp(max_distance*(values[0]-value) / e))
		
	su = 0
	for co in coef:
		su += co
	results = []
	for co in coef:
		results.append(co/su)
	# print results
	return results

def dp(fn):
	su = 0
	h0 = 0
	hm = 0
	points = extract_data(fn)
	for point in points:
		h0 += point[0]
		hm += min(point)
	print "Differential Privacy"
	print find_global_maxdistance(points)
	e = find_e(points)
	#e = 0.01
	print "e => ", e
	for point in points:
		coef = find_coefficients(point, e)

		for i in range (0,8):
			su = su + coef[i] * point[i]

	print "result => ", su
	print "origin => ", h0
	print "min => ", hm

#n linear parameter
def coefficient_geo(e, n):
	coef = []
	for i in range(8):
		coef.append(math.exp((0-e)*i*n))
	su = 0
	for co in coef:
		su += co
	results = []
	for co in coef:
		results.append(co/su)
	return results

def e_geo(p, n):
	return math.log(p*(curve_num-1)/(1-p),2.72) / (7.0*n)

def dp_geo(fn):
	su = 0
	h0 = 0
	hm = 0
	points = extract_data(fn)
	e = e_geo(1.0/60, 10)
	#e = 0.01
	coef = coefficient_geo(e, 10)
	#coef = [0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125]
	for point in points:
		h0 += point[0]
		hm += min(point)
	for point in points:
		point.sort()
		for i in range (0,8):
			su = su + coef[i] * point[i]
	print "Geo-Indistinguishability"
	print "e => ", e
	print "result => ", su
	print "origin => ", h0
	print "min => ", hm
# if using differential identifiability, n is useless.
dp("test_result.txt")
dp_geo("test_result.txt")