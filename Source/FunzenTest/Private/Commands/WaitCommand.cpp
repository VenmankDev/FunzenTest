// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/WaitCommand.h"

void UWaitCommand::StartCommand(UGroupOfUnits* Group)
{
	Super::StartCommand(Group);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWaitCommand::OnTimer, TimerTime);
}

void UWaitCommand::OnTimer()
{
	OnCommandCompleted.Broadcast();
}
