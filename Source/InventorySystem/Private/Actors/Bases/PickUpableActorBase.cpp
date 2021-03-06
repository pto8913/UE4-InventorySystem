// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "Actors/Bases/PickUpableActorBase.h"

#include "Characters/Bases/CharacterBase.h"

#include "Components/Bases/InventoryComponentBase.h"

#include "Assets/ptoAssetManager.h"
#include "Assets/ItemDataAssetBase.h"

// Sets default values
APickUpableActorBase::APickUpableActorBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void APickUpableActorBase::BeginPlay()
{
	AActorBase::BeginPlay();

	if (IsValid(MeshComp) == true)
	{
		if (bIsIgnoreSimulatePhysics == true)
		{
			MeshComp->SetSimulatePhysics(false);
		}
		else
		{
			MeshComp->SetSimulatePhysics(true);
		}
	}
}


/////////////////////////////////////////
// Action

bool APickUpableActorBase::PickUp(ACharacterBase* In)
{
	if (bIsIgnorePickUp == true)
	{
		return false;
	}

	UActorComponent* _Comp = In->GetComponentByClass(UInventoryComponentBase::StaticClass());
	if (IsValid(_Comp) == true)
	{
		UInventoryComponentBase* _InventoryComp = Cast<UInventoryComponentBase>(_Comp);
		if (IsValid(_InventoryComp) == true)
		{
			LoadAssetData();

			if (_InventoryComp->AddToInventory(
				FInventorySlots(
					ItemType,
					FMath::Clamp(Quantity, 1, 9999)
				)) == true)
			{
				Destroy();
				return true;
			}
		}
	}
	return false;
}

void APickUpableActorBase::SetEquipMode()
{
	bIsIgnorePickUp = true;
	bIsIgnoreSimulatePhysics = true;
	MeshComp->SetSimulatePhysics(false);
}