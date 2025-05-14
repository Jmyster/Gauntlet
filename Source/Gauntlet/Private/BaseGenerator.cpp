// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGenerator.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
ABaseGenerator::ABaseGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
	SpawnRate = 1.0f;
}

// Called when the game starts or when spawned
void ABaseGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	StartSpawning();
}

// Called every frame
void ABaseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGenerator::ReceiveDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.0f)
	{
		Destroy();
	}
}

void ABaseGenerator::StartSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ABaseGenerator::SpawnEnemy, SpawnRate, true);
}

void ABaseGenerator::SpawnEnemy()
{
	if (EnemyToSpawn != NULL)
	{
		// Get spawn location (can be adjusted to add random offsets if needed)
		FVector SpawnLocation = GetActorLocation();

		// Get the spawn rotation (optional, could also be randomized)
		FRotator SpawnRotation = FRotator::ZeroRotator;  // or any rotation you want

		// Spawn the actor
		GetWorld()->SpawnActor<AActor>(EnemyToSpawn, SpawnLocation, SpawnRotation);
	}
}