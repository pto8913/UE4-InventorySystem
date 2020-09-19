// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InventorySystem : ModuleRules
{
	public InventorySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"SlateCore", "Slate", "UMG",
			"GameplayAbilities", "GameplayTags", "GameplayTasks",
		});
	}
}
