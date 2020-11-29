#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FStructureModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FStructureModule, Structure)