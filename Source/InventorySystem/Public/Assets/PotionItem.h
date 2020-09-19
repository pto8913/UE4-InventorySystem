// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Assets/ItemDataAssetBase.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UPotionItem : public UItemDataAssetBase
{
	GENERATED_BODY()
public:
	UPotionItem()
	{
		ItemType = UptoAssetManager::PotionItemType;
	}
};
