#include "encode.hpp"
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <map>

using std::string;
using std::bitset;
using std::cout;
using std::endl;
using std::map;


string base64_encode (string text){
  // we need the length of the text
  // another int for index operations
  // and strings for the end result
  int n = text.size();
  int length = 0;
  string result;
  string intermediate;

  if ( n < 3){
    // special case: input is less than 24 bits
    switch (n) {
    case 1:{
      bitset<8> b1 (text[0]);
      result = encode_bstring(b1.to_string());
      break;
    }
    case 2:{
      bitset<8> b1(text[0]);
      bitset<8> b2(text[1]);
      result = (encode_bstring(b1.to_string() + b2.to_string()));
      break;
    }
    default:
      {
        result = "error: no input";
        break;
      }
    }

  } else {
    // normal case input can be grouped into 24 or greater bits
    // all possible text lengths can be viewed in modulo 3;
    // since our protocol works on 24 bits (3 bytes, or three chars)
    // we optimize prematurely ( the greatest sin)
    // by truncating the text to some n, (n%3 == 0)
    // and handle the remainder seperately
    // since there are only two other cases (n % 3 == 1 or n % 3 == 2)
    // we have smaller cases to handle

    switch (n % 3) {
    case 1: {
      length = n - 1;
      for (int i = 0; i < length; i += 3) {
        bitset<8> b1 (text[i]);
        bitset<8> b2 (text[i+1]);
        bitset<8> b3 (text[i+2]);

        intermediate = encode_bstring(b1.to_string() + b2.to_string() + b3.to_string());
        result.append(intermediate);
      }
      // there was a fencepost error here
      // it's gone now
      intermediate = text[n-1];
      // recurse to handle special case n = 1;
      result.append(base64_encode(intermediate));
      break;
    }
    case 2:
      {
        length = n - 2;
        for (int i = 0; i < length; i += 3) {
          bitset<8> b1 (text[i]);
          bitset<8> b2 (text[i+1]);
          bitset<8> b3 (text[i+2]);
          intermediate = encode_bstring(b1.to_string() + b2.to_string() + b3.to_string());
          result.append(intermediate);
        }
        intermediate = "";
        intermediate.append(1,text[n-2]);
        intermediate.append(1,text[n-1]);
        // recurse to hande special case n == 2;
        result.append(base64_encode(intermediate));



        break;
      }
    default:
      length = n;
      for (int i = 0; i < length; i += 3) {
        bitset<8> b1 (text[i]);
        bitset<8> b2 (text[i+1]);
        bitset<8> b3 (text[i+2]);

        intermediate = encode_bstring(b1.to_string() + b2.to_string() + b3.to_string());
        result.append(intermediate);
      }

      break;
    }

  }

  return result;

}

string encode_bstring (string text) {

  string temp1;
  string temp2;
  string temp3;
  string temp4;

  // someone told me about LUTs
  // and I've never looked back
  map<string,string> b64_table {
                                {"000000", "A"},
                                {"000001", "B"},
                                {"000010", "C"},
                                {"000011", "D"},
                                {"000100", "E"},
                                {"000101", "F"},
                                {"000110", "G"},
                                {"000111", "H"},
                                {"001000", "I"},
                                {"001001", "J"},
                                {"001010", "K"},
                                {"001011", "L"},
                                {"001100", "M"},
                                {"001101", "N"},
                                {"001110", "O"},
                                {"001111", "P"},
                                {"010000", "Q"},
                                {"010001", "R"},
                                {"010010", "S"},
                                {"010011", "T"},
                                {"010100", "U"},
                                {"010101", "V"},
                                {"010110", "W"},
                                {"010111", "X"},
                                {"011000", "Y"},
                                {"011001", "Z"},
                                {"011010", "a"},
                                {"011011", "b"},
                                {"011100", "c"},
                                {"011101", "d"},
                                {"011110", "e"},
                                {"011111", "f"},
                                {"100000", "g"},
                                {"100001", "h"},
                                {"100010", "i"},
                                {"100011", "j"},
                                {"100100", "k"},
                                {"100101", "l"},
                                {"100110", "m"},
                                {"100111", "n"},
                                {"101000", "o"},
                                {"101001", "p"},
                                {"101010", "q"},
                                {"101011", "r"},
                                {"101100", "s"},
                                {"101101", "t"},
                                {"101110", "u"},
                                {"101111", "v"},
                                {"110000", "w"},
                                {"110001", "x"},
                                {"110010", "y"},
                                {"110011", "z"},
                                {"110100", "0"},
                                {"110101", "1"},
                                {"110110", "2"},
                                {"110111", "3"},
                                {"111000", "4"},
                                {"111001", "5"},
                                {"111010", "6"},
                                {"111011", "7"},
                                {"111100", "8"},
                                {"111101", "9"},
                                {"111110", "+"},
                                {"111111", "/"}
  };

  int n = text.length();

  if (n == 16) {
    text = text + "00";
    temp1 = text.substr(0,6);
    temp1 = b64_table[temp1];
    temp2 = text.substr(6,6);
    temp2 = b64_table[temp2];
    temp3 = text.substr(12,6);
    temp3 = b64_table[temp3];
    text = temp1 + temp2 + temp3 + "=";
  } else if ( n == 8){
    text = text + "0000";
    temp1 = text.substr(0,6);
    temp1 = b64_table[temp1];
    temp2 = text.substr(6,6);
    temp2 = b64_table[temp2];
    text = temp1 + temp2 + "==";
  } else  {
    temp1 = text.substr(0,6);
    temp1 = b64_table[temp1];
    temp2 = text.substr(6,6);
    temp2 = b64_table[temp2];
    temp3 = text.substr(12,6);
    temp3 = b64_table[temp3];
    temp4 = text.substr(18,6);
    temp4 = b64_table[temp4];
    text = temp1 + temp2 + temp3 + temp4;
 
  }

  return text;
}




