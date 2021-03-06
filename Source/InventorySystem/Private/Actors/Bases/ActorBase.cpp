// Copyright（C）write by pto8913. 2020. All Rights Reserved.


#include "Actors/Bases/ActorBase.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Assets/ptoAssetManager.h"
#include "Assets/ItemDataAssetBase.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "Characters/Bases/CharacterBase.h"

FName AActorBase::SceneComponentName(TEXT("Scene Comp"));
FName AActorBase::MeshComponentName(TEXT("Mesh Comp"));

//////////////////////////////////
// Init

AActorBase::AActorBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SceneComp = CreateOptionalDefaultSubobject<USceneComponent>(AActorBase::SceneComponentName);
	SetRootComponent(SceneComp);

	MeshComp = CreateOptionalDefaultSubobject<UStaticMeshComponent>(AActorBase::MeshComponentName);
	if (IsValid(MeshComp) == true)
	{
		MeshComp->SetupAttachment(SceneComp);

		/* プレイヤーがこのアクターの上に乗れないようにする */
		MeshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

		MeshComp->SetCollisionProfileName("Custom");
		FCollisionResponseContainer _CollisionRes;
		/*
		　　カメラとプレイヤーの間の直線状にアイテムがある時、
		  　カメラの位置が変わるのを防ぐ
		*/
		_CollisionRes.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		/*
			キャラクターだけアイテムをオーバーラップさせる
		*/
		_CollisionRes.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		MeshComp->SetCollisionResponseToChannels(_CollisionRes);
		//MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	}

	SetActorTickEnabled(false);
}

void AActorBase::BeginPlay()
{
	Super::BeginPlay();
}

//////////////////////////////////
// Action

UItemDataAssetBase* AActorBase::GetPrimaryAssetObject(FPrimaryAssetId In) const
{
	UptoAssetManager& Manager = UptoAssetManager::Get();
	return Manager.GetPrimaryAssetObject<UItemDataAssetBase>(In);
}

void AActorBase::Use()
{
	UItemDataAssetBase* ItemData = GetPrimaryAssetObject(ItemType);
	if (IsValid(ItemData) == true)
	{
		//ItemData->GrandientAbility
	}
}