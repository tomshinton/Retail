#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FBuildFrameworkTestsModule : public IModuleInterface
{
	virtual void StartupModule() override 
	{
		UE_LOG(LogTemp, Log, TEXT("Loading BuildFrameworkTests"));
	}

	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FBuildFrameworkTestsModule, BuildFrameworkTests)