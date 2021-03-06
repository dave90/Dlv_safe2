/*
 * Instance.h
 *
 *  Created on: 24/mar/2014
 *      Author: Jessica
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <iostream>

#include "../../util/Options.h"
#include "../../util/Assert.h"
#include "AtomSearcher.h"

using namespace std;

namespace DLV2{

namespace grounder{

class PredicateInformation{
public:
	PredicateInformation(unsigned arity);
	bool isOnlyPositive(unsigned index) const;
	bool isOnlyNegative(unsigned index) const;
	bool isOnlyPositive() const;
	bool isOnlyNegative() const;
	void update(Atom* atom);
	int getMax(unsigned index) const;
	int getMin(unsigned index) const;

private:
	vector<int> min;
	vector<int> max;
};


/**
 * This class represents the extension of each predicate (instances).
 * The class may have multiple table of atoms and for each table have an AtomSearcher associate
 */

class PredicateExtension {
public:
	///Constructors
	PredicateExtension(Predicate* predicate, unsigned tableNumber = 2): predicate(predicate), predicateInformation(new PredicateInformation(predicate->getArity())){
		if(MAX_TABLE_NUMBER){
			tables.reserve(MAX_TABLE_NUMBER);
			atomSearchers.reserve(MAX_TABLE_NUMBER);
		}
		for(unsigned i=0;i<tableNumber;++i)
			tables.push_back(new AtomVector());
	}

	///Getter for the predicate
	Predicate* getPredicate() const {return predicate;}

	///Returns the i-th AtomSeacher in atomSearchers
	AtomSearcher* getAtomSearcher(unsigned i){
		setAtomSearchers();
		assert_msg(i<atomSearchers.size(),"The specified AtomSearche doesn't exist.");
		return atomSearchers[i];
	}

	/// Add table and an AtomSearcher
	void addTable(){
		tables.push_back(new AtomVector());
		setAtomSearchers();
	}

	///Add a given atom in specified table
	bool addAtom(unsigned table, Atom* genericAtom, bool search = false){
		assert_msg(table<tables.size(),"The specified table doesn't exist.");
		if(search){
			AtomSearcher *atomSearcher=getAtomSearcher(table);
			if((atomSearcher->findAtom(genericAtom))!=nullptr)
				return false;
		}
		if(atomSearchers.size()>table){
			AtomSearcher *atomSearcher=getAtomSearcher(table);
			atomSearcher->add(genericAtom);
		}
		tables[table]->push_back(genericAtom);
		predicateInformation->update(genericAtom);
		return true;
	}

	///Get an atom in specified table
	Atom* getAtom(unsigned table, Atom* genericAtom){
		assert_msg(table<tables.size(),"The specified table doesn't exist.");
		if(tables[table]->size()==0) return nullptr;
		AtomSearcher* atomSearcher=getAtomSearcher(table);
		Atom* atomFound=atomSearcher->findAtom(genericAtom);
		return atomFound;
	}

	///Get a atom searching in all table
	Atom* getAtom(Atom* genericAtom){
		for(unsigned i=0;i<tables.size();++i){
			if(tables[i]->size()==0) continue;
			Atom* atomFound=getAtom(i,genericAtom);
			if(atomFound!=nullptr)
				return atomFound;
		}
		return nullptr;
	}

	 //Moves the content of the tableFrom (source) to the tableTo (destination)
	 void swapTables(unsigned tableFrom,unsigned tableTo);

	///Printer method for a single table
	inline void print(unsigned table){for(auto fact:*tables[table]){ClassicalLiteral::print(predicate,fact->getTerms(),false,false); cout<<"."<<endl;}}

	///Destructor
	~PredicateExtension();

	static void setMaxTableNumber(unsigned int maxTableNumber) {MAX_TABLE_NUMBER = maxTableNumber;}

	PredicateInformation* getPredicateInformation() const {return predicateInformation;}

private:
	///The predicate
	Predicate* predicate;

	///For each AtomTable in tables is present an AtomSeacher in atomSearchers
	///The vector of tables
	vector<AtomVector*> tables;
	///The vector of  AtomSeacher
	vector<AtomSearcher*> atomSearchers;

	static unsigned int MAX_TABLE_NUMBER;

	///A PredicateInformation object that stores the information about the max and the min values of each term in the instances of the predicate
	PredicateInformation* predicateInformation;

	///This method configures the searching strategy for each table
	void setAtomSearchers();

};

/**
 * This class stores the Predicate Extensions for all the predicate.
 * Is a Singleton.
 */

class PredicateExtTable {
public:

	///This method adds an Instance for a predicate
	void addPredicateExt(Predicate* p) {
		if(!predicateExtTable.count(p->getIndex())){
			PredicateExtension *is=new PredicateExtension(p);
			predicateExtTable.insert({p->getIndex(),is});
		}
	};

	///Getter for the instances of a predicate
	PredicateExtension* getPredicateExt(Predicate* p) {
		auto result= predicateExtTable.find(p->getIndex());
		if(result==predicateExtTable.end()) return nullptr;
		return (result->second);
	};

	///Getter for the instances of a predicate index
	PredicateExtension* getPredicateExt(index_object p) {
		auto result= predicateExtTable.find(p);
		if(result==predicateExtTable.end()) return nullptr;
		return (result->second);
	};

	///This method return the size of the map of instances
	unsigned int getSize() {return predicateExtTable.size();};

	///Printer method for the first table in Predicate Extension
	void print(unsigned table) {for (auto& i : predicateExtTable) i.second->print(table);};

	///Destructor
	~PredicateExtTable(){for(auto pair_predExt:predicateExtTable) delete pair_predExt.second;};

	static PredicateExtTable* getInstance(){
		if(predicateExtTable_== nullptr)
			predicateExtTable_= new PredicateExtTable;
		return predicateExtTable_;
	}

private:
	///Constructor
	PredicateExtTable(){}

	static PredicateExtTable *predicateExtTable_;

	///The map that stores all the Predicate Extension
	unordered_map<index_object,PredicateExtension*> predicateExtTable;
};

};

};

#endif /* INSTANCE_H_ */
