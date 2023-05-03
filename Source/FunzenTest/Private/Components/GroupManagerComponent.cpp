// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GroupManagerComponent.h"
#include "Commands/GroupOfUnits.h"
#include "Actors/FunzenBaseUnit.h"
#include "Commands/AttackCommand.h"
#include "Commands/WaitCommand.h"
#include "Commands/MoveToCommand.h"

// Sets default values for this component's properties
UGroupManagerComponent::UGroupManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



void UGroupManagerComponent::SpawnGroup(FTransform SpawnTransform, TSubclassOf<AFunzenBaseUnit> UnitClass, int UnitCount)
{
	UGroupOfUnits* NewGroup = NewObject<UGroupOfUnits>(this);
	NewGroup->PreviousPosition = SpawnTransform.GetLocation();
	if (!IsValid(NewGroup))
	{
		return;
	}

	Groups.Add(NewGroup);
	for (FVector  NewLocation : NewGroup->GetPositionsByPosition(SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), UnitCount))
	{
		FTransform NewTransform(SpawnTransform.GetRotation(), NewLocation, SpawnTransform.GetScale3D());
		AActor* NewActor = GetWorld()->SpawnActor(UnitClass, &NewTransform);
		if (IsValid(NewActor))
		{
			NewGroup->AddNewUnit(Cast<AFunzenBaseUnit>(NewActor));
		}
	}
}

void UGroupManagerComponent::AddMoveToCommand(int GroupID, AActor* Target, float DistanceToTarget)
{
	if (Groups.IsValidIndex(GroupID) && IsValid(Target))
	{
		UMoveToCommand* NewCommand = NewObject<UMoveToCommand>(this);
		NewCommand->Target = Target;
		NewCommand->DistanceToTarget = DistanceToTarget;
		Groups[GroupID]->AddCommand(NewCommand);
	}
}

void UGroupManagerComponent::AddWaitCommand(int GroupID, float TimeToWait)
{
	if (Groups.IsValidIndex(GroupID))
	{
		UWaitCommand* NewCommand = NewObject<UWaitCommand>(this);
		NewCommand->TimerTime = TimeToWait;
		Groups[GroupID]->AddCommand(NewCommand);
	}
}

void UGroupManagerComponent::AddAttackCommand(int GroupID, AActor* Enemy)
{
	if (Groups.IsValidIndex(GroupID) && IsValid(Enemy))
	{
		UAttackCommand* NewCommand = NewObject<UAttackCommand>(this);
		NewCommand->Enemy = Enemy;
		Groups[GroupID]->AddCommand(NewCommand);
	}
}

