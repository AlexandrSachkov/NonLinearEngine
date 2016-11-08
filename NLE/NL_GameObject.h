#ifndef NL_GAME_OBJECT_H_
#define NL_GAME_OBJECT_H_

#include "NL_ThreadLocal.h"
#include <string>

namespace NLE
{
	namespace GAME
	{
		class RenderingComponent;
		class ScriptingComponent;
		class GameObject
		{
		public:
			GameObject();
			~GameObject();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				auto name = cnv.to_bytes(_name);
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_uuid)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::string name;
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_uuid)
					);

				_name = cnv.from_bytes(name);
			}

			unsigned long long getUuid();
			void setName(std::wstring name);
			std::wstring getName();
			void setRenderingComponent(RenderingComponent* component);
			void setScriptingComponent(ScriptingComponent* component);
			RenderingComponent* getRenderingComponent();
			ScriptingComponent* getScriptingComponent();

		private:
			RenderingComponent* _renderingComponent;
			ScriptingComponent* _scriptingComponent;

			std::wstring _name;
			unsigned long long _uuid;
		};
	}
}

#endif
