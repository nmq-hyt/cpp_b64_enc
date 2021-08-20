#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <map>
#include "encode.hpp"
#include "decode.hpp"

using std::string;
using std::cout;
using std::endl;
using std::bitset;

int main (int argc, char* argv[]) {

  // convert the cmdline argument into a string
  string text = argv[1];
  string encoded_text = base64_encode(test);
  cout << encoded_text << endl;


  return EXIT_SUCCESS;
}

