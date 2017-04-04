// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		AITank->AimAt(PlayerTank->GetActorLocation());

		//Move towards Player
		auto move = MoveToActor(PlayerTank, AcceptanceRadius);


		//Fire if Ready
		AITank->Fire(); //Do not fire every frame
	}

}

