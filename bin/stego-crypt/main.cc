#include <memory>
#include <stego-crypt-lib/stego-crypt-lib.hh>

int main(int argc, char* argv[]) {
  Arguments args;
  Error_code err_code = read_args(argc, argv, &args);
  process_error_code(err_code);

  std::unique_ptr<Abstract_embedding_agent> embedder;
  std::unique_ptr<Abstract_extracting_agent> extractor;

  if (args.ftype == File_type::BMP) {
    if (!args.extract) {
      embedder = std::make_unique<BMP_embedding_agent>(args.input_fname,
                                                       args.output_fname);
    } else {
      extractor = std::make_unique<BMP_extracting_agent>(args.input_fname);
    }
    std::cout << "-- Done";
  } else { // args.ftype == File_type::WAV
    /* ***still need to implement WAV embedding and extracting agents
    if (!args.extract) {
      embedder = std::make_unique<WAV_embedding_agent>(args.input_fname,
                                                       args.output_fname);
    } else {
      extractor = std::make_unique<WAV_extracting_agent>(args.input_fname);
    }*/
    std::cout << "WAV files not yet supported\n";
  }

  if (!args.extract) {
    std::string message = message_from_file(args.message_fname);
    embedder->embed_and_save(message);
  } else {
    std::string message = extractor->extract();
    message_to_file(message, args.output_fname);
  }
  return 0;
}
