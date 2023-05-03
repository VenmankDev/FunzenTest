// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GroupManagerComponent.generated.h"

class UGroupOfUnits;
class AFunzenBaseUnit;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNZENTEST_API UGroupManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY()
	TArray<UGroupOfUnits*> Groups;

public:
	UGroupManagerComponent();

	UFUNCTION()
	void SpawnGroup(FTransform SpawnTransform, TSubclassOf<AFunzenBaseUnit> UnitClass, int UnitCount);
		
	UFUNCTION()
	void AddMoveToCommand(int GroupID, AActor* Target, float DistanceToTarget);
	UFUNCTION()
	void AddWaitCommand(int GroupID, float TimeToWait);
	UFUNCTION()
	void AddAttackCommand(int GroupID, AActor* Enemy);
};
