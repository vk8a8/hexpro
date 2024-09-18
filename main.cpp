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

	using std::string, std::istreambuf_iterator;

	constexpr char hc[17] = "0123456789ABCDEF";
	char lsd;
	char msd;
	char* inname;
	int linelength = 16;
	string outname = "out.txt";

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
	string content( (istreambuf_iterator<char>(ifs) ),
			(istreambuf_iterator<char>()));

	FILE* outfptr = fopen(outname.c_str(), "w");
	FILE* infptr = fopen(argv[1], "rb");

	fseek(infptr, 0, SEEK_END);
	long fsize = ftell(infptr);
	fseek(infptr, 0, SEEK_SET);

	int bytec = 0;
	char bytes[1 + linelength * 3] = { 0 };

	for ( long i = 0; i < fsize; i++ )
	{
		unsigned char ch = content[i];
		lsd = hc[ch & 0xF];
		msd = hc[ch >> 4];

		bytes[3 * bytec] = msd;
		bytes[3 * bytec + 1] = lsd;
		bytes[3 * bytec + 2] = ' ';

		if (bytec >= 15) {
			fprintf(outfptr,"%s\n", bytes);
			bytec = 0;
		} else bytec++;

	}
	fclose(outfptr);

	return 0;
}
