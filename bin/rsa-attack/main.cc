#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <getopt.h>
void whatAttackTypes(){
    std::cout << "\nType can be \'factoring\', \'chinese_rt\', or \'blah\'" << std::endl;
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
    { "filename", required_argument,  NULL, 'f'}
  };
  int option_index = 0;

  fflag = aflag = 0;
  while ((ch = getopt_long(argc, argv, "a:f:", longopts, &option_index)) != -1)
    switch (ch) {
    case 'a':
      aflag = 1;
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

    }
      break;
    default:
      break;

    }
  if(!fflag || !aflag){
    usage();
  }
  //argc -= optind;
  //argc += optind;
  whatWentWrong(fflag + aflag, ioerror);
}
