// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseCommand.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCommandCompleted)

class UGroupOfUnits;
/**
 * 
 */
UCLASS()
class FUNZENTEST_API UBaseCommand : public UObject
{
	GENERATED_BODY()

public:

	FOnCommandCompleted OnCommandCompleted;
public:
	UFUNCTION()
	virtual void StartCommand(UGroupOfUnits* Group);

};
