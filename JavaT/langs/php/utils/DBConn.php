<?php

  include 'SDBResult.php';

  class DBConn {
    var $host;
    var $user;
    var $pass;
    var $dbname;
    var $db;

    function doConnect($host, $user, $pass, $dbname) {
      $this->db = mysql_connect($this->host, $this->user, $this->pass);
      mysql_select_db($this->dbname); //dodalem ",$this->db"
      mysql_set_charset('utf8', $this->db);
    }

    function DBConn($host, $user, $pass, $dbname) {
      $this->host = $host;
      $this->user = $user;
      $this->pass = $pass;
      $this->dbname = $dbname;
      $this->doConnect($host, $user, $pass, $dbname);
    }

    function Execute($query) {
      echo $query;
      $this->Query($query);
    }

    function Query($query) {
      //echo "QUERY: ".$query.'<br>';
      $x = mysql_query($query, $this->db);
      echo mysql_error($this->db);
      if ($x===FALSE) {
        //Err::log("QUERY:[".$query."]" . mysql_error($this->db));
        $this->doConnect($this->host, $this->user, $this->pass, $this->dbname);
        $x = mysql_query($query, $this->db);

        if ($x===FALSE) {
          //Err::log("QUERY#2:[".$query."]" . mysql_error($this->db));
          return new SDBResult(null);
        }
        return new SDBResult($x);
      }
      return new SDBResult($x);
    }

    function Single($query) {
      $res = $this->Query($query);
      return $res->Field(0, 0);
    }

    function Escape($str) {
      return mysql_escape_string($str);
    }

    function Close() {
      mysql_close($this->db);
    }
  };
?>
