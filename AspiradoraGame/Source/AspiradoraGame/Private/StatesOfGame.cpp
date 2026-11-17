// Fill out your copyright notice in the Description page of Project Settings.


#include "StatesOfGame.h"

void AStatesOfGame::ChangeState(EStatesOfGame newState)
{
	currentState = newState;
	CheckState();

}

void AStatesOfGame::CheckState()
{
	switch (currentState)
	{
		case EStatesOfGame::InitialState:
		{
			break;
		}
		case EStatesOfGame::Running:
		{
			break;
		}
		case EStatesOfGame::Pause:
		{
			break;
		}
		case EStatesOfGame::Dead:
		{
			break;
		}
	}
}
