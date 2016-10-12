package AppData;
public class Event {
  private int id;
  private String type;
  private int session;
  public Event( int _id,  String _type,  int _session) {
    this.id = _id;
    this.type = _type;
    this.session = _session;
  }
  public int getId() {
    return this.id;
  }
  public void setId(int _v) {
    this.id = _v;
  }
  public String getType() {
    return this.type;
  }
  public void setType(String _v) {
    this.type = _v;
  }
  public int getSession() {
    return this.session;
  }
  public void setSession(int _v) {
    this.session = _v;
  }
  public String toJSON() {
    String _s = "{";
    _s+="\"id\":"+this.id+",";
    _s+="\"type\":"+"\"" + JSONUtil.escape(this.type) + "\""+",";
    _s+="\"session\":"+this.session+"}";
    return _s;
  }
  public static Event fromJSON(String s) {
    Object[] arr = new Object[3];
    int ix=0;
    for(int i=0;i<3;i++) {
      while(ix < s.length() &&  s.charAt(ix) != ':')
        ix++;
      ix+=1;
      if (ix >=s.length()) 
        throw new RuntimeException("Event::fromJSON");
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
            arr[i] = Integer.parseInt(tmp);
          }
          if (i == 1) {
            String tmp = s.substring(start, ix);
            arr[i] = JSONUtil.unescape(tmp.substring(1, tmp.length()-1));
          }
          if (i == 2) {
            String tmp = s.substring(start, ix);
            arr[i] = Integer.parseInt(tmp);
          }
          ix++;
          break;
        }
        ix++;
      }
    }
    return new Event((int)arr[0], (String)arr[1], (int)arr[2]);
  }
};

