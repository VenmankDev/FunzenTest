// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GroupOfUnits.generated.h"


class AFunzenBaseUnit;
class UBaseCommand;
/**
 * 
 */
UCLASS()
class FUNZENTEST_API UGroupOfUnits : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int UnitsInRow = 6;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float DistanceBetween = 300.f;
	UPROPERTY()
	TArray<AFunzenBaseUnit*> Units;
	UPROPERTY()
	FVector PreviousPosition;
	UPROPERTY()
	TArray<UBaseCommand*> Commands;

public:
	UFUNCTION()
	TArray<FVector> GetPositionsByPosition(FVector InVector, FRotator RotationToTarget, int Count);

	UFUNCTION()
	void AddNewUnit(AFunzenBaseUnit* NewUnit);
	UFUNCTION()
	void AddCommand(UBaseCommand* NewCommand);
	UFUNCTION()
	void OnCommandCompleted();
};
