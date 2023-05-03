// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FunzenBaseUnit.h"
#include "AIController.h" 	

#include "DrawDebugHelpers.h"

// Sets default values
AFunzenBaseUnit::AFunzenBaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("GripPoint"));
}

// Called when the game starts or when spawned
void AFunzenBaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFunzenBaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsValid(Enemy) || !bNeedToRotate)
	{
		return;
	}

	FRotator Angle = FRotationMatrix::MakeFromX(Enemy->GetActorLocation() - GetActorLocation()).Rotator() - GetActorRotation();
	Angle.Normalize();
	if (FMath::Abs(RotatingSpeed * DeltaTime) >= FMath::Abs(Angle.Yaw))
	{
		AddActorWorldRotation(FRotator(0, Angle.Yaw, 0));
		bNeedToRotate = false;
		OnRotationCompleted.Broadcast(this);
	}
	else
	{
		AddActorWorldRotation(FRotator(0, RotatingSpeed * DeltaTime * FMath::Sign( Angle.Yaw), 0));
	}
}

// Called to bind functionality to input
void AFunzenBaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFunzenBaseUnit::MoveTo(FVector Destination)
{
	DrawDebugSphere(GetWorld(), Destination, 20, 16, FColor::Red, false, 10.f);
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!IsValid(AIController))
	{
		return;
	}
	AIController->MoveToLocation(Destination, 20.f, false);
	AIController->ReceiveMoveCompleted.AddDynamic(this, &AFunzenBaseUnit::MovementEnded);
	
}

void AFunzenBaseUnit::MovementEnded(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	OnMoveToCommandCompleted.Broadcast(this);
}

void AFunzenBaseUnit::RotateTo(AActor* NewEnemy)
{
	if (!IsValid(NewEnemy))
	{
		return;
	}
	Enemy = NewEnemy;
	bNeedToRotate = true;
}

void AFunzenBaseUnit::StartFireAction()
{
	bIsFiring = true;
}

