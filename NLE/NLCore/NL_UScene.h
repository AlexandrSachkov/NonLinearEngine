#ifndef NL_USCENE_H_
#define NL_USCENE_H_

#include <cstdint>
#include <unordered_map>

namespace NLE
{
	namespace Core
	{
		class SScene;
		class UObject;
		class UScene 
		{
		public:
			UScene();
			~UScene();

			bool initialize();
			void release();

			void attachScene(uint_fast8_t sysId, SScene* scene);

			void addObject(UObject* object);

		private:
			std::unordered_map<uint_fast8_t, SScene*> _sysScenes;
		};
	}
}

#endif