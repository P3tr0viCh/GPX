// ---------------------------------------------------------------------------

#ifndef GPXMainH
#define GPXMainH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published:
	TPanel *PanelTop;
	TButton *btnClose;
	TStatusBar *StatusBar;
	TListBox *ListBox;
	TButton *btnOpen;
	TOpenDialog *OpenDialog;
	TPanel *PanelBottom;
	TGroupBox *gbDistance;
	TLabeledEdit *eHaversine;
	TLabeledEdit *eEquirectangular;
	TLabeledEdit *eSphericalLawOfCosines;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnOpenClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:
	void SetTrackName(String TrackName);

	void OpenGPXFile(String FileName);

public:
	__fastcall TMain(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
