package AppData;
public class JSONUtil {
  public static String escape(String string) {
    if (string == null || string.length() == 0)
      return "";
    char c = 0;
    int i = 0;
    int len = string.length();
    String sb = "";
    String t;
    for (i = 0; i < len; i+=1) {;
      c = string.charAt(i);
      switch (c) {
        case '\\':
        case '"':
          sb+=('\\');
          sb+=(c);
          break;
        case '/':
          sb+=('\\');
          sb+=(c);
          break;
        case '\b':
          sb+=("\\b");
          break;
        case '\t':
          sb+=("\\t");
          break;
        case '\n':
          sb+=("\\n");
          break;
        case '\f':
          sb+=("\\f");
          break;
        case '\r':
          sb+=("\\r");
        default:
          if (c < ' ') {
            t = "000"+Integer.toHexString(c);
            sb+="\\u"+t.substring(string.length() - 4);
          } else {
            sb+=(c);
        }
      }
    }
    return sb;
  }
  public static String unescape(String string) {
    char c = 0;
    int i = 0;
    int len = string.length();
    boolean escaped = false;
    String sb = "";
    String t;
    for (i = 0; i < len; i+=1) {
      c = string.charAt(i);
      if (escaped) {
        switch (c) {
          case '\\':
            sb+="\\";
            break;
          case '\"':
            sb+="\"";
            break;
          case '/':
            sb+="/";
            break;
          case 'b':
            sb+=("\b");
            break;
          case 't':
            sb+=("\t");
            break;
          case 'n':
            sb+=("\n");
            break;
          case 'f':
            sb+=("\f");
            break;
          case 'r':
            sb+=("\r");
          case 'u':
            //TODO IN CODEGEN
            break;
        }
        escaped = false;
      } else {
        if (c == '\\') 
          escaped = true;
        else
          sb+=c;
      }
    }
    return sb;
  }
}

