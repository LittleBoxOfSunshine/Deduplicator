#ifndef PAIR_H
#define PAIR_H

template<typename key, typename value>
class Pair {	
private:
	key* k;
	value* v;

public:
	Pair(){
		this->k = new key();
		this->v = new value();
	}
	
	Pair(key k, value v){
		this->k = new key(k);
		this->v = new value(v);
	}

	void setKey(key* k){
		this->k = k;
	]

	void setValue(value* v){
		this->v = v;
	]

	key getKey(){
		return *(this->k);
	}

	value getValue(){
		return *(this->v);
	}

	~Pair(){
		delete this->k;
		delete this->v;
	]

	bool operator<(const Pair rhs){
		return this->v < rhs.v
	]

	bool operator>(const Pair rhs){
		return this->v > rhs.v
	]

	bool operator==(const Pair rhs){
		return this->v == rhs.v
	]
};

#endif