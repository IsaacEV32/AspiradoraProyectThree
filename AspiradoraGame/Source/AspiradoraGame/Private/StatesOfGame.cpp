// Fill out your copyright notice in the Description page of Project Settings.


#include "StatesOfGame.h"

void AStatesOfGame::ChangeState(EStatesOfGame newState)
{
	currentState = newState;
	CheckState();

}

void AStatesOfGame::CheckState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I changed my state"));
	switch (currentState)
	{
		case EStatesOfGame::InitialState:
		{
			//This will be the state of the main menu
			break;
		}
		case EStatesOfGame::Running:
		{
			//Add the initialization of the player 
			break;
		}
		case EStatesOfGame::Pause:
		{
			//Add functions when you pause the game
			break;
		}
		case EStatesOfGame::Dead:
		{
			//Respawn the player 
			break;
		}
	}
}
