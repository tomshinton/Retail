using UnrealBuildTool;

public class BuildFramework : ModuleRules
{
	public BuildFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject",
			"InputCore",
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/BuildFramework/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/BuildFramework/Private"});
    }
}
