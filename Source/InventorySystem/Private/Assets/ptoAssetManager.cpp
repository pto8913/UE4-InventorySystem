// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Assets/ptoAssetManager.h"
#include "Assets/ItemDataAssetBase.h"
#include "AbilitySystemGlobals.h"
#include "Engine.h"

const FPrimaryAssetType	UptoAssetManager::PotionItemType = TEXT("Potion");

UptoAssetManager& UptoAssetManager::Get()
{
	UptoAssetManager* This = Cast<UptoAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		return *NewObject<UptoAssetManager>(); // never calls this
	}
}

void UptoAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

UItemDataAssetBase* UptoAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	return Cast<UItemDataAssetBase>(ItemPath.TryLoad());
}