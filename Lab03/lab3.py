import threading
import time

def perfect_number(number):
	sum_of_divisors = 0
	for i in range(1, number):
		if number % i == 0:
			sum_of_divisors += i
	return number == sum_of_divisors

def finding_perfect_primes(lst):
	print('[' +  str(lst[0]) + ', ' + str(lst[-1]) + ']', sum([perfect_number(i) for i in lst]))

N = 4
list = list(range(1, 50000))

def divide(lst, n):
    p = len(lst) // n
    if len(lst)-p > 0:
        return [lst[:p]] + divide(lst[p:], n-1)
    else:
        return [lst]
		

def parallel():
	jobs = []
	lists = divide(list, N)
	for i in range(0, N):
		thr = threading.Thread(target=finding_perfect_primes, args=(lists[i], ))
		jobs.append(thr)
		
	for i in jobs:
		i.start()
		
	for i in jobs:
		i.join()


start_time = time.time()
# finding_perfect_primes(list)
parallel()
print(time.time() - start_time)
