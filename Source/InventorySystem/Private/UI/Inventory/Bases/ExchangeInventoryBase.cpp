// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/Inventory/Bases/ExchangeInventoryBase.h"

#include "Components/Border.h"

bool UExchangeInventoryBase::Initialize()
{
	bool res = UWidgetBase::Initialize();

	bUseAddToViewport = false;

	return res;
}

void UExchangeInventoryBase::OpenUI()
{
	UWidgetBase::OpenUI();

	UpperBorder->AddChild(UpperUI);
	LowerBorder->AddChild(LowerUI);
}

void UExchangeInventoryBase::CloseUI()
{
	UWidgetBase::CloseUI();

	UpperBorder->ClearChildren();
	LowerBorder->ClearChildren();

	UpperUI = nullptr;
	LowerUI = nullptr;
}

void UExchangeInventoryBase::SetUpperUI(UWidgetBase* In)
{
	UpperUI = In;
}

void UExchangeInventoryBase::SetLowerUI(UWidgetBase* In)
{
	LowerUI = In;
}

