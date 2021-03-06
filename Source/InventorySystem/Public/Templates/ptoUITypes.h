// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "Engine/DataTable.h"
#include "ptoUITypes.generated.h"

/*
	Message contents, UI Text
*/
USTRUCT()
struct FMyTextData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Content;
};
