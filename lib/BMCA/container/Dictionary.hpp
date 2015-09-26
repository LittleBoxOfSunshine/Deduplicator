#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>

#include "AVL.hpp"
#include "Pair.hpp"

template<typename T>
class Dictionary {
private:
	AVLTree<Pair<std::string, T>> data;

	//TODO: setable overwrite behavior, default is that put overwrites
	//TODO: remove functions (waiting on completion of remove functions in avl tree class
	
public:
	Dictionary(){

	}

	bool put(std::string key, T value){
		data.insert(Pair(key, value));
	}

	T get(std::string key){
		return data.find(key).getValue();
	}

	T get(std::string * key){
		return data.find(*key).getValue();		
	}

	bool remove(std::string key){
		
	}

	bool remove(std::string * key){

	}

	bool contains(std::string key){
		return data.contains(key);
	}

	bool contains(std::string * key){
		return data.contains(*key);
	}

	int size(){
		return data.height();
	}

	void clear(){
		data.clear();
	}
}

#endif