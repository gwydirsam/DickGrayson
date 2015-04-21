#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <getopt.h>

const std::vector<std::string> attack_types = {"factoring", "chinese_rt", "other"};

void whatAttackTypes(){
  std::cout << "\nType can be ";
  for(int i= 0; i < attack_types.size(); ++i){
    std::cout << "\'" << attack_types[i] <<  "\', ";
  }
  std::cout << std::endl;
}

void usage(){
  std::cout << "Usage is --attack [type] --filename [filename]"  << std::endl;
  whatAttackTypes();
}

void whatWentWrong(int flag, bool ioerror){
  if(ioerror) {
    std::cout << "File i/o error. Check that file exists and has correct permissions." << std::endl;
  }
  if(flag == 1){
    std::cout << "missing argument --attack [type]"  << std::endl;
    whatAttackTypes();
  }
  if(flag == 2){
    std::cout << "missing argument --filename [file_to_crack]"  << std::endl;
  }
}

int main(int argc, char* argv[]) {
  int fflag, aflag, ch;
  bool ioerror = false;

  /* options descriptor */
  static struct option longopts[] = {
    { "attack",   required_argument,  NULL, 'a'},
    { "filename", required_argument,  NULL, 'f'},
    { "help", no_argument,  NULL, 'h'},
    {NULL, 0, NULL , 0}
  };

  int option_index = 0;

  fflag = aflag = 0;
  while ((ch = getopt_long(argc, argv, "ha:f:", longopts, &option_index)) != -1){
    switch (ch) {
    case 'a':
      aflag = 1;
      if(optarg == attack_types[0]){
        std::cout << "Running " << attack_types[0] << " on file.." << std::endl;
      }
      break;

    case 'f':{
      fflag = 2;
      std::string fname = optarg;
      std::fstream f(fname, std::ios::in);
      if (!f.is_open())
        ioerror = true;
      else{
        std::string line = "";
        //this should pass to our fctn eventually
        //for now, test it's reading the right file
        while ( std::getline (f,line) ) {std::cout << line << '\n';}
      }

      break;
    }
    case 'h':
    case '?':
    default:
      usage();
      exit(EXIT_FAILURE);
      break;

    }
  }
  if(!fflag || !aflag){
    usage();
  }
  whatWentWrong(fflag + aflag, ioerror);
}
