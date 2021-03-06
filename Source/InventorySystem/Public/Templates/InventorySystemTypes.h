// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "InventorySystemTypes.generated.h"

UENUM(Blueprintable)
enum class EItemIsFrom : uint8
{
	None = 0,
	Inventory = 1,
	Chest = 2,
	HotBar = 3,
	Equip = 4,
	PlayerSelled = 5,
};
ENUM_CLASS_FLAGS(EItemIsFrom)

/*
* Inventory slot contents.
* NOTE : SlotIndex will not be copied
*/
USTRUCT(Blueprintable)
struct FInventorySlots
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int SlotIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FPrimaryAssetId ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsLocked;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EItemIsFrom ItemIsFrom;

	FInventorySlots() : SlotIndex(0), Quantity(0), ItemType(), bIsLocked(false), ItemIsFrom() {}
	FInventorySlots(const FPrimaryAssetId& InType, const int32& InQuantity)
		: SlotIndex(0), Quantity(InQuantity), ItemType(InType), bIsLocked(false), ItemIsFrom() {}

	void operator=(const FInventorySlots& In)
	{
		Quantity = In.Quantity;
		ItemType = In.ItemType;
		bIsLocked = In.bIsLocked;
		ItemIsFrom = In.ItemIsFrom;
	}

	bool operator==(const FInventorySlots& In)
	{
		return ItemType == In.ItemType;
	}

	bool operator!=(const FInventorySlots& In)
	{
		return ItemType != In.ItemType;
	}
};

