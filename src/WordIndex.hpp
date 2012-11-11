#ifndef WORDINDEX_H
#define WORDINDEX_H
#include <string>
#include <string.h> // for strcmp
#include <tr1/functional> // for std::tr1::hash
#include <sparsehash/dense_hash_map>
#include "Word.hpp"

using google::dense_hash_map;

struct hashstr
{
  std::tr1::hash<string> hasher;
  long operator()(const string& s1) const
  { 
	return hasher(s1);
//	return CityHash64(s1.data(),s1.size());
  }
};



class WordIndex
{
private:
  dense_hash_map<string, unsigned int> map;
public:
  WordIndex() : map(){
    map.set_empty_key("");

  }

  int Put(const std::string& field, const std::string& token, unsigned int value) {
	map.insert(make_pair(field+token,value));
	return 1;
  }

  int Put(const Word& word, unsigned int value) {
	map.insert(make_pair(word.toString(),value));
	return 1;
  }

  int Get(const std::string& field, const std::string& token, unsigned int& value) {
	auto found = map.find(field+token);
	if (found != map.end()){
       value = found->second;
       return 1;
    } 
	return 0;		
  }


  int Get(const Word& word, unsigned int& value) {
	auto found = map.find(word.toString());
	if (found != map.end()){
       value = found->second;
       return 1;
    } 
	return 0;		
  }

  ~WordIndex() {
	
  }
};
#endif // WORDINDEX_H
