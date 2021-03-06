// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bases/WidgetBase.h"
#include "PlayerBelongingsWidget.generated.h"

class UBorder;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UPlayerBelongingsWidget : public UWidgetBase
{
	GENERATED_BODY()
public:
    void OpenUI() override final;
    void CloseUI() override final;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "pto|Player|UI", meta = (BindWidget))
		UBorder* InventoryBorder;
public:
	void AddInventoryUI(UWidgetBase* In);
	void RemoveInventoryUI(UWidgetBase* In);
};