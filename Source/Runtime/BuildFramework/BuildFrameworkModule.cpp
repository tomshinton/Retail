#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FBuildFrameworkModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FBuildFrameworkModule, BuildFramework)