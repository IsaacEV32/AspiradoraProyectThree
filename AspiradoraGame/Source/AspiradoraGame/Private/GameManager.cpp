// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
UGameManager::UGameManager()
{
	life = 3;
	maxLife = 3;
}
void UGameManager::BeginPlay()
{
	ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	playerCharacter = Cast<AAspiradoraGameCharacter>(characterInstance);
	playerCharacter->onLifeChange.AddUniqueDynamic(this, &UGameManager::OnLifeChanged);
	hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AHUDView>();
}

FText UGameManager::RequestChangeOfHealth()
{
	if (!IsValid(playerCharacter))
	{
		FText textNull = FText::FromString("Cargando");
		ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		playerCharacter = Cast<AAspiradoraGameCharacter>(characterInstance);
		playerCharacter->onLifeChange.AddUniqueDynamic(this, &UGameManager::OnLifeChanged);
		return textNull;
	}
	return hud->GetHealthIntText(playerCharacter->GetCurrentLife());

}

void UGameManager::OnLifeChanged(int newLife, int _maxLife)
{
	UE_LOG(LogTemp, Warning, TEXT("OnChangeHealth: life = %d, maxLife = %d"), life, maxLife);
	life = newLife;
	maxLife = _maxLife;
}
