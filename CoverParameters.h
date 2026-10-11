#pragma once

#include <string>
#include <vector>

enum class CoverType
{
	Overlay,
	Inset
};

enum class SealType
{
	Type1,
	Type2
};

struct CoverInput
{
	CoverType coverType = CoverType::Overlay;
	double D = 0.0;
	double h = 0.0;
	bool withSeal = false;
	SealType sealType = SealType::Type1;
	double shaftDiameter = 0.0;
};

struct CoverParameters
{
	CoverType coverType = CoverType::Overlay;
	double D = 0.0;
	double D1 = 0.0;
	double D2 = 0.0;
	double D3 = 0.0;
	double H = 0.0;
	double h = 0.0;
	double hMin = 0.0;
	double hMax = 0.0;
	double s = 0.0;
	double b = 0.0;
	double holeDiameter = 0.0;
	double counterboreDiameter = 0.0;
	int holeCount = 0;
	std::wstring fastenerThread;
	double outerMargin = 0.0;
	double outerFilletRadius = 0.0;

	bool withSeal = false;
	SealType sealType = SealType::Type1;
	double shaftDiameter = 0.0;
	double sealOuterDiameter = 0.0;
	double sealWidth = 0.0;
	double shaftClearanceDiameter = 0.0;
	double filletRadius = 2.0;
	double rearWall = 5.0;
};

bool CalculateCoverParameters(
	const CoverInput& input,
	CoverParameters& output,
	std::wstring& error);

std::vector<double> GetSealShaftDiameters(SealType type);
