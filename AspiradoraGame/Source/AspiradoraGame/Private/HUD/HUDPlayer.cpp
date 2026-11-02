// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDPlayer.h"

void UHUDPlayer::BeginPlay()
{
	Super::BeginPlay();
	maxLives = 3;
	currentLives = maxLives;
	bCanBeDamaged = true;
}

float UHUDPlayer::GetHealth()
{
	return currentLives;
}

FText UHUDPlayer::GetHealthIntText()
{
	FString livesHUD = FString::FromInt(currentLives);
	FText livesHUDText = FText::FromString("Lives:" + livesHUD);
	return livesHUDText;
}
//Invencibility timer
void UHUDPlayer::SetDamageState()
{
	bCanBeDamaged = true;
}
void UHUDPlayer::DamageTimer()
{
	GetOwner()->GetWorldTimerManager().SetTimer(damageTimerHandle, this, &UHUDPlayer::SetDamageState, 2.0f, false);
}
void UHUDPlayer::UpdateHealth(int HealthChange)
{
	currentLives += HealthChange;
	currentLives = FMath::Clamp(currentLives, 0, maxLives);

}
void UHUDPlayer::ApplyDamage(bool IsDamaged, float Damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Player received damage"));
	bCanBeDamaged = IsDamaged;
	UpdateHealth(-Damage);
	DamageTimer();

}

