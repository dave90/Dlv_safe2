/*
 * AbstractSimplifier.h
 *
 *  Created on: 18/mar/2015
 *      Author: Zeiven
 */

#ifndef DLV2_SAFE_SRC_GROUNDER_GROUND_ABSTRACTSIMPLIFIER_H_
#define DLV2_SAFE_SRC_GROUNDER_GROUND_ABSTRACTSIMPLIFIER_H_

#include "ProgramGrounder.h"
namespace DLV2 {
namespace grounder {

	class AbstractSimplifier
	{
		public:
			virtual bool simplifier(Rule*& ,const vector<vector<unsigned>>& )=0;
	};
}
}

#endif /* DLV2_SAFE_SRC_GROUNDER_GROUND_ABSTRACTSIMPLIFIER_H_ */
