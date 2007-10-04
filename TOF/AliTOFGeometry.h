#ifndef ALITOFGEOMETRY_H
#define ALITOFGEOMETRY_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  TOF geometry class                                                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "TGeoMatrix.h"
#include "TObject.h"

class AliTOFGeometry: public TObject{

 public:
  AliTOFGeometry();
  virtual ~AliTOFGeometry();

  static  Int_t NStripA()     { return kNStripA;};
  static  Int_t NStripB()     { return kNStripB;};
  static  Int_t NStripC()     { return kNStripC;};
  static  Int_t NMaxNstrip()  { return kMaxNstrip;};
  static  Int_t NpadX()       { return kNpadX;};
  static  Int_t NpadZ()       { return kNpadZ;};
  static  Int_t NpadXStrip()  { return kNpadX*kNpadZ;};
  static  Int_t NSectors()    { return kNSectors;};
  static  Int_t NPlates()     { return kNPlates;};
  static Int_t NStripXSector() { return (kNStripA + 2*kNStripB +
						2*kNStripC);};
  static Int_t NPadXSector() { return (kNStripA + 2*kNStripB +
					2*kNStripC)*kNpadX*kNpadZ;};

  static Float_t RinTOF()  { return fgkxTOF;};
  static Float_t Rmin()      { return fgkRmin;};
  static Float_t Rmax()      { return fgkRmax;};

  static  Float_t XPad()     { return fgkXPad;};
  static  Float_t ZPad()     { return fgkZPad;};

  static  Float_t StripLength() { return fgkStripLength;};

  static  Int_t TimeDiff()    { return fgkTimeDiff;};
  static  Int_t MaxTOFTree()  { return kMaxTOFTree;};

  static  Int_t NDDL()        { return kNDDL;};
  static  Int_t NTRM()        { return kNTRM;}
  static  Int_t NTdc()        { return kNTdc;};
  static  Int_t NChain()      { return kNChain;};
  static  Int_t NCh()         { return kNCh;};
  static  Int_t NPadXTRM()    { return kNCh*kNTdc*kNChain;};

  static  Float_t ZlenA()       { return fgkZlenA;};
  static  Float_t ZlenB()       { return fgkZlenB;};
  static  Float_t ZlenC()       { return fgkZlenC;};
  static  Float_t MaxhZtof()    { return fgkMaxhZtof;};

  static  Float_t SigmaForTail1() { return fgkSigmaForTail1;};
  static  Float_t SigmaForTail2() { return fgkSigmaForTail2;};
 
  static  Double_t GetAlpha()  { return 2 * 3.14159265358979323846 / kNSectors; }; 
 
  static Float_t TdcBinWidth() {return fgkTdcBin;};
  static Float_t ToTBinWidth() {return fgkToTBin;};

  virtual void    ImportGeometry();
  virtual void    SetHoles(Bool_t holes) {fHoles = holes;};
  virtual Bool_t  GetHoles() const {return fHoles;};
  virtual Float_t DistanceToPadPar(Int_t *det, Float_t *pos, Float_t *dist3d=0) const;
  virtual Bool_t  IsInsideThePadPar(Int_t *det, Float_t *pos) const;
  virtual Bool_t  IsInsideThePad(TGeoHMatrix mat, Float_t *pos, Float_t *dist3d=0) const;
  virtual void    GetVolumePath(Int_t *ind, Char_t *path );
  virtual void    GetVolumePath(Int_t sector, Char_t *path );
  virtual void    GetVolumePath(Int_t sector, Int_t plate, Int_t strip, Char_t *path );
  virtual void    GetPos(Int_t *det,Float_t *pos);
  virtual void    GetPosPar(Int_t *det,Float_t *pos) const;
  virtual void    GetDetID(Float_t *pos,Int_t *det) const;
  virtual Int_t   GetPlate(Float_t *pos) const;
  virtual Int_t   GetStrip(Float_t *pos) const;
  virtual Int_t   GetSector(Float_t *pos) const;
  virtual Int_t   GetPadX(Float_t *pos) const;
  virtual Int_t   GetPadZ(Float_t *pos) const;
  virtual Float_t GetX(Int_t *det) const ;
  virtual Float_t GetY(Int_t *det) const ;
  virtual Float_t GetZ(Int_t *det) const ;
  virtual void    DetToStripRF(Int_t nPadX, Int_t nPadZ,
			       Float_t &x,  Float_t &z) const;
  virtual void    DetToSectorRF(Int_t vol[5], Double_t ** coord);
  virtual Float_t GetPadDx(Float_t *pos);
  virtual Float_t GetPadDy(Float_t *pos);
  virtual Float_t GetPadDz(Float_t *pos);
  virtual void Translation(Float_t *xyz, Float_t translationVector[3]) const;
  virtual void Rotation(Float_t *xyz, Double_t rotationAngles[6]) const;
  virtual void InverseRotation(Float_t *xyz, Double_t rotationAngles[6]) const;

  static Float_t GetAngles(Int_t iplate, Int_t istrip)  {return fgkAngles[iplate][istrip];};
  static Float_t GetHeights(Int_t iplate, Int_t istrip)  {return fgkHeights[iplate][istrip];};
  static Float_t GetDistances(Int_t iplate, Int_t istrip)  {return fgkDistances[iplate][istrip];};

  static Int_t GetIndex(Int_t *detId); // Get channel index from det Id (for calibration mainly)

  private:

  enum {
    kNStripA    = 15, // number of strips in A type module 
    kNStripB    = 19, // number of strips in B type module 
    kNStripC    = 19, // number of strips in C type module 
    kNpadX      = 48, // Number of pads along X 
    kNpadZ      = 2,  // Number of pads along Z
    kNSectors   = 18, // Number of Sectors
    kNPlates    = 5,  // Number of Plates
    kMaxTOFTree = 5,  // numer of geom. levels: 
    kMaxNstrip  = 20  // Max. number of strips
  };

  // DAQ characteristics
  // cfr. TOF-TDR pag. 105 for Glossary
  // TARODA : TOF-ALICE Read Out and Data Acquisition system
  enum {
    kNDDL        =    4, // Number of DDL (Detector Data Link) per sector
    kNTRM        =   12, // Number of TRM ( Readout Module) per DDL
    kNTdc        =   15, // Number of Tdc (Time to Digital Converter) per TRM
    kNChain      =    2, // Number of chains per TRM
    kNCh         =    8  // Number of channels per Tdc
  };

  static const Int_t fgkTimeDiff;      // Min signal separation (ps)

  static const Float_t fgkZlenA;       // length (cm) of the A module
  static const Float_t fgkZlenB;       // length (cm) of the B module
  static const Float_t fgkZlenC;       // length (cm) of the C module
  static const Float_t fgkMaxhZtof;    // Max half z-size of TOF (cm)

  static const Float_t fgkRmin;        // Inner radius of the TOF (cm)
  static const Float_t fgkRmax;        // Outer radius of the TOF (cm)
  static const Float_t fgkxTOF;        // Inner TOF Radius used in Reconstruction (cm)

  static const Float_t fgkStripLength; // Strip Length (rho X phi direction) (cm)

  static const Float_t fgkXPad;     // Pad size in the x direction (cm)
  static const Float_t fgkZPad;     // Pad size in the z direction (cm)

  static const Float_t fgkSigmaForTail1;//Sig1 for simulation of TDC tails 
  static const Float_t fgkSigmaForTail2;//Sig2 for simulation of TDC tails

  static const Float_t fgkPhiSec; //sector Phi width (deg)

  Bool_t fHoles; //logical for geometry version (w/wo holes)

  static const Float_t fgkAngles[kNPlates][kMaxNstrip];   //Strip Tilt Angles
  static const Float_t fgkHeights[kNPlates][kMaxNstrip];  //Strip heights
  static const Float_t fgkDistances[kNPlates][kMaxNstrip];//Strip distances


  static const Float_t fgkTdcBin;   // time-of-flight bin width [ps]
  static const Float_t fgkToTBin;   // time-over-threshold bin width [ps]

  ClassDef(AliTOFGeometry,5) // TOF Geometry base class
};

#endif
