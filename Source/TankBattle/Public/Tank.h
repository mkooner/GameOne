// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Paste new classes above

class UTankBarrel;
class UTankTurret;
class AProjectile; 
class UTankMovementComponent;
class UTankAimComponent; 

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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	
	UTankAimComponent* TankAim = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMove = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	float ReloadTime = 3.0;
	double LastFireTime = 0.0;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 5000.0;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> Projectile; 

		
};
