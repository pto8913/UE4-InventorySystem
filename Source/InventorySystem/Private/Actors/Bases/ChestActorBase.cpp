// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Actors/Bases/ChestActorBase.h"

#include "UI/Inventory/Bases/InventoryWidgetBase.h"
#include "UI/Inventory/Bases/ExchangeInventoryBase.h"
#include "UI/ptoHUD.h"

#include "Characters/Bases/CharacterBase.h"
#include "Characters/Player/Bases/ptoPlayer.h"

#include "Components/Bases/InventoryComponentBase.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

FName AChestActorBase::InventoryCompName(TEXT("Inventory Comp"));

///////////////////
// Init

AChestActorBase::AChestActorBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InventoryComp = CreateOptionalDefaultSubobject<UInventoryComponentBase>(
		AChestActorBase::InventoryCompName
	);
	if (IsValid(InventoryComp))
	{
		InventoryComp->SetNumOfSlot(15);
		InventoryComp->Init();
	}

	if (IsValid(MeshComp))
	{
		MeshComp->SetSimulatePhysics(false);
	}
}


///////////////////
// Action

bool AChestActorBase::PickUp(ACharacterBase* Interacter)
{
	AptoPlayer* Player = Cast<AptoPlayer>(Interacter);
	if (!IsValid(Player)) return false;

	if (IsValid(ExchangeUI))
	{
		InventoryComp->ToggleInventory();
		Player->HandleToggleInventory();

		Player->HandleRemoveExchangeUI(ExchangeUI);
		ExchangeUI->CloseUI();
		ExchangeUI = nullptr;

		Player->HandleEndTalk();
	}
	else
	{
		ExchangeUI = CreateWidget<UExchangeInventoryBase>(GetWorld(), ExchangeUIClass);
		
		InventoryComp->ToggleInventory();
		InventoryComp->HandleSetInventoryName("Chest");
		ExchangeUI->SetUpperUI(InventoryComp->GetInventoryUI());
		
		Player->HandleToggleInventory();
		ExchangeUI->SetLowerUI(Player->HandleGetInventoryUI());

		Player->HandleAddExchangeUI(ExchangeUI);
		ExchangeUI->OpenUI();

		Player->HandleBeginTalk();
	}

	return true;
}