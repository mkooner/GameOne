// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Paste new classes above

class UTankBarrel;
class UTankTurret;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector Hit);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	// Called when the game starts or when spawned
	
	UTankAimComponent* TankAim = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 5000.0;
	
	
};
