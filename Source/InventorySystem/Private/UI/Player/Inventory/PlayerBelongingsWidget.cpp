// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/Player/Inventory/PlayerBelongingsWidget.h"
#include "UI/Inventory/Bases/InventoryWidgetBase.h"

#include "Characters/Player/Bases/ptoPlayer.h"

#include "Components/Bases/InventoryComponentBase.h"

#include "Components/Button.h"
#include "Components/Border.h"

#include "Assets/ItemDataAssetBase.h"

void UPlayerBelongingsWidget::AddInventoryUI(UWidgetBase* In)
{
	InventoryBorder->AddChild(In);
}

void UPlayerBelongingsWidget::RemoveInventoryUI(UWidgetBase* In)
{
	InventoryBorder->RemoveChild(In);
}

void UPlayerBelongingsWidget::OpenUI()
{
	UWidgetBase::OpenUI();
}

void UPlayerBelongingsWidget::CloseUI()
{
	UWidgetBase::CloseUI();
}