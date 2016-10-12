#ifndef _PDFUI_GEN_H_
#define _PDFUI_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- PdfSize ---------------
class PdfSize {
  AnsiString width;
  AnsiString height;
public:
  PdfSize(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getWidth() const;
  virtual const AnsiString& getHeight() const;
  virtual AnsiString& getWidth();
  virtual AnsiString& getHeight();

  virtual AnsiString toJSON() const;
  static PdfSize fromJSON(AnsiString);

  virtual ~PdfSize();

};
//----------------------------------

//------------- PdfPos ---------------
class PdfPos {
  AnsiString x;
  AnsiString y;
public:
  PdfPos(const AnsiString&, const AnsiString&);
  virtual const AnsiString& getX() const;
  virtual const AnsiString& getY() const;
  virtual AnsiString& getX();
  virtual AnsiString& getY();

  virtual AnsiString toJSON() const;
  static PdfPos fromJSON(AnsiString);

  virtual ~PdfPos();

};
//----------------------------------

//------------- PdfFontWeight ---------------
class PdfFontWeight {
  int _type;
  void* _ptr;

  static const int _TypeNormal;
  static const int _TypeBold;

  virtual void init(int, void*);
  virtual void clean();
  PdfFontWeight();
public:
  PdfFontWeight(const PdfFontWeight&);
  virtual PdfFontWeight& operator=(const PdfFontWeight&);

  virtual bool isNormal() const;
  virtual bool isBold() const;


  virtual AnsiString toJSON() const;
  static PdfFontWeight fromJSON(AnsiString);

  virtual ~PdfFontWeight();

  static PdfFontWeight createNormal();
  static PdfFontWeight createBold();

};
//----------------------------------

//------------- PdfFont ---------------
class PdfFont {
  AnsiString fontFamily;
  AnsiString fontSize;
  PdfFontWeight fontWeight;
  AnsiString color;
public:
  PdfFont(const AnsiString&, const AnsiString&, const PdfFontWeight&, const AnsiString&);
  virtual const AnsiString& getFontFamily() const;
  virtual const AnsiString& getFontSize() const;
  virtual const PdfFontWeight& getFontWeight() const;
  virtual const AnsiString& getColor() const;
  virtual AnsiString& getFontFamily();
  virtual AnsiString& getFontSize();
  virtual PdfFontWeight& getFontWeight();
  virtual AnsiString& getColor();

  virtual AnsiString toJSON() const;
  static PdfFont fromJSON(AnsiString);

  virtual ~PdfFont();

};
//----------------------------------

//------------- PdfText ---------------
class PdfText {
  PdfPos pos;
  AnsiString value;
  PdfFont font;
public:
  PdfText(const PdfPos&, const AnsiString&, const PdfFont&);
  virtual const PdfPos& getPos() const;
  virtual const AnsiString& getValue() const;
  virtual const PdfFont& getFont() const;
  virtual PdfPos& getPos();
  virtual AnsiString& getValue();
  virtual PdfFont& getFont();

  virtual AnsiString toJSON() const;
  static PdfText fromJSON(AnsiString);

  virtual ~PdfText();

};
//----------------------------------

//------------- PdfRectText ---------------
class PdfRectText {
  PdfPos pos;
  PdfSize size;
  AnsiString value;
  PdfFont font;
public:
  PdfRectText(const PdfPos&, const PdfSize&, const AnsiString&, const PdfFont&);
  virtual const PdfPos& getPos() const;
  virtual const PdfSize& getSize() const;
  virtual const AnsiString& getValue() const;
  virtual const PdfFont& getFont() const;
  virtual PdfPos& getPos();
  virtual PdfSize& getSize();
  virtual AnsiString& getValue();
  virtual PdfFont& getFont();

  virtual AnsiString toJSON() const;
  static PdfRectText fromJSON(AnsiString);

  virtual ~PdfRectText();

};
//----------------------------------

//------------- PdfLineStyle ---------------
class PdfLineStyle {
  int _type;
  void* _ptr;

  static const int _TypeSolid;
  static const int _TypeDash;

  virtual void init(int, void*);
  virtual void clean();
  PdfLineStyle();
public:
  PdfLineStyle(const PdfLineStyle&);
  virtual PdfLineStyle& operator=(const PdfLineStyle&);

  virtual bool isSolid() const;
  virtual bool isDash() const;


  virtual AnsiString toJSON() const;
  static PdfLineStyle fromJSON(AnsiString);

  virtual ~PdfLineStyle();

  static PdfLineStyle createSolid();
  static PdfLineStyle createDash();

};
//----------------------------------

//------------- PdfLine ---------------
class PdfLine {
  PdfPos pos1;
  PdfPos pos2;
  AnsiString width;
  AnsiString color;
  PdfLineStyle style;
public:
  PdfLine(const PdfPos&, const PdfPos&, const AnsiString&, const AnsiString&, const PdfLineStyle&);
  virtual const PdfPos& getPos1() const;
  virtual const PdfPos& getPos2() const;
  virtual const AnsiString& getWidth() const;
  virtual const AnsiString& getColor() const;
  virtual const PdfLineStyle& getStyle() const;
  virtual PdfPos& getPos1();
  virtual PdfPos& getPos2();
  virtual AnsiString& getWidth();
  virtual AnsiString& getColor();
  virtual PdfLineStyle& getStyle();

  virtual AnsiString toJSON() const;
  static PdfLine fromJSON(AnsiString);

  virtual ~PdfLine();

};
//----------------------------------

//------------- PdfRect ---------------
class PdfRect {
  PdfPos pos;
  PdfSize size;
  AnsiString color;
public:
  PdfRect(const PdfPos&, const PdfSize&, const AnsiString&);
  virtual const PdfPos& getPos() const;
  virtual const PdfSize& getSize() const;
  virtual const AnsiString& getColor() const;
  virtual PdfPos& getPos();
  virtual PdfSize& getSize();
  virtual AnsiString& getColor();

  virtual AnsiString toJSON() const;
  static PdfRect fromJSON(AnsiString);

  virtual ~PdfRect();

};
//----------------------------------

//------------- PdfElem ---------------
class PdfElem {
  int _type;
  void* _ptr;

  static const int _TypeText;
  static const int _TypeRectText;
  static const int _TypeLine;
  static const int _TypeRect;

  virtual void init(int, void*);
  virtual void clean();
  PdfElem();
public:
  PdfElem(const PdfElem&);
  virtual PdfElem& operator=(const PdfElem&);

  virtual bool isText() const;
  virtual bool isRectText() const;
  virtual bool isLine() const;
  virtual bool isRect() const;

  virtual const PdfText& asText() const;
  virtual PdfText& asText();
  virtual const PdfRectText& asRectText() const;
  virtual PdfRectText& asRectText();
  virtual const PdfLine& asLine() const;
  virtual PdfLine& asLine();
  virtual const PdfRect& asRect() const;
  virtual PdfRect& asRect();

  virtual AnsiString toJSON() const;
  static PdfElem fromJSON(AnsiString);

  virtual ~PdfElem();

  static PdfElem createText(const PdfText&);
  static PdfElem createRectText(const PdfRectText&);
  static PdfElem createLine(const PdfLine&);
  static PdfElem createRect(const PdfRect&);

};
//----------------------------------

//------------- PdfElems ---------------
#include "DynSet.h"


class PdfElems : public DynSet<PdfElem> {
public:
  PdfElems();

  virtual AnsiString toJSON() const;
  static PdfElems fromJSON(AnsiString);

  virtual ~PdfElems();

};
//----------------------------------

//------------- PdfPage ---------------
class PdfPage {
  PdfSize size;
  PdfElems elems;
public:
  PdfPage(const PdfSize&, const PdfElems&);
  virtual const PdfSize& getSize() const;
  virtual const PdfElems& getElems() const;
  virtual PdfSize& getSize();
  virtual PdfElems& getElems();

  virtual AnsiString toJSON() const;
  static PdfPage fromJSON(AnsiString);

  virtual ~PdfPage();

};
//----------------------------------

//------------- PdfObj ---------------
#include "DynSet.h"


class PdfObj : public DynSet<PdfPage> {
public:
  PdfObj();

  virtual AnsiString toJSON() const;
  static PdfObj fromJSON(AnsiString);

  virtual ~PdfObj();

};
//----------------------------------

#endif
