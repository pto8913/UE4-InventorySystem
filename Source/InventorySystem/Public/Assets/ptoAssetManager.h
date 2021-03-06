// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ptoAssetManager.generated.h"

class UItemDataAssetBase;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UptoAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	// Constructor and overrides
	UptoAssetManager() {}
	virtual void StartInitialLoading() override;

	/** Returns the current AssetManager object */
	static UptoAssetManager& Get();

	/** Static types for items */
	static const FPrimaryAssetType	PotionItemType;

	UItemDataAssetBase* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId);
};
