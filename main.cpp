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

int main (int argc, char* argv[]) {

  // convert the cmdline argument into a string
  string text = argv[1];
  string encoded_text = base64_encode(text);
  cout << encoded_text << endl;
  text = base64_decode(encoded_text);
  cout << text << endl;

  return EXIT_SUCCESS;
}

