// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class GameController : ModuleRules
{
	public GameController(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "PaperZD", "Paper2D", "DBTween", "UMG", "SerialCOM"});

        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(ModuleDirectory, "../../Plugins/DBTween/Source/DBTween/Public"),
            Path.Combine(ModuleDirectory, "../../Plugins/SerialCOM/Source/SERIALCOM/Public")
        });

        CppStandard = CppStandardVersion.Cpp20;

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
