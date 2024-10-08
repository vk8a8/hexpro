#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printHelp() {
	puts("Usage: hexpro <input file> [options]");
	puts("Options:");
	puts("	-h, --help		Show this message and exit");
	puts("	-o FILE			Specify output file");
	puts("	-l LENGTH		Specify line length in byte pairs");
}

void parseArgs(int argc, char* argv[],
		int* ll, char** inname, char** outname) {

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			printHelp();
			exit(0);
		}
		else if (!strcmp(argv[i], "-o"))
			*outname = argv[++i];
		else if (!strcmp(argv[i], "-l"))
			*ll = (int) strtol(argv[++i], NULL, 10);
		else
			*inname = argv[i];
	}
}


int main(int argc, char* argv[]) {
	const char hc[17] = "0123456789ABCDEF";

	char lsd;	// least sig digit
	char msd;	// most sig digit
	char* inname;
	int ll = 16;
	char* outname = "out.txt";

	parseArgs(argc, argv, &ll, &inname, &outname);

	short chunkll = ll * 3;

	FILE* outfptr = fopen(outname, "w");
	if (!outfptr) {
		puts("Error writing to file");
		return -1;
	}

	FILE* infptr = fopen(inname, "rb");
	if (!infptr) {
		puts("Invalid input file");
		return -1;
	}

	unsigned int bytec = 0;
	char bytes[chunkll + 1];

	memset(bytes, ' ', sizeof(bytes));
	bytes[chunkll] = '\0';
	bytes[chunkll - 1] = '\n';

	int p;
	while ((p = fgetc(infptr)) != EOF)
	{
		unsigned char ch = (unsigned char) p;
		lsd = hc[ch & 0xF];	// abcdABCD & 00001111 -> 0000ABCD
		msd = hc[ch >> 4];	// abcdABCD >> 4 -> 0000abcd

		bytes[3 * bytec] = msd;
		bytes[3 * bytec + 1] = lsd;

		if (bytec == ll - 1) {
			fputs(bytes, outfptr);
			bytec = 0;

			memset(bytes, ' ', sizeof(bytes));
			bytes[chunkll] = '\0';
			bytes[chunkll - 1] = '\n';
		} else bytec++;

	}

	if (bytec)
	{
		bytes[3 * bytec] = '\n';
		bytes[3 * bytec + 1] = '\0';
		fputs(bytes, outfptr);
	}

	fclose(infptr);
	fclose(outfptr);

	return 0;
}
