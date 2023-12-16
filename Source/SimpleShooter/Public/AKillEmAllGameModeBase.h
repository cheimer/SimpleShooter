// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "AKillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* Pawn) override;

private:
	void EndGame(bool bIsPlayerWinner);

};
