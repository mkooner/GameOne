// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBattle.h"
#include "Tank.h"
//#include "TankAimComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction

	//TankAim = CreateDefaultSubobject<UTankAimComponent>(FName("Aim Component"));
	//TankMove = CreateDefaultSubobject<UTankMovementComponent>(FName("Move Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	Health = StartHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	
	// Call the base class - this will tell us how much damage to apply  
	int32 ActualDamage = FMath::Clamp<int32>(DamagePoints, 0, Health);
	
	Health -= ActualDamage;
		
	if (Health <= 0)
	{
		Death.Broadcast();
	}

	return ActualDamage;
}

float ATank::GetHealth() const
{
	return (float)Health / (float)StartHealth;
}
