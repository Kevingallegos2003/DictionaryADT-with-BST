//Kevin Gallegos 1858764 PA7

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

// Private Construct---------------------------

Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

//classs construct and destruct
Dictionary::Dictionary(){
	nil = new Node("NIL", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
        nil = new Node("NIL", -1);
        root = nil;
        current = nil;
	//cout<<"size of deez"<<D.size()<<endl;
        num_pairs = D.size();
}
Dictionary::~Dictionary(){
	clear();
	delete nil;
}
//helpers--------------------
void Dictionary::inOrderString(std::string& s, Node* R)const{
	if(R != nil){
		inOrderString(s, R->left);
		s.append(R->key);
		s.append(" : ");
		s.append(std::to_string(R->val));
		s.append("\n");
		inOrderString(s,R->right);
	}
}
void Dictionary::inOrderStringKeys(std::string& s, Node* R)const{
        if(R != nil){
                inOrderStringKeys(s, R->left);
                s.append(R->key);
                s.append("\n");
                inOrderStringKeys(s,R->right);
        }
}



void Dictionary::preOrderString(std::string& s, Node* R)const{
	if (R != nil) {
		s.append(R->key);
		s.append(" : ");
		s.append(std::to_string(R->val));
		s.append("\n");
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderStringKeys(std::string& s, Node* R)const{
	if (R != nil) {
                s.append(R->key);
                s.append("\n");
                preOrderStringKeys(s, R->left);
                preOrderStringKeys(s, R->right);
        }
}

void Dictionary::preOrderCopy(Node* R, Node* N){
	if (R != N) {
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
		//remove(N->key);
	}
}

void Dictionary::postOrderDelete(Node* R){
	if (R != nil) {
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}

}

Dictionary::Node* Dictionary::search(Node* R, keyType k)const{
	while(R != nil) {
		if(R == nil || k == R->key){return R;}
		else if (k < R->key){return search(R->left, k);}
		else if (k > R->key){return search(R->right, k);}
	}
	return nil;

}

Dictionary::Node* Dictionary::findMin(Node* R){
	while (R->left != nil){
		R = R->left;
	}
	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
	while (R->right != nil){
		R = R->right;
	}
	return R;
}

Dictionary::Node* Dictionary::findNext(Node* N){
	if (N->right != nil) {
		return findMin(N->right);
	}
	Node* next = N->parent;
	while (next != nil && N == next->right){
		N = next;
		next = next->parent;
	}
	return next;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N->left != nil) {
		return findMax(N->left);
	}
	Node* prev = N->parent;
	while (prev != nil && N == prev->left){
		N = prev;
		prev = prev->parent;
	}
	return prev;
}


//access--------------------------
int Dictionary::size()const{
	return num_pairs;
}

bool Dictionary::contains(keyType k)const{
	if (search(root, k) != nil){return true;}
	return false;

}

valType& Dictionary::getValue(keyType k)const{
	if (contains(k)==false) {
		cout<<"Dictionary: getValue(): key "<<k;
		throw std::invalid_argument(" does not exist");
	}
	Node* result = search(root, k);
	return result->val;
}

bool Dictionary::hasCurrent()const{
	if(current == nil){return false;}
	else{return true;}
}

keyType Dictionary::currentKey()const{
	if(current->key == nil->key){
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}

valType& Dictionary::currentVal() const{
	if(current->val == nil->val){
                throw std::logic_error("Dictionary: currentVal(): current undefined");
        }
	return current->val;
}
//manipulation-------------------------------
void Dictionary::clear() {
	if(num_pairs != 0 && root != this->nil){
		postOrderDelete(root);
		root = nil;
		current = nil;
		num_pairs = 0;
	}
}

void Dictionary::setValue(keyType k, valType v){
	Node* P = nil;
	Node* m = new Node(k, v);
	Node* R = root;
	while (R != nil) {
		P = R;
		if (m->key < R->key) {
			R = R->left;
		}
		else if (m->key > R->key) {
			R = R->right;
		}
		else {
			R->val = m->val;
			delete m;
			return;
		}
	}
	m->parent = P;
	if (P == nil) {
		root = m;
	}
	else if (m->key < P->key) {
		P->left = m;
	}
	else {
		P->right = m;
	}
	m->left = nil;
	m->right = nil;
	num_pairs++;
}

void Dictionary::transplant(Node* u, Node* v) {
	if (u->parent == nil) {
		root = v;
		//delete u;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
		//delete u;
	}
	else {
		u->parent->right = v;
		//delete u;
	}
	if (v != nil) {
		v->parent = u->parent;
		//delete u;
	}
	//delete u;
}

void Dictionary::remove(keyType k) {
	if (contains(k) == false) {
		cout<<"Dictionary: remove(): key "<<k;
		throw std::invalid_argument(" does not exist");
	}
	Node* m = search(root, k);
	if (m->left == nil) {
		transplant(m, m->right);
		delete m;
		num_pairs--;
	}
	else if (m->right == nil) {
		transplant(m, m->left);
		delete m;
		num_pairs--;
	}
	else {
		Node* min = findMin(m->right);
		if (min->parent != m) {
			transplant(min, min->right);
			min->right = m->right;
			min->right->parent = min;
		}
		transplant(m, min);
		min->left = m->left;
		min->left->parent = min;
		delete m;
		num_pairs--;
	}

}

void Dictionary::begin() {
	if (num_pairs != 0) {
		current = findMin(root);
	}
}

void Dictionary::end() {
	if (num_pairs != 0) {
		current = findMax(root);
	}
}

void Dictionary::next() {
	if (hasCurrent() == false) {
		throw std::invalid_argument("Dictionary: next(): current undefined");
	}
	this->current = findNext(this->current);
}

void Dictionary::prev() {
	if (hasCurrent() == false) {
		throw std::invalid_argument("Dictionary: prev(): current undefined");
	}
	current = findPrev(current);
}

//---other---------

std::string Dictionary::to_string()const{
	std::string s;
	inOrderString(s, root);
	return s;
}

std::string Dictionary::pre_string()const{
	std::string s;
	//Node* N = root;
	preOrderStringKeys(s, root);
	return s;
	/*
	Node* N = root;
	if (N != nil) {
                while(N->left!=nil){
			N = N->left;
		}
		while(N != root){
			N = N->parent;
			s.append(N->left->key);
			s.append("\n");
			N->
		}
                //s.append(" : ");
                //s.append(std::to_string(R->val));
                //s.append("\n");
		if(N->
                pre_string();
		N = N->left;
                pre_string();
        }
	return s;
	*/
}

bool Dictionary::equals(const Dictionary& D) const {
	std::string T1 = this->to_string();
	//cout<<"string is " << endl<<T1<< endl;
	std::string T2 = D.to_string();
	//cout<<"string is " << endl<< T2<< endl;
	if (T1 == T2 && num_pairs == D.num_pairs) {
		//cout<<"trueeeee"<<endl;
		return true;
	}
	else{
		return false;
	}
}

//---------operators------------

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
	return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
	return (A.equals(B));
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
	clear();
	preOrderCopy(D.root, D.nil);//null D.root
	//remove("NIL");
	//postOrderDelete(this->root);	
	return *this;
}
