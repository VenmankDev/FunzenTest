// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FunzenGameMode.generated.h"


class UGroupManagerComponent;
class AFunzenBaseUnit;
/**
 * 
 */
UCLASS(Blueprintable)
class FUNZENTEST_API AFunzenGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UGroupManagerComponent* GroupManagerComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CylinderClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFunzenBaseUnit> UnitClass;
	UPROPERTY(EditDefaultsOnly)
	int UnitsCount = 2;

	UPROPERTY()
	AActor* FirstGroupTargetPoint;
	UPROPERTY()
	AActor* SecondGroupTargetPoint;
	UPROPERTY()
	AActor* CylinderTargetPoint;

public:
	AFunzenGameMode();

protected:
	virtual void BeginPlay() override;
	void StopSimulation();
};
