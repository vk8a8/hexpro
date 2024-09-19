#include <fstream>
#include <cstring>
#include <iostream>

void printHelp() {
	using std::cout;
	cout << "Usage: hexpro <input file> [options]\n";
	cout << "Options:\n";
	cout << "	-h, --help		Show this message and exit\n";
	cout << "	-o FILE			Specify output file\n";
	cout << "	-l LENGTH		Specify line length in byte pairs\n";
	cout << std::endl;
}

int main(int argc, char* argv[]) {
	constexpr char hc[17] = "0123456789ABCDEF";

	using std::string, std::istreambuf_iterator;

	char lsd; // least sig digit
	char msd; // most sig digit
	char* inname;
	char linelength = 16;
	string outname = "out.txt";

	for ( int i = 1; i < argc; i++ )
	{
		if ( !strcmp( argv[i], "-h") || !strcmp( argv[i], "--help") ) {
			printHelp();
			return 0;
		} else if ( !strcmp( argv[i], "-o") ) {
			outname = argv[i + 1];
			continue;
		} else if ( !strcmp( argv[i], "-l") ) {
			linelength = static_cast<char>( strtol(argv[i + 1], NULL, 10) );
			continue;
		}
		else
			inname = argv[i];
		
	}

	short chunkll = linelength * 3;

	std::ifstream ifs(inname);
	string content( (istreambuf_iterator<char>(ifs) ),
			(istreambuf_iterator<char>()));

	FILE* outfptr = fopen(outname.c_str(), "w");
	FILE* infptr = fopen(argv[1], "rb");

	fseek(infptr, 0, SEEK_END);
	long fsize = ftell(infptr);
	fseek(infptr, 0, SEEK_SET);
	fclose(infptr);

	char bytec = 0;
	char bytes[1 + chunkll] = { 0 };

	memset(bytes, ' ', linelength * 3);

	for ( long i = 0; i < fsize; i++ )
	{
		unsigned char ch = content[i];
		lsd = hc[ch & 0xF];	// abcdABCD & 00001111 -> 0000ABCD
		msd = hc[ch >> 4];	// abcdABCD >> 4 -> 0000abcd (uchar makes it not preserve first bit)

		bytes[3 * bytec] = msd;
		bytes[3 * bytec + 1] = lsd;

		if (bytec == linelength - 1 ) {
			fprintf(outfptr,"%s\n", bytes);
			bytec = 0;
		} else bytec++;

	}
	fclose(outfptr);

	return 0;
}
