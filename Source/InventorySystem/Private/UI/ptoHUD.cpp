// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/ptoHUD.h"

#include "Characters/Player/Bases/ptoPlayer.h"

#include "Components/ProgressBar.h"
#include "Components/Border.h"

bool UptoHUD::Initialize()
{
	bool Res = Super::Initialize();

	bUseInputMode = false;

	return Res;
}

void UptoHUD::OpenUI()
{
	UWidgetBase::OpenUI();

	if (IsValid(OwnerChara) == true && !bIsInitialized)
	{
		bIsInitialized = true;
	}
}

void UptoHUD::AddDelegate()
{
	if (IsValid(OwnerChara))
	{
		OwnerChara->OnBeginTalk.AddDynamic(this, &UptoHUD::Hidden);
		OwnerChara->OnEndTalk.AddDynamic(this, &UptoHUD::Visible);
	}
}

void UptoHUD::RemoveDelegate()
{
	if (IsValid(OwnerChara))
	{
		OwnerChara->OnBeginTalk.RemoveDynamic(this, &UptoHUD::Hidden);
		OwnerChara->OnEndTalk.RemoveDynamic(this, &UptoHUD::Visible);
	}
}

void UptoHUD::AddExchangeUI(UWidgetBase* In)
{
	ExchangeBorder->AddChild(In);
}

void UptoHUD::RemoveExchangeUI(UWidgetBase* In)
{
	ExchangeBorder->RemoveChild(In);
}