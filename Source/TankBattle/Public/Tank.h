// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Paste new classes above

class UTankBarrel;
class UTankTurret;
class AProjectile; 
class UTankMovementComponent;
class UTankAimComponent; 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);



UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	FTankDelegate Death;
	
	/*
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetAim(UTankAimComponent* AimToSet);
	*/


protected:

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

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int32 StartHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 Health;

	// Called by the engine when the Actor is damaged
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	//Returns health to UI bar
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealth() const;
};
