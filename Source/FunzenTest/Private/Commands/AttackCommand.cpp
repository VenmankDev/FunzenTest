// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/AttackCommand.h"
#include "Commands/GroupOfUnits.h"
#include "Actors/FunzenBaseUnit.h"

void UAttackCommand::StartCommand(UGroupOfUnits* Group)
{
	Super::StartCommand(Group);
	for (int i = 0; i < Group->Units.Num(); i++)
	{
		Group->Units[i]->OnRotationCompleted.AddUObject(this, &UAttackCommand::OnUnitRotationEnded);
		Group->Units[i]->RotateTo(Enemy);
	}
}

void UAttackCommand::OnUnitRotationEnded(AFunzenBaseUnit* Unit)
{
	Unit->StartFireAction();
}