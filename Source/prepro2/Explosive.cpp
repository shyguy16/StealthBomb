// Fill out your copyright notice in the Description page of Project Settings.

#include "prepro2.h"
#include "Explosive.h"
#include "Perception/AISense_Hearing.h"
#include "XrayMode.h"

// Sets default values
AExplosive::AExplosive()
	:mRadForce(CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce")))
	, mParticleSystem(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem")))
	, mExplosionDelay(5.0f)
	, mExplosionRadius(200)
	, mExplosionSound(4000.0f)
	, mExploded(false)
	//,RangeTelegraph(CreateDefaultSubobject<UBoxComponent>(TEXT("RangeTelegraph")))
{
	mParticleSystem->bAutoActivate = false;
	mRadForce->bAutoActivate = false;
}


void AExplosive::Explode()
{
	mParticleSystem->ActivateSystem();
	mRadForce->FireImpulse();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 200, GetActorLocation(), mExplosionRadius, UDamageType::StaticClass(), TArray<AActor*>());
	UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1, this, mExplosionSound);
	mExploded = true;
}


