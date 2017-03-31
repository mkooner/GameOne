// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller"));

	AITank = GetControlledTank();
	PlayerTank = GetPlayerTank();
	/*
	if (AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is : %s"), *AITank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is Not Found"));
	}

	
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is : %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player is Not Found"));
	}
	*/
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		AITank->AimAt(PlayerTank->GetActorLocation());
	}

}

ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}