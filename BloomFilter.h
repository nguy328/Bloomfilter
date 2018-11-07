#include <string>
#include <vector>

class BloomFilter {
public:

  BloomFilter();
  BloomFilter (int s); // Constructor for the given size (see below).
  ~BloomFilter (); // destructor

  void insert (std::string input);
   /* Add this string to the Bloom Filter.
      Do nothing if the string is already in the Bloom Filter. */

  bool contains (std::string input);
  /* returns whether this string is in the set.
     Being a Bloom Filter, may sometimes return "yes" when the true answer is "no". */ 

protected:
  int hash1 (std::string input) const;
  int hash2 (std::string input) const;
  int hash3 (std::string input) const;

private:
  int getCharVal(const char k) const;
  std::vector<int> getSequence(std::string input) const;
  bool isValid(std::string web);
  int randNum[21];
  unsigned int size = 0;
  bool *hashtable;

};