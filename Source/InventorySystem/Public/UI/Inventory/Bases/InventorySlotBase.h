// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bases/WidgetBase.h"
#include "Templates/InventorySystemTypes.h"
#include "InventorySlotBase.generated.h"

class UImage;
class UTextBlock;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FptoExchangeSlotDelegate,
	UInventorySlotBase*, FromSlot,
	UInventorySlotBase*, ToSlot
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FptoExchangeSlotIsSameTypeDelegate,
	UInventorySlotBase*, FromSlot,
	UInventorySlotBase*, ToSlot
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FptoDroppedFromOtherCompSlotDelegate,
	UInventorySlotBase*, FromSlot,
	UInventorySlotBase*, ToSlot
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FptoUpdateSlotDelegate,
	UInventorySlotBase*, UpdatedSlot
);

/**
 * If you want to use owner ui, you should use _OwnerUI.
 * Because I want to not Cast.
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySlotBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	// Begin Init
	/*  */
	void OpenUI() override;
	/* Slot Content */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slot")
		FInventorySlots SlotContents;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slot")
		EItemIsFrom ItemIsFrom;

	//// Begin Delegate
	UPROPERTY(BlueprintAssignable)
		FptoExchangeSlotDelegate OnExchangeSlot;
	UPROPERTY(BlueprintAssignable)
		FptoExchangeSlotIsSameTypeDelegate OnExchangeSlotSameType;
	UPROPERTY(BlueprintAssignable)
		FptoDroppedFromOtherCompSlotDelegate OnDroppedFromOtherCompSlot;
	UPROPERTY(BlueprintAssignable)
		FptoUpdateSlotDelegate OnUpdateSlot;
	//// End Delegate

	UPROPERTY(BlueprintReadOnly, Category = "Inventory|Slot")
		FSlateBrush Temp_ItemImage;
protected:
	/* Item Image */
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UImage* ItemImage;
	/* If this slot locked set LockdImage */
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UImage* LockImage;
	/*
		If SlotContents item is stackable item, set quantity.
		else if skill set cost?
	*/
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* QuantityText;
	UPROPERTY(EditAnywhere, Category = "Inventory|Slot")
		UTexture2D* LockedImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slot")
		TSubclassOf<UUserWidget> DraggedWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Slot")
		bool bDeactiveDrag = false;
	// End Init

public:
	// Begin Action
	/* Set Item Image from FSlateBrush */
	void SetItemImage(FSlateBrush In);
	void SetItemImageRenderOpacity(const float& In);
	void SetItemImageTransparent();
	/* Set Locked Image */
	void SetLockedImage(const bool& bIsLock = false);
	/* Set Quantity text */
	void SetQuantityText(const int32& In);

	/*
		UpdateSlot.
	@ bUpdateFromOutOfInventoryComp : Broadcast the delegate for update InventoryComp Inventory
	delegate : FptoUpdateSlotDelegate
	*/
	UFUNCTION(BlueprintCallable, Category = "Invetory|Slot")
		virtual void UpdateSlot(const FInventorySlots& SlotInfo, const bool& bUpdateFromOutOfInventorySystem = false);
	virtual void UpdateSlot();

protected:
	virtual bool NativeOnDrop(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation
	) override;

	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation
	) override;

	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;
	// End Action

	// Begin End
public:
	void CloseUI() override;
	// End End

protected:
	// Player visiblity
	virtual void NativeOnMouseEnter(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;

	virtual void NativeOnMouseLeave(
		const FPointerEvent& InMouseEvent
	) override;

	virtual void NativeOnDragEnter(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation
	) override;

	virtual void NativeOnDragLeave(
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation
	) override;
};
