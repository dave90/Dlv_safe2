/*
 * Simplifier.h
 *
 *  Created on: 18/mar/2015
 *      Author: Zeiven
 */

#ifndef DLV2_SAFE_SRC_GROUNDER_GROUND_SIMPLIFIER_H_
#define DLV2_SAFE_SRC_GROUNDER_GROUND_SIMPLIFIER_H_


#include "ProgramGrounder.h"
#include "AbstractSimplifier.h"
namespace DLV2 {
namespace grounder {

class Simplifier : public AbstractSimplifier
{
	public:
		Simplifier(){};
		virtual bool simplifier(Rule*& ,const vector<vector<unsigned>>&);

	private:

};

}
}



#endif /* DLV2_SAFE_SRC_GROUNDER_GROUND_SIMPLIFIER_H_ */
