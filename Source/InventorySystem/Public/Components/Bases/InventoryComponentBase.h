// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/InventorySystemTypes.h"
#include "InventoryComponentBase.generated.h"

class UInventoryWidgetBase;
class UInventorySlotBase;
class UItemDataAssetBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponentBase : public UActorComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void Init();
	
	/////////////////////////////
	// UIs
	/* Get InventoryUI */
	virtual UInventoryWidgetBase* GetInventoryUI() const;
	void HandleSetInventoryName(const FString& InName);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "pto|Inventory|Component")
		UInventoryWidgetBase* InventoryUI;
	/*
		For example,
		if you want to limit the behavior of the player's inventory when trading with merchants.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "pto|Inventory|Component")
		TSubclassOf<UInventorySlotBase> ExternalInventorySlotClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto|Inventory|Component")
		TSubclassOf<UInventoryWidgetBase> InventoryUIClass;
public:
	/////////////////////////////
	// NumOfSlot
	/* Get num of Inventory slot */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual int32 GetNumOfSlot() const;
	/* Set num of Inventory slot */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void SetNumOfSlot(const int32& In);
	/* Add num of Inventory slot */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void AddNumOfSlot(const int32& In);
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void UpdateNumOfSlot();
protected:
	/* Number Of InventorySlot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|Inventory|Component")
		int32 NumOfSlot;

public:
	/////////////////////////////
	// Inventory
	/* Get Inventory slot info from Inventory */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		FInventorySlots GetSlotInfoAtIndex(const int32& Idx) const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|Inventory|Component")
		TArray<FInventorySlots> Inventory;

public:
	/////////////////////////////
	// SlottedSlotInfo
	/* Get slot at index from SlottedSlotInfo */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		UInventorySlotBase* GetSlotAtIndex(const int32& Idx) const;
protected:
	UPROPERTY()
		TArray<UInventorySlotBase*> SlottedSlotInfo;

public:

	/* Open / Close InventoryUI */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void ToggleInventory();
	/////////////////////////////
	// PickUp Action
	/* Add to inventory */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual bool AddToInventory(const FInventorySlots& InSlotInfo);
	/* Get Stackable Idx from Inventory */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual bool GetStackableIdx(
			const FInventorySlots& InSlotInfo,
			int32& StackableIdx
		);
	/* Add to stack */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void AddToStack(
			const int32& StackableIdx,
			const FInventorySlots& InSlotInfo
		);
	/* Create Stack */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual bool CreateStack(const FInventorySlots& InSlotInfo);
	/* Drop slot */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void DropSlot(const int32& Idx);


	//////////////////////////////////////////////
	// Slot Action

	/* set inventory slot info */
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void SetSlotInfo(UInventorySlotBase* In);
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void CloseSlottedSlotInfo();

	UFUNCTION()
		virtual void DynamicAddToStack(
			UInventorySlotBase* FromSlot,
			UInventorySlotBase* ToSlot
		);
	/*
		CreateSlotでインベントリに入りきらなかったアイテムや、
		DropSlotで捨てたアイテムを生成する
	*/
	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void SpawnRemainItem(const FInventorySlots& InSlotInfo);

	UFUNCTION(BlueprintCallable, Category = "pto|Inventory|Component")
		virtual void ExchangeSlot(
			UInventorySlotBase* FromSlot,
			UInventorySlotBase* ToSlot
		);
	UFUNCTION(BlueprintCallable, Category = "pto|Invnetory|Component")
		virtual void ExchangeSlotFromOtherComp(
			UInventorySlotBase* FromSlot,
			UInventorySlotBase* ToSlot
		);
	UFUNCTION(BlueprintCallable, Category = "pto|Invnetory|Component")
		virtual void UpdateFromOutOfInventoryComp(
			UInventorySlotBase* UpdatedSlot
		);
protected:
	UFUNCTION()
		virtual void RemoveSlotDelegate(UInventorySlotBase* InSlot);

	UItemDataAssetBase* GetPrimaryAssetObject(const FPrimaryAssetId& PrimaryAssetId) const;
};
