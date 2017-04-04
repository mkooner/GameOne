// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* Left, UTankTrack* Right)
{
	LeftTrack = Left;
	RightTrack = Right;

}


void UTankMovementComponent::MoveFoward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Move throttle at %f"),Throw);

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);


	//TODO Prevent doublespeed form dual control input

}


void UTankMovementComponent::MoveTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Move throttle at %f"),Throw);

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(-Throw);

	//TODO Prevent doublespeed form dual control input

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Do not call super, we are replacing functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MoveNormalVector = MoveVelocity.GetSafeNormal();

	MoveFoward(FVector::DotProduct(TankForward, MoveNormalVector));
	MoveTurn(FVector::CrossProduct(TankForward, MoveNormalVector).Z);
	

}