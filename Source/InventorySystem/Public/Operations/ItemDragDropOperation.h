// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "UI/Inventory/Bases/InventorySlotBase.h"
#include "ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
    UPROPERTY()
        UInventorySlotBase* InventorySlotUI;

    EItemIsFrom GetItemIsFrom() const { return InventorySlotUI->ItemIsFrom; }
};
