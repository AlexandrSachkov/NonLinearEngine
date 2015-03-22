#ifndef NL_SSCENE_H_
#define NL_SSCENE_H_

namespace NLE 
{
	namespace Core 
	{
		class SObject;
		class SScene 
		{
		public:
			virtual ~SScene(){}
			virtual void addObject(SObject* object) = 0;
		};
	}
}

#endif