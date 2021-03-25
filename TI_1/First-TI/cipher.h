#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string RailCipher(string input, int key);
string RailDecipher(string input, int key);

string ColumnCipher(string input, string key);
string ColumnDecipher(string input, string key);

string LatticeCipher(string input);
string LatticeDecipher(string input);

void Matrix(string key, char arr[5][5], int dec);
string PleiferCipher(string input, string key, int dec);