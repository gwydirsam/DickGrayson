#include <getopt.h>
#include <vector>
#include <dgtype/dgtype.hh>
#include "stego-attack-lib/stego-attack-lib.hh"

enum class Attack_error_code {
  UNKNOWN_ARG,
  UNKNOWN_TYPE,
  UNSPECIFIED_TYPE,
  MISSING_ARG,
  MISSING_INPUT,
  MISSING_OUTPUT,
  INACCESSIBLE_FILE,
  HELP_ARG,
  SUCCESS
};

struct AttackArgs {
	bool md5_attack = false;
	bool original_provided = false;
	bool scramble = false;
	std::string original_file;
	std::string altered_file;
	std::vector<Attack_error_code> errors;
	
};

int main(int argc, char *argv[]) {
  AttackArgs attack_args;
  int c;
  bool found_error = false;
  while ((c = getopt(argc, argv, "m:o:s:")) != -1 && !found_error) {
	switch (c) {
	case 'm':
		attack_args.md5_attack = true;
		attack_args.altered_file = optarg;
		break;
	case 'o':
		attack_args.original_provided = true;
		attack_args.original_file = optarg;
		break;
	case 's':
		attack_args.scramble = true;
		attack_args.altered_file = optarg;
		break;
	case ':':
		attack_args.errors.push_back(Attack_error_code::MISSING_ARG);
		found_error = true;
		break;
	case '?': 
		attack_args.errors.push_back(Attack_error_code::MISSING_ARG);
		found_error = true;
		break;
	}
  }
  
  if (!attack_args.md5_attack && !attack_args.original_provided && !attack_args.scramble) {
	std::cout << "Error: please provide valid arguments.\n\n"
				  
			  << "-m <alt file> -o <orig file> -- MD5 attack (.bmp and .wav)\n"
			  << "Compares MD5 hashes and returns the encoded message if different.\n\n"
												
			  << "-s <alt file> -- LSB scramble (.bmp and .wav)\n"
			  << "Randomizes the altered file's LSBs to destroy the encoded message.\n\n";
	return 1;
  }
  if ((!attack_args.md5_attack || attack_args.scramble || !attack_args.original_provided)
		&& (attack_args.md5_attack || !attack_args.scramble || attack_args.original_provided))  {
	std::cout << "Error: Please use either -m and -o or -s." << std::endl;
	return 1;
  }
  
  if (attack_args.md5_attack && attack_args.original_provided && !attack_args.scramble) {
	if (file_type_of(attack_args.altered_file) == File_type::UNKNOWN) {
		std::cout << "Error: unknown file type used as argument for -m" << std::endl;
		return 1;
		}
	if (file_type_of(attack_args.original_file) == File_type::UNKNOWN) {
		std::cout << "Error: unknown file type used as argument for -o" << std::endl;
		return 1;
		}
	if (!is_file_accessible(attack_args.altered_file)) {
		std::cout << "Error: invalid file provided in argument -m" << std::endl;
		return 1;
	}
	if (!is_file_accessible(attack_args.original_file)) {
		std::cout << "Error: invalid file provided in argument -o" << std::endl;
		return 1;
	}
	std::cout << "Hidden message: " << retrieveMessage(attack_args.original_file, attack_args.altered_file) << std::endl;
	return 0;
  }
  
  if (!attack_args.md5_attack && !attack_args.original_provided && attack_args.scramble) {
	if (file_type_of(attack_args.altered_file) == File_type::UNKNOWN) {
		std::cout << "Error: unknown file type used as argument for -s" << std::endl;
		return 1;
		}
	if (!is_file_accessible(attack_args.altered_file)) {
		std::cout << "Error: invalid file provided in argument -s" << std::endl;
		return 1;
	}
	scrambleLSB(attack_args.altered_file);
	return 0;
  }
  
  return 0;
}
