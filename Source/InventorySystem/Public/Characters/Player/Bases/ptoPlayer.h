// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/Bases/InventorySystemCharacter.h"
#include "ptoPlayer.generated.h"

class UBoxComponent;
class UptoHUD;
class UWidgetBase;
class UInventoryWidgetBase;
class UPlayerBelongingsWidget;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AptoPlayer : public AInventorySystemCharacter
{
	GENERATED_UCLASS_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = "pto|Character|Talk")
		UBoxComponent* TalkableArea;

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//////////////////////////
	// Inventory

	virtual void ToggleBelongings();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "pto|Character|UI")
		UPlayerBelongingsWidget* PlayerBelongingsUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto|Character|UI")
		TSubclassOf<UPlayerBelongingsWidget> PlayerBelongingsUIClass;

public:
	//////////////////////////
	// HUD

	UPROPERTY(BlueprintReadOnly, Category = "pto|Character|UI")
		UptoHUD* ptoHUD;
	
	virtual void HandleAddExchangeUI(UWidgetBase* In);
	virtual void HandleRemoveExchangeUI(UWidgetBase* In);
	virtual UInventoryWidgetBase* HandleGetInventoryUI();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto|Character|UI")
		TSubclassOf<UptoHUD> ptoHUDClass;
};
