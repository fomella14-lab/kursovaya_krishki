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

