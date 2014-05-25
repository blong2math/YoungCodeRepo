# -*- coding: utf-8 -*-

def quick_sort(seq):
	def undecorated_quick_sort(seq, b, e):
		if b < e:
			if seq[b] > seq[e]:
				seq[b], seq[e] = seq[e], seq[b]
			i = b
			j = e + 1
			mid = seq[b]
			while i < j:
				i = i + 1
				while seq[i] < mid:
					i = i + 1
				j = j - 1
				while seq[j] > mid:
					j = j - 1
				if i < j:
					seq[i], seq[j] = seq[j], seq[i]
			seq[b], seq[j] = seq[j], seq[b]
			undecorated_quick_sort(seq, b, j - 1)
			undecorated_quick_sort(seq, j + 1, e)
	undecorated_quick_sort(seq, 0, len(seq)-1)