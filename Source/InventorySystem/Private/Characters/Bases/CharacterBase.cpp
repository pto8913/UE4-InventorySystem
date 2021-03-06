// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Characters/Bases/CharacterBase.h"

#include "Components/Bases/InventoryComponentBase.h"

#include "Actors/Bases/PickUpableActorBase.h"

FName ACharacterBase::InventoryCompName(TEXT("Inventory Comp"));

// Sets default values
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InventoryComp = CreateOptionalDefaultSubobject<UInventoryComponentBase>(
		ACharacterBase::InventoryCompName	
	);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::PickUp()
{
	TArray<AActor*> Res;
	GetOverlappingActors(Res);

	for (AActor* Actor : Res)
	{
		APickUpableActorBase* _Item = Cast<APickUpableActorBase>(Actor);
		if (IsValid(_Item))
		{
			if (_Item->bIsIgnorePickUp == true) continue;
			_Item->PickUp(this);
			break;
		}
	}
}


////////////////
// Inventory

UInventoryComponentBase* ACharacterBase::GetInventoryComp() const
{
	return InventoryComp;
}

void ACharacterBase::HandleToggleInventory()
{
	InventoryComp->ToggleInventory();
}


////////////////
// Talk

void ACharacterBase::HandleBeginTalk()
{
	UE_LOG(LogTemp, Log, TEXT("HandleBeginTalk"));
	bIsTalking = true;
	OnBeginTalk.Broadcast();
}

void ACharacterBase::HandleEndTalk()
{
	UE_LOG(LogTemp, Log, TEXT("HandleEndTalk"));
	bIsTalking = false;
	OnEndTalk.Broadcast();
}