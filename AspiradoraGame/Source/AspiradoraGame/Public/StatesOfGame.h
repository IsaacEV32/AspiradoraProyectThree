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
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangingState, EStatesOfGame, currentState);
UCLASS()
class ASPIRADORAGAME_API AStatesOfGame : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ChangeState(EStatesOfGame newState);
	UFUNCTION()
	void CheckState();
	FOnChangingState OnChangeState;
private:
	EStatesOfGame currentState;
};