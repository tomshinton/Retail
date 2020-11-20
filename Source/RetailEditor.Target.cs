// Tom Shinton - Retail 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class RetailEditorTarget : TargetRules
{
	public RetailEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] 
		{ 
			"Retail",
		});

        ExtraModuleNames.AddRange(new string[]
		{
            "BuildFrameworkTests",
	}	);
    }
}
