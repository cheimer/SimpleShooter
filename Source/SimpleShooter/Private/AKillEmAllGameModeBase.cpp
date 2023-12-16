// Fill out your copyright notice in the Description page of Project Settings.


#include "AKillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AAKillEmAllGameModeBase::PawnKilled(APawn* Pawn)
{
	Super::PawnKilled(Pawn);

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}

	AShooterAIController* AIController = Cast<AShooterAIController>(Pawn->GetController());
	if (AIController)
	{
		for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!Controller->IsDead())
			{
				return;
			}
		}

		EndGame(true);
	}

}

void AAKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}

}
