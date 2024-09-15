#include <fstream>

int main(int argc, char* argv[]) {
	constexpr char hc[17] = "0123456789ABCDEF";
	char lsd;
	char msd;

	std::ifstream ifs(argv[1]);
	std::string content( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>())	);


	FILE* outfptr = fopen("out.txt", "w");
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
