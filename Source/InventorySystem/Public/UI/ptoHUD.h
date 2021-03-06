// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bases/WidgetBase.h"
#include "ptoHUD.generated.h"

class UBorder;
class AptoPlayer;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UptoHUD : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
		bool bIsInitialized = false;

public:
	UFUNCTION()
		virtual void AddExchangeUI(UWidgetBase* In);
	UFUNCTION()
		virtual void RemoveExchangeUI(UWidgetBase* In);
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UBorder* ExchangeBorder;

public:
	UPROPERTY()
		AptoPlayer* OwnerChara;

	void OpenUI() override;
	bool Initialize() override;
	void AddDelegate() override;

public:
	void RemoveDelegate() override;
};