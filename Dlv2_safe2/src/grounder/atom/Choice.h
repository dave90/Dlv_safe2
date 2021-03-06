/*
 * Choice.h
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#ifndef CHOICE_H_
#define CHOICE_H_

#include "Atom.h"
#include <string>

using namespace std;

namespace DLV2{

namespace grounder{

class Choice: public Atom {
public:
	///Default constructor
	Choice(): firstBinop(Binop::NONE_OP), secondBinop(Binop::NONE_OP){terms.push_back(nullptr);terms.push_back(nullptr);};

	/** Constructor
	 * @param fB set the first binary operation
	 * @param sB set the second binary operation
	 * @param t set the terms vector
	 * @param cE set the choice elements vectors
	 */
	Choice(Binop fB, Binop sB, vector<Term*> t, vector<ChoiceElement*> cE)
		: Atom(t), firstBinop(fB), secondBinop(sB), choiceElements(cE) {};

	///Return the term of variable present in the Atom
	virtual set_term getVariable();

	///Getter method for the first binary operation
	Binop getFirstBinop() const {return firstBinop;};
	///Setter method for the first binary operation
	void setFirstBinop(Binop firstBinop) {this->firstBinop = firstBinop;};
	///Getter method for the second binary operation
	Binop getSecondBinop() const {return secondBinop;};
	///Setter method for the second binary operation
	void setSecondBinop(Binop secondBinop) {this->secondBinop = secondBinop;};
	///Getter method for the choice elements
	const vector<ChoiceElement*>& getChoiceElements() const {return choiceElements;};
	///Setter method for the choice elements
	void setChoiceElements(const vector<ChoiceElement*>& choiceElements) {this->choiceElements = choiceElements;};
	///Returns the choice elements size
	unsigned getChoiceElementsSize() const {return choiceElements.size();}
	///Returns the i-th choice element
	ChoiceElement* getChoiceElement(unsigned i) const {return choiceElements[i];}
	///Set first guard of the choice
	virtual void setFirstGuard(Term* lower){terms[0]=lower;};
	///Set second guard of the choice
	virtual void setSecondGuard(Term* upper){if(terms.size()==0) terms[0]=0; terms[1]=upper;};
	///Get lower guard of the choice
	virtual Term* getFirstGuard(){return terms[0];};
	///Get upper guard of the choice
	virtual Term* getSecondGuard(){return terms[1];};
	///Add a choice element
	virtual void addChoiceElement(ChoiceElement* choiceElement){choiceElements.push_back(choiceElement);}
	///Add a choice element composed with the atom
	virtual void addSingleChoiceElement(Atom* atom){
		ChoiceElement *element=new ChoiceElement;
		element->add(atom);
		choiceElements.push_back(element);
	}

	virtual bool isChoice(){return true;}

	///This method compute the resulting hash of a choice atom TODO
	size_t getHash() const {return 0;};

	virtual void print();

	//TODO
	virtual bool operator==(const Atom& a){return false;};
	virtual size_t hash(){return 0;};

	virtual Atom* clone();

	///Return the predicate of classical literal (the first atom in choice elements) in choice elements
	virtual set_predicate getPredicates() const {return getClassicalPredicates();};
	virtual unordered_set<index_object> getPredicatesIndices() const {
		set_predicate predicates=getClassicalPredicates();
		unordered_set<index_object> indices;
		for(auto p:predicates)
			indices.insert(p->getIndex());
		return indices;
	}

	///Return the predicate of classical literal (the first atom in choice elements) in choice elements
	virtual set_predicate getClassicalPredicates()const{
		set_predicate predicates;
		for(auto& element:choiceElements){
			auto predicate_in_atom=element->getFirstAtom()->getPredicate();
			predicates.insert(predicate_in_atom);
		}

		return predicates;
	}

	/// Return the variable to safe:
	///		- the variables of the first atom of each choice element
	/// 	- the variables of each negative atoms in each choice element
	///		- the variables in the guards
	set_term getVariableToSave();

	//Return the variable in the guard of an aggregate
	virtual set_term getGuardVariable();

	///Destructor
	virtual ~Choice() {
		for (auto& choiceElement : choiceElements)
			delete choiceElement;
	}

	void getGuardVaribale(set_term& terms_variable);

	virtual void deleteAtoms() {for(auto& choiceElem:choiceElements) choiceElem->deleteAtoms();}

	virtual bool isDefaultGuard(){
		if(firstBinop==NONE_OP && secondBinop==GREATER_OR_EQ && terms[1]->getIndex()==TermTable::getInstance()->term_zero->getIndex())
			return true;
		return false;
	}

private:
	///First binary operation
	Binop firstBinop;
	///Second binary operation
	Binop secondBinop;
	//Vector of choice elements
	vector<ChoiceElement*> choiceElements;

	/* For the vector of terms, it contains the first and the second term of comparison.
	 * Notice that the vector contains the terms in the same order as they appear: the first term in position 0, the second in position 1.
	 */
};

};

};

#endif /* CHOICE_H_ */
