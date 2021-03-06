// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bases/WidgetBase.h"
#include "ExchangeInventoryBase.generated.h"

class UBorder;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UExchangeInventoryBase : public UWidgetBase
{
	GENERATED_BODY()
protected:
	// Begin Init
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UBorder* UpperBorder;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UBorder* LowerBorder;

	virtual bool Initialize() override;
public:

	UPROPERTY()
		UWidgetBase* UpperUI;

	UPROPERTY()
		UWidgetBase* LowerUI;

	virtual void SetUpperUI(UWidgetBase* In);
	virtual void SetLowerUI(UWidgetBase* In);

	void OpenUI() override;
	

	// End Init

	// Begin End
	void CloseUI() override;
	// End End
};