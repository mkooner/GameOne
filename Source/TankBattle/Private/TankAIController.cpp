// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"
#include "TankAimComponent.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto MyTank = Cast<ATank>(InPawn);

		if (!ensure(MyTank)) { return; }

		// Subscribe our local method to the tank's death event
		MyTank->Death.AddUniqueDynamic(this, &ATankAIController::TankDeath);
		
	}


}

void ATankAIController::TankDeath()
{
	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>(GetPawn());

	auto AIAim = AITank->FindComponentByClass<UTankAimComponent>();

	if (PlayerTank)
	{
		AIAim->AimAt(PlayerTank->GetActorLocation());

		//Move towards Player
		auto move = MoveToActor(PlayerTank, AcceptanceRadius);

		if (AIAim->GetFiringState() != EFiringStatus::Reloading && AIAim->GetFiringState() != EFiringStatus::Empty)
		{   //Fire if Aiming or Locked
			AIAim->Fire(); //Do not fire every frame
		}
	}

}

