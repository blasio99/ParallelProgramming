from pandas import DataFrame
import numpy as np
Z = 26

# task 2
def has_inverse(a):
	det = ((a[0][0] * a[1][1]) % Z) - ((a[0][1] * a[1][0]) % Z)
	if det < 0:
		det += Z
	if det % 2 != 0 and det != 13:	
		for i in range(Z):
			new_det = (det * i) % Z
			if new_det == 1:
				det = i
				break
		inv = [
			[
				(det * a[1][1]) % Z,
				((det * (-a[0][1] + Z)) % Z)
			],
			[
				(det * (-a[1][0] + Z)) % Z,
				(det * a[0][0]) % Z
			]
		]
	else:
		inv = None
	return inv


def print_mat(fd, A):
	mat = ''
	for i in range(2):
		for j in range(2):
			mat += (chr(A[i][j] + 65) + ' ')
	if not fd:
		return mat
	fd.write(mat)
	fd.write('\n')


# task 3
def encryption(key_matrix, A):
	return np.array(key_matrix).dot(np.array(A)) % Z
	
def decryption(key_matrix, A):
	inv = has_inverse(key_matrix)
	return np.array(inv).dot(np.array(A)) % Z

if __name__ == '__main__':
	# task 1
	
	fdA = open('keys_2x2.txt', 'w')
	fdInv = open('invkeys_2x2.txt', 'w')
	for i in range(Z):
		for j in range(Z):
			for k in range(Z):
				for l in range(Z):
					a = [[i, j], [k, l]]
					pos_b = has_inverse(a)
					if pos_b:
						print_mat(fdA, a)
						print_mat(fdInv, pos_b)
					
	fdA.close()
	fdInv.close()
	
	# task 3
	'''keyword = 'HILL'
	key_matrix = [[0] * 2, [0] * 2]
	for i in range(2):
		for j in range(2):
			key_matrix[i][j] = ord(keyword[i * 2 + j]) - 65

	m = [18, 7]  # SH

	enc = encryption(key_matrix, m)
	print(enc)
	dec = decryption(key_matrix, enc)
	print(dec)'''
	
	# task 4
	fdInv = open('invkeys_2x2.txt', 'r')
	fdMsgs = open('messages_2x2.txt', 'w')
	data = fdInv.readlines()
	fdInv.close()
	
	m1 = [7, 8]  # HI
	m2 = [0, 19]  # AT
	for d in data:
		d = d.replace(' ', '')
		key_matrix = [[0] * 2, [0] * 2]
		for i in range(2):
			for j in range(2):
				key_matrix[i][j] = ord(d[i * 2 + j]) - 65
		result = [[0] * 2, [0] * 2]
		
		result[0] = encryption(key_matrix, m1).tolist()
		result[1] = encryption(key_matrix, m2).tolist()
		
		print_mat(fdMsgs, result)
	fdMsgs.close()
