# cpp_b64_enc
A small program I wrote to encode ASCII text to base 64, using c++, as part of my process of learning c++.

# Yes, it actually works
After fixing a few small fencepost errors and memory bound issues, the program works as intended. Invoking the compiled program (for linux users, that should be c++ base64-decode.cpp base64-encode.cpp main.cpp -o output) with a single command line argument being your text to encode, will will return the encoding and decoded text on the command line.

# How does it work?
This program is an almost word-for-word copy of the method recommended for base64 encoding found in (https://datatracker.ietf.org/doc/html/rfc4648), RFC4648. It seemed as good as of any method.

The program accepts alphanumerical input and splits it into three byte chunks at a time, which are concatenated and then split into 6-bit segments, which are then changed into their base 64 equivalent using cpp's map feature.

The decoding takes alphanumerical input, and turns four characters at a time into their 6 bit representation (the inverse of the function which maps characters to 6-bit binary strings), concatenting those and converting them into three byte chunks which are then converted from binary to ascii text.

I should note explicilty that this program doesn't cover the entirety of the ASCII set when it comes to decoding. The alphanumerical and punctation characters are covered, since they seemed to be the most pertinent to me.
