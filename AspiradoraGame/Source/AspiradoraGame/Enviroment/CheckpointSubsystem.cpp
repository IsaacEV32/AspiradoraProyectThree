// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/CheckpointSubsystem.h"
#include "Enviroment/Checkpoint.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

void UCheckpointSubsystem::SetCheckpoint(ACheckpoint* NewCheckpoint)
{
	CurrentCheckpoint = NewCheckpoint;
}

void UCheckpointSubsystem::RespawnPlayer(AController* Controller)
{
	if (!Controller || !CurrentCheckpoint.IsValid()) return;

	AGameModeBase* GM = GetWorld()->GetAuthGameMode();
	if (!GM) return; // solo existe en el servidor

	// Eliminar el pawn anterior
	if (APawn* OldPawn = Controller->GetPawn())
	{
		Controller->UnPossess();
		OldPawn->Destroy();
	}

	GM->RestartPlayerAtTransform(Controller, CurrentCheckpoint->GetRespawnTransform());
}



