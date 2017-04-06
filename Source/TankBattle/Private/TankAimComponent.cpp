// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBattle.h"
#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankMovementComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool Reloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTime;

	if (Reloaded)
		{	    FiringState = EFiringStatus::Reloading;	}
	else if (IsBarrelMoving())
	    {		FiringState = EFiringStatus::Aiming;	}
	else 
		{ FiringState = EFiringStatus::Locked; }

}

bool UTankAimComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector CurrentDirection = Barrel->GetForwardVector();
	
	if (CurrentDirection.Equals(GlobalAimDirection, 0.001))
	{
		return false;
	}

	return true;
}

void UTankAimComponent::AimAt(FVector Hit)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector Start = Barrel->GetSocketLocation(FName("Socket"));

	//Calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity,
		Start,
		Hit,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		GlobalAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(GlobalAimDirection);
	}
	else
	{
		//If no solution do nothing
		//UE_LOG(LogTemp, Warning, TEXT("No Aim Solution Found"));
	}
}

UTankBarrel* UTankAimComponent::GetBarrelReference()
{
	return Barrel;
}

void UTankAimComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimComponent::MoveBarrel(FVector AimDirection)
{
	//Workout difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
    FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
}

void UTankAimComponent::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank Fires"), Time);


	if (Barrel && FiringState != EFiringStatus::Reloading)
	{
		// Spawn projectile at barrel socket
		auto spawn = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Socket")), Barrel->GetSocketRotation(FName("Socket")));
		spawn->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
