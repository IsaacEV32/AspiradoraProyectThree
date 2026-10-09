// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AspiradoraGame : ModuleRules
{
	public AspiradoraGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AspiradoraGame",
			"AspiradoraGame/Variant_Platforming",
			"AspiradoraGame/Variant_Platforming/Animation",
			"AspiradoraGame/Variant_Combat",
			"AspiradoraGame/Variant_Combat/AI",
			"AspiradoraGame/Variant_Combat/Animation",
			"AspiradoraGame/Variant_Combat/Gameplay",
			"AspiradoraGame/Variant_Combat/Interfaces",
			"AspiradoraGame/Variant_Combat/UI",
			"AspiradoraGame/Variant_SideScrolling",
			"AspiradoraGame/Variant_SideScrolling/AI",
			"AspiradoraGame/Variant_SideScrolling/Gameplay",
			"AspiradoraGame/Variant_SideScrolling/Interfaces",
			"AspiradoraGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
