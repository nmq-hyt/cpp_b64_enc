#include "decode.hpp"
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

string base64_decode (string text){

  int n = text.size();
  string result;
  string intermediate;
  // since the encoding pads the message
  // we don't have to deal with variable input lengths in the decoding process
  // but we do have to deal with padding character =
  // this means that we will always deal with a string of length
  // n mod 4 = 0
  map<string,string> sixbit_table {
                                   {"A","000000"},
                                   {"B","000001"},
                                   {"C","000010"},
                                   {"D","000011"},
                                   {"E","000100"},
                                   {"F","000101"},
                                   {"G","000110"},
                                   {"H","000111"},
                                   {"I","001000"},
                                   {"J","001001"},
                                   {"K","001010"},
                                   {"L","001011"},
                                   {"M","001100"},
                                   {"N","001101"},
                                   {"O","001110"},
                                   {"P","001111"},
                                   {"Q","010000"},
                                   {"R","010001"},
                                   {"S","010010"},
                                   {"T","010011"},
                                   {"U","010100"},
                                   {"V","010101"},
                                   {"W","010110"},
                                   {"X","010111"},
                                   {"Y","011000"},
                                   {"Z","011001"},
                                   {"a","011010"},
                                   {"b","011011"},
                                   {"c","011100"},
                                   {"d","011101"},
                                   {"e","011110"},
                                   {"f","011111"},
                                   {"g","100000"},
                                   {"h","100001"},
                                   {"i","100010"},
                                   {"j","100011"},
                                   {"k","100100"},
                                   {"l","100101"},
                                   {"m","100110"},
                                   {"n","100111"},
                                   {"o","101000"},
                                   {"p","101001"},
                                   {"q","101010"},
                                   {"r","101011"},
                                   {"s","101100"},
                                   {"t","101101"},
                                   {"u","101110"},
                                   {"v","101111"},
                                   {"w","110000"},
                                   {"x","110001"},
                                   {"y","110010"},
                                   {"z","110011"},
                                   {"0","110100"},
                                   {"1","110101"},
                                   {"2","110110"},
                                   {"3","110111"},
                                   {"4","111000"},
                                   {"5","111001"},
                                   {"6","111010"},
                                   {"7","111011"},
                                   {"8","111100"},
                                   {"9","111101"},
                                   {"+","111110"},
                                   {"/","111111"},
                                   {"=",""}
  };

  for (int i = 0; i < n; i+=4){
    string b1 (1,text[i]);
    b1 = sixbit_table[b1];
    string b2 (1,text[i+1]);
    b2 = sixbit_table[b2];
    string b3 (1,text[i+2]);
    b3 = sixbit_table[b3];
    string b4 (1,text[i+3]);
    b4 = sixbit_table[b4];

    intermediate = decode_bstring(b1 + b2 + b3 + b4);
    result.append(intermediate);
  }

  return result;

}
string decode_bstring (string text){

  string temp1;
  string temp2;
  string temp3;
  int n = text.length();

  map<string,string> normal_table  {
                                    {"01100001", "a"},
                                    {"01100010", "b"},
                                    {"01100011", "c"},
                                    {"01100100", "d"},
                                    {"01100101", "e"},
                                    {"01100110", "f"},
                                    {"01100111", "g"},
                                    {"01101000", "h"},
                                    {"01101001", "i"},
                                    {"01101010", "j"},
                                    {"01101011", "k"},
                                    {"01101100", "l"},
                                    {"01101101", "m"},
                                    {"01101110", "n"},
                                    {"01101111", "o"},
                                    {"01110000", "p"},
                                    {"01110001", "q"},
                                    {"01110010", "r"},
                                    {"01110011", "s"},
                                    {"01110100", "t"},
                                    {"01110101", "u"},
                                    {"01110110", "v"},
                                    {"01110111", "w"},
                                    {"01111000", "x"},
                                    {"01111001", "y"},
                                    {"01111010", "z"},
                                    {"01000001", "A"},
                                    {"01000010","B" },
                                    {"01000011","C" },
                                    {"01000100", "D"},
                                    {"01000101","E" },
                                    {"01000110","F"},
                                    {"01000111", "G"},
                                    {"01001000" ,"H"},
                                    {"01001001" ,"I"},
                                    {"01001010", "J"},
                                    {"01001011","K" },
                                    {"01001100", "L"},
                                    {"01001101", "M"},
                                    {"01001110", "N"},
                                    {"01001111", "O"},
                                    {"01010000", "P"},
                                    {"01010001", "Q"},
                                    {"01010010", "R"},
                                    {"01010011", "S"},
                                    {"01010100", "T"},
                                    {"01010101", "U"},
                                    {"01010110", "V"},
                                    {"01010111", "W"},
                                    {"01011000", "X"},
                                    {"01011001", "Y"},
                                    {"01011010", "Z"},
                                    {"00110000","0"},
                                    {"00110001","1"},
                                    {"00110010","2"},
                                    {"00110011","3"},
                                    {"00110100","4"},
                                    {"00110101","5"},
                                    {"00110110","6"},
                                    {"00110111","7"},
                                    {"00111000","8"},
                                    {"00111001","9"},
                                    {"00101011","+"},
                                    {"00101111", "/"},
                                    {"00100001","!"},
                                    {"00100000", " "},
                                    {"00101110","."},
                                    {"00101100",","},
                                    {"00111011",";"},
                                    {"00111010",":"},
                                    {"00111111","?"},
                                    {"00100010","\""},
                                    {"00100111","\'"},
                                    {"00111101",""}
  };
  
  temp1 = text.substr(0,8);
  temp2 = text.substr(8,8);
  temp3 = text.substr(16,8);


  // dealing with padding
  // either the last character in a 3-char string is padded
  // or the second its, or there's no padding
  // we replace the padding as the empty string


  temp1 = normal_table[temp1];
  temp2 = normal_table[temp2];
  temp3 = normal_table[temp3];

  text = temp1 + temp2 + temp3;

  return text;
}