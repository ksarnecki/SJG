package JsonTest;
public class Rekord {
  private Wariant pierwszy;
  private int drugi;
  private String trzeci;
  private IntArray czwarty;
  public Rekord( Wariant _pierwszy,  int _drugi,  String _trzeci,  IntArray _czwarty) {
    this.pierwszy = _pierwszy;
    this.drugi = _drugi;
    this.trzeci = _trzeci;
    this.czwarty = _czwarty;
  }
  public Wariant getPierwszy() {
    return this.pierwszy;
  }
  public void setPierwszy(Wariant _v) {
    this.pierwszy = _v;
  }
  public int getDrugi() {
    return this.drugi;
  }
  public void setDrugi(int _v) {
    this.drugi = _v;
  }
  public String getTrzeci() {
    return this.trzeci;
  }
  public void setTrzeci(String _v) {
    this.trzeci = _v;
  }
  public IntArray getCzwarty() {
    return this.czwarty;
  }
  public void setCzwarty(IntArray _v) {
    this.czwarty = _v;
  }
  public String toJSON() {
    String _s = "{";
    _s+="\"pierwszy\":"+this.pierwszy.toJSON()+",";
    _s+="\"drugi\":"+this.drugi+",";
    _s+="\"trzeci\":"+"\"" + JSONUtil.escape(this.trzeci) + "\""+",";
    _s+="\"czwarty\":"+this.czwarty.toJSON()+"}";
    return _s;
  }
  public static Rekord fromJSON(String s) {
    Object[] arr = new Object[4];
    int ix=0;
    for(int i=0;i<4;i++) {
      while(ix < s.length() &&  s.charAt(ix) != ':')
        ix++;
      ix+=1;
      if (ix >=s.length()) 
        throw new RuntimeException("Rekord::fromJSON");
      int start = ix;
      boolean inString = false;
      int bracketLevel = 0;
      while(ix<s.length()) {
        if (s.charAt(ix) == '\\')
          ix+=2;
        else if (s.charAt(ix) == '"')
          inString = !inString;
        else if (!inString && s.charAt(ix) == '[')
          bracketLevel++;
        else if (!inString && s.charAt(ix) == '{')
          bracketLevel++;
        else if (!inString && s.charAt(ix) == ']')
          bracketLevel--;
        else if (!inString && s.charAt(ix) == '}')
          bracketLevel--;
        if (bracketLevel <= 0 && !inString && (s.charAt(ix) == ',' || ix == s.length()-1)) {
          if (i == 0) {
            String tmp = s.substring(start, ix);
            arr[i] = Wariant.fromJSON(tmp);
          }
          if (i == 1) {
            String tmp = s.substring(start, ix);
            arr[i] = Integer.parseInt(tmp);
          }
          if (i == 2) {
            String tmp = s.substring(start, ix);
            arr[i] = JSONUtil.unescape(tmp.substring(1, tmp.length()-1));
          }
          if (i == 3) {
            String tmp = s.substring(start, ix);
            arr[i] = IntArray.fromJSON(tmp);
          }
          ix++;
          break;
        }
        ix++;
      }
    }
    return new Rekord((Wariant)arr[0], (int)arr[1], (String)arr[2], (IntArray)arr[3]);
  }
};

