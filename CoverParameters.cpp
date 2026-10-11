#include "pch.h"
#include "CoverParameters.h"

#include <algorithm>
#include <cmath>

namespace
{
	constexpr double kEpsilon = 1e-7;

	struct SealRow
	{
		double shaftDiameter;
		double outerDiameter;
		double h1;
		double h2;
	};

	const SealRow kSealRows[] =
	{
		{ 10, 26, 7, 0 }, { 11, 26, 7, 0 },
		{ 12, 28, 7, 0 }, { 13, 28, 7, 0 }, { 14, 28, 7, 0 },
		{ 15, 30, 7, 0 }, { 16, 30, 7, 0 },
		{ 17, 32, 7, 0 },
		{ 18, 35, 7, 0 }, { 19, 35, 7, 0 },
		{ 20, 40, 10, 14 }, { 21, 40, 10, 14 }, { 22, 40, 10, 14 },
		{ 24, 41, 10, 14 }, { 25, 42, 10, 14 }, { 26, 45, 10, 14 },
		{ 30, 52, 10, 14 }, { 32, 52, 10, 14 },
		{ 35, 58, 10, 14 }, { 36, 58, 10, 14 }, { 38, 58, 10, 14 },
		{ 40, 60, 10, 14 }, { 42, 62, 10, 14 }, { 45, 65, 10, 14 },
		{ 48, 70, 10, 14 }, { 50, 70, 10, 14 }, { 52, 75, 10, 14 },
		{ 55, 80, 12, 16 }, { 56, 80, 12, 16 }, { 58, 80, 12, 16 },
		{ 60, 85, 12, 16 },
		{ 63, 90, 12, 16 }, { 65, 90, 12, 16 },
		{ 70, 95, 12, 16 }, { 71, 95, 12, 16 },
		{ 75, 100, 12, 16 }, { 80, 105, 12, 16 }, { 85, 110, 12, 16 },
		{ 90, 120, 12, 16 }, { 95, 120, 12, 16 }, { 100, 125, 12, 16 }
	};

	bool InRange(double value, double minimum, double maximum)
	{
		return value + kEpsilon >= minimum && value - kEpsilon <= maximum;
	}

	const SealRow* FindSealRow(double shaftDiameter)
	{
		for (const auto& row : kSealRows)
		{
			if (std::abs(row.shaftDiameter - shaftDiameter) < kEpsilon)
				return &row;
		}
		return nullptr;
	}

	bool CalculateOverlay(const CoverInput& input, CoverParameters& p, std::wstring& error)
	{
		if (InRange(input.D, 40, 62))
		{
			p.D1 = input.D + 15;
			p.D2 = input.D + 30;
			p.D3 = input.D - 10;
			p.holeDiameter = 7;
			p.counterboreDiameter = 14;
			p.fastenerThread = L"M6";
			p.holeCount = 6;
			p.H = 10;
			p.hMin = 5;
			p.hMax = 15;
			p.s = 5;
		}
		else if (input.D >= 65 - kEpsilon && input.D < 75 - kEpsilon)
		{
			p.D1 = input.D + 20;
			p.D2 = input.D + 40;
			p.D3 = input.D - 10;
			p.holeDiameter = 9;
			p.counterboreDiameter = 18;
			p.fastenerThread = L"M8";
			p.holeCount = 6;
			p.H = 12;
			p.hMin = 5;
			p.hMax = 20;
			p.s = 6;
		}
		else if (InRange(input.D, 75, 95))
		{
			p.D1 = input.D + 20;
			p.D2 = input.D + 40;
			p.D3 = input.D - 10;
			p.holeDiameter = 9;
			p.counterboreDiameter = 18;
			p.fastenerThread = L"M8";
			p.holeCount = 6;
			p.H = 12;
			p.hMin = 5;
			p.hMax = 20;
			p.s = 6;
		}
		else if (InRange(input.D, 100, 145))
		{
			p.D1 = input.D + 25;
			p.D2 = input.D + 50;
			p.D3 = input.D - 15;
			p.holeDiameter = 11;
			p.counterboreDiameter = 22;
			p.fastenerThread = L"M10";
			p.holeCount = 6;
			p.H = 15;
			p.hMin = 5;
			p.hMax = 30;
			p.s = 7;
		}
		else if (InRange(input.D, 150, 180))
		{
			p.D1 = input.D + 30;
			p.D2 = input.D + 60;
			p.D3 = input.D - 15;
			p.holeDiameter = 13;
			p.counterboreDiameter = 24;
			p.fastenerThread = L"M12";
			p.holeCount = 6;
			p.H = 18;
			p.hMin = 5;
			p.hMax = 30;
			p.s = 8;
		}
		else if (InRange(input.D, 190, 220))
		{
			p.D1 = input.D + 30;
			p.D2 = input.D + 60;
			p.D3 = input.D - 20;
			p.holeDiameter = 13;
			p.counterboreDiameter = 24;
			p.fastenerThread = L"M12";
			p.holeCount = 6;
			p.H = 18;
			p.hMin = 5;
			p.hMax = 30;
			p.s = 8;
		}
		else
		{
			error = L"Диаметр D не входит в поддерживаемые диапазоны накладных крышек.";
			return false;
		}

		if (!InRange(input.h, p.hMin, p.hMax))
		{
			error = L"Размер h должен находиться в табличном диапазоне для выбранного D.";
			return false;
		}

		// Радиальный остаток металла между цековкой и наружной кромкой фланца.
		p.outerMargin = (p.D2 - p.D1 - p.counterboreDiameter) / 2.0;
		if (p.outerMargin > 2.0)
			p.outerFilletRadius = 2.0;
		else if (p.outerMargin > 1.0)
			p.outerFilletRadius = 1.0;
		else
			p.outerFilletRadius = 0.5;

		p.h = input.h;
		return true;
	}

	bool CalculateInset(const CoverInput& input, CoverParameters& p, std::wstring& error)
	{
		if (InRange(input.D, 40, 62))
		{
			p.D1 = input.D + 5;
			p.D2 = input.D - 10;
			p.H = 20;
			p.h = 5;
			p.s = 5;
			p.b = 3;
		}
		else if (InRange(input.D, 65, 95))
		{
			p.D1 = input.D + 6;
			p.D2 = input.D - 12;
			p.H = 25;
			p.h = 6;
			p.s = 6;
			p.b = 5;
		}
		else if (InRange(input.D, 100, 145))
		{
			p.D1 = input.D + 7;
			p.D2 = input.D - 15;
			p.H = 25;
			p.h = 7;
			p.s = 7;
			p.b = 5;
		}
		else if (InRange(input.D, 150, 220))
		{
			p.D1 = input.D + 8;
			p.D2 = input.D - 15;
			p.H = 25;
			p.h = 8;
			p.s = 8;
			p.b = 5;
		}
		else
		{
			error = L"Диаметр D не входит в поддерживаемые диапазоны закладных крышек.";
			return false;
		}
		return true;
	}
}

bool CalculateCoverParameters(
	const CoverInput& input,
	CoverParameters& output,
	std::wstring& error)
{
	error.clear();
	output = CoverParameters{};
	output.coverType = input.coverType;
	output.D = input.D;
	output.withSeal = input.withSeal;
	output.sealType = input.sealType;

	if (!std::isfinite(input.D) || input.D <= 0)
	{
		error = L"Введите положительный диаметр D.";
		return false;
	}

	const bool dimensionsOk = input.coverType == CoverType::Overlay
		? CalculateOverlay(input, output, error)
		: CalculateInset(input, output, error);
	if (!dimensionsOk)
		return false;

	if (!input.withSeal)
		return true;

	const SealRow* seal = FindSealRow(input.shaftDiameter);
	if (seal == nullptr)
	{
		error = L"Выберите стандартный диаметр вала для манжеты.";
		return false;
	}

	const double width = input.sealType == SealType::Type1 ? seal->h1 : seal->h2;
	if (width <= 0)
	{
		error = L"Манжета типа 2 для выбранного диаметра вала отсутствует в таблице.";
		return false;
	}

	output.shaftDiameter = seal->shaftDiameter;
	output.sealOuterDiameter = seal->outerDiameter;
	output.sealWidth = width;
	output.shaftClearanceDiameter = seal->shaftDiameter + 1;

	const double availableDiameter = input.coverType == CoverType::Overlay ? output.D3 : output.D2;
	if (output.sealOuterDiameter + 2 * output.filletRadius > availableDiameter + kEpsilon)
	{
		error = L"Выбранная манжета не помещается в крышку по диаметру с учётом скругления R2.";
		return false;
	}

	const double axialLength = input.coverType == CoverType::Overlay
		? output.H + output.h
		: output.H;
	if (output.sealWidth + output.rearWall + output.filletRadius > axialLength + kEpsilon)
	{
		error = L"Выбранная манжета не помещается в крышку по осевой длине.";
		return false;
	}

	return true;
}

std::vector<double> GetSealShaftDiameters(SealType type)
{
	std::vector<double> result;
	for (const auto& row : kSealRows)
	{
		if (type == SealType::Type1 || row.h2 > 0)
			result.push_back(row.shaftDiameter);
	}
	return result;
}
