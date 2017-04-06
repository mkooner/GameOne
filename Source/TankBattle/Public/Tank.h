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
	
	/*
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetAim(UTankAimComponent* AimToSet);
	*/


protected:
	// Called when the game starts or when spawned
	
	
	/*
	UPROPERTY(BlueprintReadOnly)
	UTankAimComponent* TankAim = nullptr;
	*/
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMove = nullptr;
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


		
};
