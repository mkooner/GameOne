// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	ATank* AITank = nullptr;
	ATank* PlayerTank = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float AcceptanceRadius = 8000.0; //How close can the tank get to the player
	
};
