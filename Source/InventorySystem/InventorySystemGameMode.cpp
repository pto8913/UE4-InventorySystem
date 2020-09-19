// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventorySystemGameMode.h"
#include "Characters/Player/Bases/InventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventorySystemGameMode::AInventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/Player/BP_Player")
	);
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
