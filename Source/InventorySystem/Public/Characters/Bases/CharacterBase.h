// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UInventoryComponentBase;


/* Use all ui close when the player begin talk */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginTalkDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTalkDelegate);


UCLASS()
class INVENTORYSYSTEM_API ACharacterBase : public ACharacter
{
	GENERATED_UCLASS_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	////////////////
	// Inventory

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "pto|Character|Inventory")
		UInventoryComponentBase* InventoryComp;
public:
	///// Delegates

	UPROPERTY(BlueprintAssignable)
		FOnBeginTalkDelegate OnBeginTalk;
	UPROPERTY(BlueprintAssignable)
		FOnEndTalkDelegate OnEndTalk;
	/* 
		If you want to derived InventoryComp class.
		You can override in constructor. you can see example on merchant.
	*/
	static FName InventoryCompName;
	UFUNCTION()
		virtual UInventoryComponentBase* GetInventoryComp() const;
	
	UFUNCTION(BlueprintCallable, Category = "pto|Character|Inventory")
		virtual void PickUp();

	UFUNCTION()
		virtual void HandleToggleInventory();

	////////////////
	// Talk

	UPROPERTY(BlueprintReadWrite, Category = "pto|Character")
		bool bIsTalking = false;
	UFUNCTION()
		virtual void HandleBeginTalk();
	UFUNCTION()
		virtual void HandleEndTalk();
};