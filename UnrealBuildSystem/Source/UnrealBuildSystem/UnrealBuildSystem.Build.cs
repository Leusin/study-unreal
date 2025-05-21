// Source/UnrealBuildSystem/UnrealBuildSystem.Build.cs
using UnrealBuildTool;

public class UnrealBuildSystem : ModuleRules
{
    public UnrealBuildSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CommonUtility" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
