// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Launch(float Speed); 
	void OnTimerExpire();

private: 
	UPROPERTY(EditAnywhere)
		float DestroyTime = 5.0;

	UPROPERTY(EditAnywhere)
		float Damage = 20.0;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Blast = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Impact = nullptr;
	UPROPERTY(VisibleAnywhere)
		URadialForceComponent* Force = nullptr;
};
