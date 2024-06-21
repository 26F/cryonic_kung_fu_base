
from PIL import Image

BYTES = 8
BITS  = 8


strr = """const int ASCII_FONT_DATA[ASCII_CHAR_NM][ASCII_CHAR_WH] = 
{"""



for n in range(61):

	img = Image.open("./ascii/{}.png".format(n))

	mat = [[0 for _ in range(BITS)] for __ in range(BYTES)]

	for r in range(BYTES):
		for c in range(BITS):
			hit = img.getpixel((c, r))
			if hit[0] == 255:
				mat[r][c] = 1

	# byte: rightmost is top row
	# bit:  leftmost is left of column

	bytes_data = [0, 0, 0, 0, 0, 0, 0, 0]

	for i in range(BYTES):
		row = mat[BYTES - i - 1]
		for j in range(BITS):
			colv = row[j]
			if colv == 1:
				bytes_data[BYTES - i - 1] |= (1 << (BITS - (j + 1)))

	strr += "\n\t\t" + str(bytes_data).replace('[', '{').replace(']', '}') + ","

	img.close()

strr += "\n};"

print(strr)