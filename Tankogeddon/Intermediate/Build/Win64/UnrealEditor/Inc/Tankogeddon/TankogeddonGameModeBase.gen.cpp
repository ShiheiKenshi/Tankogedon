// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tankogeddon/TankogeddonGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTankogeddonGameModeBase() {}
// Cross Module References
	TANKOGEDDON_API UClass* Z_Construct_UClass_ATankogeddonGameModeBase_NoRegister();
	TANKOGEDDON_API UClass* Z_Construct_UClass_ATankogeddonGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Tankogeddon();
// End Cross Module References
	void ATankogeddonGameModeBase::StaticRegisterNativesATankogeddonGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATankogeddonGameModeBase);
	UClass* Z_Construct_UClass_ATankogeddonGameModeBase_NoRegister()
	{
		return ATankogeddonGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ATankogeddonGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATankogeddonGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Tankogeddon,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankogeddonGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TankogeddonGameModeBase.h" },
		{ "ModuleRelativePath", "TankogeddonGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATankogeddonGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATankogeddonGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATankogeddonGameModeBase_Statics::ClassParams = {
		&ATankogeddonGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATankogeddonGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATankogeddonGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATankogeddonGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ATankogeddonGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATankogeddonGameModeBase.OuterSingleton, Z_Construct_UClass_ATankogeddonGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATankogeddonGameModeBase.OuterSingleton;
	}
	template<> TANKOGEDDON_API UClass* StaticClass<ATankogeddonGameModeBase>()
	{
		return ATankogeddonGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATankogeddonGameModeBase);
	struct Z_CompiledInDeferFile_FID_Tankogeddon_Source_Tankogeddon_TankogeddonGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogeddon_Source_Tankogeddon_TankogeddonGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATankogeddonGameModeBase, ATankogeddonGameModeBase::StaticClass, TEXT("ATankogeddonGameModeBase"), &Z_Registration_Info_UClass_ATankogeddonGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATankogeddonGameModeBase), 1454479164U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogeddon_Source_Tankogeddon_TankogeddonGameModeBase_h_436786684(TEXT("/Script/Tankogeddon"),
		Z_CompiledInDeferFile_FID_Tankogeddon_Source_Tankogeddon_TankogeddonGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Tankogeddon_Source_Tankogeddon_TankogeddonGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
