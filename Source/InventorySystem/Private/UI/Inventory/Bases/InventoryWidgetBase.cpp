// Copyright（C）write by pto8913. 2020. All Rights Reserved.


#include "UI/Inventory/Bases/InventoryWidgetBase.h"
#include "UI/Inventory/Bases/InventorySlotBase.h"

#include "Components/GridPanel.h"
#include "Components/TextBlock.h"


///////////////////////////////
// Init

void UInventoryWidgetBase::OpenUI()
{
	//UWidgetBase::OpenUI();

	for (int32 Idx = 0; Idx < NumOfSlot; ++Idx)
	{
		const FInventorySlots SlotInfo = OnGetSlotInfoAtIndex.Execute(Idx);
		UInventorySlotBase* _Slot = CreateSlot(SlotInfo);

		OnSetSlotInfo.Broadcast(_Slot);

		_Slot->OwnerUI = this;
		_Slot->SlotContents.SlotIndex = Idx;
		_Slot->OpenUI();
		_Slot->UpdateSlot(SlotInfo);

		AddNewItem(Idx, _Slot);
	}
}

void UInventoryWidgetBase::AddNewItem(const int32& Idx, UInventorySlotBase* InSlot)
{
	ItemList->AddChildToGrid(
		InSlot,
		Idx / GridColumnSize,
		Idx % GridColumnSize
	);
}

UInventorySlotBase* UInventoryWidgetBase::CreateSlot(const FInventorySlots& SlotInfo)
{
	return CreateWidget<UInventorySlotBase>(this, InventorySlotClass);
}

void UInventoryWidgetBase::SetInventoryName(const FString& InName)
{
	InventoryName->SetText(FText::FromString(InName));
}

///////////////////////////
// End 

void UInventoryWidgetBase::CloseUI()
{
	//UWidgetBase::CloseUI();
	
	OnClickedClose.Broadcast();
}

///////////////////////////
// Action

UInventorySlotBase* UInventoryWidgetBase::GetSlotAtIndex(const int32& Idx) const
{
	return OnGetSlotAtIndex.Execute(Idx);
}