#include <memory>
#include <stego-crypt-lib/stego-crypt-lib.hh>

int main(int argc, char* argv[]) {
  Arguments args;
  Error_code err_code = read_args(argc, argv, &args);
  process_error_code(err_code);

  File_type file_type = file_type_of(args.input_fname);

  std::unique_ptr<Abstract_embedding_agent> embedder;
  std::unique_ptr<Abstract_extracting_agent> extractor;

  std::cout << "-- Running\n";
  if (!args.extract) {
    print_if("-- Loading the embedding agent\n", args.verbose);
    embedder = which_embedding_agent(file_type, args.input_fname, args.output_fname);

    print_if("-- Loading message from disk\n", args.verbose);
    std::string message = message_from_file(args.message_fname);

    print_if("-- Embedding and saving to disk\n", args.verbose);
    embedder->embed_and_save(message);
  } else {
    print_if("-- Loading the extracting agent\n", args.verbose);
    extractor = which_extracting_agent(file_type, args.input_fname);

    print_if("-- Extracting the message\n", args.verbose);
    std::string message = extractor->extract();

    print_if("-- Saving message to disk\n", args.verbose);
    message_to_file(message, args.output_fname);
  }
  std::cout << "-- Done\n";
  return 0;
}
