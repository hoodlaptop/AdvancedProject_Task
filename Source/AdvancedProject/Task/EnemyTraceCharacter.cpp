#include "EnemyTraceCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyTraceCharacter::AEnemyTraceCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	TraceRange = 2000.0f;
	TraceInterval = 0.25f;
	bDrawDebug = true;

	TraceElapsedTime = 0.0f;
	bTracePending = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AEnemyTraceCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyTraceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceElapsedTime += DeltaTime;

	if (TraceElapsedTime > TraceInterval && !bTracePending)
	{
		TraceElapsedTime = 0.0f;
		StartAsyncTrace();
	}
}

void AEnemyTraceCharacter::StartAsyncTrace()
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	bTracePending = true;

	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &AEnemyTraceCharacter::OnAsyncTraceCompleted);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;

	FCollisionResponseParams ResponseParams;

	const FVector Start = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
	const FVector End = Start + GetActorForwardVector() * TraceRange;

	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Single,
		Start,
		End,
		ECC_Visibility,
		QueryParams,
		ResponseParams,
		&TraceDelegate
	);

	if (bDrawDebug)
	{
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor::Yellow,
			false,
			TraceInterval,
			0,
			2.0f);
	}
}


void AEnemyTraceCharacter::OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
	bTracePending = false;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	for (const FHitResult& Hit : Data.OutHits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor == PlayerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy found player with async trace: %s"), *HitActor->GetName());

			if (bDrawDebug)
			{
				DrawDebugSphere(
					GetWorld(),
					Hit.ImpactPoint,
					25.0f,
					12,
					FColor::Green,
					false,
					1.0f);
			}

			return;
		}
	}
}
