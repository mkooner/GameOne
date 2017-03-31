// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBattle.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction

	TankAim = CreateDefaultSubobject<UTankAimComponent>(FName("Aim Component"));
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector Hit)
{
	TankAim->AimAt(Hit, LaunchSpeed);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAim->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAim->SetTurretReference(TurretToSet);
}
