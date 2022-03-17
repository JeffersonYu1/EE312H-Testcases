import random 

def main():
	# modify numCases for more / less cases
	numCases = 1000

	print('SetResults setResults[' + str(numCases) + '] = {')
	for i in range(numCases):
		print('\t{')
		printSetResults()
		print('\t}' + (',' if i < numCases - 1 else ''))
	print('};')


def printSetResults():
	a = set()
	b = set()

	i = -100

	while len(a) < 50:
		if i % random.randint(2, 6) == 0:
			a.add(int(i))
		i += 1

	i = -100

	while len(b) < 50:
		if i % random.randint(2, 6) == 0:
			b.add(int(i))
		i += 1

	aList = sorted(a)
	bList = sorted(b)

	print('\t\t{' + ', '.join(str(num) for num in sorted(a)) + '},')
	print('\t\t{' + ', '.join(str(num) for num in sorted(b)) + '},')

	union = sorted(a | b)
	intersection = sorted(a & b)
	difference = sorted(a - b)

	print('\t\t' + str(len(union)) + ',')
	print('\t\t{' + ', '.join(str(num) for num in union) + '},') # union

	print('\t\t' + str(len(intersection)) + ',')
	print('\t\t{' + ', '.join(str(num) for num in intersection) + '},') # intersection

	print('\t\t' + str(len(difference)) + ',')
	print('\t\t{' + ', '.join(str(num) for num in difference) + '},') # difference a - b

	# if includes (1) or no (0)
	print('\t\t{' + ','.join('1' if num in a else '0' for num in range(-100, 100, 1)) + '}')

if __name__ == "__main__":
    main()