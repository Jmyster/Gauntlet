/*
 * Author: Jonathan Sullivan
 * Last Updated: 5/2/2025
 * 
 */

#include "PlayerData.h"

// Sets default values for this component's properties
UPlayerData::UPlayerData()
{
	PlayerScore = 0;
	HealthDecreaseRate = 1;
	PlayerHealth = 700;
	PlayerSpeed = 100;
	PlayerArmor = 100;
	DamagePower = 1.0f;
	ShotDamagePower = 1.0f;
	AttackSpeed = 1.0f;
	MagicPower = 1.0f;
	ShotSpeed = 1.0f;
}


// Called when the game starts
void UPlayerData::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerData::ReduceHealthEverySecond, 1.0f, true);
	
}

void UPlayerData::IncreaseScore(const int Score)
{
	PlayerScore += Score;
}

void UPlayerData::TakeDamage(const int Damage)
{
	PlayerHealth -= Damage;
	if (PlayerHealth <= 0)
	{
		PlayerHealth = 0;
		OnPlayerDeath.Broadcast();
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("PlayerHealth: %i"), PlayerHealth));
}

void UPlayerData::ReduceHealthEverySecond()
{
	TakeDamage(HealthDecreaseRate);
}