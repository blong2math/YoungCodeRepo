#-*- coding: utf-8 -*-

def insert_sort(seq):
	temp_seq = [seq[0]]
	for i in range(1, len(seq)):
		j = i - 1
		while temp_seq[j] > seq[i] and j >= 0:
			j = j - 1
		temp_seq.insert(j + 1, seq[i])
	for i in range(0, len(seq)):
		seq[i] = temp_seq[i]