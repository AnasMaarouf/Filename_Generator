#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#define First_Characrter_Is_Capital_Letter 0b0000000000000000000000000000000000000000000000000000000000000001
#define Ignore_Capital_Letters 0b0000000000000000000000000000000000000000000000000000000000000010
#define Ignore_Non_Capital_Letters 0b0000000000000000000000000000000000000000000000000000000000000100
#define Ignore_Special_Characters 0b0000000000000000000000000000000000000000000000000000000000001000
#define Ignore_Numbers 0b0000000000000000000000000000000000000000000000000000000000010000
std::string RandomFileNameGenerator(unsigned int length /*IN*/, uint64_t Arg_register/*IN*/);

using namespace std;

int main()
{
	srand(time(nullptr));
	
	const unsigned int Nr_of_filenames = 100;

	string fileDirectory = "";
	string filename = "file names";
	string filetype = ".txt";
	ofstream file_containing_generated_file_names("file names.txt");
	
	cout << "Random file names:" << endl;

	for (size_t i = 1; i <= Nr_of_filenames; i++) {
		string Generated_filename = RandomFileNameGenerator(rand() % 5 + 20,0);
		if (i <= 9){
			cout << i << "." << setw(size(Generated_filename) + 4) << Generated_filename << endl;
			file_containing_generated_file_names << i << "." << setw(size(Generated_filename) + 4) << Generated_filename << endl;
		} else if (i > 9 && i <= 99) {
			cout << i << "." << setw(size(Generated_filename) + 3) << Generated_filename << endl;
			file_containing_generated_file_names << i << "." << setw(size(Generated_filename) + 3) << Generated_filename << endl;
		} else if (i > 99 && i <= 999) {
			cout << i << "." << setw(size(Generated_filename) + 2) << Generated_filename << endl;
			file_containing_generated_file_names << i << "." << setw(size(Generated_filename) + 2) << Generated_filename << endl;
		} else if (i > 999 && i <= 9999) {
			cout << i << "." << setw(size(Generated_filename) + 1) << Generated_filename << endl;
			file_containing_generated_file_names << i  << "." << setw(size(Generated_filename) + 1) << Generated_filename << endl;
		}
	}


	file_containing_generated_file_names.close();

	return 0;
}



std::string RandomFileNameGenerator(unsigned int length /*IN*/, uint64_t Arg_register/*IN*/) {
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<int> uni(0, 4);

    std::string FileName;

    constexpr char NonCapitalLetters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    constexpr char CapitalLetters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    constexpr char SpecialCharacters[] = { '#', '%', '&', '(', ')', '+', '-', '@', '[', ']', '_', '$' };

    constexpr char Numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


    for (unsigned int i = 0; i < length; i++) {
        unsigned int Random_Category_Selector = uni(rng);

        if ((Arg_register & First_Characrter_Is_Capital_Letter) && i == 0) {    // First letter must be capital letter argument.
            FileName += CapitalLetters[rand() % sizeof(CapitalLetters)];
        }


        switch (Random_Category_Selector)
        {
            case 0:
                if (!(Arg_register & Ignore_Capital_Letters)) {
                    FileName += CapitalLetters[rand() % sizeof(CapitalLetters)];
                    break;
                }
            case 1:
                if (!(Arg_register & Ignore_Non_Capital_Letters)) {
                    FileName += NonCapitalLetters[rand() % sizeof(NonCapitalLetters)];
                    break;
                }
            case 2:
                if (!(Arg_register & Ignore_Special_Characters)) {
                    FileName += SpecialCharacters[rand() % sizeof(SpecialCharacters)];
                    break;
                }

            case 3:
                if (!(Arg_register & Ignore_Numbers)) {
                    FileName += Numbers[rand() % sizeof(Numbers)];
                    break;
                }

            default:
                i--;
                break;
        }
    }

    return FileName;
}
