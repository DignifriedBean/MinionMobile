using UnrealBuildTool;
using System.Collections.Generic;

public class MinionMobileTarget : TargetRules
{
	public MinionMobileTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("MinionMobile");
	}
}
