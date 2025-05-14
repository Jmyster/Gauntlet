// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActor)
	{
		float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerActor->GetActorLocation());

		if (!bIsChasingPlayer && DistanceToPlayer <= AgroRadius)
		{
			bIsChasingPlayer = true;
		}

		if (bIsChasingPlayer)
		{
			AAIController* AICon = Cast<AAIController>(GetController());
			if (AICon)
			{
				AICon->MoveToActor(PlayerActor, 50.0f);
			}
		}
	}

	float Distance = FVector::Dist(GetActorLocation(), PlayerActor->GetActorLocation());

	if (Distance <= DamageRadius)
	{
		TimeSinceLastDamage += DeltaTime;

		if (TimeSinceLastDamage >= DamageCooldown)
		{
			ACharacter* PlayerChar = Cast<ACharacter>(PlayerActor);
			if (PlayerChar)
			{
				UGameplayStatics::ApplyDamage(PlayerChar, DamageAmount, GetController(), this, nullptr);
			}

			TimeSinceLastDamage = 0.0f;
		}
	}
	else
	{
		TimeSinceLastDamage = DamageCooldown;
	}
}

void ABaseEnemy::ReceiveDamage(float TakeDamageAmount)
{
	CurrentHealth -= TakeDamageAmount;

	if (CurrentHealth <= 0.0f)
	{
		Destroy();
	}
}