# 	Code eval challenge: Data Recovery

# 	Author: Ravi Niure
# 	Linkedin/Github: niurerav
# 	Twitter: NiureRavi
# 	Website: www.raviniure.com
# 	Department of Electrical and Computer Engineering
# 	University of Toronto

import random
import sys
import os

f = open(sys.argv[1], 'r')
lines = tuple(line.rstrip('\n') for line in f)
f.close()

total_lines = len(lines)

sentence_list = []
hint_list = []

for i in range (0, total_lines):
	sentence, hint = lines[i].split(';')
	sentence_list.append(sentence)
	hint_list.append(hint)

lookup_list = [0 for i in range (total_lines)]

for i in range (0, total_lines):
	word_list = sentence_list[i].split(' ')
	number_list = hint_list[i].split(' ')
	lookup_list[i] = len(word_list)

	
	final_word_list = ["" for k in range (lookup_list[i])]

	for j in range (0, len(number_list)):
		final_word_list[int(number_list[j]) - 1] = word_list[j]
	left_string = word_list[lookup_list[i] - 1]

	for k in range (0, lookup_list[i]):
		if not final_word_list[k]:
			final_word_list[k] = left_string

	for k in range (0, lookup_list[i]):
		print final_word_list[k], 
	print ('')