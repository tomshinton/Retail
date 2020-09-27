// Tom Shinton - Retail 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class RetailTarget : TargetRules
{
	public RetailTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Retail" } );
	}
}
