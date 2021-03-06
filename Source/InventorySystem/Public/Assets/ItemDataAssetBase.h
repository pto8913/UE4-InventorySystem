// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "Assets/ptoAssetManager.h"
#include "ItemDataAssetBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemDataAssetBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    UItemDataAssetBase() {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
        FPrimaryAssetType ItemType;

    /* Display Name */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        FName ItemName;

    /* Display Description */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        FString ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        UClass* ItemClass;

    /* Display Image */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        FSlateBrush ItemImage;

    /* Buy Price use from Merchant */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        int32 BuyPrice;

    /* Sell Price use from Merchant */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        int32 SellPrice;

    /* Max Stack of item that can be in Inventory at once */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        int32 MaxStackSize;

    UFUNCTION(BlueprintCallable, Category = Item)
        bool IsConsumable() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
        int32 MaxLevel;

    UFUNCTION(BlueprintCallable, Category = Item)
        FString GetIdentifierString() const;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
