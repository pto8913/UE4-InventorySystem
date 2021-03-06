// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bases/ActorBase.h"
#include "PickUpableActorBase.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API APickUpableActorBase : public AActorBase
{
	GENERATED_UCLASS_BODY()
public:
	// Begin Init
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Item")
		bool bIsIgnorePickUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Item")
		bool bIsIgnoreSimulatePhysics = false;
	// End Init

	virtual void BeginPlay() override;

	// Begin Action
	/*
		Pick up item and add to inventory
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory|Item")
		virtual bool PickUp(ACharacterBase* Interacter);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Item")
		virtual void SetEquipMode();
};
