using UnrealBuildTool;

public class Structure : ModuleRules
{
	public Structure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
			"BuildFramework",
            "Engine",
            "CoreUObject",
			"ObjectMessaging"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Structure/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Structure/Private"});
    }
}
