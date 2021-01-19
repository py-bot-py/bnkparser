CC=gcc
C_FLAGS="-DDEBUG"
C_FILES=$(wildcard *.c)


BNK_Parser: $(C_FILES)
	$(CC) $^ -o $@ $(C_FLAGS) -Wall


run: BNK_Parser
	./$^ MXGS_Global_Music.bnk


clean:
	rm BNK_Parser
