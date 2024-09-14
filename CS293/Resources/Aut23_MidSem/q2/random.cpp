#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char *argv[]) {

  if( argc < 2 ) {
    cout<<"Give number of random numbers \n"
      <<endl;
    return 1;
  }
  // Providing a seed value
  srand((unsigned) time(NULL));
  
  for( unsigned i=0; i < atoi(argv[1]); i++) {
  // Get a random number
    int random = rand();
    cout<<random<<endl;
  }
  // Print the random number

  return 0;
}
