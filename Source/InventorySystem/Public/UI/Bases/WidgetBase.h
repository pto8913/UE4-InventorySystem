// CopyrightiCjwrite by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Templates/ptoUITypes.h"
#include "WidgetBase.generated.h"

class UItemDataAssetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FptoClickedClose);

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	/* UIText like a message, button label...etc */
	UPROPERTY(EditAnywhere, Category = "pto|UI")
		UDataTable* UITextData;
	FString GetUITextData(const FName& In) const;

public:
	//// Delegates
	UPROPERTY(BlueprintAssignable)
		FptoClickedClose OnClickedClose;

	UPROPERTY(BlueprintReadWrite, Category = "pto|UI")
		UWidgetBase* OwnerUI;

	/*
		For check the Delegates are already has add
		Because, Crash cause the delegate is already has add when AddDelegate twice.

		** So, If you use UI not recreate, use this in AddDelegate/RemoveDelegate. **

		Check UWidgetBase::AddDelegate/RemoveDelegate.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "pto|UI")
		bool bAddedDelegate = false;
	/*
		If you want to use InputModeGameAndUI, you should true
		else no input mode
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|UI")
		bool bUseInputMode = true;
	/*
		If you want to AddToViewport this ui, you should true.
		else not AddToViewport
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|UI")
		bool bUseAddToViewport = true;
	/* Open UI */
	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		virtual void OpenUI();
protected:
	/*
		All delegates will be bound here

		if you AddDynamic in AddDelegate
		like this,
		```
		UButton* StartButton;
		UFUNCTION(BlueprintCallable)
			void ClickedStart();
		StartButton->OnClicked.AddDynamic(this, &UHoge::ClickedStart);
		```
	*/
	virtual void AddDelegate();
public:
	/* Close UI */
	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		virtual void CloseUI();

	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		virtual void Visible();

	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		virtual void Hidden();
protected:
	/*
		All delegatess will be removed here

		Do RemoveDynamic in RemoveDelegate
		like this,
		```
		StartButton->OnClicked.RemoveDynamic(this, &UHoge::ClickedStart);
		```
	*/
	virtual void RemoveDelegate();

	/*
		Set InputMode GameAndUI
		When use open ui.
	*/
	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		void SetInputModeGameAndUI();
	/*
		Set InputMode GameOnly
		When use close ui.
	*/
	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		void SetInputModeGameOnly();
	/*
		Set InputMode UIOnly
		When use if you want to use IsFocusable ui.
	*/
	UFUNCTION(BlueprintCallable, Category = "pto|UI")
		void SetInputModeUIOnly();
	void SetUIController();
	void SetGameController();

	/* If you want to get unique PlayerController */
	template<class T>
	T* GetPlayerController(const int& Idx = 0);
	/* Get PlayerController	*/
	APlayerController* GetPlayerController(const int& Idx = 0);

	/* If you want to get unique PlayerCharacter */
	template<class T>
	T* GetPlayerCharacter(const int& Idx = 0);
	/* Get PlayerCharacter */
	ACharacter* GetPlayerCharacter(const int& Idx = 0);

	UItemDataAssetBase* GetPrimaryAssetObject(const FPrimaryAssetId& PrimaryAssetId) const;

};