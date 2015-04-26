#include <stego-crypt-lib/stego-crypt-lib.hh>

int main(int argc, char* argv[]) {
  Arguments args;
  Error_code err_code = read_args(argc, argv, &args);
  process_error_code(err_code);

  if (args.ftype == File_type::BMP) {
    if (!args.extract) {
      Embedding_agent embedder(args.input_fname, args.output_fname);
      std::string message = message_from_file(args.message_fname);
      embedder.embed_and_save(message);
      print_psnr(args.input_fname, args.output_fname);
    } else {
      Extracting_agent extractor(args.input_fname);
      std::string message = extractor.extract();
      message_to_file(message, args.output_fname);
    }
  } else { // args.ftype == File_type::WAV
    std::cout << "WAV files not yet supported\n";
  }
  return 0;
}
