// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commands/BaseCommand.h"
#include "MoveToCommand.generated.h"

class AFunzenBaseUnit;
/**
 * 
 */
UCLASS()
class FUNZENTEST_API UMoveToCommand : public UBaseCommand
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int UncompetedCommands = 0;
	UPROPERTY()
	AActor* Target;
	UPROPERTY()
	float DistanceToTarget = 0.f;

public:
	virtual void StartCommand(UGroupOfUnits* Group) override;
	void OnUnitMovementEnded(AFunzenBaseUnit* Unit);
};
