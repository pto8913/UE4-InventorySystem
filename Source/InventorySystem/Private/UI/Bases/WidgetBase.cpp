// CopyrightiCjwrite by pto8913. 2020. All Rights Reserved.

#include "UI/Bases/WidgetBase.h"

#include "Assets/ItemDataAssetBase.h"

#include "Kismet/GameplayStatics.h"

FString UWidgetBase::GetUITextData(const FName& In) const
{
	if (IsValid(UITextData) == true)
	{
		return UITextData->FindRow<FMyTextData>(In, FString())->Content;
	}
	return FString();
}

void UWidgetBase::OpenUI()
{
	AddDelegate();

	if (bUseInputMode)
	{
		SetInputModeGameAndUI();
		SetUIController();
	}
	if (bUseAddToViewport && !IsInViewport())
	{
		AddToViewport();
	}
}

void UWidgetBase::AddDelegate()
{
	if (!bAddedDelegate)
	{
		// add delegates here.

		bAddedDelegate = true;
	}
}

void UWidgetBase::CloseUI()
{
	RemoveDelegate();

	if (bUseInputMode)
	{
		SetInputModeGameOnly();
		SetGameController();
	}
	if (bUseAddToViewport && IsInViewport())
	{
		RemoveFromViewport();
	}
}

void UWidgetBase::RemoveDelegate()
{
	if (bAddedDelegate)
	{
		// Remove delegates here

		bAddedDelegate = false;
	}
}

void UWidgetBase::SetInputModeGameAndUI()
{
	APlayerController* _Controller = GetPlayerController();
	if (IsValid(_Controller) == true)
	{
		_Controller->SetInputMode(FInputModeGameAndUI());
	}
}

void UWidgetBase::SetInputModeGameOnly()
{
	APlayerController* _Controller = GetPlayerController();
	if (IsValid(_Controller) == true)
	{
		_Controller->SetInputMode(FInputModeGameOnly());
	}
}

void UWidgetBase::SetInputModeUIOnly()
{
	APlayerController* _Controller = GetPlayerController();
	if (IsValid(_Controller) == true)
	{
		_Controller->SetInputMode(FInputModeUIOnly());
	}
}

void UWidgetBase::SetUIController()
{
	APlayerController* _Controller = GetPlayerController();
	if (IsValid(_Controller) == true)
	{
		_Controller->bShowMouseCursor = true;
		_Controller->SetIgnoreMoveInput(true);
		_Controller->SetIgnoreLookInput(true);
	}
}

void UWidgetBase::SetGameController()
{
	APlayerController* _Controller = GetPlayerController();
	if (IsValid(_Controller) == true)
	{
		_Controller->bShowMouseCursor = false;
		_Controller->SetIgnoreMoveInput(false);
		_Controller->SetIgnoreLookInput(false);
	}
}

template<class T>
T* UWidgetBase::GetPlayerController(const int& Idx)
{
	return Cast<T>(UGameplayStatics::GetPlayerController(GetWorld(), Idx))
}

APlayerController* UWidgetBase::GetPlayerController(const int& Idx)
{
	return UGameplayStatics::GetPlayerController(GetWorld(), Idx);
}

template<class T>
T* UWidgetBase::GetPlayerCharacter(const int& Idx)
{
	return Cast<T>(UGameplayStatics::GetPlayerCharacter(GetWorld(), Idx))
}

ACharacter* UWidgetBase::GetPlayerCharacter(const int& Idx)
{
	return UGameplayStatics::GetPlayerCharacter(GetWorld(), Idx);
}

UItemDataAssetBase* UWidgetBase::GetPrimaryAssetObject(const FPrimaryAssetId& PrimaryAssetId) const
{
	UptoAssetManager& Manager = UptoAssetManager::Get();
	return Manager.GetPrimaryAssetObject<UItemDataAssetBase>(
		PrimaryAssetId
	);
}

void UWidgetBase::Visible()
{
	SetRenderOpacity(1.f);
	SetVisibility(ESlateVisibility::Visible);
}

void UWidgetBase::Hidden()
{
	SetRenderOpacity(0.f);
	SetVisibility(ESlateVisibility::Hidden);
}