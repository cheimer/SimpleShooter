// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "ShooterCharacter.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	check(AIBehavior);

	RunBehaviorTree(AIBehavior);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	
	
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AShooterAIController::IsDead()
{
	auto ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
	if (!ShooterCharacter)
	{
		return true; // Dettach to Actor
	}

	return ShooterCharacter->IsDead();
}
