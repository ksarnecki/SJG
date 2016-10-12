package JsonTest;
public class Wariant {
  private int _type;
  private Object _ptrObj;

  private static final int _TypeInty = 0;
  private static final int _TypeStry = 1;

  private Wariant() {}
  public boolean isInty() {
    return this._type==Wariant._TypeInty;
  }
  public boolean isStry() {
    return this._type==Wariant._TypeStry;
  }

  public IntArray asInty() {
    if (this._type!=Wariant._TypeInty)
      throw new RuntimeException("Wariant::asInty");
    return (IntArray) this._ptrObj;
  }
  public StringArray asStry() {
    if (this._type!=Wariant._TypeStry)
      throw new RuntimeException("Wariant::asStry");
    return (StringArray) this._ptrObj;
  }

  static public Wariant createInty(IntArray _v) {
    Wariant _value = new Wariant();
    _value._type = Wariant._TypeInty;
    _value._ptrObj = _v;
    return _value;
  }
  static public Wariant createStry(StringArray _v) {
    Wariant _value = new Wariant();
    _value._type = Wariant._TypeStry;
    _value._ptrObj = _v;
    return _value;
  }
  public String toJSON() {
    String _s = "{";
    if (0==1) {
      ;
    } else if (this._type==Wariant._TypeInty) {
      _s+="\"inty\":"+((IntArray) this._ptrObj).toJSON();
    } else if (this._type==Wariant._TypeStry) {
      _s+="\"stry\":"+((StringArray) this._ptrObj).toJSON();
    } else
      throw new RuntimeException("Wariant::toJSON()");
    _s = _s+"}";
    return _s;
  }
  public static Wariant fromJSON(String s) {
    String variantName = "";
    int ix = 0;
    while(ix < s.length() && s.charAt(ix) != ':')
      ix++;
    if (ix >=s.length()) 
      throw new RuntimeException("Wariant::fromJSON");
    variantName = s.substring(2, ix-1);
     if (variantName.equals("inty")) {
      s = s.substring(ix+1, s.length()-1);
      return Wariant.createInty(IntArray.fromJSON(s));
    } else if (variantName.equals("stry")) {
      s = s.substring(ix+1, s.length()-1);
      return Wariant.createStry(StringArray.fromJSON(s));
    } else 
      throw new RuntimeException("Wariant::fromJSON");
  }
};

