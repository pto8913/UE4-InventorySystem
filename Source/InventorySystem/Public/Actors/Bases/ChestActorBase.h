// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bases/PickUpableActorBase.h"
#include "ChestActorBase.generated.h"

class ACharacterBase;
class UInventoryComponentBase;
class UExchangeInventoryBase;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AChestActorBase : public APickUpableActorBase
{
	GENERATED_UCLASS_BODY()
protected:
	///////////////
	// Inventory

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chest")
		UInventoryComponentBase* InventoryComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chest")
		TSubclassOf<UExchangeInventoryBase> ExchangeUIClass;

	UPROPERTY(BlueprintReadOnly, Category = "Chest")
		UExchangeInventoryBase* ExchangeUI;
public:
	static FName InventoryCompName;
	
	/* Chest pickup can be only ptoPlayer. */
	virtual bool PickUp(ACharacterBase* Interacter) override;
};