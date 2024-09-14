#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv) {

  if( argc < 2 ) {
    cout<<"Give a sequence of paranthesses!\n"
        <<endl;
    return 1;
  }
  auto s = string(argv[1]);
  int matched_length = 0;
  cout << s << " " << matched_length <<  endl;
}
