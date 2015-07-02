/*
 * Simplifier.cpp
 *
 *  Created on: 23/mar/2015
 *      Author: Zeiven
 */

#include "Simplifier.h"
#include "ProgramGrounder.h"
#include "iostream"
namespace DLV2 {
namespace grounder {
	bool Simplifier::simplifier(Rule*& currentRule,const vector<vector<unsigned>>& tableSearcher)
	{
		if(currentRule->isChoiceRule()) {//salta
			cout<<"regola choice salta";
			currentRule->print();
			return false;
		}

		cout<<"inizio semplificazione regola: ";
		currentRule->print();
		int sizeHead=currentRule->getSizeHead();
		bool truthValue=!currentRule->areThereUndefinedAtomInBody() && sizeHead==1;
		unsigned index_head_atom=0;
		Atom* searchAtom=0;

		for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++index_head_atom)
		{
			cout<<"entro nel for con atomo corrente: ";
			(*atom)->print();
			cout<<endl;
			PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((*atom)->getPredicate()->getIndex());
			searchAtom=predicateExt->getAtom((*atom));
			if(searchAtom==nullptr)
			{
				cout<<"atomo non presente in tabella (aggiungo)";
				(*atom)->print();
				(*atom)->setFact(truthValue);
				currentRule->setAtomToSimplifyInHead(index_head_atom,truthValue);
				for(unsigned i=0;i<tableSearcher[index_head_atom].size();++i)
					predicateExt->addAtom(tableSearcher[index_head_atom][i],*atom);
			}
			else
			{
				cout<<"atomo presente in tabella"<<endl;
				if(truthValue)
				{
					if(searchAtom->isFact())
					{
						currentRule->setAtomToSimplifyInHead(index_head_atom,truthValue);
						return false;
					}
					else
						searchAtom->setFact(true);
						continue;
				}

				if(!(*atom)->isFact() && searchAtom->isFact())
				{
					for(unsigned  i=0;i<sizeHead;i++)
					{
						currentRule->setAtomToSimplifyInHead(i,true);
					}
					return false;
				}
//
//				cout<<"atomo non semplificabile (indefinito)"<<endl;
//				currentRule->setAtomToSimplifyInHead(index_head_atom,false);

			}
		}
		return false;
	}
}
}


//		Rule* ruleSimplified=new Rule;
//		unsigned index_body_atom=0;
//		unsigned index_head_atom=0;
//		Atom* searchAtom=0;
//		int sizeBody=0;
//		for(auto atom=currentRule->getBeginBody();
//				atom!=currentRule->getEndBody();++atom,++index_body_atom)
//		{
//			if(atom_undef_inbody[index_body_atom]){
//				ruleSimplified->addInBody(*atom);
//				sizeBody++;
//			}
//			else{
//				Atom* searchAtom=0;
//				PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((*atom)->getPredicate()->getIndex());
//				searchAtom=predicateExt->getGenericAtom(*atom);
//				if(searchAtom!=nullptr) //if atom is in table check if it is true or not
//				{
//					if(!searchAtom->isFact() && !searchAtom->isNegative()) //false atom in body => delete rule
//					{
//						delete currentRule;
//						return;
//					}
//				}
//		}
//	}
//
//		if(sizeBody==0 && currentRule->getSizeHead()==1)
//		{
//
//				for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++index_head_atom)
//				{
//					ruleSimplified->addInHead(*atom);
//					PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((*atom)->getPredicate()->getIndex());
//					searchAtom=predicateExt->getGenericAtom((*atom));
//					if(searchAtom==nullptr)
//					{
//						GenericAtom* genericHeadAtom=new GenericAtom;
//						genericHeadAtom->setTerms((*atom)->getTerms());
//						genericHeadAtom->setFact(true);
//						for(unsigned i=0;i<tableSearcher[index_head_atom].size();++i)
//							predicateExt->addGenericAtom(tableSearcher[index_head_atom][i],genericHeadAtom);
//					}
//					else
//					{
//						searchAtom->setFact(true);
//					}
//				}
//		}
//
//		delete currentRule;
//		currentRule=ruleSimplified;
//	}

//Atom* Simplifier::getSearchAtom(Atom& atom)
//{
//	Atom* searchAtom=0;
//	PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((atom).getPredicate()->getIndex());
//	searchAtom=predicateExt->getGenericAtom(atom);
//	return searchAtom;
//}

