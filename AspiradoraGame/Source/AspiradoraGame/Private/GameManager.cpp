// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
UGameManager::UGameManager()
{
	life = 3;
	maxLife = 3;
	
}
void UGameManager::BeginPlay()
{
	hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AHUDView>();
	changeGameStateManager = Cast<AStatesOfGame>(GetWorld()->GetGameState());
	changeGameStateManager->OnChangeState.AddUniqueDynamic(changeGameStateManager, &AStatesOfGame::ChangeState);
	changeGameStateManager->OnChangeState.Broadcast(EStatesOfGame::InitialState);
}

FText UGameManager::RequestChangeOfHealth()
{
	if (!IsValid(hud))
	{
		FText textNull = FText::FromString("Cargando");
		hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AHUDView>();
		return textNull;
	}
	else if (!IsValid(changeGameStateManager))
	{
		changeGameStateManager = Cast<AStatesOfGame>(GetWorld()->GetGameState());
		changeGameStateManager->OnChangeState.AddUniqueDynamic(changeGameStateManager, &AStatesOfGame::ChangeState);
		changeGameStateManager->OnChangeState.Broadcast(EStatesOfGame::InitialState);
	}
	return hud->GetHealthIntText(life);

}

void UGameManager::OnLifeChanged(int newLife, int _maxLife)
{
	UE_LOG(LogTemp, Warning, TEXT("OnChangeHealth: life = %d, maxLife = %d"), life, maxLife);
	life = newLife;
	maxLife = _maxLife;
}
