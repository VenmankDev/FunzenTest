// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commands/BaseCommand.h"
#include "WaitCommand.generated.h"

/**
 * 
 */
UCLASS()
class FUNZENTEST_API UWaitCommand : public UBaseCommand
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float TimerTime = 0.f;

public:
	virtual void StartCommand(UGroupOfUnits* Group) override;
	void OnTimer();
};
