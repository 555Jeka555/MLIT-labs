from collections import deque

amount1 = 0
amount = 0

def queenRecurs(N):
	board = [[0 for i in range(N)] for i in range(N)]

	def setQueen(i, j, N):
		for x in range(N):
			board[x][j] += 1
			board[i][x] += 1
			if 0 <= i + j - x < N:
				board[i + j - x][x] += 1
			if 0 <= i - j + x < N:
				board[i - j + x][x] += 1
		board[i][j] = -1

	def removeQueen(i, j, N):
		for x in range(N):
			board[x][j] -= 1
			board[i][x] -= 1
			if 0 <= i + j - x < N:
				board[i + j - x][x] -= 1
			if 0 <= i - j + x < N:
				board[i - j + x][x] -= 1
		board[i][j] = 0

	def printPosition(N):
		global amount
		amount += 1

		abc = 'abcdefghiklmnopqrtw'
		ans = []
		for i in range(N):
			for j in range(N):
				if board[i][j] == -1:
					ans.append(abc[j] + str(i + 1))
		print(', '.join(ans))

	def solve(i, N):
		for j in range(N):
			if board[i][j] == 0:
				setQueen(i, j, N)
				if i == N - 1:
					printPosition(N)
				else:
					solve(i + 1, N)
				removeQueen(i, j, N)

	solve(0, N)
	print(amount)

def queenBFS(N):
	def solve(N):
		queue = deque([(0, [])])
		solutions = []

		while queue:
			row, queens = queue.popleft()

			if row == N:
				solutions.append(queens)
				continue

			for col in range(N):
				if all(col != queen_col and abs(row - i) != abs(col - queen_col) for i, queen_col in enumerate(queens)):
					queue.append((row + 1, queens + [col]))
			print(queens)
		return solutions


	def print_positions(solutions):
	    abc = 'abcdefghiklmnopqrtw'
	    for solution in solutions:
	        ans = [abc[col] + str(row + 1) for row, col in enumerate(solution)]
	        print(', '.join(ans))

	solutions = solve(N)
	print_positions(solutions)
	print(len(solutions), "positions")


queenBFS(4)