#include "EnemigoPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

	Movimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movimiento"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
}

void AEnemigoPawn::BeginPlay()
{
	Super::BeginPlay();

	Movimiento->MaxSpeed = Velocidad;

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
