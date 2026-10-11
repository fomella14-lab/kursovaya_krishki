#include "pch.h"
#include "CKompas.h"

#include <algorithm>
#include <cmath>

namespace
{
	constexpr double kPi = 3.14159265358979323846;

	class ProfileWriter
	{
	public:
		ProfileWriter(const Kompas6API5::ksDocument2DPtr& document, double startX, double startY)
			: m_document(document), m_startX(startX), m_startY(startY), m_x(startX), m_y(startY)
		{
		}

		bool LineTo(double x, double y)
		{
			if (!m_ok || m_document->ksLineSeg(m_x, m_y, x, y, 1) == 0)
			{
				m_ok = false;
				return false;
			}
			m_x = x;
			m_y = y;
			return true;
		}

		bool ArcTo(double centerX, double centerY, double x, double y)
		{
			const double startAngle = std::atan2(m_y - centerY, m_x - centerX);
			const double endAngle = std::atan2(y - centerY, x - centerX);
			double delta = endAngle - startAngle;
			while (delta > kPi)
				delta -= 2 * kPi;
			while (delta < -kPi)
				delta += 2 * kPi;
			const double radius = std::hypot(m_x - centerX, m_y - centerY);
			const double middleAngle = startAngle + delta / 2.0;
			const double middleX = centerX + radius * std::cos(middleAngle);
			const double middleY = centerY + radius * std::sin(middleAngle);
			if (!m_ok || m_document->ksArcBy3Points(m_x, m_y, middleX, middleY, x, y, 1) == 0)
			{
				m_ok = false;
				return false;
			}
			m_x = x;
			m_y = y;
			return true;
		}

		bool Close()
		{
			return LineTo(m_startX, m_startY);
		}

		bool IsValid() const { return m_ok; }

	private:
		Kompas6API5::ksDocument2DPtr m_document;
		double m_startX;
		double m_startY;
		double m_x;
		double m_y;
		bool m_ok = true;
	};

	bool DrawOverlayProfile(
		const Kompas6API5::ksDocument2DPtr& sketch,
		const CoverParameters& p)
	{
		const double outerRadius = p.D2 / 2.0;
		const double bodyRadius = p.D / 2.0;
		const double cavityRadius = p.D3 / 2.0;
		const double length = p.H + p.h;
		const double radius = p.filletRadius;
		const double outerFillet = p.outerFilletRadius;
		ProfileWriter profile(sketch, 0, outerRadius - outerFillet);
		profile.ArcTo(outerFillet, outerRadius - outerFillet,
			outerFillet, outerRadius);
		profile.LineTo(p.H, outerRadius);
		profile.LineTo(p.H, bodyRadius);
		profile.LineTo(length, bodyRadius);

		if (!p.withSeal)
		{
			profile.LineTo(length, cavityRadius + radius);
			profile.ArcTo(length - radius, cavityRadius + radius, length - radius, cavityRadius);
			profile.LineTo(p.s + radius, cavityRadius);
			profile.ArcTo(p.s + radius, cavityRadius - radius, p.s, cavityRadius - radius);
			profile.LineTo(p.s, 0);
			profile.LineTo(0, 0);
		}
		else
		{
			const double sealRadius = p.sealOuterDiameter / 2.0;
			const double clearanceRadius = p.shaftClearanceDiameter / 2.0;
			const double chamferLength = 2.0;
			const double chamferRise = chamferLength * std::tan(15.0 * kPi / 180.0);
			const double seatBack = length - p.sealWidth;
			profile.LineTo(length, sealRadius + chamferRise);
			profile.LineTo(length - chamferLength, sealRadius);
			profile.LineTo(seatBack, sealRadius);
			profile.LineTo(seatBack, cavityRadius);
			profile.LineTo(p.rearWall + radius, cavityRadius);
			profile.ArcTo(p.rearWall + radius, cavityRadius - radius,
				p.rearWall, cavityRadius - radius);
			profile.LineTo(p.rearWall, clearanceRadius);
			profile.LineTo(0, clearanceRadius);
		}

		profile.Close();
		if (sketch->ksLineSeg(-5, 0, length + 5, 0, 3) == 0)
			return false;
		return profile.IsValid();
	}

	bool DrawInsetProfile(
		const Kompas6API5::ksDocument2DPtr& sketch,
		const CoverParameters& p)
	{
		const double mainRadius = p.D / 2.0;
		const double flangeRadius = p.D1 / 2.0;
		const double cavityRadius = p.D2 / 2.0;
		const double radius = p.filletRadius;
		const double grooveStart = p.H - p.h - p.b;
		const double grooveEnd = p.H - p.h;
		const double grooveDepth = (std::min)(1.0, (std::max)(0.5, (p.D1 - p.D) / 4.0));
		const double grooveRadius = mainRadius - grooveDepth;

		ProfileWriter profile(sketch, 0, mainRadius);
		profile.LineTo(grooveStart, mainRadius);
		profile.LineTo(grooveStart, grooveRadius);
		profile.LineTo(grooveEnd, grooveRadius);
		profile.LineTo(grooveEnd, flangeRadius);
		profile.LineTo(p.H, flangeRadius);

		if (!p.withSeal)
		{
			profile.LineTo(p.H, cavityRadius + radius);
			profile.ArcTo(p.H - radius, cavityRadius + radius, p.H - radius, cavityRadius);
			profile.LineTo(p.s + radius, cavityRadius);
			profile.ArcTo(p.s + radius, cavityRadius - radius, p.s, cavityRadius - radius);
			profile.LineTo(p.s, 0);
			profile.LineTo(0, 0);
		}
		else
		{
			const double sealRadius = p.sealOuterDiameter / 2.0;
			const double clearanceRadius = p.shaftClearanceDiameter / 2.0;
			const double chamferLength = 2.0;
			const double chamferRise = chamferLength * std::tan(15.0 * kPi / 180.0);
			const double seatBack = p.H - p.sealWidth;
			profile.LineTo(p.H, sealRadius + chamferRise);
			profile.LineTo(p.H - chamferLength, sealRadius);
			profile.LineTo(seatBack, sealRadius);
			profile.LineTo(seatBack, cavityRadius);
			profile.LineTo(p.rearWall + radius, cavityRadius);
			profile.ArcTo(p.rearWall + radius, cavityRadius - radius,
				p.rearWall, cavityRadius - radius);
			profile.LineTo(p.rearWall, clearanceRadius);
			profile.LineTo(0, clearanceRadius);
		}

		profile.LineTo(0, mainRadius);
		if (sketch->ksLineSeg(-5, 0, p.H + 5, 0, 3) == 0)
			return false;
		return profile.IsValid();
	}

	bool CreateRevolvedBody(
		const Kompas6API5::ksPartPtr& part,
		const CoverParameters& parameters)
	{
		Kompas6API5::ksEntityPtr sketchEntity(part->NewEntity(o3d_sketch));
		if (!sketchEntity)
			return false;
		Kompas6API5::ksSketchDefinitionPtr sketchDefinition(sketchEntity->GetDefinition());
		Kompas6API5::ksEntityPtr plane(part->GetDefaultEntity(o3d_planeXOY));
		if (!sketchDefinition || !plane || !sketchDefinition->SetPlane(plane) || !sketchEntity->Create())
			return false;
		sketchEntity->Putname(L"Осевой профиль крышки");

		Kompas6API5::ksDocument2DPtr sketch(sketchDefinition->BeginEdit());
		if (!sketch)
			return false;
		const bool drawn = parameters.coverType == CoverType::Overlay
			? DrawOverlayProfile(sketch, parameters)
			: DrawInsetProfile(sketch, parameters);
		if (!sketchDefinition->EndEdit() || !drawn)
			return false;

		Kompas6API5::ksEntityPtr rotation(part->NewEntity(o3d_bossRotated));
		if (!rotation)
			return false;
		Kompas6API5::ksBossRotatedDefinitionPtr definition(rotation->GetDefinition());
		if (!definition)
			return false;
		definition->PutdirectionType(dtNormal);
		definition->SetThinParam(VARIANT_FALSE, dtNormal, 0, 0);
		definition->SetSideParam(VARIANT_TRUE, 360.0);
		definition->SetSketch(sketchEntity);
		rotation->Putname(L"Тело вращения крышки");
		return rotation->Create() == VARIANT_TRUE;
	}

	bool CreateHoleCut(
		const Kompas6API5::ksPartPtr& part,
		const CoverParameters& parameters,
		double diameter,
		bool throughAll,
		const wchar_t* name)
	{
		Kompas6API5::ksEntityPtr sketchEntity(part->NewEntity(o3d_sketch));
		Kompas6API5::ksSketchDefinitionPtr sketchDefinition(
			sketchEntity ? sketchEntity->GetDefinition() : nullptr);
		Kompas6API5::ksEntityPtr plane(part->GetDefaultEntity(o3d_planeYOZ));
		if (!sketchEntity || !sketchDefinition || !plane ||
			!sketchDefinition->SetPlane(plane) || !sketchEntity->Create())
			return false;

		Kompas6API5::ksDocument2DPtr sketch(sketchDefinition->BeginEdit());
		if (!sketch)
			return false;
		const double pitchRadius = parameters.D1 / 2.0;
		for (int i = 0; i < parameters.holeCount; ++i)
		{
			const double angle = 2.0 * kPi * i / parameters.holeCount;
			const double x = pitchRadius * std::cos(angle);
			const double y = pitchRadius * std::sin(angle);
			if (sketch->ksCircle(x, y, diameter / 2.0, 1) == 0)
			{
				sketchDefinition->EndEdit();
				return false;
			}
		}
		if (!sketchDefinition->EndEdit())
			return false;

		Kompas6API5::ksEntityPtr cut(part->NewEntity(o3d_cutExtrusion));
		Kompas6API5::ksCutExtrusionDefinitionPtr definition(cut ? cut->GetDefinition() : nullptr);
		if (!cut || !definition)
			return false;
		definition->SetSketch(sketchEntity);
		definition->SetThinParam(VARIANT_FALSE, dtNormal, 0, 0);
		if (throughAll)
		{
			definition->PutdirectionType(dtBoth);
			definition->SetSideParam(VARIANT_TRUE, etThroughAll, 0, 0, VARIANT_FALSE);
			definition->SetSideParam(VARIANT_FALSE, etThroughAll, 0, 0, VARIANT_FALSE);
		}
		else
		{
			definition->PutdirectionType(dtNormal);
			definition->SetSideParam(VARIANT_TRUE, etBlind, 2.0, 0, VARIANT_FALSE);
		}
		cut->Putname(name);
		return cut->Create() == VARIANT_TRUE;
	}
}

CKompas::CKompas()
{
	Connect();
}

bool CKompas::Connect()
{
	KompasApp5 = nullptr;
	Doc = nullptr;
	Part = nullptr;

	CLSID applicationClsid{};
	HRESULT result = CLSIDFromProgID(L"Kompas.Application.5", &applicationClsid);
	if (FAILED(result))
		return false;

	IUnknown* applicationUnknown = nullptr;
	result = ::GetActiveObject(applicationClsid, nullptr, &applicationUnknown);
	if (FAILED(result))
	{
		// Если КОМПАС не запущен, запускаем локальный COM-сервер.
		result = CoCreateInstance(
			applicationClsid,
			nullptr,
			CLSCTX_LOCAL_SERVER,
			IID_IUnknown,
			reinterpret_cast<void**>(&applicationUnknown));
	}

	if (FAILED(result) || applicationUnknown == nullptr)
		return false;

	try
	{
		KompasApp5 = Kompas6API5::KompasObjectPtr(applicationUnknown);
		KompasApp5->PutVisible(VARIANT_TRUE);
	}
	catch (const _com_error&)
	{
		KompasApp5 = nullptr;
		applicationUnknown->Release();
		return false;
	}

	applicationUnknown->Release();
	return KompasApp5 != nullptr;
}

bool CKompas::IsConnected() const
{
	return KompasApp5 != nullptr;
}

bool CKompas::CreateCover(const CoverParameters& parameters, std::wstring& error)
{
	error.clear();
	if (!IsConnected() && !Connect())
	{
		error = L"Не удалось подключиться к КОМПАС-3D.";
		return false;
	}

	try
	{
		Doc = Kompas6API5::ksDocument3DPtr(KompasApp5->Document3D());
		if (!Doc || Doc->Create(VARIANT_FALSE, VARIANT_TRUE) != VARIANT_TRUE)
		{
			error = L"КОМПАС-3D не создал новый документ-деталь.";
			return false;
		}
		Doc->SetActive();
		Doc->PutdrawMode(vm_Shaded);
		Doc->PutshadedWireframe(VARIANT_TRUE);

		Part = Kompas6API5::ksPartPtr(Doc->GetPart(pTop_Part));
		if (!Part)
		{
			error = L"Не удалось получить главный компонент новой детали.";
			return false;
		}
		Part->Putname(parameters.coverType == CoverType::Overlay
			? L"Крышка подшипника накладная"
			: L"Крышка подшипника закладная");

		if (!CreateRevolvedBody(Part, parameters))
		{
			error = L"Не удалось создать осевой профиль или операцию вращения крышки.";
			return false;
		}

		if (parameters.coverType == CoverType::Overlay)
		{
			if (!CreateHoleCut(Part, parameters, parameters.holeDiameter, true,
				L"Крепёжные отверстия"))
			{
				error = L"Не удалось построить крепёжные отверстия накладной крышки.";
				return false;
			}
			if (!CreateHoleCut(Part, parameters, parameters.counterboreDiameter, false,
				L"Цековки глубиной 2 мм"))
			{
				error = L"Не удалось построить цековки накладной крышки.";
				return false;
			}
		}

		Part->Update();
		Part->RebuildModel();
		Doc->RebuildDocument();
		return true;
	}
	catch (const _com_error& exception)
	{
		error = L"Ошибка API КОМПАС-3D: ";
		const wchar_t* message = exception.ErrorMessage();
		if (message != nullptr)
			error += message;
		return false;
	}
}
