// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.Math.hpp>

#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

#include <AboutFrm.h>

#include <UtilsGeo.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsKAndM.h>
#include <UtilsFileIni.h>

#include "GPXMain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
	SetTrackName("");

	FormatSettings.DecimalSeparator = '.';

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOpenClick(TObject *Sender) {
	if (OpenDialog->Execute()) {
		OpenGPXFile(OpenDialog->FileName);
	}
}

// ---------------------------------------------------------------------------
void TMain::SetTrackName(String TrackName) {
	Caption = Application->Title + " " + GetFileVer(Application->ExeName);

	if (!TrackName.IsEmpty()) {
		Caption = TrackName + " — " + Caption;
	}
}

// ---------------------------------------------------------------------------
String FToS(Extended F, int Digits) {
	return FloatToStrF(F, ffFixed, 18, Digits);
}

// ---------------------------------------------------------------------------
String ReadName(_di_IXMLDocument XMLDocument) {
	// Strava
	String Result = XMLDocument->DocumentElement->ChildNodes->Nodes["trk"]
		->ChildNodes->Nodes["name"]->Text;

	if (Result.IsEmpty()) {
		// OsmAnd
		Result = XMLDocument->DocumentElement->ChildNodes->Nodes["metadata"]
			->ChildNodes->Nodes["name"]->Text;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void ReadPoint(_di_IXMLNode XMLNode, TGPXPointDeg &GPXPointDeg,
	TGPXPointRad &GPXPointRad) {
	GPXPointDeg.Latitude = StrToFloat(XMLNode->Attributes["lat"]);
	GPXPointDeg.Longitude = StrToFloat(XMLNode->Attributes["lon"]);
	GPXPointDeg.Altitude = StrToFloat(XMLNode->ChildNodes->Nodes["ele"]->Text);

	GPXPointRad = DegToRad(GPXPointDeg);
}

// ---------------------------------------------------------------------------
void TMain::OpenGPXFile(String FileName) {
	ShowWaitCursor();

	SetTrackName("");

	ListBox->Clear();

	eHaversine->Text = "";
	eEquirectangular->Text = "";
	eSphericalLawOfCosines->Text = "";
	eAltPlus->Text = "";

	btnOpen->Enabled = false;

	_di_IXMLDocument XMLDocument;
	_di_IXMLNode XMLNode;
	_di_IXMLNodeList XMLNodeList;

	TGPXPointDeg PointDeg;
	TGPXPointRad PointRad1, PointRad2;

	Extended IntervalHaversine, IntervalEquirectangular,
		IntervalSphericalLawOfCosines;
	Extended DistanceHaversine = 0, DistanceEquirectangular = 0,
		DistanceSphericalLawOfCosines = 0;

	float altPlus = 0, altPlus2 = 0;

	try {
		StatusBar->SimpleText = FileName;

		ListBox->Items->Add("Чтение...");

		ProcMess();

		try {
			XMLDocument = LoadXMLDocument(FileName);

			SetTrackName(ReadName(XMLDocument));

			XMLNode = XMLDocument->DocumentElement->ChildNodes->Nodes["trk"];

			XMLNodeList = XMLNode->ChildNodes->Nodes["trkseg"]->ChildNodes;

			ListBox->Clear();

			ProcMess();

			ListBox->Items->BeginUpdate();

			int MinLength = IntToStr(XMLNodeList->Count).Length();

			ReadPoint(XMLNodeList->Nodes[0], PointDeg, PointRad1);

			float alt1 = PointDeg.Altitude;
			float alt2 = 0;

			ListBox->Items->Add(IToS_0(1, MinLength) + ": " +
				FToS(PointDeg.Latitude, 7) + ", " + FToS(PointDeg.Longitude,
				7) + ", " + FToS(alt1, 1) + " | " + FToS(PointRad1.Latitude,
				18) + ", " + FToS(PointRad1.Longitude, 18));

			Extended distance = 0;
			Extended distanceOver = 0;

			float altSum = PointDeg.Altitude;
			int altCount = 1;
			float altAvg = 0, altAvg1 = PointDeg.Altitude, altAvg2 = 0;

			for (int i = 1; i < XMLNodeList->Count; i++) {
				PointRad2 = PointRad1;

				ReadPoint(XMLNodeList->Nodes[i], PointDeg, PointRad1);

				IntervalHaversine = Haversine(PointRad1, PointRad2);
				IntervalEquirectangular = Equirectangular(PointRad1, PointRad2);
				IntervalSphericalLawOfCosines =
					SphericalLawOfCosines(PointRad1, PointRad2);

				DistanceHaversine += IntervalHaversine;
				DistanceEquirectangular += IntervalEquirectangular;
				DistanceSphericalLawOfCosines += IntervalSphericalLawOfCosines;

				if (distance > 10) {
					distanceOver = distance;
					distance = 0;

					altAvg = altSum / altCount;
					altSum = 0;
					altCount = 0;

					altAvg2 = altAvg;
					
					if (altAvg2 > altAvg1) {
						altPlus2 += (altAvg2 - altAvg1);
					}

					altAvg1 = altAvg2;
				}
				else {
					distanceOver = 0;
					distance += IntervalHaversine;

					altSum += PointDeg.Altitude;
					altCount++;
				}

				alt2 = PointDeg.Altitude;

				if (alt2 > alt1) {
					altPlus += (alt2 - alt1);
				}

				ListBox->Items->Add(IToS_0(i + 1, MinLength) + ": " +
					FToS(PointDeg.Latitude, 7) + ", " + FToS(PointDeg.Longitude,
					7) + ", " + FToS(alt2, 1) + " (" + FToS(alt2 - alt1, 1) +
					")" + " | " + FToS(PointRad1.Latitude, 18) + ", " +
					FToS(PointRad1.Longitude, 18) + " >>> " +
					FToS(IntervalHaversine, 2) + " | " +
					FToS(IntervalEquirectangular, 2) + " | " +
					FToS(IntervalSphericalLawOfCosines, 2) + " | " +
					FToS(distanceOver, 2) + " | " + FToS(altAvg, 2));

				altAvg = 0;

				alt1 = alt2;

				ProcMess();
			}

			eHaversine->Text = FToS(DistanceHaversine / 1000, 3);
			eEquirectangular->Text = FToS(DistanceEquirectangular / 1000, 3);
			eSphericalLawOfCosines->Text =
				FToS(DistanceSphericalLawOfCosines / 1000, 3);

			eAltPlus->Text = FToS(altPlus, 1) + " | " + FToS(altPlus2, 1);
		}
		catch (Exception &E) {
			ListBox->Items->Add("Error: " + E.Message);
		}
		catch (...) {
			ListBox->Items->Add("Error");
		}
	}
	__finally {
		ListBox->Items->EndUpdate();

		btnOpen->Enabled = true;

		RestoreCursor();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject * Sender, WORD & Key,
	TShiftState Shift) {
	if (Key == VK_F1) {
		ShowAbout(24);
	}
}
// ---------------------------------------------------------------------------
