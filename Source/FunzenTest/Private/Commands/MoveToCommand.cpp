// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/MoveToCommand.h"
#include "Commands/GroupOfUnits.h"
#include "Actors/FunzenBaseUnit.h"

void UMoveToCommand::StartCommand(UGroupOfUnits* Group)
{
	Super::StartCommand(Group);
	UncompetedCommands = Group->Units.Num();
	FVector NormalizedVectorToNewPosition = Target->GetActorLocation() - Group->PreviousPosition;
	NormalizedVectorToNewPosition.Normalize();


	TArray<FVector> TargetLocations = Group->GetPositionsByPosition(Target->GetActorLocation() - NormalizedVectorToNewPosition * DistanceToTarget, FRotationMatrix::MakeFromX(NormalizedVectorToNewPosition).Rotator(), UncompetedCommands);
	for (int i = 0; i < TargetLocations.Num(); i++)
	{
		Group->Units[i]->OnMoveToCommandCompleted.AddUObject(this, &UMoveToCommand::OnUnitMovementEnded);
		Group->Units[i]->MoveTo(TargetLocations[i]);
	}

	Group->PreviousPosition = Target->GetActorLocation() - NormalizedVectorToNewPosition * DistanceToTarget;
}

void UMoveToCommand::OnUnitMovementEnded(AFunzenBaseUnit* Unit)
{
	--UncompetedCommands;
	if (!UncompetedCommands)
	{
		OnCommandCompleted.Broadcast();
	}
}