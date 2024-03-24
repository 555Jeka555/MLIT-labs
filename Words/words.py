from itertools import permutations


while True:
	word = input()

	if word == "...":
		break
		
	perms = sorted(set(permutations(word)))
	print(perms)

