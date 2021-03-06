// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Components/Bases/InventoryComponentBase.h"

#include "UI/Inventory/Bases/InventoryWidgetBase.h"
#include "UI/Inventory/Bases/InventorySlotBase.h"

#include "Assets/ptoAssetManager.h"
#include "Assets/ItemDataAssetBase.h"

#include "Actors/Bases/PickUpableActorBase.h"

///////////////////
// Init

void UInventoryComponentBase::Init()
{
	int32 NumOfInventory = Inventory.Num();
	if (Inventory.Num() == 0)
	{
		Inventory.Init(FInventorySlots(), NumOfSlot);
	}
}

void UInventoryComponentBase::BeginPlay()
{
	UActorComponent::BeginPlay();

	Init();
	UpdateNumOfSlot();
}


///////////////////
// UI

UInventoryWidgetBase* UInventoryComponentBase::GetInventoryUI() const
{
	return InventoryUI;
}

void UInventoryComponentBase::HandleSetInventoryName(const FString& InName)
{
	InventoryUI->SetInventoryName(InName);
}


///////////////////
// NumOfSlot

int32 UInventoryComponentBase::GetNumOfSlot() const
{
	return NumOfSlot;
}

void UInventoryComponentBase::SetNumOfSlot(const int32& In)
{
	NumOfSlot = In;
	UpdateNumOfSlot();
}

void UInventoryComponentBase::AddNumOfSlot(const int32& In)
{
	NumOfSlot += In;
	UpdateNumOfSlot();
}

void UInventoryComponentBase::UpdateNumOfSlot()
{
	int32 NumOfInventory = Inventory.Num();
	if (NumOfInventory < NumOfSlot)
	{
		for (int32 Idx = 0; Idx < NumOfSlot - NumOfInventory; ++Idx)
		{
			Inventory.Emplace(FInventorySlots());
		}
	}
}


///////////////////
// Inventory

FInventorySlots UInventoryComponentBase::GetSlotInfoAtIndex(const int32& Idx) const
{
	if (Inventory.IsValidIndex(Idx) == true)
	{
		return Inventory[Idx];
	}
	return FInventorySlots();
}


///////////////////
// SlottedSlotInfo

UInventorySlotBase* UInventoryComponentBase::GetSlotAtIndex(const int32& Idx) const
{
	if (SlottedSlotInfo.IsValidIndex(Idx) == true)
	{
		return SlottedSlotInfo[Idx];
	}
	return nullptr;
}


/////////////////////////////
// Inventory action

void UInventoryComponentBase::ToggleInventory()
{
	if (IsValid(InventoryUI))
	{
		InventoryUI->CloseUI();
		InventoryUI->OnSetSlotInfo.RemoveDynamic(this, &UInventoryComponentBase::SetSlotInfo);
		InventoryUI->OnGetSlotAtIndex.Unbind();
		InventoryUI->OnGetSlotInfoAtIndex.Unbind();
		InventoryUI = nullptr;
		CloseSlottedSlotInfo();
	}
	else
	{
		InventoryUI = CreateWidget<UInventoryWidgetBase>(GetWorld(), InventoryUIClass);
		if (IsValid(InventoryUI) == true)
		{
			InventoryUI->NumOfSlot = NumOfSlot;
			if (IsValid(ExternalInventorySlotClass) == true)
			{
				InventoryUI->InventorySlotClass = ExternalInventorySlotClass;
			}
			InventoryUI->OnGetSlotAtIndex.BindUFunction(this, "GetSlotAtIndex");
			InventoryUI->OnGetSlotInfoAtIndex.BindUFunction(this, "GetSlotInfoAtIndex");
			InventoryUI->OnSetSlotInfo.AddDynamic(this, &UInventoryComponentBase::SetSlotInfo);
			InventoryUI->OpenUI();
		}
	}
}

/////////////////////////////
// PickUp Action

bool UInventoryComponentBase::AddToInventory(
	const FInventorySlots& InSlotInfo
)
{
	int32 StackableIdx = 0;
	int32 SwtackableIdx = -1;
	if (GetStackableIdx(InSlotInfo, StackableIdx) == true)
	{
		AddToStack(StackableIdx, InSlotInfo);
		if (SlottedSlotInfo.IsValidIndex(StackableIdx))
		{
			SlottedSlotInfo[StackableIdx]->UpdateSlot(Inventory[StackableIdx]);
		}
		return true;
	}
	else
	{
		CreateStack(InSlotInfo);
		return true;
	}
	return false;
}

bool UInventoryComponentBase::GetStackableIdx(
	const FInventorySlots& InSlotInfo,
	int32& StackableIdx
)
{
	UItemDataAssetBase* InItem = GetPrimaryAssetObject(InSlotInfo.ItemType);
	int Idx = 0;
	for (const FInventorySlots& SlotInfo : Inventory)
	{
		if (!IsValid(InItem))
		{
			UItemDataAssetBase* InventoryItem = GetPrimaryAssetObject(SlotInfo.ItemType);
			if (IsValid(InventoryItem) == true)
			{
				if (SlotInfo.Quantity < InventoryItem->MaxStackSize)
				{
					StackableIdx = Idx;
					return true;
				}
			}
			else
			{
				/* Objが存在しないということはスロットがからなので、追加できる */
				StackableIdx = Idx;
				return true;
			}
		}

		if (SlotInfo.Quantity < InItem->MaxStackSize)
		{
			if (SlotInfo.ItemType == InSlotInfo.ItemType)
			{
				StackableIdx = Idx;
				return true;
			}
		}
		++Idx;
	}
	return false;
}

void UInventoryComponentBase::AddToStack(
	const int32& StackableIdx,
	const FInventorySlots& InSlotInfo
)
{
	FInventorySlots& SlotInfo = Inventory[StackableIdx];
	const UItemDataAssetBase* AddItem = GetPrimaryAssetObject(InSlotInfo.ItemType);
	const int32 PredictAddQuantity = SlotInfo.Quantity + InSlotInfo.Quantity;
	if (PredictAddQuantity > AddItem->MaxStackSize)
	{
		SlotInfo.Quantity = AddItem->MaxStackSize;
		AddToInventory(FInventorySlots(
			InSlotInfo.ItemType,
			PredictAddQuantity - AddItem->MaxStackSize
		));
	}
	else
	{
		SlotInfo = InSlotInfo;
		SlotInfo.Quantity = PredictAddQuantity;
	}
}

bool UInventoryComponentBase::CreateStack(const FInventorySlots& InSlotInfo)
{
	int _Quantity = InSlotInfo.Quantity;
	if (_Quantity <= 0) return false;

	/*
		When the player pickup item, if can't find stackable slot, create new stack
	*/
	const UItemDataAssetBase* Item = GetPrimaryAssetObject(InSlotInfo.ItemType);
	const int32 MaxStackSize = Item->MaxStackSize;
	int Idx = 0;
	for (FInventorySlots& SlotInfo : Inventory)
	{
		if (SlotInfo.Quantity <= 0)
		{
			_Quantity = FMath::Clamp(_Quantity, 1, 9999);

			if (_Quantity >= MaxStackSize)
			{
				SlotInfo = FInventorySlots(InSlotInfo.ItemType, MaxStackSize);
				if (SlottedSlotInfo.IsValidIndex(Idx))
				{
					SlottedSlotInfo[Idx]->UpdateSlot(SlotInfo);
				}
				CreateStack(FInventorySlots(InSlotInfo.ItemType, _Quantity - MaxStackSize));
			}
			else
			{
				SlotInfo = InSlotInfo;
				if (SlottedSlotInfo.IsValidIndex(Idx))
				{
					SlottedSlotInfo[Idx]->UpdateSlot(SlotInfo);
				}
			}
			return true;
		}
		++Idx;
	}
	if (_Quantity > 0)
	{
		/* Spawn Item */
		FInventorySlots _NewSlotInfo = InSlotInfo;
		_NewSlotInfo.Quantity = _Quantity;
		SpawnRemainItem(_NewSlotInfo);
	}

	return false;
}

void UInventoryComponentBase::DropSlot(const int32& Idx)
{
	UInventorySlotBase* _Slot = GetSlotAtIndex(Idx);
	if (IsValid(_Slot))
	{
		_Slot->UpdateSlot(FInventorySlots());
		RemoveSlotDelegate(_Slot);

		_Slot = nullptr;
	}
}

void UInventoryComponentBase::SpawnRemainItem(const FInventorySlots& InSlotInfo)
{
	UItemDataAssetBase* DropItem = GetPrimaryAssetObject(InSlotInfo.ItemType);
	if (!IsValid(DropItem->ItemClass)) return;

	FRotator SpawnRot = { FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f) };

	APickUpableActorBase* _Item = GetWorld()->SpawnActor<APickUpableActorBase>(
		DropItem->ItemClass,
		GetOwner()->GetActorLocation(),
		SpawnRot
	);
	if (IsValid(_Item) == true)
	{
		_Item->Quantity = InSlotInfo.Quantity;
	}
}


//////////////////////////////////////////////
// Slot Action

void UInventoryComponentBase::SetSlotInfo(UInventorySlotBase* In)
{
	if (In->SlotContents.SlotIndex > NumOfSlot) return;

	In->OnExchangeSlot.AddDynamic(this, &UInventoryComponentBase::ExchangeSlot);
	In->OnExchangeSlotSameType.AddDynamic(this, &UInventoryComponentBase::DynamicAddToStack);
	In->OnDroppedFromOtherCompSlot.AddDynamic(this, &UInventoryComponentBase::ExchangeSlotFromOtherComp);
	In->OnUpdateSlot.AddDynamic(this, &UInventoryComponentBase::UpdateFromOutOfInventoryComp);

	SlottedSlotInfo.Emplace(In);
}

void UInventoryComponentBase::CloseSlottedSlotInfo()
{
	for (UInventorySlotBase* _Slot : SlottedSlotInfo)
	{
		RemoveSlotDelegate(_Slot);
		_Slot->CloseUI();
	}
	SlottedSlotInfo.Empty();
}

void UInventoryComponentBase::RemoveSlotDelegate(UInventorySlotBase* InSlot)
{
	InSlot->OnExchangeSlot.RemoveDynamic(this, &UInventoryComponentBase::ExchangeSlot);
	InSlot->OnExchangeSlotSameType.RemoveDynamic(this, &UInventoryComponentBase::DynamicAddToStack);
	InSlot->OnDroppedFromOtherCompSlot.RemoveDynamic(this, &UInventoryComponentBase::ExchangeSlotFromOtherComp);
	InSlot->OnUpdateSlot.RemoveDynamic(this, &UInventoryComponentBase::UpdateFromOutOfInventoryComp);
}


//////////////////////////////////////////////
// Other

UItemDataAssetBase* UInventoryComponentBase::GetPrimaryAssetObject(const FPrimaryAssetId& PrimaryAssetId) const
{
	UptoAssetManager& Manager = UptoAssetManager::Get();
	return Manager.GetPrimaryAssetObject<UItemDataAssetBase>(
		PrimaryAssetId
	);
}

//////////////////////////////////////////////
// Delegates

void UInventoryComponentBase::DynamicAddToStack(
	UInventorySlotBase* FromSlot,
	UInventorySlotBase* ToSlot
)
{
	UE_LOG(LogTemp, Log, TEXT("DynamicAddToStack"));
	const UItemDataAssetBase* Item = GetPrimaryAssetObject(FromSlot->SlotContents.ItemType);
	if (IsValid(Item) == true)
	{
		const int32 FromIdx = FromSlot->SlotContents.SlotIndex;
		const int32 ToIdx = ToSlot->SlotContents.SlotIndex;
		const int32 MaxStackSize = Item->MaxStackSize;
		const int32 PredictQuantity = FromSlot->SlotContents.Quantity + ToSlot->SlotContents.Quantity;

		if (PredictQuantity > MaxStackSize)
		{
			Inventory[ToIdx].Quantity = MaxStackSize;
			ToSlot->UpdateSlot(Inventory[ToIdx]);

			Inventory[FromIdx].Quantity = PredictQuantity - MaxStackSize;
			FromSlot->UpdateSlot(Inventory[FromIdx]);
		}
		else
		{
			Inventory[ToIdx].Quantity = PredictQuantity;
			ToSlot->UpdateSlot(Inventory[ToIdx]);

			Inventory[FromIdx] = FInventorySlots();
			FromSlot->UpdateSlot(Inventory[FromIdx]);
		}
	}
}

void UInventoryComponentBase::ExchangeSlot(
	UInventorySlotBase* FromSlot,
	UInventorySlotBase* ToSlot
)
{
	UE_LOG(LogTemp, Log, TEXT("ExchangeSlot"));
	/* NOTE: SlotIndex is not exchange */
	const int32 FromIdx = FromSlot->SlotContents.SlotIndex;
	const int32 ToIdx = ToSlot->SlotContents.SlotIndex;

	FInventorySlots Temp = Inventory[FromIdx];

	Inventory[FromIdx] = MoveTemp(Inventory[ToIdx]);
	FromSlot->UpdateSlot(Inventory[FromIdx]);

	Inventory[ToIdx] = MoveTemp(Temp);
	ToSlot->UpdateSlot(Inventory[ToIdx]);
}

void UInventoryComponentBase::ExchangeSlotFromOtherComp(
	UInventorySlotBase* FromSlot,
	UInventorySlotBase* ToSlot
)
{
	UE_LOG(LogTemp, Log, TEXT("ExchangeSlotFromOtherComp"));

	/* NOTE: SlotIndex is not exchange */
	const int32 FromIdx = FromSlot->SlotContents.SlotIndex;
	const int32 ToIdx = ToSlot->SlotContents.SlotIndex;

	if (FromSlot->SlotContents.ItemType == ToSlot->SlotContents.ItemType)
	{
		const UItemDataAssetBase* Item = GetPrimaryAssetObject(FromSlot->SlotContents.ItemType);
		if (IsValid(Item))
		{
			const int32 MaxStackSize = Item->MaxStackSize;
			const int32 PredictQuantity = FromSlot->SlotContents.Quantity + ToSlot->SlotContents.Quantity;
			if (PredictQuantity > MaxStackSize)
			{
				Inventory[ToIdx].Quantity = MaxStackSize;
				ToSlot->UpdateSlot(Inventory[ToIdx]);

				int32 Idx = 0;
				GetStackableIdx(FromSlot->SlotContents, Idx);

				CreateStack(FInventorySlots(FromSlot->SlotContents.ItemType, PredictQuantity - MaxStackSize));
			}
			else
			{
				Inventory[ToIdx].Quantity = PredictQuantity;
				ToSlot->UpdateSlot(Inventory[ToIdx]);
			}
			FromSlot->UpdateSlot(FInventorySlots(), true);
			//FromSlot->_OwnerUI->InventoryComp->Inventory[FromIdx] = FInventorySlots();
			//FromSlot->UpdateSlot(FromSlot->_OwnerUI->InventoryComp->Inventory[FromIdx]);
			return;
		}
	}

	FInventorySlots Temp = MoveTemp(FromSlot->SlotContents);

	FromSlot->UpdateSlot(Inventory[ToIdx], true);
	//FromSlot->_OwnerUI->InventoryComp->Inventory[FromIdx] = MoveTemp(Inventory[ToIdx]);
	//FromSlot->UpdateSlot(FromSlot->_OwnerUI->InventoryComp->Inventory[FromIdx]);

	//Inventory[ToIdx] = MoveTemp(Temp);
	ToSlot->UpdateSlot(Temp, true);
}

void UInventoryComponentBase::UpdateFromOutOfInventoryComp(
	UInventorySlotBase* UpdatedSlot
)
{
	//UE_LOG(LogTemp, Log, TEXT("ExchangeSlotFromOtherComp"));

	const int32 Idx = UpdatedSlot->SlotContents.SlotIndex;
	Inventory[Idx] = UpdatedSlot->SlotContents;
}