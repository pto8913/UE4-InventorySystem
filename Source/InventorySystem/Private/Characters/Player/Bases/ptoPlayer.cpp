// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Characters/Player/Bases/ptoPlayer.h"

#include "UI/Inventory/Bases/InventoryWidgetBase.h"
#include "UI/Player/Inventory/PlayerBelongingsWidget.h"
#include "UI/ptoHUD.h"

#include "Components/Bases/InventoryComponentBase.h"
#include "Components/BoxComponent.h"

AptoPlayer::AptoPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TalkableArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Talkable area"));
	TalkableArea->SetupAttachment(RootComponent);
}

void AptoPlayer::BeginPlay()
{
	AInventorySystemCharacter::BeginPlay();

	ptoHUD = CreateWidget<UptoHUD>(GetWorld(), ptoHUDClass);
	ptoHUD->OpenUI();
}

// Called to bind functionality to input
void AptoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	AInventorySystemCharacter::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	/* InputKey E */
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AptoPlayer::PickUp);
	/* InputKey Q */
	PlayerInputComponent->BindAction("ToggleBelongings", IE_Pressed, this, &AptoPlayer::ToggleBelongings);
}


//////////////////////////
// Inventory

void AptoPlayer::ToggleBelongings()
{
	if (IsValid(PlayerBelongingsUI) == true)
	{
		PlayerBelongingsUI->RemoveInventoryUI(HandleGetInventoryUI());
		PlayerBelongingsUI->CloseUI();
		PlayerBelongingsUI = nullptr;
		HandleToggleInventory();
		HandleEndTalk();
	}
	else
	{
		if (bIsTalking == true) return;

		PlayerBelongingsUI = CreateWidget<UPlayerBelongingsWidget>(GetWorld(), PlayerBelongingsUIClass);
		if (IsValid(PlayerBelongingsUI) == true)
		{
			HandleToggleInventory();
			PlayerBelongingsUI->AddInventoryUI(HandleGetInventoryUI());
			PlayerBelongingsUI->OpenUI();
		}
		HandleBeginTalk();
	}
}

UInventoryWidgetBase* AptoPlayer::HandleGetInventoryUI()
{
	return InventoryComp->GetInventoryUI();
}


//////////////////////////
// ptoHUD

void AptoPlayer::HandleAddExchangeUI(UWidgetBase* In)
{
	ptoHUD->AddExchangeUI(In);
}

void AptoPlayer::HandleRemoveExchangeUI(UWidgetBase* In)
{
	ptoHUD->RemoveExchangeUI(In);
}

