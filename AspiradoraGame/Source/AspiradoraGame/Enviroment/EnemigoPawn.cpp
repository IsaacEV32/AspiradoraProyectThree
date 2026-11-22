#include "EnemigoPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AspiradoraGameCharacter.h"

AEnemigoPawn::AEnemigoPawn()
{
	PrimaryActorTick.bCanEverTick = true; //era false

	Capsula = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsula"));
	SetRootComponent(Capsula);
	Capsula->InitCapsuleSize(40.f, 90.f);
	Capsula->SetCollisionProfileName(TEXT("Pawn"));
	Capsula->SetCanEverAffectNavigation(true); //era false

	
	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	Malla->SetupAttachment(Capsula);
	Malla->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	boxCollisionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	boxCollisionArea->SetupAttachment(Capsula);
	boxCollisionArea->InitBoxExtent(FVector(110.0f,110.f,110.f));


	Movimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movimiento"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
	bCanApplyDamage = false;
}

void AEnemigoPawn::BeginPlay()
{
	Super::BeginPlay();

	Movimiento->MaxSpeed = Velocidad;
	boxCollisionArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemigoPawn::OnActorOverlapBegin);
	boxCollisionArea->OnComponentEndOverlap.AddUniqueDynamic(this, &AEnemigoPawn::OnActorOverlapEnd);

	GetWorldTimerManager().SetTimer(TimerComprobacion, this,
		&AEnemigoPawn::ComprobarJugador, IntervaloComprobacion, true);
}

void AEnemigoPawn::ComprobarJugador()
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(this, 0);
	AAIController* AI = Cast<AAIController>(GetController());
	if (!Jugador || !AI) return;

	const float Distancia = FVector::Dist(GetActorLocation(), Jugador->GetActorLocation());

	if (!bPersiguiendo && Distancia <= RadioDeteccion)
	{
		bPersiguiendo = true;
	}
	else if (bPersiguiendo && Distancia > RadioPerdida)
	{
		bPersiguiendo = false;
		AI->StopMovement();
	}

	if (bPersiguiendo)
	{
		AI->MoveToActor(Jugador, 50.f);
	}
}
void AEnemigoPawn::OnActorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Actor entered in the overlap"));
	if ((OtherActor->ActorHasTag("Player")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Player has the tag"));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Player has not the tag"));
	}

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->ActorHasTag("Player")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Actor overlapped with damage area"));
		bCanApplyDamage = true;
		player = Cast<AActor>(OtherActor);
		hit = SweepResult;
		GetWorldTimerManager().SetTimer(damageTimerHandle, this, &AEnemigoPawn::ApplyDamage, 2.2f, true, 0.0f);
	}
}
void AEnemigoPawn::OnActorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
	GetWorldTimerManager().ClearTimer(damageTimerHandle);
}
void AEnemigoPawn::ApplyDamage()
{
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyDamage(player, 1, nullptr, this, collisionDamage);
		/*UGameplayStatics::ApplyPointDamage(player, 1, (player->GetActorLocation() - GetActorLocation()).GetSafeNormal(), hit, nullptr, this, collisionDamage);*/
	}
}