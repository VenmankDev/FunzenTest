// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commands/BaseCommand.h"
#include "AttackCommand.generated.h"

class AFunzenBaseUnit;
class UGroupOfUnits;
/**
 * 
 */
UCLASS()
class FUNZENTEST_API UAttackCommand : public UBaseCommand
{
	GENERATED_BODY()

public:
	AActor* Enemy;

public:
	virtual void StartCommand(UGroupOfUnits* Group) override;
	void OnUnitRotationEnded(AFunzenBaseUnit* Unit);
};
