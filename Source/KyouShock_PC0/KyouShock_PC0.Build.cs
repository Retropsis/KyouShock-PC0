// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KyouShock_PC0 : ModuleRules
{
	public KyouShock_PC0(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });
	}
}
