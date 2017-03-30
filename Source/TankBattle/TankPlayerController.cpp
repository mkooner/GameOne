// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller"));
	
	PlayerTank = GetControlledTank();

	if (PlayerTank)
	{		
		UE_LOG(LogTemp, Warning, TEXT("Name is : %s"),*PlayerTank->GetName());
	}


}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	
	FVector HitLocation; //Out Parameter
	

	// Get World Location of linetrace through crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Location = %s"), *HitLocation.ToString());
	}

	// If it hits the landscape

	// Tell controlled tank to aim to this point

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& Hit) const 
{
	//Find the crosshair position
	int32 SizeX, SizeY;

	GetViewportSize(SizeX, SizeY);

	auto ScreenLocation = FVector2D(SizeX * CrosshairX, SizeY * CrosshairY);
	

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection, WorldLocation;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Location = %s"), *WorldDirection.ToString());
	}

	// Line-trace along that look direction, and see what we hit (up to max range)
	
	return false; 
}