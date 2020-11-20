#pragma once

#include <Runtime/Core/Public/Misc/AutomationTest.h>

#include <Runtime/BuildFramework/Public/BuildInfo/BuildInfo.h>
#include <Runtime/BuildFramework/Public/Footprint/BuildFootprint.h>

#if WITH_DEV_AUTOMATION_TESTS

namespace BuildFootprintTestsPrivate
{
	const FIntVector Extent = FIntVector(10, 10, 0);
}

class FBuildFootprintTestFixture : public FAutomationTestBase
{
public:

	FBuildFootprintTestFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{}

	FBuildFootprint CreateFootprint()
	{
		UBuildInfo* BuildInfo = NewObject<UBuildInfo>(GetTransientPackage());
		FBuildFootprint NewFootprint = FBuildFootprint(*BuildInfo);

		NewFootprint.Extent = BuildFootprintTestsPrivate::Extent;
		return NewFootprint;
	}
};

#define IMPLEMENT_BUILDFOOTPRINT_TEST(TestName) IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TestName, FBuildFootprintTestFixture, "BuildFramework.BuildFootprint."#TestName, EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter )

IMPLEMENT_BUILDFOOTPRINT_TEST(ExtentProvided_ExtentAlongSides_StraightTypeReturned)
bool ExtentProvided_ExtentAlongSides_StraightTypeReturned::RunTest(const FString& Parameters)
{
	FBuildFootprint Footprint = CreateFootprint();
	EBuildPointType Type = EBuildPointType::INVALID;
		
	Type = Footprint.GetPointTypeForIndex(FIntVector(9, 0, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Straight);

	Type = Footprint.GetPointTypeForIndex(FIntVector(0, 9, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Straight);

	return true;
}

IMPLEMENT_BUILDFOOTPRINT_TEST(ExtentProvided_ExtentMatchesFootprintExtents_CornerTypeReturned)
bool ExtentProvided_ExtentMatchesFootprintExtents_CornerTypeReturned::RunTest(const FString& Parameters)
{
	FBuildFootprint Footprint = CreateFootprint();
	EBuildPointType Type = EBuildPointType::INVALID;

	Type = Footprint.GetPointTypeForIndex(FIntVector(Footprint.Extent.X, Footprint.Extent.Y, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Corner);

	Type = Footprint.GetPointTypeForIndex(FIntVector(0, 0, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Corner);

	Type = Footprint.GetPointTypeForIndex(FIntVector(Footprint.Extent.X, 0, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Corner);

	Type = Footprint.GetPointTypeForIndex(FIntVector(0, Footprint.Extent.Y, 0));
	TestEqual(TEXT("Expected Type to be Straight"), Type, EBuildPointType::Corner);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
