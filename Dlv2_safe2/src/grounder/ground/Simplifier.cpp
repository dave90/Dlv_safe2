/*
 * Simplifier.cpp
 *
 *  Created on: 23/mar/2015
 *      Author: Zeiven
 */


#include "Simplifier.h"
#include "ProgramGrounder.h"
namespace DLV2 {
namespace grounder {

	void Simplifier::simplifier(Rule*& currentRule,const vector<vector<unsigned>>& tableSearcher)
	{

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
	}

//Atom* Simplifier::getSearchAtom(Atom& atom)
//{
//	Atom* searchAtom=0;
//	PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((atom).getPredicate()->getIndex());
//	searchAtom=predicateExt->getGenericAtom(atom);
//	return searchAtom;
//}


}
}

