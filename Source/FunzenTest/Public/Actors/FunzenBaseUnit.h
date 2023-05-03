// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "FunzenBaseUnit.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUnitCommandCompleted, AFunzenBaseUnit*)

UCLASS()
class FUNZENTEST_API AFunzenBaseUnit : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY()
	AActor* Enemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotatingSpeed = 0.f;
	UPROPERTY(BlueprintReadOnly)
	bool bNeedToRotate = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFiring = false;


	FUnitCommandCompleted OnMoveToCommandCompleted;
	FUnitCommandCompleted OnRotationCompleted;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AFunzenBaseUnit();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveTo(FVector Destination);
	UFUNCTION()
	void MovementEnded(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	UFUNCTION()
	void RotateTo(AActor* NewEnemy);
	UFUNCTION()
	void StartFireAction();

};
