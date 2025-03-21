/**
 * @file 		GronkUtils.Build.cs
 * @brief 		The module rules for the GronkUtils module.
 * @copyright 	Grant Wilk, all rights reserved.
 */

using UnrealBuildTool;
using System.IO;


public class GronkUtils : ModuleRules
{
	public GronkUtils(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Public"),
			}
		);
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Private")
			}
		);
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
			}
		);
	}
}
