//Kevin Gallegos 1858764 PA7

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
	/*
	Dictionary A;
	A.setValue("urmom", 5);
	A.setValue("tacos!!!", 2);
	A.setValue("pizza!", 8);
	A.setValue("loser", 23);
	cout<<A<<endl;
	*/
	   string s;
   int x;
   string S[] =   {
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   {
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                  };

   Dictionary A;
   Dictionary B;
   Dictionary C;

   cout << endl;


   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }

   // call operator=()
   B = A;

   //cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "A==B is " << endl << (B==A?"true":"false") << endl;
   
   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);
   C = B;
   cout << "A==B is " << endl << (B==A?"true":"false") << endl;
   cout << "C==B is " << endl << (B==C?"true":"false") << endl;
   cout << "C==A is " << endl << (A==C?"true":"false") << endl;
   cout<<"C = "<< endl << C<<endl;
      // perform alterations on A
   cout << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << A.getValue("hemiolia") << endl << endl;
      // remove some pairs from A
      //A.remove("cul");
         // remove some pairs from A
   for(int i=0; i<13; i++){
      cout << "removing " << T[i] << " from Dictionary A" << endl;
      A.remove(T[i]);
   }



	return( EXIT_SUCCESS );
}

