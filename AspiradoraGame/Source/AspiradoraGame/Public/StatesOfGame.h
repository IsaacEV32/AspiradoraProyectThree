// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StatesOfGame.generated.h"

/**
 * 
 */
UENUM()
enum class EStatesOfGame : uint8
{
	InitialState UMETA(DisplayName = "InitialState"),
	Running UMETA(DisplayName = "Running"),
	Pause UMETA(DisplayName = "Pause"),
	Dead UMETA(DisplayName = "Dead")
};
UCLASS()
class ASPIRADORAGAME_API AStatesOfGame : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ChangeState(EStatesOfGame newState);
	UFUNCTION()
	void CheckState();
	
private:
	EStatesOfGame currentState;
	
	
};