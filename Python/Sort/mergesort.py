#-*- coding:utf-8 -*-
import math

def merge_sort(ls):
	def undecorated_merge_sort(ls, p, r):
		if r > p:
			q = int(math.floor((p+r)/2))
			undecorated_merge_sort(ls, p, q)
			undecorated_merge_sort(ls, q+1, r)
			merge(ls, p, q, r)
	undecorated_merge_sort(ls, 0, len(ls) - 1)

def merge(ls, p, q, r):
	'''merge p-q and q+1-r'''
	templs1, templs2 = ([], [])
	l1, l2 = q - p + 1, r - q
	for count in range(0, l1):
		templs1.append(ls[p + count])
	for count in range(0, l2):
		templs2.append(ls[q + count + 1])
	templs1.append(max(ls) + 1)
	templs2.append(max(ls) + 1)
	i, j = (0, 0)
	for count in range(p, r + 1):
		if templs1[i] < templs2[j]:
			ls[count] = templs1[i]
			i = i + 1
		else:
			ls[count] = templs2[j]
			j = j + 1