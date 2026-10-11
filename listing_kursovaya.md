
## Файл `targetver.h`

```cpp
#pragma once
#include <SDKDDKVer.h>
```

## Файл `framework.h`

```cpp
#pragma once
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif
#include <afxcontrolbars.h>
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
```

## Файл `pch.h`

```cpp
#ifndef PCH_H
#define PCH_H
#include "framework.h"
#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\ksConstants.h"
#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\ksConstants3D.h"
#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\kAPI7.h"
#import"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\lib\kAPI5.tlb" \
    rename("min", "kAPI5_min") \
    rename("max", "kAPI5_max") \
    rename("GetObject", "kAPI5_GetObject")
#import"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\lib\kAPI7.tlb" \
    rename("DeleteFile", "kAPI7_DeleteFile") \
    rename("PostMessage", "kAPI7_PostMessage") \
    rename("GetObject", "kAPI7_GetObject") \
    rename("FindText", "kAPI7_FindText") \
    rename("MessageBoxEx", "kAPI7_MessageBoxEx") \
    rename("DrawText", "kAPI7_DrawText")
#endif
```

## Файл `pch.cpp`

```cpp
#include "pch.h"
```

## Файл `Resource.h`

```cpp
#define IDR_MAINFRAME 128
#define IDM_ABOUTBOX 0x0010
#define IDD_ABOUTBOX 100
#define IDS_ABOUTBOX 101
#define IDD_KURSOVAYA_DETMASH_DIALOG 102
#define IDC_RADIO_OVERLAY 1000
#define IDC_RADIO_INSET 1001
#define IDC_EDIT_D 1002
#define IDC_EDIT_H 1003
#define IDC_STATIC_H_RANGE 1004
#define IDC_CHECK_SEAL 1005
#define IDC_RADIO_SEAL_TYPE1 1006
#define IDC_RADIO_SEAL_TYPE2 1007
#define IDC_COMBO_SHAFT_D 1008
#define IDC_EDIT_D1_RESULT 1010
#define IDC_EDIT_D2_RESULT 1011
#define IDC_EDIT_D3_RESULT 1012
#define IDC_EDIT_H_RESULT 1013
#define IDC_EDIT_H_SMALL_RESULT 1014
#define IDC_EDIT_S_RESULT 1015
#define IDC_EDIT_B_RESULT 1016
#define IDC_EDIT_HOLE_D_RESULT 1017
#define IDC_EDIT_COUNTERBORE_RESULT 1018
#define IDC_EDIT_THREAD_RESULT 1019
#define IDC_EDIT_HOLE_COUNT_RESULT 1020
#define IDC_EDIT_SEAL_D_RESULT 1021
#define IDC_EDIT_SEAL_H_RESULT 1022
#define IDC_EDIT_CLEARANCE_RESULT 1023
#define IDC_STATIC_STATUS 1024
#define IDC_BUTTON_BUILD 1025
#define IDC_BUTTON_RESET 1026
#define IDC_EDIT_FILLET_RESULT 1027
#define IDC_EDIT_OUTER_FILLET_RESULT 1028
#define IDC_TAB_MAIN 1029
#define IDC_STATIC_DRAWING_OVERLAY 1030
#define IDC_STATIC_DRAWING_INSET 1031
#define IDC_STATIC_DRAWING_SEALS 1032
#define IDC_STATIC_DRAWING_OVERLAY_HINT 1033
#define IDC_STATIC_DRAWING_INSET_HINT 1034
#define IDC_STATIC_DRAWING_SEALS_HINT 1035
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE 129
#define _APS_NEXT_CONTROL_VALUE 1036
#define _APS_NEXT_SYMED_VALUE 101
#define _APS_NEXT_COMMAND_VALUE 32771
#endif
#endif
```

## Файл `CoverParameters.h`

```cpp
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
```

## Файл `CoverParameters.cpp`

```cpp
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
```

## Файл `CKompas.h`

```cpp
#pragma once
#include "CoverParameters.h"
#include <string>
class CKompas
{
public:
    CKompas();
    bool Connect();
    bool IsConnected() const;
    bool CreateCover(const CoverParameters& parameters, std::wstring& error);
    Kompas6API5::KompasObjectPtr KompasApp5;
    Kompas6API5::ksDocument3DPtr Doc;
    Kompas6API5::ksPartPtr Part;
};
```

## Файл `CKompas.cpp`

```cpp
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
```

## Файл `kursovaya_detmash.h`

```cpp
#pragma once
#ifndef __AFXWIN_H__
    #error "включить pch.h до включения этого файла в PCH"
#endif
#include "resource.h"
class CkursovayadetmashApp : public CWinApp
{
public:
    CkursovayadetmashApp();
public:
    virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};
extern CkursovayadetmashApp theApp;
```

## Файл `kursovaya_detmash.cpp`

```cpp
#include "pch.h"
#include "framework.h"
#include "kursovaya_detmash.h"
#include "kursovaya_detmashDlg.h"
#include "CKompas.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BEGIN_MESSAGE_MAP(CkursovayadetmashApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()
CkursovayadetmashApp::CkursovayadetmashApp()
{
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}
CkursovayadetmashApp theApp;
BOOL CkursovayadetmashApp::InitInstance()
{
    // Координаты элементов диалога масштабируются в OnInitDialog. Режим Per-Monitor V2
    // нужен, чтобы GetDpiForWindow возвращал реальный DPI монитора, а Windows не растягивала окно как картинку.
    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
    CWinApp::InitInstance();
    if (!AfxOleInit())
    {
        AfxMessageBox(_T("Не удалось инициализировать COM/OLE."));
        return FALSE;
    }
    AfxEnableControlContainer();
    CKompas kompas;
    if (!kompas.IsConnected())
    {
        AfxMessageBox(_T("Не удалось запустить КОМПАС-3D."));
        return FALSE;
    }
    CShellManager *pShellManager = new CShellManager;
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
    SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
    CkursovayadetmashDlg dlg(kompas);
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
    }
    else if (nResponse == IDCANCEL)
    {
    }
    else if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
        TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
    }
    if (pShellManager != nullptr)
    {
        delete pShellManager;
    }
#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
    ControlBarCleanUp();
#endif
    return FALSE;
}
```

## Файл `kursovaya_detmashDlg.h`

```cpp
#pragma once
#include "CoverParameters.h"
class CKompas;
class CkursovayadetmashDlg : public CDialog
{
public:
    CkursovayadetmashDlg(CKompas& kompas, CWnd* pParent = nullptr);
    virtual ~CkursovayadetmashDlg();
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_KURSOVAYA_DETMASH_DIALOG };
#endif
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnParametersChanged();
    afx_msg void OnSealExecutionChanged();
    afx_msg void OnSealTypeChanged();
    afx_msg void OnSealDiameterChanged();
    afx_msg void OnBuildModel();
    afx_msg void OnResetParameters();
    afx_msg void OnTabSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
private:
    CKompas& m_kompas;
    CFont m_uiFont;
    std::vector<HWND> m_parameterControls;
    std::vector<HWND> m_drawingPageControls[3];
    HWND m_drawingPreviews[3]{};
    HWND m_drawingHints[3]{};
    HBITMAP m_drawingBitmaps[3]{};
    CSize m_fixedWindowSize;
    bool m_updatingUi = false;
    void CreateMainTabs();
    void CreateParameterControls();
    void CreateDrawingControls();
    void ShowSelectedTab();
    bool LoadDrawing(int index, const CString& path, bool showError);
    void LoadProjectDrawings();
    void ResetParameters();
    void UpdateInterface();
    void PopulateSealDiameters();
    bool TryReadBaseInput(CoverInput& input) const;
    bool HasCompatibleSeal(const CoverInput& baseInput, SealType type) const;
    bool SelectCompatibleSeal(const CoverInput& baseInput, SealType type);
    bool ReadInput(CoverInput& input, CString& error, bool requireSealSelection = true) const;
    void ShowParameters(const CoverParameters* parameters);
    void SetStatus(const CString& text);
};
```

## Файл `kursovaya_detmashDlg.cpp`

```cpp
#include "pch.h"
#include "framework.h"
#include "kursovaya_detmash.h"
#include "kursovaya_detmashDlg.h"
#include "CKompas.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
namespace
{
    UINT g_layoutDpi = 96;
    HFONT g_layoutFont = nullptr;
    int g_layoutOffsetY = 0;
    std::vector<HWND>* g_createdControls = nullptr;
    int ScaleLayout(int value)
    {
        return ::MulDiv(value, static_cast<int>(g_layoutDpi), 96);
    }
    HWND CreateControl(HWND parent, DWORD exStyle, LPCWSTR className, LPCWSTR text,
        DWORD style, int x, int y, int width, int height, int id)
    {
        HWND control = ::CreateWindowExW(
            exStyle, className, text, WS_CHILD | WS_VISIBLE | style,
            ScaleLayout(x), ScaleLayout(y + g_layoutOffsetY),
            ScaleLayout(width), ScaleLayout(height), parent,
            reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
            AfxGetInstanceHandle(), nullptr);
        if (control != nullptr)
        {
            ::SendMessage(control, WM_SETFONT,
                reinterpret_cast<WPARAM>(g_layoutFont != nullptr
                    ? g_layoutFont
                    : ::GetStockObject(DEFAULT_GUI_FONT)), TRUE);
            if (g_createdControls != nullptr)
                g_createdControls->push_back(control);
        }
        return control;
    }
    void CreateLabel(HWND parent, LPCWSTR text, int x, int y, int width, int height = 18)
    {
        CreateControl(parent, 0, L"STATIC", text, SS_LEFT, x, y, width, height, -1);
    }
    void CreateReadOnlyEdit(HWND parent, int id, int x, int y, int width)
    {
        CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"",
            ES_AUTOHSCROLL | ES_READONLY, x, y, width, 22, id);
    }
    CString FormatNumber(double value)
    {
        CString text;
        if (std::abs(value - std::round(value)) < 1e-7)
            text.Format(L"%.0f", value);
        else
        {
            text.Format(L"%.2f", value);
            text.TrimRight(L'0');
            text.TrimRight(L'.');
        }
        return text;
    }
}
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
CkursovayadetmashDlg::CkursovayadetmashDlg(CKompas& kompas, CWnd* pParent )
    : CDialog(IDD_KURSOVAYA_DETMASH_DIALOG, pParent)
    , m_kompas(kompas)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CkursovayadetmashDlg::~CkursovayadetmashDlg()
{
    for (HBITMAP bitmap : m_drawingBitmaps)
    {
        if (bitmap != nullptr)
            ::DeleteObject(bitmap);
    }
}
void CkursovayadetmashDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CkursovayadetmashDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_GETMINMAXINFO()
    ON_BN_CLICKED(IDC_RADIO_OVERLAY, &CkursovayadetmashDlg::OnParametersChanged)
    ON_BN_CLICKED(IDC_RADIO_INSET, &CkursovayadetmashDlg::OnParametersChanged)
    ON_BN_CLICKED(IDC_CHECK_SEAL, &CkursovayadetmashDlg::OnSealExecutionChanged)
    ON_BN_CLICKED(IDC_RADIO_SEAL_TYPE1, &CkursovayadetmashDlg::OnSealTypeChanged)
    ON_BN_CLICKED(IDC_RADIO_SEAL_TYPE2, &CkursovayadetmashDlg::OnSealTypeChanged)
    ON_EN_CHANGE(IDC_EDIT_D, &CkursovayadetmashDlg::OnParametersChanged)
    ON_EN_CHANGE(IDC_EDIT_H, &CkursovayadetmashDlg::OnParametersChanged)
    ON_CBN_SELCHANGE(IDC_COMBO_SHAFT_D, &CkursovayadetmashDlg::OnSealDiameterChanged)
    ON_BN_CLICKED(IDC_BUTTON_BUILD, &CkursovayadetmashDlg::OnBuildModel)
    ON_BN_CLICKED(IDC_BUTTON_RESET, &CkursovayadetmashDlg::OnResetParameters)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CkursovayadetmashDlg::OnTabSelectionChanged)
END_MESSAGE_MAP()
BOOL CkursovayadetmashDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    g_layoutDpi = ::GetDpiForWindow(GetSafeHwnd());
    if (g_layoutDpi == 0)
        g_layoutDpi = 96;
    LOGFONT uiFont{};
    uiFont.lfHeight = -::MulDiv(9, static_cast<int>(g_layoutDpi), 72);
    uiFont.lfWeight = FW_NORMAL;
    uiFont.lfCharSet = DEFAULT_CHARSET;
    wcscpy_s(uiFont.lfFaceName, L"Segoe UI");
    m_uiFont.CreateFontIndirect(&uiFont);
    g_layoutFont = static_cast<HFONT>(m_uiFont.GetSafeHandle());
    SetFont(&m_uiFont);
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    SetWindowText(L"Построение крышки подшипника редуктора");
    ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, 0, SWP_FRAMECHANGED);
    SetWindowPos(nullptr, 0, 0, ScaleLayout(880), ScaleLayout(610),
        SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
    CRect fixedWindowRect;
    GetWindowRect(&fixedWindowRect);
    m_fixedWindowSize = fixedWindowRect.Size();
    if (CMenu* systemMenu = GetSystemMenu(FALSE))
    {
        systemMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
        systemMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
        DrawMenuBar();
    }
    CenterWindow();
    if (CWnd* okButton = GetDlgItem(IDOK))
        okButton->ShowWindow(SW_HIDE);
    if (CWnd* placeholder = GetDlgItem(IDC_STATIC))
        placeholder->ShowWindow(SW_HIDE);
    CreateMainTabs();
    g_layoutOffsetY = 34;
    g_createdControls = &m_parameterControls;
    CreateParameterControls();
    g_createdControls = nullptr;
    g_layoutOffsetY = 0;
    CreateDrawingControls();
    LoadProjectDrawings();
    ShowSelectedTab();
    SetDefID(IDC_BUTTON_BUILD);
    ResetParameters();
    return TRUE;
}
void CkursovayadetmashDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}
void CkursovayadetmashDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}
HCURSOR CkursovayadetmashDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
void CkursovayadetmashDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    CDialog::OnGetMinMaxInfo(lpMMI);
    if (m_fixedWindowSize.cx <= 0 || m_fixedWindowSize.cy <= 0)
        return;
    lpMMI->ptMinTrackSize.x = m_fixedWindowSize.cx;
    lpMMI->ptMinTrackSize.y = m_fixedWindowSize.cy;
    lpMMI->ptMaxTrackSize.x = m_fixedWindowSize.cx;
    lpMMI->ptMaxTrackSize.y = m_fixedWindowSize.cy;
}
void CkursovayadetmashDlg::CreateMainTabs()
{
    HWND tab = ::CreateControl(
        GetSafeHwnd(), 0, WC_TABCONTROLW, L"",
        TCS_BUTTONS | TCS_FLATBUTTONS | TCS_FIXEDWIDTH | WS_TABSTOP,
        10, 6, 820, 30, IDC_TAB_MAIN);
    if (tab == nullptr)
        return;
    ::SendMessage(tab, TCM_SETITEMSIZE, 0,
        MAKELPARAM(ScaleLayout(195), ScaleLayout(24)));
    const wchar_t* titles[] =
    {
        L"Параметры",
        L"Накладная крышка",
        L"Закладная крышка",
        L"Манжеты"
    };
    for (int index = 0; index < 4; ++index)
    {
        TCITEM item{};
        item.mask = TCIF_TEXT;
        item.pszText = const_cast<LPWSTR>(titles[index]);
        ::SendMessage(tab, TCM_INSERTITEM, index,
            reinterpret_cast<LPARAM>(&item));
    }
    ::SendMessage(tab, TCM_SETCURSEL, 0, 0);
}
void CkursovayadetmashDlg::CreateDrawingControls()
{
    const wchar_t* hints[] =
    {
        L"Чертёж накладной крышки ещё не выбран",
        L"Чертёж закладной крышки ещё не выбран",
        L"Чертёж манжет ещё не выбран"
    };
    const int previewIds[] =
    {
        IDC_STATIC_DRAWING_OVERLAY,
        IDC_STATIC_DRAWING_INSET,
        IDC_STATIC_DRAWING_SEALS
    };
    const int hintIds[] =
    {
        IDC_STATIC_DRAWING_OVERLAY_HINT,
        IDC_STATIC_DRAWING_INSET_HINT,
        IDC_STATIC_DRAWING_SEALS_HINT
    };
    const wchar_t* sourceNames[] = { L"overlay", L"inset", L"seals" };
    for (int index = 0; index < 3; ++index)
    {
        g_createdControls = &m_drawingPageControls[index];
        m_drawingPreviews[index] = ::CreateControl(
            GetSafeHwnd(), WS_EX_CLIENTEDGE, L"STATIC", L"",
            SS_BITMAP | SS_CENTERIMAGE | SS_SUNKEN,
            24, 48, 812, 450, previewIds[index]);
        m_drawingHints[index] = ::CreateControl(
            GetSafeHwnd(), 0, L"STATIC", hints[index],
            SS_CENTER | SS_CENTERIMAGE,
            40, 64, 780, 418, hintIds[index]);
        CString sourceLabel;
        sourceLabel.Format(
            L"Файл: drawings\\%s.png (также поддерживаются .jpg, .jpeg и .bmp)",
            sourceNames[index]);
        ::CreateControl(
            GetSafeHwnd(), 0, L"STATIC", sourceLabel,
            SS_LEFT, 24, 505, 620, 20, -1);
    }
    g_createdControls = nullptr;
}
void CkursovayadetmashDlg::ShowSelectedTab()
{
    CWnd* tabWindow = GetDlgItem(IDC_TAB_MAIN);
    const int selection = tabWindow == nullptr
        ? 0
        : static_cast<int>(tabWindow->SendMessage(TCM_GETCURSEL));
    for (HWND control : m_parameterControls)
        ::ShowWindow(control, selection == 0 ? SW_SHOW : SW_HIDE);
    for (int page = 0; page < 3; ++page)
    {
        const bool visible = selection == page + 1;
        for (HWND control : m_drawingPageControls[page])
            ::ShowWindow(control, visible ? SW_SHOW : SW_HIDE);
        if (visible && m_drawingBitmaps[page] != nullptr)
            ::ShowWindow(m_drawingHints[page], SW_HIDE);
    }
    SetDefID(selection == 0
        ? IDC_BUTTON_BUILD
        : IDCANCEL);
    Invalidate(FALSE);
}
void CkursovayadetmashDlg::OnTabSelectionChanged(NMHDR*, LRESULT* pResult)
{
    ShowSelectedTab();
    *pResult = 0;
}
bool CkursovayadetmashDlg::LoadDrawing(
    int index,
    const CString& path,
    bool showError)
{
    if (index < 0 || index >= 3 || m_drawingPreviews[index] == nullptr)
        return false;
    CImage source;
    const HRESULT loadResult = source.Load(path);
    if (FAILED(loadResult) || source.GetWidth() <= 0 || source.GetHeight() <= 0)
    {
        if (showError)
            AfxMessageBox(L"Не удалось открыть выбранное изображение.", MB_ICONERROR);
        return false;
    }
    CRect previewRect;
    ::GetClientRect(m_drawingPreviews[index], &previewRect);
    const int canvasWidth = previewRect.Width();
    const int canvasHeight = previewRect.Height();
    if (canvasWidth <= 0 || canvasHeight <= 0)
        return false;
    CImage canvas;
    if (!canvas.Create(canvasWidth, canvasHeight, 32))
        return false;
    HDC canvasDc = canvas.GetDC();
    RECT background{ 0, 0, canvasWidth, canvasHeight };
    ::FillRect(canvasDc, &background,
        static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH)));
    ::SetStretchBltMode(canvasDc, HALFTONE);
    const int padding = ScaleLayout(12);
    const double widthScale = static_cast<double>(canvasWidth - 2 * padding) / source.GetWidth();
    const double heightScale = static_cast<double>(canvasHeight - 2 * padding) / source.GetHeight();
    const double scale = (std::min)(widthScale, heightScale);
    const int drawingWidth = (std::max)(1, static_cast<int>(std::lround(source.GetWidth() * scale)));
    const int drawingHeight = (std::max)(1, static_cast<int>(std::lround(source.GetHeight() * scale)));
    const int drawingX = (canvasWidth - drawingWidth) / 2;
    const int drawingY = (canvasHeight - drawingHeight) / 2;
    source.Draw(canvasDc, drawingX, drawingY, drawingWidth, drawingHeight);
    canvas.ReleaseDC();
    HBITMAP newBitmap = canvas.Detach();
    ::SendMessage(m_drawingPreviews[index], STM_SETIMAGE,
        IMAGE_BITMAP, reinterpret_cast<LPARAM>(newBitmap));
    if (m_drawingBitmaps[index] != nullptr)
        ::DeleteObject(m_drawingBitmaps[index]);
    m_drawingBitmaps[index] = newBitmap;
    ::ShowWindow(m_drawingHints[index], SW_HIDE);
    ::InvalidateRect(m_drawingPreviews[index], nullptr, TRUE);
    return true;
}
void CkursovayadetmashDlg::LoadProjectDrawings()
{
    wchar_t modulePath[MAX_PATH]{};
    if (::GetModuleFileNameW(nullptr, modulePath, _countof(modulePath)) == 0)
        return;
    CString executableDirectory(modulePath);
    const int lastSlash = executableDirectory.ReverseFind(L'\\');
    if (lastSlash < 0)
        return;
    executableDirectory = executableDirectory.Left(lastSlash);
    const wchar_t* baseNames[] = { L"overlay", L"inset", L"seals" };
    const wchar_t* extensions[] = { L".png", L".jpg", L".jpeg", L".bmp" };
    CString projectDrawingDirectory;
    projectDrawingDirectory.Format(L"%s\\..\\..\\drawings",
        executableDirectory.GetString());
    const CString drawingDirectories[] =
    {
        projectDrawingDirectory,
        executableDirectory + L"\\drawings"
    };
    for (int index = 0; index < 3; ++index)
    {
        bool loaded = false;
        for (const CString& drawingDirectory : drawingDirectories)
        {
            for (const wchar_t* extension : extensions)
            {
                CString path;
                path.Format(L"%s\\%s%s",
                    drawingDirectory.GetString(), baseNames[index], extension);
                const DWORD attributes = ::GetFileAttributesW(path);
                if (attributes == INVALID_FILE_ATTRIBUTES ||
                    (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                    continue;
                if (LoadDrawing(index, path, false))
                {
                    loaded = true;
                    break;
                }
            }
            if (loaded)
                break;
        }
    }
}
#define CreateControl(...) ::CreateControl(__VA_ARGS__)
void CkursovayadetmashDlg::CreateParameterControls()
{
    const HWND parent = GetSafeHwnd();
    CreateControl(parent, 0, L"BUTTON", L"Тип крышки", BS_GROUPBOX, 10, 8, 390, 54, -1);
    CreateControl(parent, 0, L"BUTTON", L"Накладная", BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP,
        24, 29, 130, 20, IDC_RADIO_OVERLAY);
    CreateControl(parent, 0, L"BUTTON", L"Закладная", BS_AUTORADIOBUTTON | WS_TABSTOP,
        190, 29, 130, 20, IDC_RADIO_INSET);
    CreateControl(parent, 0, L"BUTTON", L"Основные параметры, мм", BS_GROUPBOX, 10, 68, 390, 118, -1);
    CreateLabel(parent, L"Исходный диаметр D:", 24, 92, 155);
    CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"", ES_AUTOHSCROLL | WS_TABSTOP,
        185, 88, 75, 23, IDC_EDIT_D);
    CreateLabel(parent, L"Размер крышки h:", 24, 124, 155);
    CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"", ES_AUTOHSCROLL | WS_TABSTOP,
        185, 120, 75, 23, IDC_EDIT_H);
    CreateControl(parent, 0, L"STATIC", L"Введите D", SS_LEFT,
        270, 124, 116, 18, IDC_STATIC_H_RANGE);
    CreateControl(parent, 0, L"BUTTON", L"Исполнение с манжетой", BS_AUTOCHECKBOX | WS_TABSTOP,
        24, 154, 210, 20, IDC_CHECK_SEAL);
    CreateControl(parent, 0, L"BUTTON", L"Манжета по ГОСТ 8752-79", BS_GROUPBOX, 10, 192, 390, 142, -1);
    CreateControl(parent, 0, L"BUTTON", L"Тип 1 — без пыльника",
        BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP, 24, 216, 170, 20, IDC_RADIO_SEAL_TYPE1);
    CreateControl(parent, 0, L"BUTTON", L"Тип 2 — с пыльником",
        BS_AUTORADIOBUTTON | WS_TABSTOP, 205, 216, 175, 20, IDC_RADIO_SEAL_TYPE2);
    CreateLabel(parent, L"Диаметр вала d*:", 24, 250, 145);
    CreateControl(parent, WS_EX_CLIENTEDGE, L"COMBOBOX", L"",
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, 185, 245, 75, 190, IDC_COMBO_SHAFT_D);
    CreateLabel(parent, L"Посадочный D*:", 24, 282, 125);
    CreateReadOnlyEdit(parent, IDC_EDIT_SEAL_D_RESULT, 150, 278, 75);
    CreateLabel(parent, L"Ширина h*:", 238, 282, 75);
    CreateReadOnlyEdit(parent, IDC_EDIT_SEAL_H_RESULT, 310, 278, 65);
    CreateLabel(parent, L"Проходное отверстие равно d* + 1 мм", 24, 309, 320);
    CreateControl(parent, 0, L"BUTTON", L"Рассчитанные параметры, мм", BS_GROUPBOX,
        410, 8, 420, 326, -1);
    CreateLabel(parent, L"D1", 430, 36, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_D1_RESULT, 458, 31, 70);
    CreateLabel(parent, L"D2", 550, 36, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_D2_RESULT, 578, 31, 70);
    CreateLabel(parent, L"D3", 670, 36, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_D3_RESULT, 698, 31, 70);
    CreateLabel(parent, L"H", 430, 70, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_H_RESULT, 458, 65, 70);
    CreateLabel(parent, L"h", 550, 70, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_H_SMALL_RESULT, 578, 65, 70);
    CreateLabel(parent, L"s", 670, 70, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_S_RESULT, 698, 65, 70);
    CreateLabel(parent, L"b", 430, 104, 25);
    CreateReadOnlyEdit(parent, IDC_EDIT_B_RESULT, 458, 99, 70);
    CreateLabel(parent, L"R внутр.", 550, 104, 68);
    CreateReadOnlyEdit(parent, IDC_EDIT_FILLET_RESULT, 620, 99, 48);
    CreateLabel(parent, L"R нар.", 680, 104, 56);
    CreateReadOnlyEdit(parent, IDC_EDIT_OUTER_FILLET_RESULT, 738, 99, 52);
    CreateControl(parent, 0, L"BUTTON", L"Крепёж накладной крышки", BS_GROUPBOX,
        424, 134, 390, 86, -1);
    CreateLabel(parent, L"d отверстия:", 440, 158, 88);
    CreateReadOnlyEdit(parent, IDC_EDIT_HOLE_D_RESULT, 530, 153, 58);
    CreateLabel(parent, L"d1 цековки:", 602, 158, 85);
    CreateReadOnlyEdit(parent, IDC_EDIT_COUNTERBORE_RESULT, 690, 153, 58);
    CreateLabel(parent, L"Резьба:", 440, 190, 55);
    CreateReadOnlyEdit(parent, IDC_EDIT_THREAD_RESULT, 500, 185, 58);
    CreateLabel(parent, L"Количество n:", 602, 190, 88);
    CreateReadOnlyEdit(parent, IDC_EDIT_HOLE_COUNT_RESULT, 690, 185, 58);
    CreateControl(parent, 0, L"BUTTON", L"Посадочное место манжеты", BS_GROUPBOX,
        424, 226, 390, 92, -1);
    CreateLabel(parent, L"Отверстие d*+1:", 440, 252, 112);
    CreateReadOnlyEdit(parent, IDC_EDIT_CLEARANCE_RESULT, 554, 247, 65);
    CreateLabel(parent, L"Фаска:", 642, 252, 54);
    HWND chamfer = CreateControl(parent, WS_EX_CLIENTEDGE, L"EDIT", L"2x15°",
        ES_AUTOHSCROLL | ES_READONLY, 698, 247, 80, 22, -1);
    if (chamfer != nullptr)
        ::SetWindowTextW(chamfer, L"2x15°");
    CreateLabel(parent, L"Входная фаска 2x15°, задняя стенка 5 мм", 440, 286, 320);
    CreateControl(parent, 0, L"BUTTON", L"Порядок работы", BS_GROUPBOX, 10, 342, 820, 104, -1);
    CreateLabel(parent, L"1. Выберите тип крышки и введите D.", 24, 366, 380);
    CreateLabel(parent, L"2. Для накладной крышки задайте h в показанном диапазоне.", 24, 389, 390);
    CreateLabel(parent, L"3. При необходимости включите манжету и задайте её параметры.", 420, 366, 390);
    CreateLabel(parent, L"4. Нажмите «Построить модель». Будет создана новая деталь.", 420, 389, 390);
    CreateLabel(parent, L"Материал детали не назначается. Модель остаётся несохранённой в КОМПАС-3D.", 24, 416, 760);
    CreateControl(parent, 0, L"STATIC", L"Введите исходные параметры.", SS_CENTER,
        10, 454, 820, 22, IDC_STATIC_STATUS);
    CreateControl(parent, 0, L"BUTTON", L"Построить модель", BS_DEFPUSHBUTTON | WS_TABSTOP,
        420, 490, 132, 30, IDC_BUTTON_BUILD);
    CreateControl(parent, 0, L"BUTTON", L"Сбросить параметры", BS_PUSHBUTTON | WS_TABSTOP,
        560, 490, 142, 30, IDC_BUTTON_RESET);
    if (CWnd* closeButton = GetDlgItem(IDCANCEL))
    {
        closeButton->SetWindowText(L"Закрыть");
        closeButton->SetFont(&m_uiFont);
        closeButton->MoveWindow(
            ScaleLayout(710), ScaleLayout(524),
            ScaleLayout(120), ScaleLayout(30));
        closeButton->ShowWindow(SW_SHOW);
    }
}
#undef CreateControl
void CkursovayadetmashDlg::ResetParameters()
{
    m_updatingUi = true;
    CheckRadioButton(IDC_RADIO_OVERLAY, IDC_RADIO_INSET, IDC_RADIO_OVERLAY);
    CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
    CheckRadioButton(IDC_RADIO_SEAL_TYPE1, IDC_RADIO_SEAL_TYPE2, IDC_RADIO_SEAL_TYPE1);
    SetDlgItemText(IDC_EDIT_D, L"40");
    SetDlgItemText(IDC_EDIT_H, L"5");
    m_updatingUi = false;
    PopulateSealDiameters();
    UpdateInterface();
}
void CkursovayadetmashDlg::OnResetParameters()
{
    ResetParameters();
}
void CkursovayadetmashDlg::OnParametersChanged()
{
    if (m_updatingUi)
        return;
    PopulateSealDiameters();
    if (IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED)
    {
        CoverInput baseInput;
        if (TryReadBaseInput(baseInput))
        {
            const SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
                ? SealType::Type2
                : SealType::Type1;
            SelectCompatibleSeal(baseInput, type);
        }
    }
    UpdateInterface();
}
void CkursovayadetmashDlg::OnSealExecutionChanged()
{
    if (m_updatingUi)
        return;
    if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED)
    {
        PopulateSealDiameters();
        UpdateInterface();
        return;
    }
    CoverInput baseInput;
    if (!TryReadBaseInput(baseInput))
    {
        PopulateSealDiameters();
        UpdateInterface();
        return;
    }
    const bool hasType1 = HasCompatibleSeal(baseInput, SealType::Type1);
    const bool hasType2 = HasCompatibleSeal(baseInput, SealType::Type2);
    if (!hasType1 && !hasType2)
    {
        AfxMessageBox(
            L"Для текущих размеров крышки не помещается ни одна манжета.\n"
            L"Измените D или h, затем снова включите исполнение с манжетой.",
            MB_ICONWARNING);
        CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
        PopulateSealDiameters();
        UpdateInterface();
        return;
    }
    SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
        ? SealType::Type2
        : SealType::Type1;
    if ((type == SealType::Type1 && !hasType1) ||
        (type == SealType::Type2 && !hasType2))
    {
        type = hasType1 ? SealType::Type1 : SealType::Type2;
        CheckRadioButton(
            IDC_RADIO_SEAL_TYPE1,
            IDC_RADIO_SEAL_TYPE2,
            type == SealType::Type1 ? IDC_RADIO_SEAL_TYPE1 : IDC_RADIO_SEAL_TYPE2);
    }
    PopulateSealDiameters();
    SelectCompatibleSeal(baseInput, type);
    UpdateInterface();
}
void CkursovayadetmashDlg::OnSealTypeChanged()
{
    if (m_updatingUi)
        return;
    const SealType selectedType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
        ? SealType::Type2
        : SealType::Type1;
    PopulateSealDiameters();
    if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED)
    {
        UpdateInterface();
        return;
    }
    CoverInput baseInput;
    if (!TryReadBaseInput(baseInput))
    {
        UpdateInterface();
        return;
    }
    if (!HasCompatibleSeal(baseInput, selectedType))
    {
        const CString typeName = selectedType == SealType::Type1 ? L"1" : L"2";
        CString message;
        message.Format(
            L"Манжеты типа %s не помещаются в крышку с текущими размерами.\n"
            L"Измените D или h либо выберите другой тип манжеты.",
            typeName.GetString());
        AfxMessageBox(message, MB_ICONWARNING);
        const SealType otherType = selectedType == SealType::Type1
            ? SealType::Type2
            : SealType::Type1;
        if (HasCompatibleSeal(baseInput, otherType))
        {
            CheckRadioButton(
                IDC_RADIO_SEAL_TYPE1,
                IDC_RADIO_SEAL_TYPE2,
                otherType == SealType::Type1 ? IDC_RADIO_SEAL_TYPE1 : IDC_RADIO_SEAL_TYPE2);
            PopulateSealDiameters();
            SelectCompatibleSeal(baseInput, otherType);
        }
        else
        {
            CheckDlgButton(IDC_CHECK_SEAL, BST_UNCHECKED);
        }
    }
    else
    {
        SelectCompatibleSeal(baseInput, selectedType);
    }
    UpdateInterface();
}
void CkursovayadetmashDlg::OnSealDiameterChanged()
{
    if (m_updatingUi)
        return;
    CoverInput baseInput;
    if (IsDlgButtonChecked(IDC_CHECK_SEAL) != BST_CHECKED ||
        !TryReadBaseInput(baseInput))
    {
        UpdateInterface();
        return;
    }
    CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
    const int selection = combo == nullptr ? CB_ERR : combo->GetCurSel();
    if (selection != CB_ERR)
    {
        CoverInput trial = baseInput;
        trial.withSeal = true;
        trial.sealType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
            ? SealType::Type2
            : SealType::Type1;
        trial.shaftDiameter = static_cast<double>(combo->GetItemData(selection));
        CoverParameters parameters;
        std::wstring error;
        if (!CalculateCoverParameters(trial, parameters, error))
        {
            AfxMessageBox(CString(error.c_str()), MB_ICONWARNING);
            SelectCompatibleSeal(baseInput, trial.sealType);
        }
    }
    UpdateInterface();
}
bool CkursovayadetmashDlg::ReadInput(
    CoverInput& input,
    CString& error,
    bool requireSealSelection) const
{
    auto readNumber = [this](int id, double& value) -> bool
    {
        CString text;
        GetDlgItemText(id, text);
        text.Trim();
        text.Replace(L',', L'.');
        if (text.IsEmpty())
            return false;
        wchar_t* end = nullptr;
        value = std::wcstod(text.GetString(), &end);
        return end != text.GetString() && end != nullptr && *end == L'\0' && std::isfinite(value);
    };
    input.coverType = IsDlgButtonChecked(IDC_RADIO_INSET) == BST_CHECKED
        ? CoverType::Inset
        : CoverType::Overlay;
    if (!readNumber(IDC_EDIT_D, input.D))
    {
        error = L"Введите числовое значение D.";
        return false;
    }
    if (input.coverType == CoverType::Overlay)
    {
        if (!readNumber(IDC_EDIT_H, input.h))
        {
            error = L"Введите числовое значение h.";
            return false;
        }
    }
    else
    {
        input.h = 5;
    }
    input.withSeal = IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED;
    input.sealType = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
        ? SealType::Type2
        : SealType::Type1;
    if (input.withSeal)
    {
        const CComboBox* combo = reinterpret_cast<const CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
        const int selection = combo == nullptr ? CB_ERR : combo->GetCurSel();
        if (selection == CB_ERR)
        {
            if (!requireSealSelection)
            {
                input.withSeal = false;
                return true;
            }
            error = L"Выберите диаметр вала для манжеты.";
            return false;
        }
        input.shaftDiameter = static_cast<double>(combo->GetItemData(selection));
    }
    return true;
}
void CkursovayadetmashDlg::PopulateSealDiameters()
{
    CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
    if (combo == nullptr)
        return;
    int previousValue = -1;
    const int oldSelection = combo->GetCurSel();
    if (oldSelection != CB_ERR)
        previousValue = static_cast<int>(combo->GetItemData(oldSelection));
    m_updatingUi = true;
    combo->ResetContent();
    const SealType type = IsDlgButtonChecked(IDC_RADIO_SEAL_TYPE2) == BST_CHECKED
        ? SealType::Type2
        : SealType::Type1;
    for (double shaftDiameter : GetSealShaftDiameters(type))
    {
        const CString value = FormatNumber(shaftDiameter);
        const int index = combo->AddString(value);
        combo->SetItemData(index, static_cast<DWORD_PTR>(std::lround(shaftDiameter)));
        if (static_cast<int>(std::lround(shaftDiameter)) == previousValue)
            combo->SetCurSel(index);
    }
    if (combo->GetCurSel() == CB_ERR && combo->GetCount() > 0)
        combo->SetCurSel(0);
    m_updatingUi = false;
}
bool CkursovayadetmashDlg::TryReadBaseInput(CoverInput& input) const
{
    CString inputError;
    if (!ReadInput(input, inputError, false))
        return false;
    input.withSeal = false;
    CoverParameters parameters;
    std::wstring calculationError;
    return CalculateCoverParameters(input, parameters, calculationError);
}
bool CkursovayadetmashDlg::HasCompatibleSeal(
    const CoverInput& baseInput,
    SealType type) const
{
    for (double shaftDiameter : GetSealShaftDiameters(type))
    {
        CoverInput trial = baseInput;
        trial.withSeal = true;
        trial.sealType = type;
        trial.shaftDiameter = shaftDiameter;
        CoverParameters parameters;
        std::wstring error;
        if (CalculateCoverParameters(trial, parameters, error))
            return true;
    }
    return false;
}
bool CkursovayadetmashDlg::SelectCompatibleSeal(
    const CoverInput& baseInput,
    SealType type)
{
    CComboBox* combo = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO_SHAFT_D));
    if (combo == nullptr)
        return false;
    auto isCompatible = [&baseInput, type](double shaftDiameter) -> bool
    {
        CoverInput trial = baseInput;
        trial.withSeal = true;
        trial.sealType = type;
        trial.shaftDiameter = shaftDiameter;
        CoverParameters parameters;
        std::wstring error;
        return CalculateCoverParameters(trial, parameters, error);
    };
    const int currentSelection = combo->GetCurSel();
    if (currentSelection != CB_ERR &&
        isCompatible(static_cast<double>(combo->GetItemData(currentSelection))))
        return true;
    for (int index = 0; index < combo->GetCount(); ++index)
    {
        if (isCompatible(static_cast<double>(combo->GetItemData(index))))
        {
            combo->SetCurSel(index);
            return true;
        }
    }
    return false;
}
void CkursovayadetmashDlg::UpdateInterface()
{
    if (m_updatingUi)
        return;
    m_updatingUi = true;
    const bool overlay = IsDlgButtonChecked(IDC_RADIO_INSET) != BST_CHECKED;
    const bool withSeal = IsDlgButtonChecked(IDC_CHECK_SEAL) == BST_CHECKED;
    if (CWnd* hEdit = GetDlgItem(IDC_EDIT_H))
        hEdit->EnableWindow(overlay);
    for (const int id : { IDC_RADIO_SEAL_TYPE1, IDC_RADIO_SEAL_TYPE2, IDC_COMBO_SHAFT_D })
    {
        if (CWnd* control = GetDlgItem(id))
            control->EnableWindow(withSeal);
    }
    CoverInput input;
    CString inputError;
    if (!ReadInput(input, inputError))
    {
        ShowParameters(nullptr);
        SetStatus(inputError);
        m_updatingUi = false;
        return;
    }
    CoverInput baseInput = input;
    baseInput.withSeal = false;
    if (baseInput.coverType == CoverType::Overlay && baseInput.h <= 0)
        baseInput.h = 5;
    CoverParameters baseParameters;
    std::wstring baseError;
    if (CalculateCoverParameters(baseInput, baseParameters, baseError))
    {
        if (overlay)
        {
            CString range;
            range.Format(L"Допустимо: %.0f–%.0f", baseParameters.hMin, baseParameters.hMax);
            SetDlgItemText(IDC_STATIC_H_RANGE, range);
        }
        else
        {
            SetDlgItemText(IDC_EDIT_H, FormatNumber(baseParameters.h));
            SetDlgItemText(IDC_STATIC_H_RANGE, L"По таблице");
        }
    }
    else
    {
        SetDlgItemText(IDC_STATIC_H_RANGE, L"Проверьте D");
    }
    CoverParameters parameters;
    std::wstring calculationError;
    if (CalculateCoverParameters(input, parameters, calculationError))
    {
        ShowParameters(&parameters);
        SetStatus(L"Параметры корректны. Модель готова к построению.");
    }
    else
    {
        ShowParameters(baseError.empty() ? &baseParameters : nullptr);
        SetStatus(CString(calculationError.c_str()));
    }
    m_updatingUi = false;
}
void CkursovayadetmashDlg::ShowParameters(const CoverParameters* p)
{
    const int resultIds[] =
    {
        IDC_EDIT_D1_RESULT, IDC_EDIT_D2_RESULT, IDC_EDIT_D3_RESULT,
        IDC_EDIT_H_RESULT, IDC_EDIT_H_SMALL_RESULT, IDC_EDIT_S_RESULT,
        IDC_EDIT_B_RESULT, IDC_EDIT_HOLE_D_RESULT, IDC_EDIT_COUNTERBORE_RESULT,
        IDC_EDIT_THREAD_RESULT, IDC_EDIT_HOLE_COUNT_RESULT,
        IDC_EDIT_SEAL_D_RESULT, IDC_EDIT_SEAL_H_RESULT,
        IDC_EDIT_CLEARANCE_RESULT, IDC_EDIT_FILLET_RESULT,
        IDC_EDIT_OUTER_FILLET_RESULT
    };
    for (int id : resultIds)
        SetDlgItemText(id, L"");
    if (p == nullptr)
        return;
    SetDlgItemText(IDC_EDIT_D1_RESULT, FormatNumber(p->D1));
    SetDlgItemText(IDC_EDIT_D2_RESULT, FormatNumber(p->D2));
    if (p->coverType == CoverType::Overlay)
        SetDlgItemText(IDC_EDIT_D3_RESULT, FormatNumber(p->D3));
    SetDlgItemText(IDC_EDIT_H_RESULT, FormatNumber(p->H));
    SetDlgItemText(IDC_EDIT_H_SMALL_RESULT, FormatNumber(p->h));
    SetDlgItemText(IDC_EDIT_S_RESULT, FormatNumber(p->s));
    if (p->coverType == CoverType::Inset)
        SetDlgItemText(IDC_EDIT_B_RESULT, FormatNumber(p->b));
    SetDlgItemText(IDC_EDIT_FILLET_RESULT, FormatNumber(p->filletRadius));
    if (p->coverType == CoverType::Overlay)
        SetDlgItemText(IDC_EDIT_OUTER_FILLET_RESULT, FormatNumber(p->outerFilletRadius));
    if (p->coverType == CoverType::Overlay)
    {
        SetDlgItemText(IDC_EDIT_HOLE_D_RESULT, FormatNumber(p->holeDiameter));
        SetDlgItemText(IDC_EDIT_COUNTERBORE_RESULT, FormatNumber(p->counterboreDiameter));
        SetDlgItemText(IDC_EDIT_THREAD_RESULT, CString(p->fastenerThread.c_str()));
        CString count;
        count.Format(L"%d", p->holeCount);
        SetDlgItemText(IDC_EDIT_HOLE_COUNT_RESULT, count);
    }
    if (p->withSeal)
    {
        SetDlgItemText(IDC_EDIT_SEAL_D_RESULT, FormatNumber(p->sealOuterDiameter));
        SetDlgItemText(IDC_EDIT_SEAL_H_RESULT, FormatNumber(p->sealWidth));
        SetDlgItemText(IDC_EDIT_CLEARANCE_RESULT, FormatNumber(p->shaftClearanceDiameter));
    }
}
void CkursovayadetmashDlg::SetStatus(const CString& text)
{
    SetDlgItemText(IDC_STATIC_STATUS, text);
}
void CkursovayadetmashDlg::OnBuildModel()
{
    CoverInput input;
    CString inputError;
    if (!ReadInput(input, inputError))
    {
        AfxMessageBox(inputError, MB_ICONWARNING);
        return;
    }
    CoverParameters parameters;
    std::wstring calculationError;
    if (!CalculateCoverParameters(input, parameters, calculationError))
    {
        AfxMessageBox(CString(calculationError.c_str()), MB_ICONWARNING);
        return;
    }
    SetStatus(L"Создание новой детали в КОМПАС-3D...");
    UpdateWindow();
    std::wstring buildError;
    if (!m_kompas.CreateCover(parameters, buildError))
    {
        const CString message = buildError.empty()
            ? L"Не удалось построить модель крышки."
            : CString(buildError.c_str());
        SetStatus(message);
        AfxMessageBox(message, MB_ICONERROR);
        return;
    }
    SetStatus(L"Модель успешно построена в новой несохранённой детали.");
}
```
