#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	const char hexchars[17] = "0123456789ABCDEF";
	char lsd;
	char msd;
	
	char* outname;
	if (argc > 2) outname = argv[2];
	else outname = "out.txt";

	FILE* outfptr = fopen(outname, "w");
	FILE* infptr = fopen(argv[1], "rb");

	char ch;
	
	while ((ch = fgetc(infptr)) != EOF)
	{
		lsd = hexchars[ch & 0xF];
		msd = hexchars[ch >>  4];

		fprintf(outfptr,"%c%c ", msd, lsd);
	}
	fclose(outfptr);

	return 0;
}
