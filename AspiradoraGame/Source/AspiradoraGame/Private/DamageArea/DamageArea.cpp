 // Fill out your copyright notice in the Description page of Project Settings.


#include "DamageArea/DamageArea.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADamageArea::ADamageArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionArea"));
	collisionArea->InitBoxExtent(FVector(20.0f,60.0f,10.0f));

	RootComponent = collisionArea;

	bCanApplyDamage = false;
}

// Called when the game starts or when spawned
void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	collisionArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADamageArea::OnActorOverlapBegin);
	collisionArea->OnComponentEndOverlap.AddUniqueDynamic(this, &ADamageArea::OnActorOverlapEnd);
}

// Called every frame
//void ADamageArea::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ADamageArea::OnActorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (PrimaryActorTick.bCanEverTick) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Actor overlapped with damage area")	);
		bCanApplyDamage = true;
		player = Cast<AActor>(OtherActor);
		hit = SweepResult;
		GetWorldTimerManager().SetTimer(damageTimerHandle, this, &ADamageArea::ApplyDamage, 2.2f, true, 0.0f);
	}
}

void ADamageArea::OnActorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
	GetWorldTimerManager().ClearTimer(damageTimerHandle);
}

void ADamageArea::ApplyDamage()
{
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyPointDamage(player, 1, (player->GetActorLocation() - GetActorLocation()).GetSafeNormal(), hit, nullptr, this, collisionDamage);
	}
}

