/*
 * Author: Jonathan Sullivan
 * Last Updated: 5/2/2025
 * Handles the player damage, broadcasting death event, and holds players data.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerData.generated.h"

//Creates an event for on player death
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UPlayerData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerData();

	//variable constants no matter the class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerData)
	int PlayerScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerData)
	int HealthDecreaseRate;

	//variables changed for classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	int PlayerHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	int PlayerSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	int PlayerArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	float ShotDamagePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	float DamagePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	float MagicPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	float ShotSpeed;

	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDeath OnPlayerDeath;

	//Functions
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage);

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(int Score);

	UFUNCTION()
	void ReduceHealthEverySecond();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};
