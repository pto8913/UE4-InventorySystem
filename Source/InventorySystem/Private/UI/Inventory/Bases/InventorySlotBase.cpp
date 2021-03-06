// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/Inventory/Bases/InventorySlotBase.h"
#include "UI/Inventory/Bases/InventoryWidgetBase.h"
#include "Operations/ItemDragDropOperation.h"

#include "Assets/ItemDataAssetBase.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h"

#include "Blueprint/WidgetBlueprintLibrary.h"


/////////////////////////////
// Init

void UInventorySlotBase::OpenUI()
{
	if (!SlotContents.bIsLocked)
	{
		SetLockedImage(false);
	}
	if (!SlotContents.ItemType.IsValid())
	{
		SetItemImageTransparent();
	}
}


/////////////////////////////
// Action

void UInventorySlotBase::SetItemImage(FSlateBrush In)
{
	Temp_ItemImage = In;
	ItemImage->SetBrush(In);
	if (In != FSlateBrush())
	{
		SetItemImageRenderOpacity(1.f);
	}
	else
	{
		SetItemImageTransparent();
	}
}

void UInventorySlotBase::SetItemImageTransparent()
{
	FLinearColor Color;
	ItemImage->SetColorAndOpacity(Color.Transparent);
	
	ItemImage->SetBrushTintColor(Color.Transparent);

	//ItemImage->SetRenderOpacity(0.f);
}

void UInventorySlotBase::SetItemImageRenderOpacity(const float& In)
{
	ItemImage->SetRenderOpacity(In);

	FLinearColor Color;
	ItemImage->SetColorAndOpacity(Color.White);
}

void UInventorySlotBase::SetLockedImage(const bool& bIsLock)
{
	SlotContents.bIsLocked = bIsLock;

	if (bIsLock == true)
	{
		LockImage->SetBrushFromTexture(LockedImage);
		LockImage->SetRenderOpacity(1.f);
	}
	else
	{
		LockImage->SetBrushFromTexture(nullptr);
		LockImage->SetRenderOpacity(0.f);
	}
}

void UInventorySlotBase::SetQuantityText(const int32& In)
{
	QuantityText->SetText(FText::AsNumber(In));

	if (In <= 0)
	{
		QuantityText->SetRenderOpacity(0.f);
	}
	else
	{
		QuantityText->SetRenderOpacity(1.f);
	}
}

void UInventorySlotBase::UpdateSlot(const FInventorySlots& SlotInfo, const bool& bUpdateFromOutOfInventorySystem)
{
	SlotContents = SlotInfo;
	UItemDataAssetBase* ItemData = GetPrimaryAssetObject(SlotContents.ItemType);
	if (SlotInfo.Quantity == 0 || !IsValid(ItemData))
	{
		SlotContents = FInventorySlots();
		SetItemImage(FSlateBrush());
		SetLockedImage(false);
		SetQuantityText(0);
	}
	else
	{
		SetItemImage(ItemData->ItemImage);
		SetLockedImage(SlotContents.bIsLocked);
		SetQuantityText(SlotContents.Quantity);
	}

	if (bUpdateFromOutOfInventorySystem == true)
	{
		OnUpdateSlot.Broadcast(this);
	}
}

void UInventorySlotBase::UpdateSlot()
{
	if (!SlotContents.ItemType.IsValid())
	{
		Temp_ItemImage = FSlateBrush();
	}
	SetItemImage(Temp_ItemImage);
	SetLockedImage(SlotContents.bIsLocked);
	SetQuantityText(SlotContents.Quantity);
}

bool UInventorySlotBase::NativeOnDrop(
	const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation
)
{
	if (SlotContents.bIsLocked == true) return false;

	UItemDragDropOperation* ItemOperation = Cast<UItemDragDropOperation>(InOperation);
	if (IsValid(ItemOperation) == true)
	{
		if (ItemOperation->InventorySlotUI == this) return false;

		UE_LOG(LogTemp, Log, TEXT("From %d %s"), ItemOperation->InventorySlotUI->SlotContents.SlotIndex, *ItemOperation->InventorySlotUI->GetName());
		UE_LOG(LogTemp, Log, TEXT("To %d %s"), SlotContents.SlotIndex, *GetName());

		/* Dropped slot owner is not same this Slot owner. */
		if (ItemOperation->InventorySlotUI->OwnerUI != OwnerUI)
		{
			UE_LOG(LogTemp, Log, TEXT("ExchangeSlotFromOtherComp"));

			OnDroppedFromOtherCompSlot.Broadcast(
				ItemOperation->InventorySlotUI,
				this
			);
		}
		else if (ItemOperation->InventorySlotUI->SlotContents.ItemType == SlotContents.ItemType)
		{
			UE_LOG(LogTemp, Log, TEXT("DynamicAddToStack"));

			/* They are the same ItemType, so they stack. */
			OnExchangeSlotSameType.Broadcast(ItemOperation->InventorySlotUI, this);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ExchangeSlot"));

			OnExchangeSlot.Broadcast(ItemOperation->InventorySlotUI, this);
		}
	}

	UWidgetBase::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}

void UInventorySlotBase::NativeOnDragDetected(
	const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation
)
{
	if (SlotContents.Quantity == 0) return;
	if (bDeactiveDrag == true) return;
	if (SlotContents.bIsLocked == true) return;

	/* スロットの情報をドロップしたスロットへ渡すためのオペレーションの作成 */
	UItemDragDropOperation* ItemOperation = Cast<UItemDragDropOperation>(
		UWidgetBlueprintLibrary::CreateDragDropOperation(
			UItemDragDropOperation::StaticClass()
		)
	);

	if (IsValid(ItemOperation) == true)
	{
		/* ドラッグされたアイテムの画像を表示するだけのUI */
		UUserWidget* DraggedItem = CreateWidget<UUserWidget>(
			GetWorld(), DraggedWidgetClass
			);
		UImage* ImageBox = Cast<UImage>(DraggedItem->GetWidgetFromName("ItemImage"));
		if (ImageBox != nullptr)
		{
			ImageBox->SetBrush(Temp_ItemImage);
		}
		/* スロットの情報をオペレーションに渡す */
		ItemOperation->DefaultDragVisual = DraggedItem;
		ItemOperation->Pivot = EDragPivot::MouseDown;

		ItemOperation->InventorySlotUI = this;
		SetItemImageRenderOpacity(0.5f);
		OutOperation = Cast<UDragDropOperation>(ItemOperation);
	}

	UUserWidget::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

FReply UInventorySlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (SlotContents.bIsLocked) return FReply::Unhandled();

	UUserWidget::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Rep = UWidgetBlueprintLibrary::DetectDragIfPressed(
		InMouseEvent, this, EKeys::LeftMouseButton
	);
	if (Rep.NativeReply.IsEventHandled())
	{
		return Rep.NativeReply;
	}
	return Rep.NativeReply;
}


/////////////////////////////
// End

void UInventorySlotBase::CloseUI()
{
}


///////////////////////////////////////////////
// Player visiblity

void UInventorySlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UUserWidget::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (!SlotContents.ItemType.IsValid()) return;

	FLinearColor c;
	ItemImage->SetColorAndOpacity(c.Yellow);
}

void UInventorySlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UUserWidget::NativeOnMouseLeave(InMouseEvent);

	if (!SlotContents.ItemType.IsValid()) return;

	FLinearColor c;
	ItemImage->SetColorAndOpacity(c.White);
}

void UInventorySlotBase::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UUserWidget::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	if (!SlotContents.ItemType.IsValid()) return;

	FLinearColor c;
	ItemImage->SetColorAndOpacity(c.Yellow);
}

void UInventorySlotBase::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UUserWidget::NativeOnDragLeave(InDragDropEvent, InOperation);

	if (!SlotContents.ItemType.IsValid()) return;

	FLinearColor c;
	ItemImage->SetColorAndOpacity(c.White);
}