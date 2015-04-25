#include <stego-crypt-lib/stego-crypt-lib.hh>

int main(int argc, char* argv[]) {
  Arguments args;
  Error_code err_code = read_args(argc, argv, &args);
  process_error_code(err_code);

  if (args.ftype == File_type::WAV) {
    std::cout << "WAV files not yet supported\n";
  }
  return 0;
}
