// Fill out your copyright notice in the Description page of Project Settings.

#include "prepro2.h"

#include "Engine.h"
#include "Enemy_RealTest.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "MyLevelScriptActor.h"
#include "DetonateBomb.h"
#include "prepro2Character.h"
#include "LightDetector.h"
#include "EnemyController.h"
#include "prepro2Character.h"
//#include "Runtime/Engine/Classes/GameFramework/Controller.h"



// Sets default values
AEnemy_RealTest::AEnemy_RealTest()
{
	PrimaryActorTick.bCanEverTick = true;
	mWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GrowlSound = nullptr;
//	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
//	PawnSense->SetPeripheralVisionAngle(90.f);
	//AIControllerClass = AEnemyController::StaticClass();
	
}

/*
void AEnemy_RealTest::OnSeePlayer(APawn* pawn)
{
	AEnemyController* AIControll = Cast<AEnemyController>(GetController());
	if (AIControll)
	{
		age = 0;
		cleared = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you using Pawn Sense!");
		AIControll->SetTargetEnemy(pawn);
	}
}
*/

// Called when the game starts or when spawned
void AEnemy_RealTest::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame


void AEnemy_RealTest::Tick(float DeltaTime)
{
	//if (mHealth > 0)
	{
	Super::Tick(DeltaTime);
	}
	
	if (Screeched)
	{
		mScreechDelay -= DeltaTime;
		if (mScreechDelay < 0)
		{
			Screeched = false;
			mScreechDelay = 0.5f;
		}
	}

		mGrowlDelay -= DeltaTime;
		if (mGrowlDelay < 0)
		{
			if (GrowlSound)
			{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), GrowlSound,GetActorLocation());
			}
			mGrowlDelay = GrowlFrequency;
			
		}
}

float AEnemy_RealTest::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return 0.f;
	mHealth -= DamageAmount;
	FString message = TEXT("Enemy took Damage. Health Remaining") + FString::FromInt(static_cast<int>(mHealth));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, message);
	if (mHealth <= 0)
	{
		//Destroy();
		isAlive = false;	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enemy Has Died");
		AEnemyController* AIControll = Cast<AEnemyController>(GetController());
		AIControll->UpdateStatus();
		SetActorHiddenInGame(true);
		SetActorTickEnabled(false);
		SetActorEnableCollision(false);
	}
	return DamageAmount;
}
// Called to bind functionality to input
void AEnemy_RealTest::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}
