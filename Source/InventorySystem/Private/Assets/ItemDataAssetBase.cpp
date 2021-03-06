// Copyright（C）write by pto8913. 2020. All Rights Reserved.


#include "Assets/ItemDataAssetBase.h"

bool UItemDataAssetBase::IsConsumable() const
{
	if (MaxStackSize <= 0) return true;
	return false;
}

FString UItemDataAssetBase::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UItemDataAssetBase::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}