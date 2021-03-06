// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bases/WidgetBase.h"
#include "Templates/InventorySystemTypes.h"
#include "InventoryWidgetBase.generated.h"

class UGridPanel;
class UInventoryComponentBase;
class UInventorySlotBase;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FptoSetSlotInfo, UInventorySlotBase*, InSlot);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UInventorySlotBase*, FptoGetSlotAtIndex, const int32&, Idx);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FInventorySlots, FptoGetSlotInfoAtIndex, const int32&, Idx);

/**
 * This is InventorySlotBase container and the connector for the inventory component and the slot.
 * This ui is used on any widget border or anything.
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryWidgetBase : public UWidgetBase
{
	GENERATED_BODY()
protected:
	// Begin Init
	/* InventorySlot list */
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UGridPanel* ItemList;
	/* Decide how many columns inventory should be */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Widegt")
		int32 GridColumnSize;
public:
	//// Delegates
	UPROPERTY(BlueprintAssignable)
		FptoSetSlotInfo OnSetSlotInfo;
	UPROPERTY()
		FptoGetSlotAtIndex OnGetSlotAtIndex;
	UPROPERTY()
		FptoGetSlotInfoAtIndex OnGetSlotInfoAtIndex;

	UPROPERTY(BlueprintReadWrite, Category = "pto|Inventory|UI")
		int32 NumOfSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* InventoryName;
	virtual void SetInventoryName(const FString& InName);
	/* Add result of CreateSlot in ItemList */
	virtual void AddNewItem(const int32& Idx, UInventorySlotBase* InSlot);

	/* Create Inventory Slot */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Widegt")
		virtual UInventorySlotBase* CreateSlot(const FInventorySlots& SlotInfo);

	void OpenUI() override;

	//// Begin Widgets
	/*
		InventoryComponentBase::ExternalInventorySlotClass is overwritten from 
		the InventoryComponentBase's ToggleInventory by setting the InventoryComponentBase::ExternalInventorySlotClass.
	*/
	UPROPERTY(EditAnywhere, Category = "Inventory|Widegt")
		TSubclassOf<UInventorySlotBase> InventorySlotClass;
	//// End Widgets
	// End Init

	// Begin End
	void CloseUI() override;
	// End End

	// Begin Action
	/* If you want to use this, this UI must have InventoryComp. */
	UInventorySlotBase* GetSlotAtIndex(const int32& Idx) const;
	// End Action
};
