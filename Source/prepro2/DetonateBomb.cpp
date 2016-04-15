// Fill out your copyright notice in the Description page of Project Settings.

#include "prepro2.h"
#include "DetonateBomb.h"


// Sets default values
ADetonateBomb::ADetonateBomb()
	: mBombModel(CreateDefaultSubobject<UDestructibleComponent>(TEXT("Model")))
	, mIsActive(true)
	, mDisappearDelay(5.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = mBombModel;
	
	mParticleSystem->AttachTo(mBombModel);
	mRadForce->AttachTo(mBombModel);

	mDisappearTimer = mDisappearDelay;
}

// Called when the game starts or when spawned
void ADetonateBomb::BeginPlay()
{
	Super::BeginPlay();
	
	mOriginalMesh = mBombModel->DestructibleMesh;
}

// Called every frame
void ADetonateBomb::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (mExplosionTimer < 0)
	{
		Explode();
		mDisappearTimer = mDisappearDelay;
	}

	if (mDisappearTimer < 0)
	{
		mExploded = false;
		mBombModel->SetDestructibleMesh(mOriginalMesh);
		mDisappearTimer = mDisappearDelay;
		SetActive(false);
	}

	if (mExploded)
	{
		mDisappearTimer -= DeltaTime;
	}

	else
	{
		if (mBombTriggered)
		{
			mExplosionTimer -= DeltaTime;
		}
	}
	
}

void ADetonateBomb::SetActive(bool active)
{
	if (mIsActive == active)
	{
		return;
	}

	
	mIsActive = active;

	SetActorHiddenInGame(!active);
	if (active)
	{
		mBombModel->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		mBombModel->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	SetActorTickEnabled(active);
	mBombModel->GetBodyInstance()->SetInstanceSimulatePhysics(active);
	UDestructibleComponent* meshComp = Cast<UDestructibleComponent>(GetComponentByClass(UDestructibleComponent::StaticClass()));
	if (meshComp != nullptr)
	{
		if (active)
		{
			UNavigationSystem::OnComponentRegistered(meshComp);
		}
		else
		{
			UNavigationSystem::OnComponentUnregistered(meshComp);
		}
	}
	
}