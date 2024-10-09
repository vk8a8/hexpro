#include <fstream>
#include <cstring>
#include <iostream>
#include <stdio.h>

void printHelp() {
	printf("Usage: hexpro <input file> [options]\n");
	printf("Options:\n");
	printf("	-h, --help		Show this message and exit\n");
	printf("	-o FILE			Specify output file\n");
	printf("	-l LENGTH		Specify line length in byte pairs\n");
}

int main(int argc, char* argv[]) {
	constexpr char hc[17] = "0123456789ABCDEF";

	using std::string, std::istreambuf_iterator;

	char lsd; // least sig digit
	char msd; // most sig digit
	char* inname;
	char linelength = 16;
	char* outname = "out.txt";

	for ( int i = 1; i < argc; i++ ) // whatever
	{
		if ( !strcmp( argv[i], "-h") || !strcmp( argv[i], "--help") ) {
			printHelp();
			return 0;
		} else if ( !strcmp( argv[i], "-o") ) {
			i++;
			outname = argv[i];
		} else if ( !strcmp( argv[i], "-l") ) {
			i++;
			linelength = static_cast<char>( strtol(argv[i], NULL, 10) );
		}
		else
			inname = argv[i];
		
	}

	short chunkll = linelength * 3;

	std::ifstream ifs(inname);
	string content( (istreambuf_iterator<char>(ifs) ),
			(istreambuf_iterator<char>()));

	FILE* outfptr = fopen(outname, "w");
	FILE* infptr = fopen(argv[1], "rb");

	fseek(infptr, 0, SEEK_END);
	long fsize = ftell(infptr);
	fseek(infptr, 0, SEEK_SET);

	char bytec = 0;
	char bytes[1 + chunkll] = { 0 };

	memset(bytes, ' ', linelength * 3);

//	for ( long i = 0; i < fsize; i++ )
	int p;
	while ((p = fgetc(infptr)) != EOF)
	{
//		unsigned char ch = content[i];
		unsigned char ch = (unsigned char) p;
		lsd = hc[ch & 0xF];	// abcdABCD & 00001111 -> 0000ABCD
		msd = hc[ch >> 4];	// abcdABCD >> 4 -> 0000abcd (uchar makes it not preserve first bit)

		bytes[3 * bytec] = msd;
		bytes[3 * bytec + 1] = lsd;

		if (bytec == linelength - 1 ) {
			fprintf(outfptr,"%s\n", bytes);
			bytec = 0;
		} else bytec++;

	}
	fclose(infptr);
	fclose(outfptr);

	return 0;
}
