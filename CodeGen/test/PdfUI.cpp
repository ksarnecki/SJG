
#include "PdfUI.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- PdfSize ---------------
PdfSize::PdfSize(const AnsiString& _width, const AnsiString& _height) : width(_width), height(_height) {
}
const AnsiString& PdfSize::getWidth() const {
  return width;
}
AnsiString& PdfSize::getWidth() {
  return width;
}
const AnsiString& PdfSize::getHeight() const {
  return height;
}
AnsiString& PdfSize::getHeight() {
  return height;
}
AnsiString PdfSize::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"width\":";
    _json += "\"" + JSONEscape::encode(width) + "\"";
    _json += ",";
    _json += "\"height\":";
    _json += "\"" + JSONEscape::encode(height) + "\"";
  _json += "}";
  return _json.get();
}
PdfSize PdfSize::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfSize::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<2) {
          if (ix-start-1<=0)
            throw Exception("PdfSize::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfSize((arr[0].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))));
}
PdfSize::~PdfSize() {
}
//----------------------------------

//------------- PdfPos ---------------
PdfPos::PdfPos(const AnsiString& _x, const AnsiString& _y) : x(_x), y(_y) {
}
const AnsiString& PdfPos::getX() const {
  return x;
}
AnsiString& PdfPos::getX() {
  return x;
}
const AnsiString& PdfPos::getY() const {
  return y;
}
AnsiString& PdfPos::getY() {
  return y;
}
AnsiString PdfPos::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"x\":";
    _json += "\"" + JSONEscape::encode(x) + "\"";
    _json += ",";
    _json += "\"y\":";
    _json += "\"" + JSONEscape::encode(y) + "\"";
  _json += "}";
  return _json.get();
}
PdfPos PdfPos::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfPos::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<2) {
          if (ix-start-1<=0)
            throw Exception("PdfPos::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfPos((arr[0].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))));
}
PdfPos::~PdfPos() {
}
//----------------------------------

//------------- PdfFontWeight ---------------
const int PdfFontWeight::_TypeNormal = 0;
const int PdfFontWeight::_TypeBold = 1;
void PdfFontWeight::init(int type, void* ptr) {
  if (type==_TypeNormal) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeBold) {
    _type = type;
    _ptr = 0;
  }
}
void PdfFontWeight::clean() {
  if (_type==_TypeNormal) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("PdfFontWeight::clean()");
  } else if (_type==_TypeBold) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("PdfFontWeight::clean()");
  }
}
PdfFontWeight::PdfFontWeight() : _type(-1), _ptr(0) {
}
PdfFontWeight::PdfFontWeight(const PdfFontWeight& _value) {
  init(_value._type, _value._ptr);
}
PdfFontWeight& PdfFontWeight::operator=(const PdfFontWeight& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool PdfFontWeight::isNormal() const {
  return _type==_TypeNormal;
}
bool PdfFontWeight::isBold() const {
  return _type==_TypeBold;
}

AnsiString PdfFontWeight::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
      _json += "0";
    else if (_type==1)
      _json += "0";
    else
      throw Exception("PdfFontWeight::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
PdfFontWeight PdfFontWeight::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("PdfFontWeight::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return PdfFontWeight::createNormal();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    return PdfFontWeight::createBold();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("PdfFontWeight::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("normal")) {
    return PdfFontWeight::createNormal();
  } else if (variantName==("bold")) {
    return PdfFontWeight::createBold();
  } else 
    throw Exception("PdfFontWeight::fromJSON");
}

PdfFontWeight::~PdfFontWeight() {
  clean();
}
PdfFontWeight PdfFontWeight::createNormal() {
  PdfFontWeight _value;
  _value._type = _TypeNormal;
  _value._ptr = 0;
  return _value;
}
PdfFontWeight PdfFontWeight::createBold() {
  PdfFontWeight _value;
  _value._type = _TypeBold;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- PdfFont ---------------
PdfFont::PdfFont(const AnsiString& _fontFamily, const AnsiString& _fontSize, const PdfFontWeight& _fontWeight, const AnsiString& _color) : fontFamily(_fontFamily), fontSize(_fontSize), fontWeight(_fontWeight), color(_color) {
}
const AnsiString& PdfFont::getFontFamily() const {
  return fontFamily;
}
AnsiString& PdfFont::getFontFamily() {
  return fontFamily;
}
const AnsiString& PdfFont::getFontSize() const {
  return fontSize;
}
AnsiString& PdfFont::getFontSize() {
  return fontSize;
}
const PdfFontWeight& PdfFont::getFontWeight() const {
  return fontWeight;
}
PdfFontWeight& PdfFont::getFontWeight() {
  return fontWeight;
}
const AnsiString& PdfFont::getColor() const {
  return color;
}
AnsiString& PdfFont::getColor() {
  return color;
}
AnsiString PdfFont::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"fontFamily\":";
    _json += "\"" + JSONEscape::encode(fontFamily) + "\"";
    _json += ",";
    _json += "\"fontSize\":";
    _json += "\"" + JSONEscape::encode(fontSize) + "\"";
    _json += ",";
    _json += "\"fontWeight\":";
    _json += fontWeight.toJSON();
    _json += ",";
    _json += "\"color\":";
    _json += "\"" + JSONEscape::encode(color) + "\"";
  _json += "}";
  return _json.get();
}
PdfFont PdfFont::fromJSON(AnsiString s) {
  AnsiString arr[4];
  int ix=1;
  for (int i=0;i<4;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfFont::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<4) {
          if (ix-start-1<=0)
            throw Exception("PdfFont::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfFont((arr[0].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), PdfFontWeight::fromJSON(arr[2]), (arr[3].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[3].SubString(2, arr[3].Length()-2))));
}
PdfFont::~PdfFont() {
}
//----------------------------------

//------------- PdfText ---------------
PdfText::PdfText(const PdfPos& _pos, const AnsiString& _value, const PdfFont& _font) : pos(_pos), value(_value), font(_font) {
}
const PdfPos& PdfText::getPos() const {
  return pos;
}
PdfPos& PdfText::getPos() {
  return pos;
}
const AnsiString& PdfText::getValue() const {
  return value;
}
AnsiString& PdfText::getValue() {
  return value;
}
const PdfFont& PdfText::getFont() const {
  return font;
}
PdfFont& PdfText::getFont() {
  return font;
}
AnsiString PdfText::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"pos\":";
    _json += pos.toJSON();
    _json += ",";
    _json += "\"value\":";
    _json += "\"" + JSONEscape::encode(value) + "\"";
    _json += ",";
    _json += "\"font\":";
    _json += font.toJSON();
  _json += "}";
  return _json.get();
}
PdfText PdfText::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfText::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("PdfText::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfText(PdfPos::fromJSON(arr[0]), (arr[1].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), PdfFont::fromJSON(arr[2]));
}
PdfText::~PdfText() {
}
//----------------------------------

//------------- PdfRectText ---------------
PdfRectText::PdfRectText(const PdfPos& _pos, const PdfSize& _size, const AnsiString& _value, const PdfFont& _font) : pos(_pos), size(_size), value(_value), font(_font) {
}
const PdfPos& PdfRectText::getPos() const {
  return pos;
}
PdfPos& PdfRectText::getPos() {
  return pos;
}
const PdfSize& PdfRectText::getSize() const {
  return size;
}
PdfSize& PdfRectText::getSize() {
  return size;
}
const AnsiString& PdfRectText::getValue() const {
  return value;
}
AnsiString& PdfRectText::getValue() {
  return value;
}
const PdfFont& PdfRectText::getFont() const {
  return font;
}
PdfFont& PdfRectText::getFont() {
  return font;
}
AnsiString PdfRectText::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"pos\":";
    _json += pos.toJSON();
    _json += ",";
    _json += "\"size\":";
    _json += size.toJSON();
    _json += ",";
    _json += "\"value\":";
    _json += "\"" + JSONEscape::encode(value) + "\"";
    _json += ",";
    _json += "\"font\":";
    _json += font.toJSON();
  _json += "}";
  return _json.get();
}
PdfRectText PdfRectText::fromJSON(AnsiString s) {
  AnsiString arr[4];
  int ix=1;
  for (int i=0;i<4;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfRectText::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<4) {
          if (ix-start-1<=0)
            throw Exception("PdfRectText::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfRectText(PdfPos::fromJSON(arr[0]), PdfSize::fromJSON(arr[1]), (arr[2].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))), PdfFont::fromJSON(arr[3]));
}
PdfRectText::~PdfRectText() {
}
//----------------------------------

//------------- PdfLineStyle ---------------
const int PdfLineStyle::_TypeSolid = 0;
const int PdfLineStyle::_TypeDash = 1;
void PdfLineStyle::init(int type, void* ptr) {
  if (type==_TypeSolid) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDash) {
    _type = type;
    _ptr = 0;
  }
}
void PdfLineStyle::clean() {
  if (_type==_TypeSolid) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("PdfLineStyle::clean()");
  } else if (_type==_TypeDash) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("PdfLineStyle::clean()");
  }
}
PdfLineStyle::PdfLineStyle() : _type(-1), _ptr(0) {
}
PdfLineStyle::PdfLineStyle(const PdfLineStyle& _value) {
  init(_value._type, _value._ptr);
}
PdfLineStyle& PdfLineStyle::operator=(const PdfLineStyle& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool PdfLineStyle::isSolid() const {
  return _type==_TypeSolid;
}
bool PdfLineStyle::isDash() const {
  return _type==_TypeDash;
}

AnsiString PdfLineStyle::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
      _json += "0";
    else if (_type==1)
      _json += "0";
    else
      throw Exception("PdfLineStyle::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
PdfLineStyle PdfLineStyle::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("PdfLineStyle::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return PdfLineStyle::createSolid();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    return PdfLineStyle::createDash();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("PdfLineStyle::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("solid")) {
    return PdfLineStyle::createSolid();
  } else if (variantName==("dash")) {
    return PdfLineStyle::createDash();
  } else 
    throw Exception("PdfLineStyle::fromJSON");
}

PdfLineStyle::~PdfLineStyle() {
  clean();
}
PdfLineStyle PdfLineStyle::createSolid() {
  PdfLineStyle _value;
  _value._type = _TypeSolid;
  _value._ptr = 0;
  return _value;
}
PdfLineStyle PdfLineStyle::createDash() {
  PdfLineStyle _value;
  _value._type = _TypeDash;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- PdfLine ---------------
PdfLine::PdfLine(const PdfPos& _pos1, const PdfPos& _pos2, const AnsiString& _width, const AnsiString& _color, const PdfLineStyle& _style) : pos1(_pos1), pos2(_pos2), width(_width), color(_color), style(_style) {
}
const PdfPos& PdfLine::getPos1() const {
  return pos1;
}
PdfPos& PdfLine::getPos1() {
  return pos1;
}
const PdfPos& PdfLine::getPos2() const {
  return pos2;
}
PdfPos& PdfLine::getPos2() {
  return pos2;
}
const AnsiString& PdfLine::getWidth() const {
  return width;
}
AnsiString& PdfLine::getWidth() {
  return width;
}
const AnsiString& PdfLine::getColor() const {
  return color;
}
AnsiString& PdfLine::getColor() {
  return color;
}
const PdfLineStyle& PdfLine::getStyle() const {
  return style;
}
PdfLineStyle& PdfLine::getStyle() {
  return style;
}
AnsiString PdfLine::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"pos1\":";
    _json += pos1.toJSON();
    _json += ",";
    _json += "\"pos2\":";
    _json += pos2.toJSON();
    _json += ",";
    _json += "\"width\":";
    _json += "\"" + JSONEscape::encode(width) + "\"";
    _json += ",";
    _json += "\"color\":";
    _json += "\"" + JSONEscape::encode(color) + "\"";
    _json += ",";
    _json += "\"style\":";
    _json += style.toJSON();
  _json += "}";
  return _json.get();
}
PdfLine PdfLine::fromJSON(AnsiString s) {
  AnsiString arr[5];
  int ix=1;
  for (int i=0;i<5;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfLine::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<5) {
          if (ix-start-1<=0)
            throw Exception("PdfLine::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfLine(PdfPos::fromJSON(arr[0]), PdfPos::fromJSON(arr[1]), (arr[2].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))), (arr[3].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[3].SubString(2, arr[3].Length()-2))), PdfLineStyle::fromJSON(arr[4]));
}
PdfLine::~PdfLine() {
}
//----------------------------------

//------------- PdfRect ---------------
PdfRect::PdfRect(const PdfPos& _pos, const PdfSize& _size, const AnsiString& _color) : pos(_pos), size(_size), color(_color) {
}
const PdfPos& PdfRect::getPos() const {
  return pos;
}
PdfPos& PdfRect::getPos() {
  return pos;
}
const PdfSize& PdfRect::getSize() const {
  return size;
}
PdfSize& PdfRect::getSize() {
  return size;
}
const AnsiString& PdfRect::getColor() const {
  return color;
}
AnsiString& PdfRect::getColor() {
  return color;
}
AnsiString PdfRect::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"pos\":";
    _json += pos.toJSON();
    _json += ",";
    _json += "\"size\":";
    _json += size.toJSON();
    _json += ",";
    _json += "\"color\":";
    _json += "\"" + JSONEscape::encode(color) + "\"";
  _json += "}";
  return _json.get();
}
PdfRect PdfRect::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfRect::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("PdfRect::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfRect(PdfPos::fromJSON(arr[0]), PdfSize::fromJSON(arr[1]), (arr[2].Length()-2<=0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))));
}
PdfRect::~PdfRect() {
}
//----------------------------------

//------------- PdfElem ---------------
const int PdfElem::_TypeText = 0;
const int PdfElem::_TypeRectText = 1;
const int PdfElem::_TypeLine = 2;
const int PdfElem::_TypeRect = 3;
void PdfElem::init(int type, void* ptr) {
  if (type==_TypeText) {
    _type = type;
    _ptr = new PdfText(*(PdfText*) ptr);
  } else if (type==_TypeRectText) {
    _type = type;
    _ptr = new PdfRectText(*(PdfRectText*) ptr);
  } else if (type==_TypeLine) {
    _type = type;
    _ptr = new PdfLine(*(PdfLine*) ptr);
  } else if (type==_TypeRect) {
    _type = type;
    _ptr = new PdfRect(*(PdfRect*) ptr);
  }
}
void PdfElem::clean() {
  if (_type==_TypeText) {
    _type = -1;
    delete (PdfText*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeRectText) {
    _type = -1;
    delete (PdfRectText*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeLine) {
    _type = -1;
    delete (PdfLine*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeRect) {
    _type = -1;
    delete (PdfRect*) _ptr;
    _ptr = 0;
  }
}
PdfElem::PdfElem() : _type(-1), _ptr(0) {
}
PdfElem::PdfElem(const PdfElem& _value) {
  init(_value._type, _value._ptr);
}
PdfElem& PdfElem::operator=(const PdfElem& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool PdfElem::isText() const {
  return _type==_TypeText;
}
bool PdfElem::isRectText() const {
  return _type==_TypeRectText;
}
bool PdfElem::isLine() const {
  return _type==_TypeLine;
}
bool PdfElem::isRect() const {
  return _type==_TypeRect;
}
const PdfText& PdfElem::asText() const {
  if (_type!=_TypeText)
    throw Exception("PdfElem::asText");
  return *(PdfText*) _ptr;
}
PdfText& PdfElem::asText() {
  if (_type!=_TypeText)
    throw Exception("PdfElem::asText");
  return *(PdfText*) _ptr;
}
const PdfRectText& PdfElem::asRectText() const {
  if (_type!=_TypeRectText)
    throw Exception("PdfElem::asRectText");
  return *(PdfRectText*) _ptr;
}
PdfRectText& PdfElem::asRectText() {
  if (_type!=_TypeRectText)
    throw Exception("PdfElem::asRectText");
  return *(PdfRectText*) _ptr;
}
const PdfLine& PdfElem::asLine() const {
  if (_type!=_TypeLine)
    throw Exception("PdfElem::asLine");
  return *(PdfLine*) _ptr;
}
PdfLine& PdfElem::asLine() {
  if (_type!=_TypeLine)
    throw Exception("PdfElem::asLine");
  return *(PdfLine*) _ptr;
}
const PdfRect& PdfElem::asRect() const {
  if (_type!=_TypeRect)
    throw Exception("PdfElem::asRect");
  return *(PdfRect*) _ptr;
}
PdfRect& PdfElem::asRect() {
  if (_type!=_TypeRect)
    throw Exception("PdfElem::asRect");
  return *(PdfRect*) _ptr;
}

AnsiString PdfElem::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((PdfText*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((PdfRectText*) _ptr)->toJSON();
    else if (_type==2)
    _json += ((PdfLine*) _ptr)->toJSON();
    else if (_type==3)
    _json += ((PdfRect*) _ptr)->toJSON();
    else
      throw Exception("PdfElem::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
PdfElem PdfElem::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("PdfElem::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return PdfElem::createText(PdfText::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return PdfElem::createRectText(PdfRectText::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return PdfElem::createLine(PdfLine::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return PdfElem::createRect(PdfRect::fromJSON(s));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("PdfElem::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("text")) {
    if (s.Length()-ix-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return PdfElem::createText(PdfText::fromJSON(s));
  } else if (variantName==("rectText")) {
    if (s.Length()-ix-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return PdfElem::createRectText(PdfRectText::fromJSON(s));
  } else if (variantName==("line")) {
    if (s.Length()-ix-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return PdfElem::createLine(PdfLine::fromJSON(s));
  } else if (variantName==("rect")) {
    if (s.Length()-ix-1<=0)
      throw Exception("PdfElem::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return PdfElem::createRect(PdfRect::fromJSON(s));
  } else 
    throw Exception("PdfElem::fromJSON");
}

PdfElem::~PdfElem() {
  clean();
}
PdfElem PdfElem::createText(const PdfText& _param) {
  PdfElem _value;
  _value._type = _TypeText;
  _value._ptr = new PdfText(_param);
  return _value;
}
PdfElem PdfElem::createRectText(const PdfRectText& _param) {
  PdfElem _value;
  _value._type = _TypeRectText;
  _value._ptr = new PdfRectText(_param);
  return _value;
}
PdfElem PdfElem::createLine(const PdfLine& _param) {
  PdfElem _value;
  _value._type = _TypeLine;
  _value._ptr = new PdfLine(_param);
  return _value;
}
PdfElem PdfElem::createRect(const PdfRect& _param) {
  PdfElem _value;
  _value._type = _TypeRect;
  _value._ptr = new PdfRect(_param);
  return _value;
}


//----------------------------------

//------------- PdfElems ---------------
PdfElems::PdfElems() {
}
AnsiString PdfElems::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
PdfElems PdfElems::fromJSON(AnsiString s) {
  PdfElems arr = PdfElems();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("PdfElems::fromJSON");
  while (ix<=s.Length()) {
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {
        if (start==ix)
          return arr;
        if (ix-start<=0)
          throw Exception("PdfElems::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(PdfElem::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
PdfElems::~PdfElems() {
}
//----------------------------------

//------------- PdfPage ---------------
PdfPage::PdfPage(const PdfSize& _size, const PdfElems& _elems) : size(_size), elems(_elems) {
}
const PdfSize& PdfPage::getSize() const {
  return size;
}
PdfSize& PdfPage::getSize() {
  return size;
}
const PdfElems& PdfPage::getElems() const {
  return elems;
}
PdfElems& PdfPage::getElems() {
  return elems;
}
AnsiString PdfPage::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"size\":";
    _json += size.toJSON();
    _json += ",";
    _json += "\"elems\":";
    _json += elems.toJSON();
  _json += "}";
  return _json.get();
}
PdfPage PdfPage::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PdfPage::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<2) {
          if (ix-start-1<=0)
            throw Exception("PdfPage::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PdfPage(PdfSize::fromJSON(arr[0]), PdfElems::fromJSON(arr[1]));
}
PdfPage::~PdfPage() {
}
//----------------------------------

//------------- PdfObj ---------------
PdfObj::PdfObj() {
}
AnsiString PdfObj::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
PdfObj PdfObj::fromJSON(AnsiString s) {
  PdfObj arr = PdfObj();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("PdfObj::fromJSON");
  while (ix<=s.Length()) {
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {
        if (start==ix)
          return arr;
        if (ix-start<=0)
          throw Exception("PdfObj::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(PdfPage::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
PdfObj::~PdfObj() {
}
//----------------------------------

