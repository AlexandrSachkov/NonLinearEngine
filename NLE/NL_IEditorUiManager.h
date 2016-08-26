#ifndef NL_I_EDITOR_UI_MANAGER_H_
#define NL_I_EDITOR_UI_MANAGER_H_

namespace NLE
{
	namespace UI
	{
		class IEditorUiManager
		{
		public:
			virtual void show(bool show) = 0;
		};
	}
}

#endif
