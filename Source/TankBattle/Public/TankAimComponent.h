// Mehrab Kooner Copyright
#pragma once

#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel; //Forward Declaration
class UTankTurret;

// Sets the aiming points for the tank
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();
	UTankBarrel*  GetBarrelReference();
	void SetTurretReference(UTankTurret* TurretToSet);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Aiming;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector Hit, float LaunchSpeed);
	void MoveBarrel(FVector AimDirection);

		
	
};
