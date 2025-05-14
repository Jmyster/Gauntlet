// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class GAUNTLET_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* PlayerActor;

	float TimeSinceLastDamage = 0.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageRadius = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageAmount = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageCooldown = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AgroRadius = 800.0f;

	bool bIsChasingPlayer = false;

	// Take damage
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float TakeDamageAmount);
};
