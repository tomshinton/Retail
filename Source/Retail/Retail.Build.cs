// Tom Shinton - Retail 2020

using UnrealBuildTool;

public class Retail : ModuleRules
{
	public Retail(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{

		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
			"BuildFramework",
			"Core",
			"CoreUObject",
			"Engine",
			"Movement",
		});
	}
}
