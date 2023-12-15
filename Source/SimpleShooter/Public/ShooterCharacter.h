// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCameraComponent* Camera;

private:
	void MoveForward(float Value);
	void LookUp(float Value);
	void MoveRight(float Value);
	void LookRight(float Value);
	void LookUpRate(float Value);
	void LookRightRate(float Value);
	void ShooterJump();

	UFUNCTION(BlueprintPure)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UPROPERTY(EditAnywhere)
	float RotationRate = 60.0f;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TSubclassOf<class AGun> GunClass;

	class AGun* Gun;

};
