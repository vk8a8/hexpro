#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	const char hexchars[17] = "0123456789ABCDEF";
	char lsd;
	char msd;
	char hexdec[3];
	
	char* outname;
	if (argc == 3) outname = argv[2];
	else outname = "out.txt";

	if (argc > 3)
	{
		fprintf(stderr, "Error: E2BIG %d\n", E2BIG);
		return E2BIG;
	}

	FILE* outfptr = fopen(outname, "w");
	FILE* infptr = fopen(argv[1], "rb");

	char ch;
	
	while ((ch = fgetc(infptr)) != EOF)
	{
		lsd = ch & 0xF;
		msd = ch >>  4;
		hexdec[0] = hexchars[msd];
		hexdec[1] = hexchars[lsd];

		fprintf(outfptr,hexdec);
	}
	fclose(outfptr);

	return 0;
}
