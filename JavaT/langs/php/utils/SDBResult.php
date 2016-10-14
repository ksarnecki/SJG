<?php
  class SDBResult {
    var $res;

    function SDBResult($res) {
      $this->res = $res;
    }

    function Field($row, $col) {
      //debug_print_backtrace();
      return mysql_result($this->res, $row, $col);
    }

    function Cols() {
      if ($this->res===null)
        return 0;
      return mysql_num_fields($this->res);
    }

    function Rows() {
      if ($this->res===null)
        return 0;
      return mysql_num_rows($this->res);
    }
  };
?>