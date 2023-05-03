// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/GroupOfUnits.h"
#include "Actors/FunzenBaseUnit.h"
#include "Commands/BaseCommand.h"

TArray<FVector> UGroupOfUnits::GetPositionsByPosition(FVector InVector, FRotator RotationToTarget, int Count)
{
    TArray<FVector> result;
	FVector RightVector = FRotationMatrix(RotationToTarget).GetScaledAxis(EAxis::Y);
	FVector ForwardVector = FRotationMatrix(RotationToTarget).GetScaledAxis(EAxis::X);



	for (int i = 0; i < Count; i++)
	{
		result.Add(InVector - ForwardVector * DistanceBetween * (i / UnitsInRow) + RightVector * DistanceBetween * ((i % UnitsInRow) - (UnitsInRow - 1) / 2.f));
	}

    return result;
}

void UGroupOfUnits::AddNewUnit(AFunzenBaseUnit* NewUnit)
{
	if (IsValid(NewUnit))
	{
		Units.Add(NewUnit);
	}
}

void UGroupOfUnits::AddCommand(UBaseCommand* NewCommand)
{
	if (!IsValid(NewCommand))
	{
		return;
	}

	Commands.Add(NewCommand);

	if (Commands.Num() != 1)
	{
		return;
	}

	NewCommand->OnCommandCompleted.AddUObject(this, &UGroupOfUnits::OnCommandCompleted);
	NewCommand->StartCommand(this);

}

void UGroupOfUnits::OnCommandCompleted()
{
	Commands.RemoveAt(0);
	if (!Commands.Num())
	{
		return;
	}


	Commands[0]->OnCommandCompleted.AddUObject(this, &UGroupOfUnits::OnCommandCompleted);
	Commands[0]->StartCommand(this);


}
