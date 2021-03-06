// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UItemDataAssetBase;
class ACharacterBase;

UCLASS()
class INVENTORYSYSTEM_API AActorBase : public AActor
{
	GENERATED_UCLASS_BODY()
	
protected:
	// Begin Init
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "pto")
		USceneComponent* SceneComp;
	static FName SceneComponentName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "pto")
		UStaticMeshComponent* MeshComp;
	static FName MeshComponentName;

public:
	UPROPERTY(BlueprintReadOnly, Category = "pto", meta = (ExposeOnSpawn = true))
		ACharacterBase* _OwnerChara;

	/* AsyncLoad the item's data in BP */
	UFUNCTION(BlueprintImplementableEvent, Category = "pto")
		void LoadAssetData();

	/* AsyncUnLoad the item's data in BP */
	UFUNCTION(BlueprintImplementableEvent, Category = "pto")
		void UnLoadAssetData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto")
		int32 Quantity = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto")
		FPrimaryAssetId ItemType;
	// End Init

	// Begin Action
	/* Use e.g. Item, Equipment, Skill, etc
	  If use from Equipment, equip Equipment
	*/
	UFUNCTION(BlueprintCallable, Category = "pto")
		virtual void Use();

protected:
	virtual void BeginPlay() override;

	UItemDataAssetBase* GetPrimaryAssetObject(FPrimaryAssetId In) const;
};
