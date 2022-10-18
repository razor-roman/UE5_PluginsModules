// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PluginsModules : ModuleRules
{
	public PluginsModules(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "MediaAssets" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","Slate","DesktopPlatform","UMG" });
	}
}
