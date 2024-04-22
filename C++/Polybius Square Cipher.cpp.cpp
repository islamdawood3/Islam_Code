#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to create a mapping from characters to their corresponding two-digit numbers based on the key
unordered_map<char, string> create_square(const string& key) {
  unordered_map<char, string> square;
  int index = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      square[key[index]] = to_string(i) + to_string(j);
      ++index;
    }
  }
  // Handle cases where 'J' is not present in the key (replace with 'I')
  if (square.find('J') == square.end()) {
    square['J'] = square['I'];
  }
  return square;
}

// Function to encrypt a message using the provided key and character mapping
string encrypt(const string& message, const unordered_map<char, string>& square) {
  string ciphertext;
  for (char ch : message) {
    if (isalpha(ch)) {
      ch = toupper(ch);  // Convert to uppercase for consistent mapping
      ciphertext += square.at(ch);
    }
  }
  return ciphertext;
}

// Function to decrypt a ciphertext using the provided key and character mapping
string decrypt(const string& ciphertext, const unordered_map<char, string>& square) {
  string plaintext;
  for (int i = 0; i < ciphertext.size(); i += 2) {
    string number = ciphertext.substr(i, 2);
    for (auto it = square.begin(); it != square.end(); ++it) {
      if (it->second == number) {
        plaintext += it->first;
        break;
      }
    }
  }
  return plaintext;
}

int main() {
  string key, message;

  cout << "Enter the key (5 unique digits): ";
  cin >> key;

  cout << "Enter the message (uppercase letters only, no spaces): ";
  cin >> message;

  unordered_map<char, string> square = create_square(key);
  string ciphertext = encrypt(message, square);
  string decrypted_text = decrypt(ciphertext, square);

  cout << "Plaintext: " << message << endl;
  cout << "Key: " << key << endl;
  cout << "Ciphertext: " << ciphertext << endl;
  cout << "Decrypted Text: " << decrypted_text << endl;

  return 0;
}
