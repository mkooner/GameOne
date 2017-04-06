// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentHit;

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


// This method is only called when the Tank is in contact with something
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive the tracks 
	DriveTrack();
	

	//Apply sideway
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	ApplySidewaysForce(DeltaTime);

	//Reset Throttle
	CurrentThrottle = 0;

	//UE_LOG(LogTemp, Error, TEXT("We are Hit"));

}

void UTankTrack::DriveTrack()
{
	auto Name = GetName();

	//UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *Name, Throttle);

	//TODO Clamp actual throttle value so player can't over drive
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,1);
}

// This method offsets sideways friction
void UTankTrack::ApplySidewaysForce(float DeltaTime)
{
	// Calculate the slippage speed (Sideways speed)
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlipSpeed / DeltaTime * GetRightVector();

	//Calculate and apply sideways force (F = m*a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration * 0.5;
	TankRoot->AddForce(CorrectionForce);
}
