// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/FunzenGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/GroupManagerComponent.h"
#include "Actors/FunzenBaseUnit.h"


AFunzenGameMode::AFunzenGameMode()
{
	GroupManagerComponent = CreateDefaultSubobject<UGroupManagerComponent>(TEXT("GroupManagerComponent"));
}

void AFunzenGameMode::BeginPlay()
{
	TArray<AActor*> FoundedActors;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("FirstGroup"), FoundedActors);
	if (FoundedActors.Num())
	{
		FirstGroupTargetPoint = FoundedActors[0];
	}

	UGameplayStatics::GetAllActorsWithTag(this, TEXT("SecondGroup"), FoundedActors);
	if (FoundedActors.Num())
	{
		SecondGroupTargetPoint = FoundedActors[0];
	}

	UGameplayStatics::GetAllActorsWithTag(this, TEXT("Cylinder"), FoundedActors);
	if (FoundedActors.Num())
	{
		CylinderTargetPoint = FoundedActors[0];
	}

	if (IsValid(FirstGroupTargetPoint))
	{
		GroupManagerComponent->SpawnGroup(FirstGroupTargetPoint->GetTransform(), UnitClass, UnitsCount);
	}

	if (IsValid(SecondGroupTargetPoint))
	{
		GroupManagerComponent->SpawnGroup(SecondGroupTargetPoint->GetTransform(), UnitClass, UnitsCount);
	}

	GroupManagerComponent->AddWaitCommand(0, 3.f);
	GroupManagerComponent->AddWaitCommand(1, 30.f);

	AActor* Cylinder;
	if (IsValid(CylinderTargetPoint))
	{
		Cylinder = GetWorld()->SpawnActor(CylinderClass.Get(), &CylinderTargetPoint->GetTransform());
		if (IsValid(Cylinder))
		{
			GroupManagerComponent->AddMoveToCommand(0, Cylinder, 300.f);
			GroupManagerComponent->AddAttackCommand(0, Cylinder);
			GroupManagerComponent->AddMoveToCommand(1, Cylinder, 300.f);
			GroupManagerComponent->AddAttackCommand(1, Cylinder);
		}
	}


	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFunzenGameMode::StopSimulation, 180.f);

}

void AFunzenGameMode::StopSimulation()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}