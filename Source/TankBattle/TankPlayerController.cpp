// Mehrab Kooner Copyright 

#include "TankBattle.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller"));

	PlayerTank = GetControlledTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name is : %s"), *PlayerTank->GetName());
	}

	auto AimingComponent = PlayerTank->FindComponentByClass<UTankAimComponent>();

	if (AimingComponent)
	{
	  FoundAimingComponent(AimingComponent);
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
		GetControlledTank()->AimAt(HitLocation);
		
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location = %s"), *HitLocation.ToString());
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
	FVector WorldDirection;
	FVector WorldLocation;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Location = %s"), *WorldDirection.ToString());

		UWorld *World = GetWorld();
		FHitResult HitResult;
		
		FVector Start = PlayerCameraManager->GetCameraLocation();
		FVector End = WorldDirection * LineLength + Start;

		// Line-trace along that look direction, and see what we hit (up to max range)
		if (World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
		{
			Hit = HitResult.Location;
			return true;
		}
	
	}
	Hit = FVector();
	
	return false; 
}