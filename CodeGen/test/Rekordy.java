package JsonTest;
import java.util.ArrayList;
public class Rekordy {
  private ArrayList _table;
  public Rekordy() {
    this._table = new ArrayList();
  }
  public int Size() {
    return this._table.size();
  }
  public void Insert(Rekord _v) {
    this._table.add(_v);
  }
  public Rekord Get(int _ix) {
    return (Rekord) this._table.get(_ix);
  }
  public void Delete(int _ix) {
    this._table.remove(_ix);
  }
  public String toJSON() {
    String _s = "[";
    for (int i=0;i<this._table.size();i++)
    if (i<this._table.size()-1)
        _s+=""+this.Get(i).toJSON()+",";
      else
        _s+=""+this.Get(i).toJSON()+"";
    _s+="]";
    return _s;
  }
  public static Rekordy fromJSON(String s) {
    Rekordy arr = new Rekordy();
    int ix=0;
    while(ix < s.length() && s.charAt(ix)!='[')
      ix++;
    ix++;
    if (ix >=s.length()) 
      throw new RuntimeException("Rekordy::fromJSON");
    while(ix<s.length()) {
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
          String tmp = s.substring(start, ix);
          arr.Insert(Rekord.fromJSON(tmp));
          ix++;
          break;
        }
        ix++;
      }
    }
    return arr;
  }
};

