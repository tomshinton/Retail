using UnrealBuildTool;

public class BuildFrameworkTests : ModuleRules
{
	public BuildFrameworkTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject", 
			"BuildFramework"
        });
		
		PrivateIncludePaths.AddRange(new string[] { "Tests/BuildFrameworkTests/Private" });
    }
}
