#include <fstream>
#include <cstring>
#include <iostream>

void printHelp() {
	std::cout << "Usage: hexpro <input file> [options]\n";
	std::cout << "Options:\n";
	std::cout << "	-h, --help		Show this message and exit\n";
	std::cout << "	-o FILE			Specify output file\n";
	std::cout << "	-l LENGTH		Specify line length in byte pairs\n";
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	constexpr char hc[17] = "0123456789ABCDEF";
	char lsd;
	char msd;
	char* outname = const_cast<char*>("out.txt");
	char* inname;
	int linelength = 10;

	for ( int i = 0; i < argc; i++ )
	{
		if ( !strcmp( argv[i], "-h") || !strcmp( argv[i], "--help") ) {
			printHelp();
			return 0;
		} else if ( !strcmp( argv[i], "-o") ) {
			i++;
			outname = argv[i];
		} else if ( !strcmp( argv[i], "-l") ) {
			i++;
			linelength = static_cast<int>( strtol( argv[i], NULL, 10 ) );
		}
		else inname = argv[i];
	}

	std::ifstream ifs(inname);
	std::string content( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>())	);

	FILE* outfptr = fopen(outname, "w");
	FILE* infptr = fopen(argv[1], "rb");

	fseek(infptr, 0, SEEK_END);
	long fsize = ftell(infptr);
	fseek(infptr, 0, SEEK_SET);

	for ( long i = 0; i < fsize; i++ )
	{
		unsigned char ch = content[i];
		lsd = hc[ch & 0xF];
		msd = hc[ch >> 4];

		fprintf(outfptr,"%c%c ", msd, lsd);
	}
	fclose(outfptr);

	return 0;
}
