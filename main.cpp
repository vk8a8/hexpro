#include <iostream>
#include <fstream>
#include <cstdint>

int main(int argc, char* argv[]) {
	const char hexchars[17] = "0123456789ABCDEF";
	char lsd;
	char msd;
	char hexdec[3];

	std::ifstream ifs(argv[1]);
	std::string content( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>())	);
	
	FILE* outfptr = fopen("out.txt", "w");
	FILE* infptr = fopen(argv[1], "rb");

	fseek(infptr, 0, SEEK_END);
	long fsize = ftell(infptr);
	fseek(infptr, 0, SEEK_SET);

	for ( long i = 0; i < fsize; i++ )
	{
		char ch = content[i];
		lsd = hexchars[ch & 0xF];
		msd = hexchars[(ch & 0x7F) >>  4];

		hexdec[0] = msd;
		hexdec[1] = lsd;
		fprintf(outfptr,hexdec);
	}
	fclose(outfptr);

	return 0;
}
