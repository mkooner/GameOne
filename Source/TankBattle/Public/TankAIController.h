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
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	ATank* AITank = nullptr;
	ATank* PlayerTank = nullptr;

protected:
	virtual void BeginPlay() override;

	
};
